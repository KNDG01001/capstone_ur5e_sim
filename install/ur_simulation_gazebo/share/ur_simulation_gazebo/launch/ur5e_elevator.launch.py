from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, RegisterEventHandler, TimerAction
from launch.event_handlers import OnProcessStart
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import xacro
import os

def generate_launch_description():
    print("[DEBUG] ✅ Using xacro.process_file — launch file is up-to-date")

    gazebo_pkg = get_package_share_directory('gazebo_ros')
    sim_pkg = get_package_share_directory('ur_simulation_gazebo')

    world = os.path.join(sim_pkg, 'worlds', 'elevator.world')
    xacro_file = os.path.join(sim_pkg, 'urdf', 'ur.urdf.xacro')
    controller_config = os.path.join(sim_pkg, 'config', 'ur_controllers.yaml')

    robot_description_config = xacro.process_file(
        xacro_file,
        mappings={
            "ur_type": "ur5e",
            "name": "ur5e",
            "controller_config_file": controller_config
        }
    ).toxml()

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(gazebo_pkg, 'launch', 'gazebo.launch.py')
        ),
        launch_arguments={
            'world': world,
            'verbose': 'true'
        }.items()
    )

    rsp = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': True,
            'robot_description': robot_description_config
        }]
    )

    control_node = Node(
        package='controller_manager',
        executable='ros2_control_node',
        parameters=[
            {'use_sim_time': True,
             'robot_description': robot_description_config},
            controller_config
        ],
        output='screen'
    )

    spawn_entity = Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        arguments=[
            '-entity', 'ur5e',
            '-topic', 'robot_description'
        ],
        output='screen'
    )

    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'joint_state_broadcaster',
            '--controller-manager', '/controller_manager'
        ],
        output='screen'
    )

    joint_trajectory_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'joint_trajectory_controller',
            '--controller-manager', '/controller_manager'
        ],
        output='screen'
    )

    spawner_sequence = RegisterEventHandler(
        OnProcessStart(
            target_action=control_node,
            on_start=[
                TimerAction(period=2.0, actions=[joint_state_broadcaster_spawner]),
                TimerAction(period=3.0, actions=[joint_trajectory_controller_spawner])
            ]
        )
    )

    return LaunchDescription([
        gazebo,
        rsp,
        control_node,
        spawn_entity,
        spawner_sequence
    ])
