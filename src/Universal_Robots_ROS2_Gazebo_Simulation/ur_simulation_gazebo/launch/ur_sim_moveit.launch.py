from launch import LaunchDescription
import os

from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, OpaqueFunction, SetEnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node

def launch_setup(context, *args, **kwargs):
    # 기존 설정
    ur_type = LaunchConfiguration("ur_type")
    safety_limits = LaunchConfiguration("safety_limits")
    runtime_config_package = LaunchConfiguration("runtime_config_package")
    controllers_file = LaunchConfiguration("controllers_file")
    description_package = LaunchConfiguration("description_package")
    description_file = LaunchConfiguration("description_file")
    moveit_config_package = LaunchConfiguration("moveit_config_package")
    moveit_config_file = LaunchConfiguration("moveit_config_file")
    prefix = LaunchConfiguration("prefix")
    world_file = LaunchConfiguration("world")  # ✅ 추가됨
    use_wrist_camera = LaunchConfiguration("use_wrist_camera")
    detector_type = LaunchConfiguration("detector_type")
    yolo_weights = LaunchConfiguration("yolo_weights")

    # Ensure Gazebo shader libs and custom resources are discoverable
    # Mirror the effect of `source /usr/share/gazebo/setup.sh` by appending resource path entries
    default_resource_paths = [
        "/usr/share/gazebo-11",
        "/usr/share/gazebo-11/media",
    ]
    custom_world_path = "/home/sunbi/ros/capstone_ur5e_sim/src/Universal_Robots_ROS2_Gazebo_Simulation/ur_simulation_gazebo/worlds"
    extra_resource_paths = [custom_world_path]
    current_resource = os.environ.get("GAZEBO_RESOURCE_PATH", "")
    resource_paths = [p for p in current_resource.split(":") if p]
    for p in default_resource_paths + extra_resource_paths:
        if p not in resource_paths:
            resource_paths.append(p)

    current_model = os.environ.get("GAZEBO_MODEL_PATH", "")
    model_paths = [p for p in current_model.split(":") if p]
    if custom_world_path not in model_paths:
        model_paths.append(custom_world_path)

    env_setup_actions = [
        SetEnvironmentVariable("GAZEBO_RESOURCE_PATH", ":".join(resource_paths)),
        SetEnvironmentVariable("GAZEBO_MODEL_PATH", ":".join(model_paths)),
    ]

    # Select description based on camera toggle
    use_cam = use_wrist_camera.perform(context).lower() in ["1", "true", "yes"]
    if use_cam:
        desc_pkg_val = description_package
        desc_file_val = description_file
    else:
        # fallback to upstream ur_description URDF without camera
        desc_pkg_val = LaunchConfiguration("fallback_description_package")
        desc_file_val = LaunchConfiguration("fallback_description_file")

    # ur + ros2_control
    ur_control_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [FindPackageShare("ur_simulation_gazebo"), "/launch/ur_sim_control.launch.py"]
        ),
        launch_arguments={
            "ur_type": ur_type,
            "safety_limits": safety_limits,
            "runtime_config_package": runtime_config_package,
            "controllers_file": controllers_file,
            "description_package": desc_pkg_val,
            "description_file": desc_file_val,
            "prefix": prefix,
            "launch_rviz": "false",
            # Gazebo 시뮬레이션에서는 MoveIt(use_sim_time=true)과 매칭되도록
            # 기본 컨트롤러를 joint_trajectory_controller로 사용
            "initial_joint_controller": "joint_trajectory_controller",
            # Controller manager namespace (plugin logs show namespace: /)
            "controller_manager_ns": "/controller_manager",
            "world": world_file,
        }.items(),
    )

    # MoveIt 런치
    ur_moveit_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            [FindPackageShare("ur_moveit_config"), "/launch/ur_moveit.launch.py"]
        ),
        launch_arguments={
            "ur_type": ur_type,
            "safety_limits": safety_limits,
            "description_package": desc_pkg_val,
            "description_file": desc_file_val,
            "moveit_config_package": moveit_config_package,
            "moveit_config_file": moveit_config_file,
            "prefix": prefix,
            # Gazebo 시간과 일치시키기 위해 MoveIt도 sim time 사용
            "use_sim_time": "true",
            "launch_rviz": "true",
            "use_fake_hardware": "false",
        }.items(),
    )

    # CV + MoveIt node (detect red button and move)
    nodes = env_setup_actions + [ur_control_launch, ur_moveit_launch]
    if use_cam:
        nodes.append(
            Node(
                package="ur_cv_moveit",
                executable="button_detect_and_move",
                name="button_detect_and_move",
                output="screen",
                parameters=[
                    {
                        "base_frame": "base_link",
                        "detector_type": detector_type.perform(context) or "yolo",
                        "yolo_weights": yolo_weights.perform(context) or "",
                    }
                ],
            )
        )

    return nodes

def generate_launch_description():
    declared_arguments = []

    declared_arguments.append(
        DeclareLaunchArgument(
            "ur_type",
            description="Type/series of used UR robot.",
            choices=["ur3", "ur3e", "ur5", "ur5e", "ur7e", "ur10", "ur12e", "ur10e", "ur16e", "ur20", "ur30"],
            default_value="ur5e",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "safety_limits",
            default_value="true",
            description="Enables the safety limits controller if true.",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "runtime_config_package",
            default_value="ur_simulation_gazebo",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "controllers_file",
            default_value="ur_controllers.yaml",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "description_package",
            default_value="ur_simulation_gazebo",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "description_file",
            default_value="ur_with_camera.urdf.xacro",
        )
    )
    # Fallback description (no camera)
    declared_arguments.append(
        DeclareLaunchArgument(
            "fallback_description_package",
            default_value="ur_description",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "fallback_description_file",
            default_value="ur.urdf.xacro",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "moveit_config_package",
            default_value="ur_moveit_config",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "moveit_config_file",
            default_value="ur.srdf.xacro",
        )
    )
    declared_arguments.append(
        DeclareLaunchArgument(
            "prefix",
            default_value='""',
        )
    )

    # ✅ 월드 경로 전달 (네가 쓰는 elevator.world)
    declared_arguments.append(
        DeclareLaunchArgument(
            "world",
            default_value=PathJoinSubstitution([
                FindPackageShare("ur_simulation_gazebo"),
                "worlds",
                "elevator.world",
            ]),
            description="Full path to the world model file to load",
        )
    )

    # Toggle wrist camera URDF
    declared_arguments.append(
        DeclareLaunchArgument(
            "use_wrist_camera",
            default_value="true",
            description="Use URDF with wrist-mounted depth camera and launch CV node",
        )
    )

    declared_arguments.append(
        DeclareLaunchArgument(
            "detector_type",
            default_value="yolo",
            description="Detector type for button detection node (yolo/hsv)",
        )
    )

    declared_arguments.append(
        DeclareLaunchArgument(
            "yolo_weights",
            default_value="/home/sunbi/ros/runs/train_log/weights/best.pt",
            description="Path to YOLO weights file",
        )
    )

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])
