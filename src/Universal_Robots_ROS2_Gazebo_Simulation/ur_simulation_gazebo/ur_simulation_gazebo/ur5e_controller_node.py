#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from moveit_msgs.action import MoveGroup
from geometry_msgs.msg import PoseStamped, Point
from moveit_msgs.msg import MotionPlanRequest, WorkspaceParameters, Constraints, JointConstraint
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np
from math import pi

class UR5eControllerNode(Node):
    def __init__(self):
        super().__init__('ur5e_controller_node')
        
        # MoveIt 액션 클라이언트 생성
        self.move_group_client = ActionClient(self, MoveGroup, 'move_action')
        
        # OpenCV bridge 초기화
        self.bridge = CvBridge()
        
        # 객체 감지 결과 구독
        self.detection_sub = self.create_subscription(
            Image,
            '/detected_objects',
            self.detection_callback,
            10)
            
        self.get_logger().info('UR5e Controller Node has been started')

    def detection_callback(self, msg):
        try:
            # 이미지를 OpenCV 형식으로 변환
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            
            # 객체의 위치를 3D 공간 좌표로 변환
            object_position = self.get_object_position(cv_image)
            
            if object_position is not None:
                # 로봇 움직임 계획 및 실행
                self.plan_and_execute_motion(object_position)
                
        except Exception as e:
            self.get_logger().error(f'Error processing detection: {str(e)}')

    def get_object_position(self, image):
        # 이미지에서 객체의 중심점 찾기
        # 실제 구현에서는 depth 카메라나 stereo vision을 사용하여 3D 위치를 계산해야 함
        height, width = image.shape[:2]
        return Point(x=0.5, y=0.0, z=0.3)  # 예시 위치

    def plan_and_execute_motion(self, target_position):
        # MoveGroup 액션 목표 생성
        goal = MoveGroup.Goal()
        
        # 모션 계획 요청 설정
        motion_request = MotionPlanRequest()
        motion_request.workspace_parameters.header.frame_id = 'base_link'
        motion_request.workspace_parameters.min_corner.x = -1.0
        motion_request.workspace_parameters.min_corner.y = -1.0
        motion_request.workspace_parameters.min_corner.z = -1.0
        motion_request.workspace_parameters.max_corner.x = 1.0
        motion_request.workspace_parameters.max_corner.y = 1.0
        motion_request.workspace_parameters.max_corner.z = 1.0
        
        # 목표 포즈 설정
        target_pose = PoseStamped()
        target_pose.header.frame_id = 'base_link'
        target_pose.pose.position = target_position
        target_pose.pose.orientation.w = 1.0
        
        motion_request.goal_constraints = [Constraints()]
        motion_request.goal_constraints[0].position_constraints = []
        motion_request.goal_constraints[0].orientation_constraints = []
        
        goal.request = motion_request
        
        # 액션 전송
        self.move_group_client.wait_for_server()
        future = self.move_group_client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, future)

def main(args=None):
    rclpy.init(args=args)
    node = UR5eControllerNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()