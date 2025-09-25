#!/usr/bin/env python3
import math
import time
from typing import Optional, Tuple, List, Any

import rclpy
from rclpy.node import Node
from rclpy.duration import Duration
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.parameter import Parameter
from rcl_interfaces.msg import ParameterDescriptor
from action_msgs.msg import GoalStatus

from sensor_msgs.msg import Image, CameraInfo, JointState
from geometry_msgs.msg import PoseStamped, PointStamped, Quaternion
from std_msgs.msg import Header

import tf2_ros
from tf2_ros import Buffer, TransformListener
from tf2_geometry_msgs import do_transform_point

from cv_bridge import CvBridge
import cv2
import numpy as np

# Optional MoveIt Python commander (fallback to IK+FollowJointTrajectory if missing)
try:
    from moveit_commander import MoveGroupCommander, RobotCommander, PlanningSceneInterface  # type: ignore
    HAVE_MOVEIT_COMMANDER = True
except Exception:
    HAVE_MOVEIT_COMMANDER = False

from rclpy.action import ActionClient
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from moveit_msgs.srv import GetPositionIK
from builtin_interfaces.msg import Duration as RosDuration


class ButtonDetectAndMove(Node):
    def __init__(self):
        super().__init__('button_detect_and_move')
        # --- params ---
        self.declare_parameter('rgb_topic', '/wrist_camera/image_raw')
        self.declare_parameter('depth_topic', '/wrist_camera/depth/image_raw')
        self.declare_parameter('camera_info_topic', '/wrist_camera/camera_info')
        self.declare_parameter('base_frame', 'base_link')
        self.declare_parameter('camera_frame', 'wrist_camera_optical_frame')
        self.declare_parameter('end_effector_link', 'tool0')   # MoveIt/SRDF EE 링크명
        self.declare_parameter('move_group_name', '')           # 비우면 자동 탐색
        self.declare_parameter('approach_offset', 0.07)
        self.declare_parameter('plan_only', False)
        self.declare_parameter('align_with_camera', True)
        self.declare_parameter('ik_avoid_collisions', False)
        self.declare_parameter('planning_time', 3.0)
        self.declare_parameter('replan_attempts', 5)
        self.declare_parameter('vel_scale', 0.1)
        self.declare_parameter('acc_scale', 0.1)
        self.declare_parameter(
            'status_waiting_for',
            '',
            ParameterDescriptor(
                read_only=True,
                description='Diagnostic string indicating which input the node is waiting for.',
            ),
        )

        self.rgb_topic = self.get_parameter('rgb_topic').get_parameter_value().string_value
        self.depth_topic = self.get_parameter('depth_topic').get_parameter_value().string_value
        self.camera_info_topic = self.get_parameter('camera_info_topic').get_parameter_value().string_value
        self.base_frame = self.get_parameter('base_frame').get_parameter_value().string_value
        self.camera_frame = self.get_parameter('camera_frame').get_parameter_value().string_value
        self.ee_link = self.get_parameter('end_effector_link').get_parameter_value().string_value
        self.req_group_name = self.get_parameter('move_group_name').get_parameter_value().string_value
        self.approach_offset = self.get_parameter('approach_offset').get_parameter_value().double_value
        self.plan_only = self.get_parameter('plan_only').get_parameter_value().bool_value
        self.align_with_camera = self.get_parameter('align_with_camera').get_parameter_value().bool_value
        self.ik_avoid_collisions = self.get_parameter('ik_avoid_collisions').get_parameter_value().bool_value
        self.planning_time = self.get_parameter('planning_time').get_parameter_value().double_value
        self.replan_attempts = self.get_parameter('replan_attempts').get_parameter_value().integer_value
        self.vel_scale = self.get_parameter('vel_scale').get_parameter_value().double_value
        self.acc_scale = self.get_parameter('acc_scale').get_parameter_value().double_value

        # --- buffers / subs ---
        self.bridge = CvBridge()
        self.latest_rgb: Optional[np.ndarray] = None
        self.latest_depth: Optional[np.ndarray] = None
        self.K: Optional[np.ndarray] = None

        self.cb_group = ReentrantCallbackGroup()
        self.processing = False

        self.tf_buffer: Buffer = Buffer(cache_time=Duration(seconds=10.0))
        self.tf_listener = TransformListener(self.tf_buffer, self)

        self.rgb_sub = self.create_subscription(Image, self.rgb_topic, self.on_rgb, 10, callback_group=self.cb_group)
        self.depth_sub = self.create_subscription(Image, self.depth_topic, self.on_depth, 10, callback_group=self.cb_group)
        self.camera_info_sub = self.create_subscription(CameraInfo, self.camera_info_topic, self.on_camera_info, 10, callback_group=self.cb_group)
        self.joint_state_sub = self.create_subscription(JointState, '/joint_states', self.on_joint_state, 10, callback_group=self.cb_group)

        self.timer = self.create_timer(0.5, self.process, callback_group=self.cb_group)

        # --- MoveIt or fallback ---
        self.group_name = 'ur_manipulator'
        self.last_joint_state: Optional[JointState] = None
        self.waiting_reason: Optional[str] = 'startup'

        if HAVE_MOVEIT_COMMANDER:
            self.robot = RobotCommander()
            self.scene = PlanningSceneInterface()
            self.group_name = self._pick_group_name(self.req_group_name)
            if not self.group_name:
                self.group_name = 'ur_manipulator'
            self.group = MoveGroupCommander(self.group_name)
            # EE 링크 설정
            try:
                self.group.set_end_effector_link(self.ee_link)  # 일부 버전만 지원
            except Exception:
                pass
            self.group.set_max_velocity_scaling_factor(self.vel_scale)
            self.group.set_max_acceleration_scaling_factor(self.acc_scale)
            self.group.set_num_planning_attempts(max(1, int(self.replan_attempts)))
            self.group.set_planning_time(self.planning_time)
            self.get_logger().info(f"Using MoveIt group={self.group_name}, ee_link={self.group.get_end_effector_link() or self.ee_link}")
        else:
            self.get_logger().warn("moveit_commander not available. Fallback to compute_ik + FollowJointTrajectory.")
            self.group_name = self.req_group_name or 'ur_manipulator'
            self.ik_client = self.create_client(GetPositionIK, '/compute_ik', callback_group=self.cb_group)
            self.ftj_action = ActionClient(self, FollowJointTrajectory, '/joint_trajectory_controller/follow_joint_trajectory', callback_group=self.cb_group)
            if not self.ik_client.wait_for_service(timeout_sec=15.0):
                self.get_logger().warn('compute_ik service not available within timeout; will keep trying on demand.')
            self._wait_for_ftj_server()

        self.already_moved = False

    # -------- util ----------
    def _pick_group_name(self, requested: str) -> str:
        if requested:
            try:
                available = RobotCommander().get_group_names()
            except Exception:
                available = []
            if requested in available:
                return requested
            self.get_logger().warn(f"Requested move group '{requested}' not available, falling back to auto-detect.")
        try:
            names = RobotCommander().get_group_names()
        except Exception:
            names = ['ur_manipulator', 'manipulator']
        if not names:
            return 'ur_manipulator'
        preferred = ['ur_manipulator', 'manipulator']
        for target in preferred:
            if target in names:
                return target
        for n in names:
            if 'manipulator' in n:
                return n
        return names[0]

    def _quat_from_direction(self, z_axis: np.ndarray) -> Quaternion:
        z = z_axis / (np.linalg.norm(z_axis) + 1e-9)
        up = np.array([0.0, 0.0, 1.0])
        if abs(np.dot(z, up)) > 0.95:
            up = np.array([0.0, 1.0, 0.0])
        x = np.cross(up, z); x /= np.linalg.norm(x) + 1e-9
        y = np.cross(z, x)
        R = np.column_stack((x, y, z))
        trace = np.trace(R)
        if trace > 0:
            s = 0.5 / math.sqrt(trace + 1.0)
            w = 0.25 / s
            xq = (R[2, 1] - R[1, 2]) * s
            yq = (R[0, 2] - R[2, 0]) * s
            zq = (R[1, 0] - R[0, 1]) * s
        else:
            if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
                s = 2.0 * math.sqrt(max(1e-9, 1.0 + R[0, 0] - R[1, 1] - R[2, 2]))
                w = (R[2, 1] - R[1, 2]) / s; xq = 0.25 * s
                yq = (R[0, 1] + R[1, 0]) / s; zq = (R[0, 2] + R[2, 0]) / s
            elif R[1, 1] > R[2, 2]:
                s = 2.0 * math.sqrt(max(1e-9, 1.0 + R[1, 1] - R[0, 0] - R[2, 2]))
                w = (R[0, 2] - R[2, 0]) / s
                xq = (R[0, 1] + R[1, 0]) / s; yq = 0.25 * s
                zq = (R[1, 2] + R[2, 1]) / s
            else:
                s = 2.0 * math.sqrt(max(1e-9, 1.0 + R[2, 2] - R[0, 0] - R[1, 1]))
                w = (R[1, 0] - R[0, 1]) / s
                xq = (R[0, 2] + R[2, 0]) / s
                yq = (R[1, 2] + R[2, 1]) / s; zq = 0.25 * s
        q = Quaternion(); q.x, q.y, q.z, q.w = float(xq), float(yq), float(zq), float(w)
        return q

    # -------- callbacks ----------
    def on_rgb(self, msg: Image):
        try:
            self.latest_rgb = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except Exception as e:
            self.get_logger().warn(f"cv_bridge rgb error: {e}")

    def on_depth(self, msg: Image):
        try:
            self.latest_depth = self.bridge.imgmsg_to_cv2(msg, desired_encoding='32FC1')
        except Exception as e:
            self.get_logger().warn(f"cv_bridge depth error: {e}")

    def on_camera_info(self, msg: CameraInfo):
        self.K = np.array(msg.k, dtype=np.float64).reshape(3, 3)

    def on_joint_state(self, msg: JointState):
        if msg.name:
            self.last_joint_state = msg

    # -------- vision ----------
    def detect_button_pixel(self, img: np.ndarray) -> Optional[Tuple[int, int]]:
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        lower_red1 = np.array([0, 120, 80]); upper_red1 = np.array([10, 255, 255])
        lower_red2 = np.array([170, 120, 80]); upper_red2 = np.array([180, 255, 255])
        mask = cv2.bitwise_or(cv2.inRange(hsv, lower_red1, upper_red1),
                              cv2.inRange(hsv, lower_red2, upper_red2))
        mask = cv2.medianBlur(mask, 5)
        cnts, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if not cnts:
            return None
        cnt = max(cnts, key=cv2.contourArea)
        if cv2.contourArea(cnt) < 50:
            return None
        M = cv2.moments(cnt)
        if M['m00'] == 0:
            return None
        cx = int(M['m10'] / M['m00']); cy = int(M['m01'] / M['m00'])
        return cx, cy

    # -------- main loop ----------
    def process(self):
        if self.processing:
            return
        self.processing = True
        try:
            if self.already_moved:
                return
            if self.latest_rgb is None:
                self._update_waiting_reason('rgb')
                return
            if self.latest_depth is None:
                self._update_waiting_reason('depth')
                return
            if self.K is None:
                self._update_waiting_reason('camera_info')
                return
            if self.last_joint_state is None:
                self._update_waiting_reason('joint_state')
                return
            self._update_waiting_reason(None)

            px = self.detect_button_pixel(self.latest_rgb)
            if px is None:
                self.get_logger().info("Button not found in image.")
                return
            u, v = px
            depth = float(self.latest_depth[v, u])
            if not math.isfinite(depth) or depth <= 0.05:
                self.get_logger().warn("Invalid depth at detection point.")
                return

            # camera -> base transform
            fx, fy, cx, cy = self.K[0, 0], self.K[1, 1], self.K[0, 2], self.K[1, 2]
            X = (u - cx) * depth / fx; Y = (v - cy) * depth / fy; Z = depth
            pt_cam = PointStamped()
            pt_cam.header = Header(frame_id=self.camera_frame, stamp=self.get_clock().now().to_msg())
            pt_cam.point.x, pt_cam.point.y, pt_cam.point.z = float(X), float(Y), float(Z)

            try:
                tf = self.tf_buffer.lookup_transform(self.base_frame, self.camera_frame, rclpy.time.Time())
                pt_base = do_transform_point(pt_cam, tf)
            except Exception as e:
                self.get_logger().warn(f"TF transform failed: {e}")
                return

            # camera +Z direction in base
            p0_cam = PointStamped(); p0_cam.header = pt_cam.header
            p1_cam = PointStamped(); p1_cam.header = pt_cam.header; p1_cam.point.z = 1.0
            try:
                p0_base = do_transform_point(p0_cam, tf); p1_base = do_transform_point(p1_cam, tf)
                cam_dir = np.array([p1_base.point.x - p0_base.point.x,
                                    p1_base.point.y - p0_base.point.y,
                                    p1_base.point.z - p0_base.point.z])
                cam_dir_n = cam_dir / (np.linalg.norm(cam_dir) + 1e-9)
            except Exception as e:
                self.get_logger().warn(f"TF for camera dir failed: {e}")
                return

            tgt = np.array([pt_base.point.x, pt_base.point.y, pt_base.point.z])
            pre_tgt = tgt - self.approach_offset * cam_dir_n
            self.get_logger().info("Base target xyz=(%.3f, %.3f, %.3f), pre-approach xyz=(%.3f, %.3f, %.3f)"
                                   % (tgt[0], tgt[1], tgt[2], pre_tgt[0], pre_tgt[1], pre_tgt[2]))

            # ---------- MoveIt path ----------
            if HAVE_MOVEIT_COMMANDER:
                # seed를 현재 상태로 고정
                self.group.set_start_state_to_current_state()

                # 목표 pose = 위치 + 자세
                pose = PoseStamped()
                pose.header.frame_id = self.base_frame
                pose.header.stamp = self.get_clock().now().to_msg()
                pose.pose.position.x, pose.pose.position.y, pose.pose.position.z = pre_tgt.tolist()

                # 자세: 카메라 +Z를 EE Z로 정렬하거나, 현재 tool0 자세 유지
                if self.align_with_camera:
                    quat = self._quat_from_direction(cam_dir_n)
                else:
                    try:
                        base_to_tool = self.tf_buffer.lookup_transform(self.base_frame, self.ee_link, rclpy.time.Time())
                        quat = base_to_tool.transform.rotation
                    except Exception:
                        quat = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)
                pose.pose.orientation = quat

                # pose target 지정 (링크 명시)
                try:
                    self.group.set_pose_target(pose, self.ee_link)
                except TypeError:
                    # 일부 버전은 링크 인자를 받지 않음
                    self.group.set_pose_target(pose)

                # plan + execute
                plan = self.group.plan()
                success, traj = self._normalize_plan(plan)
                if not success:
                    self.get_logger().warn("No plan to pre-approach target.")
                    return
                if not self.plan_only:
                    self.group.execute(traj, wait=True)

                    # 작은 '푸시' 동작
                    push = pre_tgt + (self.approach_offset * 0.8) * cam_dir_n
                    pose.pose.position.x, pose.pose.position.y, pose.pose.position.z = push.tolist()
                    try:
                        self.group.set_pose_target(pose, self.ee_link)
                    except TypeError:
                        self.group.set_pose_target(pose)
                    plan2 = self.group.plan()
                    ok2, traj2 = self._normalize_plan(plan2)
                    if ok2:
                        self.group.execute(traj2, wait=True)

            # ---------- Fallback IK ----------
            else:
                try:
                    base_to_tool = self.tf_buffer.lookup_transform(self.base_frame, self.ee_link, rclpy.time.Time())
                    quat_default = base_to_tool.transform.rotation
                except Exception:
                    quat_default = Quaternion(x=0.0, y=0.0, z=0.0, w=1.0)

                quat_candidates = []
                if self.align_with_camera:
                    try:
                        quat_candidates.append(self._quat_from_direction(cam_dir_n))
                    except Exception as exc:  # pylint: disable=broad-except
                        self.get_logger().warn(f"Failed to compute camera-aligned orientation: {exc}")
                quat_candidates.append(quat_default)

                sol_js = None
                for idx, quat in enumerate(quat_candidates):
                    sol_js = self._solve_ik(pre_tgt, quat)
                    if sol_js is not None:
                        if idx > 0 and self.align_with_camera:
                            self.get_logger().info("IK succeeded after falling back to current tool orientation")
                        break
                if sol_js is None:
                    self.get_logger().warn("IK failed for all candidate orientations")
                    return
                traj = JointTrajectory()
                traj.joint_names = list(sol_js.name)
                pt = JointTrajectoryPoint()
                pt.positions = list(sol_js.position)
                pt.time_from_start = RosDuration(sec=3, nanosec=0)
                traj.points = [pt]

                if not self.ftj_action.server_is_ready():
                    if not self._wait_for_ftj_server(timeout_sec=15.0):
                        self.get_logger().warn("FollowJointTrajectory action server unavailable; skipping execution")
                        return

                goal = FollowJointTrajectory.Goal()
                goal.trajectory = traj
                g_fut = self.ftj_action.send_goal_async(goal)
                if not rclpy.spin_until_future_complete(self, g_fut, timeout_sec=5.0):
                    self.get_logger().warn("Timed out waiting for FollowJointTrajectory goal acknowledgement")
                    return
                gh = g_fut.result()
                if not gh or not gh.accepted:
                    self.get_logger().warn("FollowJointTrajectory goal not accepted")
                    return
                r_fut = gh.get_result_async()
                if not rclpy.spin_until_future_complete(self, r_fut, timeout_sec=15.0):
                    self.get_logger().warn("Timed out waiting for FollowJointTrajectory result")
                    return
                res = r_fut.result()
                status = res.status
                if status != GoalStatus.STATUS_SUCCEEDED:
                    self.get_logger().warn(f"FollowJointTrajectory finished with status {status}")
                    return

            self.already_moved = True
            self.get_logger().info("Motion executed towards detected button.")
        finally:
            self.processing = False

    def _update_waiting_reason(self, reason: Optional[str]):
        if reason == self.waiting_reason:
            return
        self.waiting_reason = reason
        try:
            self.set_parameters([
                Parameter('status_waiting_for', Parameter.Type.STRING, reason or ''),
            ])
        except Exception:
            pass
        if reason is None:
            self.get_logger().info("All inputs received. Starting detection/planning loop.")
        elif reason == 'rgb':
            self.get_logger().info("Waiting for RGB image on %s" % self.rgb_topic)
        elif reason == 'depth':
            self.get_logger().info("Waiting for depth image on %s" % self.depth_topic)
        elif reason == 'camera_info':
            self.get_logger().info("Waiting for camera info on %s" % self.camera_info_topic)
        elif reason == 'joint_state':
            self.get_logger().info("Waiting for /joint_states update")
        else:
            self.get_logger().info(f"Waiting for required data: {reason}")

    def _wait_for_ftj_server(self, timeout_sec: float = 30.0) -> bool:
        if not HAVE_MOVEIT_COMMANDER and hasattr(self, 'ftj_action'):
            start = time.time()
            while not self.ftj_action.wait_for_server(timeout_sec=1.0):
                if (time.time() - start) >= timeout_sec:
                    self.get_logger().warn(
                        "joint_trajectory_controller action server not ready after %.1f s" % timeout_sec
                    )
                    return False
                self.get_logger().info("Waiting for joint_trajectory_controller action server...")
            return True
        return True

    def _solve_ik(self, position: np.ndarray, quat) -> Optional[JointState]:
        target_pose = PoseStamped()
        target_pose.header = Header(frame_id=self.base_frame, stamp=self.get_clock().now().to_msg())
        target_pose.pose.position.x = float(position[0])
        target_pose.pose.position.y = float(position[1])
        target_pose.pose.position.z = float(position[2])
        target_pose.pose.orientation = quat

        req = GetPositionIK.Request()
        req.ik_request.group_name = self.group_name
        req.ik_request.ik_link_name = self.ee_link
        req.ik_request.pose_stamped = target_pose
        req.ik_request.avoid_collisions = self.ik_avoid_collisions
        if self.last_joint_state is not None:
            req.ik_request.robot_state.joint_state = self.last_joint_state

        fut = self.ik_client.call_async(req)
        rclpy.spin_until_future_complete(self, fut, timeout_sec=5.0)
        if not fut.done() or fut.result() is None:
            self.get_logger().warn("IK request timed out or returned no data")
            return None
        ik_res = fut.result()
        if ik_res.error_code.val <= 0:
            self.get_logger().warn(f"IK failed with code {ik_res.error_code.val}")
            return None
        return ik_res.solution.joint_state

    # plan() 반환형 정규화
    def _normalize_plan(self, raw_plan) -> Tuple[bool, Optional[Any]]:
        success = True; trajectory = raw_plan
        if isinstance(raw_plan, tuple):
            if len(raw_plan) >= 2:
                success = bool(raw_plan[0]); trajectory = raw_plan[1]
            else:
                success = bool(raw_plan[0]); trajectory = None
        if not success or trajectory is None:
            return False, None
        try:
            if len(trajectory.joint_trajectory.points) == 0:
                return False, None
        except Exception:
            return False, None
        return True, trajectory


def main():
    rclpy.init()
    node = ButtonDetectAndMove()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
