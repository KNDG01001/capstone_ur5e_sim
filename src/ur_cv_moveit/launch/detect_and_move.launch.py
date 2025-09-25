from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    rgb_topic = LaunchConfiguration('rgb_topic', default='/wrist_camera/image_raw')
    depth_topic = LaunchConfiguration('depth_topic', default='/wrist_camera/depth/image_raw')
    camera_info_topic = LaunchConfiguration('camera_info_topic', default='/wrist_camera/camera_info')
    base_frame = LaunchConfiguration('base_frame', default='base_link')
    plan_only = LaunchConfiguration('plan_only', default='false')

    node = Node(
        package='ur_cv_moveit',
        executable='button_detect_and_move',
        name='button_detect_and_move',
        output='screen',
        parameters=[{
            'rgb_topic': rgb_topic,
            'depth_topic': depth_topic,
            'camera_info_topic': camera_info_topic,
            'base_frame': base_frame,
            'plan_only': plan_only,
        }]
    )

    return LaunchDescription([
        DeclareLaunchArgument('rgb_topic', default_value=rgb_topic),
        DeclareLaunchArgument('depth_topic', default_value=depth_topic),
        DeclareLaunchArgument('camera_info_topic', default_value=camera_info_topic),
        DeclareLaunchArgument('base_frame', default_value=base_frame),
        DeclareLaunchArgument('plan_only', default_value=plan_only),
        node
    ])

