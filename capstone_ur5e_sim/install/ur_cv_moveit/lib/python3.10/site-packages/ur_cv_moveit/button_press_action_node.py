#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
from typing import Optional
import threading

import numpy as np
import rclpy
import time
from rclpy.duration import Duration
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.action import ActionServer, ActionClient, GoalResponse, CancelResponse
from rclpy.callback_groups import ReentrantCallbackGroup, MutuallyExclusiveCallbackGroup

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

        self.depth_topic = "/wrist_camera/depth/image_raw"
        self.camera_info_topic = "/wrist_camera/camera_info"
        self.base_frame = "base_link"
        self.camera_frame = "wrist_camera_optical_frame"

        self.approach_offset = 0.12
        self.press_offset = 0.01
        self.default_depth = 0.45
        self.ik_timeout_sec = 0.3
        self.controller_ns = "/joint_trajectory_controller"

        self.home_positions = [0.0, -2.0, 1.7, -2.7, -1.57, 0.0]

        self.bridge = CvBridge()
        self.latest_depth: Optional[np.ndarray] = None
        self.latest_info: Optional[CameraInfo] = None
        self.latest_joint_state: Optional[JointState] = None
        self.busy = False
        self.busy_lock = threading.Lock()

        self.ur_joints = [
            "shoulder_pan_joint",
            "shoulder_lift_joint",
            "elbow_joint",
            "wrist_1_joint",
            "wrist_2_joint",
            "wrist_3_joint",
        ]

        # Separate callback groups: clients use reentrant, server uses mutually-exclusive
        # This prevents client-side blocking from interfering with the server's
        # internal publishers (status/feedback) and avoids waitset index issues.
        self.client_cb_group = ReentrantCallbackGroup()
        self.server_cb_group = MutuallyExclusiveCallbackGroup()

        # TF
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)

        # Sub
        self.create_subscription(Image, self.depth_topic, self._on_depth, 10)
        self.create_subscription(CameraInfo, self.camera_info_topic, self._on_info, 10)
        self.create_subscription(JointState, "/joint_states", self._on_joint_state, 10)

        # Clients (with reentrant callback group)
        self.detect_cli = self.create_client(
            DetectButton,
            "/detect_button",
            callback_group=self.client_cb_group,
        )
        self.ik_cli = self.create_client(
            GetPositionIK,
            "/compute_ik",
            callback_group=self.client_cb_group,
        )

        # Joint trajectory ActionClient with same callback group
        self.traj_action = ActionClient(
            self,
            FollowJointTrajectory,
            f"{self.controller_ns}/follow_joint_trajectory",
            callback_group=self.client_cb_group,
        )
        
        # Wait for action server
        self.get_logger().info("Waiting for trajectory action server...")
        if not self.traj_action.wait_for_server(timeout_sec=10.0):
            self.get_logger().error("Trajectory action server not available!")
        else:
            self.get_logger().info("Trajectory action server connected")

        # PressButton ActionServer uses its own callback group to keep server
        # publishers (status/feedback) responsive even if client calls block.
        self.action_server = ActionServer(
            self,
            PressButton,
            "/press_button",
            execute_callback=self._execute_action,
            goal_callback=self._goal_cb,
            cancel_callback=self._cancel_cb,
            callback_group=self.server_cb_group,
        )

        self.get_logger().info("✅ PressButton Action Server READY")

    # --- Required Callbacks ----------------------------------------------------

    def _goal_cb(self, _):
        return GoalResponse.ACCEPT

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

    # --- Action Execute --------------------------------------------------------

    def _execute_action(self, goal_handle):
        button = goal_handle.request.button

        with self.busy_lock:
            if self.busy:
                goal_handle.abort()
                return PressButton.Result(success=False, message="busy")
            self.busy = True

        try:
            goal_handle.publish_feedback(PressButton.Feedback(status="detecting"))
            ok = self._press_button_pipeline(button, goal_handle)

            if ok:
                goal_handle.succeed()
                return PressButton.Result(success=True, message="pressed")
            else:
                goal_handle.abort()
                return PressButton.Result(success=False, message="failed")
        finally:
            with self.busy_lock:
                self.busy = False

    # --- Button Pipeline -------------------------------------------------------

    def _press_button_pipeline(self, button, goal_handle) -> bool:
        # Wait longer for the detection service to be available (YOLO may take
        # time to load/warm-up on first call).
        if not self.detect_cli.wait_for_service(timeout_sec=10.0):
            self.get_logger().error("DetectButton service not available")
            return False

        req = DetectButton.Request()
        req.label = button
                
        # Call service asynchronously and wait using spin_once loop so we don't
        # block the action server's internal publishers (avoid rclpy.spin_until_future_complete).
        future = self.detect_cli.call_async(req)

        # Wait up to 10 seconds for detection result using non-blocking sleep loop
        # (increase to accommodate model warm-up / slower inference)
        timeout_s = 10.0
        start = time.monotonic()
        while not future.done():
            if (time.monotonic() - start) > timeout_s:
                self.get_logger().error("DetectButton service call timeout")
                return False
            time.sleep(0.05)

        try:
            res = future.result()
        except Exception as e:
            self.get_logger().error(f"DetectButton call raised: {e}")
            return False
        if not res or not res.success:
            self.get_logger().error(f"Detection failed for button '{button}'")
            return False

        self.get_logger().info(f"Button '{button}' detected at ({res.u}, {res.v})")
        
        goal_handle.publish_feedback(PressButton.Feedback(status="moving"))
        ok = self._press(res.u, res.v)
        if not ok:
            self.get_logger().error("Press motion failed")
            return False

        goal_handle.publish_feedback(PressButton.Feedback(status="returning home"))
        ok = bool(self._send_traj(self.home_positions, 2.5))
        if not ok:
            self.get_logger().error("Return to home failed")
        return ok

    # --- Math / IK / Traj -----------------------------------------------------

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
        except TransformException as e:
            self.get_logger().warn(f"TF lookup failed: {e}")
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

    def _fixed_orientation(self, pose):
        q = Rotation.from_euler("xyz", [0, math.radians(90), 0]).as_quat()
        pose.pose.orientation.x, pose.pose.orientation.y, pose.pose.orientation.z, pose.pose.orientation.w = q
        return pose

    def _offset_pose(self, pose, offset):
        rot = Rotation.from_quat([
            pose.pose.orientation.x,
            pose.pose.orientation.y,
            pose.pose.orientation.z,
            pose.pose.orientation.w,
        ])
        dx, dy, dz = rot.apply([1, 0, 0])
        new = PoseStamped()
        new.header = pose.header
        new.pose = pose.pose
        new.pose.position.x += dx * offset
        new.pose.position.y += dy * offset
        new.pose.position.z += dz * offset
        return new

    def _solve_ik(self, pose):
        if self.latest_joint_state is None:
            self.get_logger().error("No joint state available for IK")
            return None
        if not self.ik_cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().error("IK service not available")
            return None

        req = GetPositionIK.Request()
        req.ik_request.group_name = "ur_manipulator"
        req.ik_request.pose_stamped = pose
        req.ik_request.ik_link_name = "tool0"
        req.ik_request.timeout = Duration(seconds=self.ik_timeout_sec).to_msg()
        req.ik_request.robot_state.joint_state = self.latest_joint_state

        fut = self.ik_cli.call_async(req)
        
        # Wait for IK result using non-blocking sleep loop
        timeout_s = 2.0
        start = time.monotonic()
        while not fut.done():
            if (time.monotonic() - start) > timeout_s:
                self.get_logger().error("IK service call timeout")
                return None
            time.sleep(0.05)
        
        res = fut.result()
        if not res or res.error_code.val != 1:
            self.get_logger().error(f"IK failed with error code: {res.error_code.val if res else 'None'}")
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

        try:
            fut = self.traj_action.send_goal_async(goal)
            
            # Wait for send_goal to complete using non-blocking sleep loop
            timeout_s = 5.0
            start = time.monotonic()
            while not fut.done():
                if (time.monotonic() - start) > timeout_s:
                    self.get_logger().error("Send goal timeout")
                    return False
                time.sleep(0.05)
                
            h = fut.result()
            if not h or not h.accepted:
                self.get_logger().error("Goal rejected by action server")
                return False

            res_fut = h.get_result_async()
            
            # Wait for goal result using non-blocking sleep loop
            timeout_s = float(duration) + 5.0
            start = time.monotonic()
            while not res_fut.done():
                if (time.monotonic() - start) > timeout_s:
                    self.get_logger().error("Get result timeout")
                    return False
                time.sleep(0.05)
                
            return True
            
        except Exception as e:
            self.get_logger().error(f"Trajectory execution error: {e}")
            return False

    def _press(self, u, v):
        xyz = self._uv_to_xyz(u, v)
        self.get_logger().info(f"Target XYZ in camera frame: {xyz}")
        
        pose = self._fixed_orientation(self._cam_to_base(xyz))
        self.get_logger().info(f"Target pose in base frame: ({pose.pose.position.x:.3f}, {pose.pose.position.y:.3f}, {pose.pose.position.z:.3f})")

        approach = self._offset_pose(pose, +self.approach_offset)
        press = self._offset_pose(pose, -self.press_offset)

        for idx, (target, name) in enumerate([(approach, "approach"), (press, "press"), (approach, "retract")]):
            self.get_logger().info(f"Step {idx+1}/3: {name}")
            js = self._solve_ik(target)
            if js is None:
                self.get_logger().error(f"IK failed for {name}")
                return False
            if not self._send_traj(js.position, 1.5):
                self.get_logger().error(f"Trajectory failed for {name}")
                return False

        self.get_logger().info("Press sequence completed successfully")
        return True


def main():
    rclpy.init()
    node = ButtonPressActionNode()
    executor = MultiThreadedExecutor(num_threads=4)
    executor.add_node(node)
    
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()