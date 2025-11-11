#!/usr/bin/env python3
import rclpy, time, os, cv2, numpy as np
from rclpy.node import Node
from sensor_msgs.msg import Image, JointState
from cv_bridge import CvBridge
from rclpy.qos import QoSProfile


def ssim(a, b):
    a = a.astype(np.float32); b = b.astype(np.float32)
    C1, C2 = 6.5025, 58.5225
    mu1, mu2 = cv2.GaussianBlur(a, (11,11), 1.5), cv2.GaussianBlur(b, (11,11), 1.5)
    mu1_sq, mu2_sq, mu12 = mu1*mu1, mu2*mu2, mu1*mu2
    sigma1_sq = cv2.GaussianBlur(a*a, (11,11), 1.5) - mu1_sq
    sigma2_sq = cv2.GaussianBlur(b*b, (11,11), 1.5) - mu2_sq
    sigma12   = cv2.GaussianBlur(a*b, (11,11), 1.5) - mu12
    num = (2*mu12 + C1)*(2*sigma12 + C2)
    den = (mu1_sq + mu2_sq + C1)*(sigma1_sq + sigma2_sq + C2)
    return float((num/den).mean())


class Recorder(Node):
    def __init__(self):
        super().__init__('dataset_recorder')

        self.declare_parameter('image_topic', '/wrist_camera/image_raw')
        self.declare_parameter('save_dir', '/home/sunbi/dataset')
        self.declare_parameter('ssim_thresh', 0.92)
        self.declare_parameter('min_interval', 0.25)
        self.declare_parameter('joint_delta_thresh', 0.02)

        # ✅ ROS2 parameter object에서 실제 값 가져오기
        self.image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        self.save_dir = self.get_parameter('save_dir').get_parameter_value().string_value
        self.ssim_thresh = self.get_parameter('ssim_thresh').get_parameter_value().double_value
        self.min_interval = self.get_parameter('min_interval').get_parameter_value().double_value
        self.joint_delta_thresh = self.get_parameter('joint_delta_thresh').get_parameter_value().double_value

        os.makedirs(self.save_dir, exist_ok=True)
        self.bridge = CvBridge()
        qos = QoSProfile(depth=10)

        self.img_sub = self.create_subscription(Image, self.image_topic, self.on_img, qos)
        self.joint_sub = self.create_subscription(JointState, '/joint_states', self.on_joint, qos)

        self.last_img_gray = None
        self.last_save_t = 0.0
        self.last_jpos = None
        self._last_saved_jpos = None
        self.count = 0
        self._img_msg_logged = False  # ✅ 추가

        self.get_logger().info(f"Recording images from {self.image_topic}")
        self.get_logger().info(f"Saving to {self.save_dir}")

    def on_joint(self, msg):
        if msg.position:
            self.last_jpos = np.array(msg.position, dtype=np.float32)

    def _joint_moved(self):
        if self.last_jpos is None:
            return False
        if self._last_saved_jpos is None:
            self._last_saved_jpos = self.last_jpos.copy()
            return True
        dv = np.linalg.norm(self.last_jpos - self._last_saved_jpos)
        if dv > self.joint_delta_thresh:
            self._last_saved_jpos = self.last_jpos.copy()
            return True
        return False

    def on_img(self, msg):
        now = time.time()
        if now - self.last_save_t < self.min_interval:
            return

        img = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        change = 1.0
        if self.last_img_gray is not None:
            change = 1.0 - ssim(gray, self.last_img_gray)

        # ✅ 최초 한 번만 로그
        if not self._img_msg_logged:
            self.get_logger().info("Receiving images...")
            self._img_msg_logged = True

        if change > (1.0 - self.ssim_thresh) or self._joint_moved():
            fname = os.path.join(self.save_dir, f"rgb_{self.count:06d}.jpg")
            cv2.imwrite(fname, img)
            self.count += 1
            self.last_img_gray = gray
            self.last_save_t = now
            self.get_logger().info(f"Saved {fname} (change={change:.3f})")


def main():
    rclpy.init()
    node = Recorder()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
