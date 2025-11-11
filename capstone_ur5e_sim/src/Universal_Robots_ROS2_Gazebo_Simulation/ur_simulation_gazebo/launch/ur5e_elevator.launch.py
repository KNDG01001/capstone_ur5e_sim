from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import Command, PathJoinSubstitution, FindExecutable
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # 패키지 경로들
    gazebo_ros_pkg = get_package_share_directory('gazebo_ros')
    ur_pkg = get_package_share_directory('ur_simulation_gazebo')
    
    try:
        ur_description_pkg = get_package_share_directory('ur_description')
        print(f"ur_description found at: {ur_description_pkg}")
    except Exception as e:
        print(f"ur_description package not found: {e}")
        ur_description_pkg = ur_pkg

    # 1. Gazebo 실행 (elevator.world 포함)
    world_path = os.path.join(ur_pkg, 'worlds', 'elevator.world')

    controller_config_file = os.path.join(ur_pkg, 'config', 'ur_controllers.yaml')

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_ros_pkg, 'launch', 'gazebo.launch.py')
        ),
        launch_arguments={
            'world': world_path,
            'verbose': 'true'
        }.items()
    )

    # 2. 로봇 URDF (xacro) 로딩: 손목 카메라가 포함된 커스텀 모델 사용
    xacro_path = os.path.join(ur_pkg, 'urdf', 'ur_with_camera.urdf.xacro')
    if not os.path.exists(xacro_path):
        # fallback to 기본 ur_description if our custom file is missing
        alt_path = os.path.join(ur_description_pkg, 'urdf', 'ur5e.urdf.xacro')
        xacro_path = alt_path if os.path.exists(alt_path) else os.path.join(ur_description_pkg, 'urdf', 'ur.urdf.xacro')

    robot_description_content = Command([
        'xacro', ' ',
        xacro_path, ' ',
        'name:=ur5e', ' ',
        'ur_type:=ur5e', ' ',
        'sim_gazebo:=true', ' ',
        'use_fake_hardware:=true', ' ',
        'controller_config_file:=/home/sunbi/ros2_ws/src/Universal_Robots_ROS2_Gazebo_Simulation/ur_simulation_gazebo/config/ur_controllers.yaml'
    ])
    
    robot_description = {'robot_description': robot_description_content}

    # 3. Robot State Publisher 실행
    robot_state_pub = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[robot_description]
    )

    # 4. 스폰 엔티티 (약간의 지연 포함)
    spawn_robot = ExecuteProcess(
        cmd=[
            'bash', '-c',
            'sleep 3 && ros2 run gazebo_ros spawn_entity.py '
            '-entity ur5e -topic robot_description -x 0.20 -y 0.18 -z 0.1 -Y 1.57'
        ],
        output='screen'
    )

    load_controllers = [
        ExecuteProcess(
            cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'joint_state_broadcaster'],
            output='screen'
        ),
        ExecuteProcess(
            cmd=['ros2', 'control', 'load_controller', '--set-state', 'active', 'scaled_joint_trajectory_controller'],
            output='screen'
        )
    ]

    return LaunchDescription([
        gazebo,
        robot_state_pub,
        spawn_robot
    ])
