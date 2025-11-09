#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node
from cv_bridge import CvBridge
from sensor_msgs.msg import Image
from ur_cv_interfaces.srv import DetectButton
from ultralytics import YOLO
import cv2
import numpy as np


class ButtonDetectionNode(Node):
    def __init__(self):
        super().__init__("button_detection_node")

        self.declare_parameter("model_path", "/home/sunbi/ros/best.pt")
        self.declare_parameter("imgsz", 640)
        self.declare_parameter("conf", 0.25)
        self.declare_parameter("iou", 0.45)

        self.model_path = self.get_parameter("model_path").value
        self.imgsz = self.get_parameter("imgsz").value
        self.conf = float(self.get_parameter("conf").value)
        self.iou = float(self.get_parameter("iou").value)

        self.bridge = CvBridge()
        self.latest_image = None

        self.model = YOLO(self.model_path)
        self.get_logger().info(f"✅ YOLO model loaded: {self.model_path}")

        self.sub = self.create_subscription(
            Image,
            "/wrist_camera/image_raw",         # ← 카메라 topic 체크
            self.image_callback,
            10,
        )

        self.srv = self.create_service(
            DetectButton,
            "detect_button",
            self.handle_service,
        )

        self.get_logger().info("🚀 ButtonDetectionNode ready.")

    def image_callback(self, msg: Image):
        """ 카메라 이미지 저장 """
        try:
            self.latest_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
        except Exception as e:
            self.get_logger().error(f"CVBridge error: {e}")

    def handle_service(self, request, response):
        """ 서비스 요청(label)을 받아 YOLO로 감지 후 좌표 반환 """
        label = request.label
        self.get_logger().info(f"➡ incoming request [{label}]")

        if self.latest_image is None:
            self.get_logger().warn("⚠ No image received yet")
            response.success = False
            return response

        frame = self.latest_image.copy()

        # 🔥 RAW 이미지만 사용 (전처리 제거)
        debug_path = "/tmp/yolo_debug_input.png"
        cv2.imwrite(debug_path, frame)
        self.get_logger().info(f"🔍 Saved debug input: {debug_path}")

        # YOLO 추론
        results = self.model.predict(
            frame, imgsz=self.imgsz, conf=self.conf, iou=self.iou, verbose=False
        )

        boxes = results[0].boxes
        if boxes is None or len(boxes) == 0:
            self.get_logger().warn("⚠ YOLO returned 0 boxes")
            response.success = False
            return response

        best = None

        for b in boxes:
            cls_id = int(b.cls[0])
            conf = float(b.conf[0])
            detected_label = self.model.names[cls_id]

            x1, y1, x2, y2 = map(int, b.xyxy[0].tolist())
            cx, cy = (x1 + x2) // 2, (y1 + y2) // 2

            self.get_logger().info(
                f"📦 detected: '{detected_label}', conf={conf:.2f}, center=({cx},{cy})"
            )

            if detected_label == label:
                best = (cx, cy, conf)
                break

        if best:
            response.success = True
            response.u = best[0]
            response.v = best[1]
            response.confidence = float(best[2])
            self.get_logger().info(f"✅ MATCH FOUND → ({best[0]}, {best[1]}) conf={best[2]:.2f}")
        else:
            self.get_logger().warn(f"❌ Target '{label}' not found")
            response.success = False

        return response


def main():
    rclpy.init()
    node = ButtonDetectionNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
