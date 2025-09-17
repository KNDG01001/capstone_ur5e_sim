#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np

class ObjectDetectionNode(Node):
    def __init__(self):
        super().__init__('object_detection_node')
        
        # OpenCV bridge 초기화
        self.bridge = CvBridge()
        
        # 카메라 이미지 구독
        self.subscription = self.create_subscription(
            Image,
            '/camera/image_raw',  # 실제 카메라 토픽으로 변경 필요
            self.image_callback,
            10)
        
        # 처리된 이미지를 발행할 퍼블리셔
        self.publisher = self.create_publisher(
            Image,
            '/detected_objects',
            10)
        
        self.get_logger().info('Object Detection Node has been started')

    def image_callback(self, msg):
        try:
            # ROS 이미지 메시지를 OpenCV 이미지로 변환
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
            
            # 이미지 처리 및 객체 탐지
            processed_image = self.detect_objects(cv_image)
            
            # 처리된 이미지를 ROS 메시지로 변환하여 발행
            processed_msg = self.bridge.cv2_to_imgmsg(processed_image, encoding='bgr8')
            self.publisher.publish(processed_msg)
            
        except Exception as e:
            self.get_logger().error(f'Error processing image: {str(e)}')

    def detect_objects(self, image):
        # HSV 색공간으로 변환
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        
        # 예시: 파란색 객체 탐지
        lower_blue = np.array([100, 50, 50])
        upper_blue = np.array([130, 255, 255])
        
        # 마스크 생성
        mask = cv2.inRange(hsv, lower_blue, upper_blue)
        
        # 객체 윤곽선 찾기
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        
        # 탐지된 객체 표시
        for contour in contours:
            if cv2.contourArea(contour) > 500:  # 노이즈 필터링
                x, y, w, h = cv2.boundingRect(contour)
                cv2.rectangle(image, (x, y), (x + w, y + h), (0, 255, 0), 2)
        
        return image

def main(args=None):
    rclpy.init(args=args)
    node = ObjectDetectionNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()