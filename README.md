명령어 예제
```bash
ros2 action send_goal /press_button ur_cv_interfaces/action/PressButton "{button: '1'}"

```
Yolo 학습
```bash
cd ~/ros
yolo detect train model=yolov8n.pt \
    data=datasets/elevator_buttons/dataset.yaml \
    epochs=100 imgsz=640 \
    project=runs/elevator_buttons \
    name=yolov8n_v1
```
가중치 설정
```bash
sunbi@sunbi:~/ros$ ros2 param set /button_detect_and_move yolo_weights /home/sunbi/ros/runs/elevator_buttons/yolov8n_v1/weights/best.pt
Set parameter successful
sunbi@sunbi:~/ros$ ros2 param set /button_detect_and_move detector_type yolo
Set parameter successful
```

# 🤖 capstone_ur5e_sim

UR5e 로봇팔의 Gazebo 시뮬레이션 및 ROS 2 Humble 기반 제어 패키지입니다.  
`Universal_Robots_ROS2_Description`과 `Universal_Robots_ROS2_Gazebo_Simulation`을 활용하여 URDF 시각화, Gazebo 통합, ros2_control 기반 제어가 가능합니다.

---

## ✅ 환경 사전 조건

- **Ubuntu 22.04**
- **ROS 2 Humble**
- **Gazebo Classic (gazebo11)**
- Python ≥ 3.8
- `colcon`, `vcstool` 설치 필요

---

## 📦 필수 패키지 설치

```bash
sudo apt update && sudo apt install -y \
  ros-humble-desktop \
  ros-humble-joint-state-publisher-gui \
  ros-humble-xacro \
  ros-humble-robot-state-publisher \
  ros-humble-gazebo-ros \
  ros-humble-gazebo-ros-pkgs \
  ros-humble-ros2-control \
  ros-humble-ros2-controllers \
  ros-humble-joint-trajectory-controller \
  ros-humble-position-controllers \
  ros-humble-velocity-controllers \
  python3-colcon-common-extensions \

  python3-vcstool
```

🧱 패키지 구조
```
ros2_ws/ 
└── src/ 
    ├── capstone_ur5e_sim/                    # 본 프로젝트 루트
    ├── Universal_Robots_ROS2_Description/    # URDF/Xacro 구성
    └── Universal_Robots_ROS2_Gazebo_Simulation/ # Gazebo launch 및 ros2_control 설정
```
⚙️ 빌드 및 실행

1. 워크스페이스 구성 및 빌드
   
```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
```

# 저장소 복제
```bash
git clone https://github.com/KNDG01001/capstone_ur5e_sim.git .
```

# 빌드

```bash
cd ~/ros2_ws
source /opt/ros/humble/setup.bash
colcon build --symlink-install
```

2. Gazebo 시뮬레이션 실행

```bash
source ~/ros2_ws/install/setup.bash
ros2 launch ur_simulation_gazebo ur5e.launch.py
```

🧩 주요 구성 요소 설명
1. ur5e.launch.py

위치: Universal_Robots_ROS2_Gazebo_Simulation/launch/

기능: UR5e URDF를 Gazebo에 로드하고, 컨트롤러 로딩 및 시뮬레이션 환경 설정 수행

포함:

robot_state_publisher, joint_state_broadcaster

joint_trajectory_controller 또는 scaled_joint_trajectory_controller

Gazebo world 로딩

2. URDF/Xacro 구조

위치: Universal_Robots_ROS2_Description/urdf/

주요 파일:

ur_macro.xacro: 로봇 구성 매크로

ur5e.xacro: 실제 UR5e 조립 정의

ur.urdf.xacro: 최상위 통합 URDF

호출 예시:

ros2 run xacro xacro ur.urdf.xacro > ur5e.urdf

3. ros2_control 설정

위치: Universal_Robots_ROS2_Gazebo_Simulation/config/controllers.yaml

주요 컨트롤러:
```
joint_state_broadcaster

scaled_joint_trajectory_controller

position_controllers/JointGroupPositionController

velocity_controllers/JointGroupVelocityController
```

컨트롤러 수동 로드 예시:
```bash
ros2 control load_controller --set-state start joint_state_broadcaster
ros2 control load_controller --set-state start scaled_joint_trajectory_controller
```

🖥️ RViz 시각화

```bash
# Launch 실행 후
ros2 run rviz2 rviz2
# 로봇 모델, TF, JointState 표시 추가
```

🔧 실물 로봇 전환 시 고려사항

Gazebo Plugin 제거

hardware_interface/ForwardCommandController 등으로 교체

실시간 통신(ethernet/IP 등) 설정

ros2_control의 실 로봇용 hardware interface 재구현 필요

📚 참고 문서

ros-controls/ros2_control

Universal Robots ROS 2

Gazebo ROS 2 Integration

📄 라이선스

MIT License
