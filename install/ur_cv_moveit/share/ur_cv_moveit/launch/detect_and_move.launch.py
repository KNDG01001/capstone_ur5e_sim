from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


def generate_launch_description():

    rgb_topic = LaunchConfiguration("rgb_topic", default="/wrist_camera/image_raw")
    depth_topic = LaunchConfiguration("depth_topic", default="/wrist_camera/depth/image_raw")
    camera_info_topic = LaunchConfiguration("camera_info_topic", default="/wrist_camera/camera_info")
    base_frame = LaunchConfiguration("base_frame", default="base_link")

    yolo_weights = LaunchConfiguration("yolo_weights", default="/home/sunbi/ros/best.pt")
    yolo_imgsz = LaunchConfiguration("yolo_imgsz", default="960")
    yolo_conf = LaunchConfiguration("yolo_conf", default="0.15")
    yolo_iou = LaunchConfiguration("yolo_iou", default="0.55")

    detection_node = Node(
        package="ur_cv_moveit",
        executable="button_detection_node",
        name="button_detection_node",
        parameters=[{
            "rgb_topic": rgb_topic,
            "yolo_weights": yolo_weights,
            "imgsz": yolo_imgsz,
            "conf": yolo_conf,
            "iou": yolo_iou,
        }],
    )

    press_node = Node(
        package="ur_cv_moveit",
        executable="button_press_action_node",
        name="button_press_action_node",
        output="screen",
        parameters=[{
            "rgb_topic": rgb_topic,
            "depth_topic": depth_topic,
            "camera_info_topic": camera_info_topic,
            "base_frame": base_frame,
        }],
    )

    return LaunchDescription([
        DeclareLaunchArgument("rgb_topic", default_value=rgb_topic),
        DeclareLaunchArgument("depth_topic", default_value=depth_topic),
        DeclareLaunchArgument("camera_info_topic", default_value=camera_info_topic),
        DeclareLaunchArgument("base_frame", default_value=base_frame),
        DeclareLaunchArgument("yolo_weights", default_value=yolo_weights),
        DeclareLaunchArgument("yolo_imgsz", default_value=yolo_imgsz),
        DeclareLaunchArgument("yolo_conf", default_value=yolo_conf),
        DeclareLaunchArgument("yolo_iou", default_value=yolo_iou),

        detection_node,
        press_node,
    ])
