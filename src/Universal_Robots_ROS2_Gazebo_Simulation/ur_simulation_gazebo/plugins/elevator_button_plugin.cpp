// File: elevator_button_plugin.cpp
// Location: ur_simulation_gazebo/plugins/

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/gazebo.hh>
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/bool.hpp>

namespace gazebo_plugins
{
  class ElevatorButtonPlugin : public gazebo::ModelPlugin
  {
  public:
    ElevatorButtonPlugin() : ModelPlugin() {}

    void Load(gazebo::physics::ModelPtr _model, sdf::ElementPtr _sdf) override
    {
      this->model_ = _model;
      this->link_ = _model->GetLink("button_link");
      this->last_pressed_ = false;

      node_ = gazebo_ros::Node::Get(_sdf);
      pub_ = node_->create_publisher<std_msgs::msg::Bool>("/elevator/button_pressed", 10);

      update_connection_ = gazebo::event::Events::ConnectWorldUpdateBegin(
        std::bind(&ElevatorButtonPlugin::OnUpdate, this));
    }

    void OnUpdate()
    {
      ignition::math::Pose3d pose = link_->WorldPose();
      bool pressed = pose.Pos().X() < 0.78;  // Assume pressed if pushed ~2cm in X-axis

      if (pressed != last_pressed_)
      {
        auto msg = std_msgs::msg::Bool();
        msg.data = pressed;
        pub_->publish(msg);
        last_pressed_ = pressed;
      }
    }

  private:
    gazebo::physics::ModelPtr model_;
    gazebo::physics::LinkPtr link_;
    gazebo::event::ConnectionPtr update_connection_;
    gazebo_ros::Node::SharedPtr node_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr pub_;
    bool last_pressed_;
  };

  GZ_REGISTER_MODEL_PLUGIN(ElevatorButtonPlugin)
}
