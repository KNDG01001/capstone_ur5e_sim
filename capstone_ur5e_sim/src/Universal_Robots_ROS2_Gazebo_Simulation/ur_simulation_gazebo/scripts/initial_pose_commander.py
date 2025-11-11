#!/usr/bin/env python3
import sys
import time
from pathlib import Path

import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.duration import Duration

import yaml

from control_msgs.action import FollowJointTrajectory
from trajectory_msgs.msg import JointTrajectoryPoint


class InitialPoseCommander(Node):
    def __init__(self):
        super().__init__("initial_pose_commander")

        self.declare_parameter("joint_names", [
            "shoulder_pan_joint",
            "shoulder_lift_joint",
            "elbow_joint",
            "wrist_1_joint",
            "wrist_2_joint",
            "wrist_3_joint",
        ])
        self.declare_parameter("initial_positions_file", "")
        self.declare_parameter("fallback_positions", [
            0.0,
            -2.2,
            1.85,
            -3.0,
            -1.57,
            0.0,
        ])
        self.declare_parameter("goal_duration", 4.0)
        self.declare_parameter("wait_timeout", 30.0)

        self._joint_names = list(self.get_parameter("joint_names").value)
        positions = self._load_positions()
        self._positions = positions

        self._goal_duration = float(self.get_parameter("goal_duration").value)
        self._wait_timeout = float(self.get_parameter("wait_timeout").value)

        self._client = ActionClient(
            self,
            FollowJointTrajectory,
            "/joint_trajectory_controller/follow_joint_trajectory",
        )

    # ------------------------------------------------------------------ utils
    def _load_positions(self):
        path_value = self.get_parameter("initial_positions_file").get_parameter_value().string_value
        if path_value:
            yaml_path = Path(path_value)
            if yaml_path.exists():
                try:
                    with yaml_path.open("r") as f:
                        data = yaml.safe_load(f) or {}
                    positions = []
                    for name in self._joint_names:
                        if name in data:
                            positions.append(float(data[name]))
                        else:
                            self.get_logger().warn(
                                f"Joint '{name}' missing in '{yaml_path}', using fallback value."
                            )
                            return list(self.get_parameter("fallback_positions").value)
                    return positions
                except Exception as exc:
                    self.get_logger().error(
                        f"Failed to read '{yaml_path}': {exc}. Using fallback positions."
                    )
        return list(self.get_parameter("fallback_positions").value)

    # ------------------------------------------------------------------ action
    def send_goal(self):
        if not self._client.wait_for_server(timeout_sec=self._wait_timeout):
            self.get_logger().error(
                "Timed out waiting for joint_trajectory_controller action server."
            )
            return False

        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = self._joint_names

        point = JointTrajectoryPoint()
        point.positions = self._positions
        duration = Duration(seconds=self._goal_duration)
        point.time_from_start = duration.to_msg()
        point.velocities = [0.0] * len(self._joint_names)
        point.accelerations = [0.0] * len(self._joint_names)
        goal.trajectory.points.append(point)

        self.get_logger().info("Sending initial joint trajectory to reach startup pose...")

        send_future = self._client.send_goal_async(goal)
        rclpy.spin_until_future_complete(self, send_future)
        goal_handle = send_future.result()

        if not goal_handle or not goal_handle.accepted:
            self.get_logger().error("Initial pose goal was rejected by the controller.")
            return False

        result_future = goal_handle.get_result_async()
        rclpy.spin_until_future_complete(self, result_future)
        result_msg = result_future.result()

        if result_msg and result_msg.result.error_code == FollowJointTrajectory.Result.SUCCESSFUL:
            self.get_logger().info("Initial pose reached successfully.")
            return True

        self.get_logger().error("Failed to reach initial pose.")
        return False


def main(args=None):
    rclpy.init(args=args)
    node = InitialPoseCommander()
    try:
        success = node.send_goal()
        # Give the controller a brief moment to settle before exiting
        time.sleep(0.5)
        if not success:
            sys.exit(1)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
