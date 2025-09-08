# =======================
# File: ur5e_elevator.launch.py
# =======================

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Package directories
    ur_pkg = get_package_share_directory('ur_simulation_gazebo')
    gazebo_ros_pkg = get_package_share_directory('gazebo_ros')

    # File paths
    world_path = os.path.join(ur_pkg, 'worlds', 'elevator.world')
    
    # Launch Gazebo
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_pkg, 'launch', 'gazebo.launch.py')
        ),
        launch_arguments={'world': world_path}.items()
    )

    # Spawn robot
    robot_description_path = os.path.join(ur_pkg, 'urdf', 'ur.urdf.xacro')
    spawn_robot = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'ur5e',
            '-topic', 'robot_description',
            '-x', '0.0', '-y', '0.0', '-z', '0.0'
        ],
        output='screen'
    )

    # Robot state publisher
    robot_state_pub = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'robot_description': LaunchConfiguration('robot_description')
        }]
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'robot_description',
            default_value=os.path.join(ur_pkg, 'urdf', 'ur.urdf.xacro'),
            description='URDF/Xacro file'
        ),
        gazebo,
        robot_state_pub,
        spawn_robot
    ])
