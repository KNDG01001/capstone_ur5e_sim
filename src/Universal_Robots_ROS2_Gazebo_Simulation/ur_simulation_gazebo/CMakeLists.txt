cmake_minimum_required(VERSION 3.5)
project(ur_simulation_gazebo)

# ===== 1. 의존성 =====
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo_msgs REQUIRED)

# ===== 2. 플러그인 빌드 =====
add_library(elevator_button_plugin SHARED
  plugins/elevator_button_plugin.cpp
)

ament_target_dependencies(elevator_button_plugin
  rclcpp
  gazebo_ros
  gazebo_msgs
)

# ===== 3. 설치 =====

# config, launch, urdf
install(DIRECTORY config launch urdf
  DESTINATION share/${PROJECT_NAME}
)

# worlds
install(DIRECTORY worlds
  DESTINATION share/${PROJECT_NAME}
)

install(DIRECTORY materials
  DESTINATION share/${PROJECT_NAME}
)


# 플러그인
install(TARGETS elevator_button_plugin
  DESTINATION lib
)

# Gazebo 환경변수 hook
ament_environment_hooks(${CMAKE_CURRENT_SOURCE_DIR}/env_hooks/aaa_ur_simulation_gazebo_env.sh)

# ===== 4. 테스트 =====
if(BUILD_TESTING)
  find_package(launch_testing_ament_cmake)
  find_package(ament_cmake_pytest REQUIRED)
  add_launch_test(test/test_gazebo.py
    TIMEOUT 180
  )
endif()

ament_package()
