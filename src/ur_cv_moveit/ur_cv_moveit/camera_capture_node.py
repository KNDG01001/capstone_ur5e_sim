#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from rclpy.qos import qos_profile_sensor_data

class CameraCaptureNode(Node):
    def __init__(self):
        super().__init__('camera_capture_node')

        self.declare_parameter('rgb_topic', '/wrist_camera/image_raw')
        self.declare_parameter('depth_topic', '/wrist_camera/depth/image_raw')
        self.declare_parameter('camera_info_topic', '/wrist_camera/camera_info')

        # 기본적으로 Gazebo 카메라에서 들어오는 토픽을 그대로 구독
        self.create_subscription(Image, self.get_parameter('rgb_topic').value,
                                 self.on_rgb, qos_profile_sensor_data)
        self.create_subscription(Image, self.get_parameter('depth_topic').value,
                                 self.on_depth, qos_profile_sensor_data)
        self.create_subscription(CameraInfo, self.get_parameter('camera_info_topic').value,
                                 self.on_info, qos_profile_sensor_data)
        self.rgb_count = 0

    def on_rgb(self, msg):
        self.rgb_count += 1
        if self.rgb_count % 30 == 0:
            self.get_logger().warn("Frame captured")

    def on_depth(self, msg):
        pass

    def on_info(self, msg):
        pass


def main():
    rclpy.init()
    node = CameraCaptureNode()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
