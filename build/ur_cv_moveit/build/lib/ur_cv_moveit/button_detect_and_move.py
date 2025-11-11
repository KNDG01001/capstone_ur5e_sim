#!/usr/bin/env python3
import math
import time
import numpy as np
from dataclasses import dataclass
from typing import Optional, Tuple, List

import rclpy
from rclpy.node import Node
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.action import ActionClient
from action_msgs.msg import GoalStatus
from std_msgs.msg import String
from sensor_msgs.msg import Image, CameraInfo, JointState
from geometry_msgs.msg import PoseStamped, PointStamped, Quaternion, Header
from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint
from moveit_msgs.srv import GetPositionIK
from cv_bridge import CvBridge
import cv2

try:
    from moveit_commander import MoveGroupCommander, RobotCommander
    HAVE_MOVEIT = True
except:
    HAVE_MOVEIT = False

try:
    from ultralytics import YOLO
    HAVE_YOLO = True
except:
    HAVE_YOLO = False


@dataclass
class DetectedButton:
    label: str
    pixel: Tuple[int, int]
    confidence: float


class ButtonDetectAndPress(Node):
    def __init__(self):
        super().__init__("button_press_action_node")

        self.declare_parameter("rgb_topic", "/wrist_camera/image_raw")
        self.declare_parameter("depth_topic", "/wrist_camera/depth/image_raw")
        self.declare_parameter("camera_info_topic", "/wrist_camera/camera_info")
        self.declare_parameter("end_effector_link", "tool0")
        self.declare_parameter("base_frame", "base_link")
        self.declare_parameter("approach_offset", 0.07)
        self.declare_parameter("button_request_topic", "/button_request")
        self.declare_parameter("yolo_weights", "")

        self.rgb_topic = self.get_parameter("rgb_topic").value
        self.depth_topic = self.get_parameter("depth_topic").value
        self.camera_info_topic = self.get_parameter("camera_info_topic").value
        self.ee_link = self.get_parameter("end_effector_link").value
        self.base_frame = self.get_parameter("base_frame").value
        self.approach_offset = self.get_parameter("approach_offset").value
        self.button_request_topic = self.get_parameter("button_request_topic").value
        self.yolo_weights = self.get_parameter("yolo_weights").value

        self.bridge = CvBridge()
        self.latest_rgb = None
        self.latest_depth = None
        self.K = None
        self.last_joint_state = None

        self.pending_label: Optional[str] = None
        self.processing = False

        self.cb_group = ReentrantCallbackGroup()

        self.create_subscription(String, self.button_request_topic, self.on_button_request, 10)
        self.create_subscription(Image, self.rgb_topic, self.on_rgb, 10)
        self.create_subscription(Image, self.depth_topic, self.on_depth, 10)
        self.create_subscription(CameraInfo, self.camera_info_topic, self.on_camera_info, 10)
        self.create_subscription(JointState, "/joint_states", self.on_joint_state, 10)

        self.timer = self.create_timer(0.3, self.process, callback_group=self.cb_group)

        if HAVE_MOVEIT:
            self.robot = RobotCommander()
            self.group = MoveGroupCommander("ur_manipulator")
            self.group.set_end_effector_link(self.ee_link)
            self.group.set_max_velocity_scaling_factor(0.2)
            self.group.set_max_acceleration_scaling_factor(0.2)

        if HAVE_YOLO and self.yolo_weights:
            self.detector = YOLO(self.yolo_weights)
        else:
            self.detector = None

        self.ftj = ActionClient(self, FollowJointTrajectory, "/joint_trajectory_controller/follow_joint_trajectory")


    def on_button_request(self, msg: String):
        self.pending_label = msg.data.strip()
        self.processing = False
        self.get_logger().info(f"[REQ] 버튼 요청 수신: {self.pending_label}")


    def on_rgb(self, msg):
        self.latest_rgb = self.bridge.imgmsg_to_cv2(msg, "bgr8")


    def on_depth(self, msg):
        self.latest_depth = self.bridge.imgmsg_to_cv2(msg, "32FC1")


    def on_camera_info(self, msg):
        self.K = np.array(msg.k).reshape(3, 3)


    def on_joint_state(self, msg):
        self.last_joint_state = msg


    def detect_button(self, img):
        if self.detector:
            results = self.detector(img, verbose=False)[0]
            if len(results.boxes) == 0:
                return None
            b = results.boxes.xyxy[0]
            cx = int((b[0] + b[2]) / 2)
            cy = int((b[1] + b[3]) / 2)
            return (cx, cy)
        return None


    def process(self):
        if not self.pending_label:
            return
        if self.processing:
            return

        # 첫 로그 반드시 출력
        self.get_logger().info(f"[RUN] 탐지 및 동작 시작. target={self.pending_label}")
        self.processing = True

        if not all([self.latest_rgb, self.latest_depth, self.K, self.last_joint_state]):
            self.processing = False
            return

        px = self.detect_button(self.latest_rgb)
        if not px:
            self.processing = False
            self.get_logger().info("[INFO] 버튼 미감지")
            return

        u, v = px
        depth = float(self.latest_depth[v, u])
        if depth <= 0.05:
            self.processing = False
            return

        fx, fy = self.K[0, 0], self.K[1, 1]
        cx, cy = self.K[0, 2], self.K[1, 2]
        X = (u - cx) * depth / fx
        Y = (v - cy) * depth / fy
        Z = depth

        pose = PoseStamped()
        pose.header.frame_id = self.base_frame
        pose.pose.position.x = float(X)
        pose.pose.position.y = float(Y)
        pose.pose.position.z = float(Z - self.approach_offset)  # pre-approach
        pose.pose.orientation = Quaternion(w=1.0)

        self.group.set_start_state_to_current_state()
        self.group.set_pose_target(pose)
        ok, plan = self.group.plan()

        if ok:
            self.group.execute(plan, wait=True)

        # push
        pose.pose.position.z = float(Z - 0.01)
        self.group.set_pose_target(pose)
        ok, plan = self.group.plan()
        if ok:
            self.group.execute(plan, wait=True)

        # ✅ 홈 포즈 복귀 (스폰 초기자세는 자동이므로 여기서만)
        self.group.set_named_target("home")
        self.group.go(wait=True)

        self.get_logger().info("[DONE] 완료. 홈 복귀.")
        self.pending_label = None
        self.processing = False


def main():
    rclpy.init()
    node = ButtonDetectAndPress()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()


if __name__ == "__main__":
    main()
