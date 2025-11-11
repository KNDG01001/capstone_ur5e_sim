#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TwistStamped
import sys, select, termios, tty, time


class ServoTeleopArm(Node):
    def __init__(self):
        super().__init__('servo_teleop_arm')

        self.pub = self.create_publisher(TwistStamped, '/servo_node/delta_twist_cmds', 10)
        self.speed_linear = 0.1   # m/s
        self.speed_angular = 0.4  # rad/s
        self.last_cmd_time = 0.0
        self.zero_sent = True
        self.get_logger().info("Keyboard teleop started. Use WASD + RF + QE + TG keys to control arm.")

    def get_key(self):
        tty.setraw(sys.stdin.fileno())
        rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
        key = sys.stdin.read(1) if rlist else ''
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
        return key

    def publish_twist(self, vx=0.0, vy=0.0, vz=0.0, wx=0.0, wy=0.0, wz=0.0):
        msg = TwistStamped()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.twist.linear.x = vx
        msg.twist.linear.y = vy
        msg.twist.linear.z = vz
        msg.twist.angular.x = wx
        msg.twist.angular.y = wy
        msg.twist.angular.z = wz
        self.pub.publish(msg)

    def run(self):
        try:
            while True:
                key = self.get_key()
                now = time.time()
                if key == 'w':
                    self.publish_twist(vx=self.speed_linear)
                elif key == 's':
                    self.publish_twist(vx=-self.speed_linear)
                elif key == 'a':
                    self.publish_twist(vy=self.speed_linear)
                elif key == 'd':
                    self.publish_twist(vy=-self.speed_linear)
                elif key == 'r':
                    self.publish_twist(vz=self.speed_linear)
                elif key == 'f':
                    self.publish_twist(vz=-self.speed_linear)
                elif key == 'q':
                    self.publish_twist(wz=self.speed_angular)
                elif key == 'e':
                    self.publish_twist(wz=-self.speed_angular)
                elif key == 't':
                    self.publish_twist(wy=self.speed_angular)
                elif key == 'g':
                    self.publish_twist(wy=-self.speed_angular)
                elif key == 'x':
                    break
                elif key == ' ':
                    self.publish_twist()
                else:
                    if not self.zero_sent and now - self.last_cmd_time > 0.2:
                        self.publish_twist()
                        self.zero_sent = True
                        continue
                    continue

                self.last_cmd_time = now
                self.zero_sent = False
        except Exception as e:
            self.get_logger().error(str(e))
        finally:
            self.publish_twist()  # Stop motion
            self.get_logger().info("Shutting down teleop.")


def main(args=None):
    global settings
    settings = termios.tcgetattr(sys.stdin)
    rclpy.init(args=args)
    node = ServoTeleopArm()
    node.run()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
