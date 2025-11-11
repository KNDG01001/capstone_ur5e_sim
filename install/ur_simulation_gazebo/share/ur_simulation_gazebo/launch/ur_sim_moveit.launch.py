from launch import LaunchDescription
import os

from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    SetEnvironmentVariable,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare
from launch_ros.actions import Node


def launch_setup(context, *args, **kwargs):

    ur_type = LaunchConfiguration("ur_type")
    safety_limits = LaunchConfiguration("safety_limits")
    runtime_config_package = LaunchConfiguration("runtime_config_package")
    controllers_file = LaunchConfiguration("controllers_file")
    description_package = LaunchConfiguration("description_package")
    description_file = LaunchConfiguration("description_file")
    moveit_config_package = LaunchConfiguration("moveit_config_package")
    moveit_config_file = LaunchConfiguration("moveit_config_file")
    prefix = LaunchConfiguration("prefix")
    world_file = LaunchConfiguration("world")

    use_wrist_camera = LaunchConfiguration("use_wrist_camera")
    yolo_weights = LaunchConfiguration("yolo_weights")

    # -----------------------------
    # Gazebo resource path setup
    # -----------------------------
    default_resource_paths = [
        "/usr/share/gazebo-11",
        "/usr/share/gazebo-11/media",
    ]
    custom_world_path = "/home/sunbi/ros/capstone_ur5e_sim/src/Universal_Robots_ROS2_Gazebo_Simulation/ur_simulation_gazebo/worlds"

    current_resource = os.environ.get("GAZEBO_RESOURCE_PATH", "")
    resource_paths = [p for p in current_resource.split(":") if p]

    for p in default_resource_paths + [custom_world_path]:
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

    # -----------------------------
    # Select URDF (camera on/off)
    # -----------------------------
    use_cam = use_wrist_camera.perform(context).lower() in ["1", "true", "yes"]
    if use_cam:
        desc_pkg_val = description_package
        desc_file_val = description_file
    else:
        desc_pkg_val = LaunchConfiguration("fallback_description_package")
        desc_file_val = LaunchConfiguration("fallback_description_file")

    # -----------------------------
    # UR Control + Gazebo spawn
    # -----------------------------
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
            "initial_joint_controller": "joint_trajectory_controller",
            "controller_manager_ns": "/controller_manager",
            "world": world_file,
        }.items(),
    )

    # -----------------------------
    # MoveIt
    # -----------------------------
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
            "use_sim_time": "true",
            "launch_rviz": "true",
            "use_fake_hardware": "false",
        }.items(),
    )

    nodes = env_setup_actions + [ur_control_launch, ur_moveit_launch]

    # -----------------------------
    # ur_cv_moveit (YOLO + IK + Traj)
    # -----------------------------
    if use_cam:
        detect_and_move_launch = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                [FindPackageShare("ur_cv_moveit"), "/launch/detect_and_move.launch.py"]
            ),
            launch_arguments={
                "rgb_topic": "/wrist_camera/image_raw",
                "depth_topic": "/wrist_camera/depth/image_raw",
                "camera_info_topic": "/wrist_camera/camera_info",
                "base_frame": "base_link",
                "plan_only": "false",
                "yolo_weights": yolo_weights.perform(context) or "",
            }.items(),
        )

        # ✅ 여기 수정됨: 반드시 반환 리스트에 append 해야 노드가 실행됨!
        return nodes + [detect_and_move_launch]

    return nodes


def generate_launch_description():

    declared_arguments = [

        DeclareLaunchArgument("ur_type", default_value="ur5e"),
        DeclareLaunchArgument("safety_limits", default_value="true"),
        DeclareLaunchArgument("runtime_config_package", default_value="ur_simulation_gazebo"),
        DeclareLaunchArgument("controllers_file", default_value="ur_controllers.yaml"),
        DeclareLaunchArgument("description_package", default_value="ur_simulation_gazebo"),
        DeclareLaunchArgument("description_file", default_value="ur_with_camera.urdf.xacro"),

        DeclareLaunchArgument("fallback_description_package", default_value="ur_description"),
        DeclareLaunchArgument("fallback_description_file", default_value="ur.urdf.xacro"),

        DeclareLaunchArgument("moveit_config_package", default_value="ur_moveit_config"),
        DeclareLaunchArgument("moveit_config_file", default_value="ur.srdf.xacro"),

        DeclareLaunchArgument("prefix", default_value='""'),

        # world
        DeclareLaunchArgument(
            "world",
            default_value=PathJoinSubstitution([
                FindPackageShare("ur_simulation_gazebo"),
                "worlds",
                "elevator.world",
            ])
        ),

        # camera on/off
        DeclareLaunchArgument("use_wrist_camera", default_value="true"),

        # YOLO weights
        DeclareLaunchArgument(
            "yolo_weights",
            default_value="/home/sunbi/ros/runs/train_log/weights/panel.pt"
        ),
    ]

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])
