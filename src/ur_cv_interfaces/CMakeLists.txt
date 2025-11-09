cmake_minimum_required(VERSION 3.8)
project(ur_cv_interfaces)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)     # ← 추가

# 인터페이스 생성
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/DetectButton.srv"
  "action/PressButton.action"
  DEPENDENCIES std_msgs
)

ament_export_dependencies(rosidl_default_runtime)

ament_package()
