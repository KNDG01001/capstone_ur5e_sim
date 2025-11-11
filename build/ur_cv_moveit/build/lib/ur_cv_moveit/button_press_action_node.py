#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math, time
from typing import Optional

import numpy as np
import rclpy
from rclpy.duration import Duration
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.action import ActionServer, ActionClient, GoalResponse, CancelResponse

from geometry_msgs.msg import PoseStamped
from sensor_msgs.msg import Image, CameraInfo, JointState
from trajectory_msgs.msg import JointTrajectoryPoint, JointTrajectory
from control_msgs.action import FollowJointTrajectory
from moveit_msgs.srv import GetPositionIK
from ur_cv_interfaces.srv import DetectButton
from ur_cv_interfaces.action import PressButton

from cv_bridge import CvBridge
from scipy.spatial.transform import Rotation
from tf2_ros import Buffer, TransformListener, TransformException


class ButtonPressActionNode(Node):
    def __init__(self):
        super().__init__("button_press_action_node")

        # topics / frames
        self.depth_topic = "/wrist_camera/depth/image_raw"
        self.camera_info_topic = "/wrist_camera/camera_info"
        self.base_frame = "base_link"
        self.camera_frame = "wrist_camera_optical_frame"

        # motion params
        self.approach_offset = 0.12
        self.press_offset = 0.01
        self.default_depth = 0.45
        self.ik_timeout_sec = 0.3
        self.controller_ns = "/joint_trajectory_controller"

        # home
        self.home_positions = [0.0, -2.0, 1.7, -2.7, -1.57, 0.0]

        # state
        self.bridge = CvBridge()
        self.latest_depth: Optional[np.ndarray] = None
        self.latest_info: Optional[CameraInfo] = None
        self.latest_joint_state: Optional[JointState] = None
        self.busy = False

        # joints
        self.ur_joints = [
            "shoulder_pan_joint",
            "shoulder_lift_joint",
            "elbow_joint",
            "wrist_1_joint",
            "wrist_2_joint",
            "wrist_3_joint",
        ]

        # TF
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # subscribers
        self.create_subscription(Image, self.depth_topic, self._on_depth, 10)
        self.create_subscription(CameraInfo, self.camera_info_topic, self._on_info, 10)
        self.create_subscription(JointState, "/joint_states", self._on_joint_state, 10)

        # service clients
        self.detect_cli = self.create_client(DetectButton, "/detect_button")
        self.ik_cli = self.create_client(GetPositionIK, "/compute_ik")

        # joint trajectory action client
        self.traj_action = ActionClient(
            self, FollowJointTrajectory, f"{self.controller_ns}/follow_joint_trajectory"
        )
        self.traj_action.wait_for_server()

        # PressButton action server
        self.action_server = ActionServer(
            self,
            PressButton,
            "/press_button",
            execute_callback=self._execute_action,
            goal_callback=self._goal_cb,
            cancel_callback=self._cancel_cb,
        )

        self.get_logger().info("PressButton Action Server ready")

    # ---- small utils ----------------------------------------------------------

    def _wait_future(self, fut, timeout: float):
        """spin_until_future_complete 대체. MT executor에서 안전."""
        start = time.monotonic()
        while not fut.done():
            if time.monotonic() - start > timeout:
                return None
            time.sleep(0.01)
        try:
            return fut.result()
        except Exception:
            return None

    def _feedback(self, gh, text: str):
        if getattr(gh, "is_active", None) and gh.is_active:
            gh.publish_feedback(PressButton.Feedback(status=text))

    # ---- callbacks ------------------------------------------------------------

    def _goal_cb(self, _):
        return GoalResponse.REJECT if self.busy else GoalResponse.ACCEPT

    def _cancel_cb(self, _):
        return CancelResponse.ACCEPT

    def _on_depth(self, msg):
        self.latest_depth = self.bridge.imgmsg_to_cv2(msg, "32FC1")

    def _on_info(self, msg):
        self.latest_info = msg

    def _on_joint_state(self, msg):
        js = JointState()
        for j in self.ur_joints:
            if j in msg.name:
                i = msg.name.index(j)
                js.name.append(j)
                js.position.append(msg.position[i])
        if len(js.name) == 6:
            self.latest_joint_state = js

    # ---- action execute -------------------------------------------------------

    def _execute_action(self, goal_handle):
        button = goal_handle.request.button
        ok = False

        if self.busy:
            return PressButton.Result(success=False, message="busy")

        self.busy = True
        try:
            self._feedback(goal_handle, "detecting")
            ok = self._press_button_pipeline(button, goal_handle)
        except Exception as e:
            self.get_logger().error(f"execute exception: {e}")
            ok = False
        finally:
            if getattr(goal_handle, "is_active", None) and goal_handle.is_active:
                try:
                    goal_handle.succeed() if ok else goal_handle.abort()
                except Exception as e:
                    self.get_logger().warn(f"finish call ignored: {e}")
            self.busy = False
            self.get_logger().info("Ready for next goal")

        return PressButton.Result(success=ok, message="pressed" if ok else "failed")

    # ---- pipeline -------------------------------------------------------------

    def _press_button_pipeline(self, button, goal_handle) -> bool:
        if not self.detect_cli.wait_for_service(timeout_sec=3.0):
            return False

        req = DetectButton.Request()
        req.label = button
        future = self.detect_cli.call_async(req)
        res = self._wait_future(future, timeout=3.0)
        if not res or not getattr(res, "success", False):
            return False

        # optional surface normal
        normal = None
        if hasattr(res, "normal_x") and hasattr(res, "normal_y") and hasattr(res, "normal_z"):
            n = np.array([res.normal_x, res.normal_y, res.normal_z], dtype=float)
            if np.isfinite(n).all() and np.linalg.norm(n) > 1e-6:
                normal = (float(n[0]), float(n[1]), float(n[2]))

        self._feedback(goal_handle, "moving")
        ok = self._press(res.u, res.v, normal)
        if not ok:
            return False

        self._feedback(goal_handle, "returning home")
        return bool(self._send_traj(self.home_positions, 2.5))

    # ---- geometry / IK / traj -------------------------------------------------

    def _uv_to_xyz(self, u, v):
        if self.latest_depth is None or self.latest_info is None:
            return (0.0, 0.0, self.default_depth)
        h, w = self.latest_depth.shape[:2]
        u = int(np.clip(u, 0, w - 1))
        v = int(np.clip(v, 0, h - 1))
        depth = float(self.latest_depth[v, u])
        if depth <= 0.0 or not math.isfinite(depth):
            depth = self.default_depth
        fx, fy, cx, cy = (
            self.latest_info.k[0], self.latest_info.k[4],
            self.latest_info.k[2], self.latest_info.k[5]
        )
        return ((u - cx) * depth / fx, (v - cy) * depth / fy, depth)

    def _cam_to_base(self, xyz):
        try:
            tf = self.tf_buffer.lookup_transform(
                self.base_frame, self.camera_frame, rclpy.time.Time()
            )
        except TransformException:
            pose = PoseStamped()
            pose.header.frame_id = self.base_frame
            pose.pose.position.x = self.default_depth
            pose.pose.position.y = 0.0
            pose.pose.position.z = 0.9
            return pose

        rot = Rotation.from_quat([
            tf.transform.rotation.x,
            tf.transform.rotation.y,
            tf.transform.rotation.z,
            tf.transform.rotation.w,
        ])
        tr = np.array([
            tf.transform.translation.x,
            tf.transform.translation.y,
            tf.transform.translation.z,
        ])
        xyz_b = rot.apply(np.array(xyz)) + tr
        pose = PoseStamped()
        pose.header.frame_id = self.base_frame
        pose.pose.position.x = float(xyz_b[0])
        pose.pose.position.y = float(xyz_b[1])
        pose.pose.position.z = float(xyz_b[2])
        return pose

    def _orientation_from_normal(self, normal):
        default_z = np.array([0.0, 0.0, 1.0], dtype=float)
        n = np.asarray(normal, dtype=float).reshape(-1)
        if n.shape[0] != 3 or not np.isfinite(n).all():
            return Rotation.from_quat([0, 0, 0, 1]).as_quat()
        norm = np.linalg.norm(n)
        if norm < 1e-9:
            return Rotation.from_quat([0, 0, 0, 1]).as_quat()
        n = n / norm
        dot = float(np.clip(np.dot(default_z, n), -1.0, 1.0))
        if np.isclose(dot, 1.0, atol=1e-6):
            return Rotation.from_quat([0, 0, 0, 1]).as_quat()
        if np.isclose(dot, -1.0, atol=1e-6):
            return Rotation.from_rotvec(np.array([1.0, 0.0, 0.0]) * math.pi).as_quat()
        axis = np.cross(default_z, n)
        axis_norm = np.linalg.norm(axis)
        if axis_norm < 1e-9:
            return Rotation.from_quat([0, 0, 0, 1]).as_quat()
        axis = axis / axis_norm
        angle = math.acos(dot)
        return Rotation.from_rotvec(axis * angle).as_quat()

    def _fixed_orientation(self, pose, normal: Optional[tuple] = None):
        q = Rotation.from_euler("xyz", [0, math.radians(90), 0]).as_quat()
        pose.pose.orientation.x, pose.pose.orientation.y, pose.pose.orientation.z, pose.pose.orientation.w = q
        return pose

    def _offset_pose(self, pose: PoseStamped, offset: float, ee_axis: str = "x"):
        rot = Rotation.from_quat([
            pose.pose.orientation.x,
            pose.pose.orientation.y,
            pose.pose.orientation.z,
            pose.pose.orientation.w,
        ])
        dx, dy, dz = rot.apply([1, 0, 0])  # EE x-axis
        new = PoseStamped()
        new.header = pose.header
        new.pose = pose.pose
        new.pose.position.x += dx * offset
        new.pose.position.y += dy * offset
        new.pose.position.z += dz * offset
        return new

    def _solve_ik(self, pose):
        if self.latest_joint_state is None:
            return None
        if not self.ik_cli.wait_for_service(timeout_sec=1.0):
            return None

        req = GetPositionIK.Request()
        req.ik_request.group_name = "ur_manipulator"
        req.ik_request.pose_stamped = pose
        req.ik_request.ik_link_name = "tool0"
        req.ik_request.timeout = Duration(seconds=self.ik_timeout_sec).to_msg()
        req.ik_request.robot_state.joint_state = self.latest_joint_state

        fut = self.ik_cli.call_async(req)
        res = self._wait_future(fut, timeout=2.0)
        if not res or res.error_code.val != 1:
            return None
        return res.solution.joint_state

    def _send_traj(self, positions, duration):
        traj = JointTrajectory()
        traj.joint_names = self.ur_joints

        pt = JointTrajectoryPoint()
        pt.positions = list(positions[:6])
        pt.time_from_start = Duration(seconds=duration).to_msg()
        traj.points.append(pt)

        goal = FollowJointTrajectory.Goal()
        goal.trajectory = traj

        f_goal = self.traj_action.send_goal_async(goal)
        handle = self._wait_future(f_goal, timeout=3.0)
        if not handle or not handle.accepted:
            return False

        f_res = handle.get_result_async()
        res = self._wait_future(f_res, timeout=duration + 8.0)
        return bool(res)

    def _press(self, u, v, normal: Optional[tuple] = None):
        # 1) 픽셀 -> 카메라좌표 -> base 좌표
        xyz = self._uv_to_xyz(u, v)
        pose_in_base = self._cam_to_base(xyz)

        # 2) 자세 결정
        if normal is not None:
            pose = self._fixed_orientation(pose_in_base, normal)
            approach = self._offset_pose(pose, +self.approach_offset, ee_axis="z")
            press = self._offset_pose(pose, -self.press_offset, ee_axis="z")
        else:
            pose = self._fixed_orientation(pose_in_base)
            approach = self._offset_pose(pose, +self.approach_offset, ee_axis="x")
            press = self._offset_pose(pose, -self.press_offset, ee_axis="x")

        # 3) 접근 → 가압 → 이탈
        for target in [approach, press, approach]:
            js = self._solve_ik(target)
            if js is None:
                return False
            if not self._send_traj(js.position, 1.5):
                return False

        return True


def main():
    rclpy.init()
    node = ButtonPressActionNode()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
