// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ur_cv_interfaces:srv/DetectButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__BUILDER_HPP_
#define UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ur_cv_interfaces/srv/detail/detect_button__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ur_cv_interfaces
{

namespace srv
{

namespace builder
{

class Init_DetectButton_Request_label
{
public:
  Init_DetectButton_Request_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ur_cv_interfaces::srv::DetectButton_Request label(::ur_cv_interfaces::srv::DetectButton_Request::_label_type arg)
  {
    msg_.label = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::srv::DetectButton_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::srv::DetectButton_Request>()
{
  return ur_cv_interfaces::srv::builder::Init_DetectButton_Request_label();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace srv
{

namespace builder
{

class Init_DetectButton_Response_confidence
{
public:
  explicit Init_DetectButton_Response_confidence(::ur_cv_interfaces::srv::DetectButton_Response & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::srv::DetectButton_Response confidence(::ur_cv_interfaces::srv::DetectButton_Response::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::srv::DetectButton_Response msg_;
};

class Init_DetectButton_Response_v
{
public:
  explicit Init_DetectButton_Response_v(::ur_cv_interfaces::srv::DetectButton_Response & msg)
  : msg_(msg)
  {}
  Init_DetectButton_Response_confidence v(::ur_cv_interfaces::srv::DetectButton_Response::_v_type arg)
  {
    msg_.v = std::move(arg);
    return Init_DetectButton_Response_confidence(msg_);
  }

private:
  ::ur_cv_interfaces::srv::DetectButton_Response msg_;
};

class Init_DetectButton_Response_u
{
public:
  explicit Init_DetectButton_Response_u(::ur_cv_interfaces::srv::DetectButton_Response & msg)
  : msg_(msg)
  {}
  Init_DetectButton_Response_v u(::ur_cv_interfaces::srv::DetectButton_Response::_u_type arg)
  {
    msg_.u = std::move(arg);
    return Init_DetectButton_Response_v(msg_);
  }

private:
  ::ur_cv_interfaces::srv::DetectButton_Response msg_;
};

class Init_DetectButton_Response_success
{
public:
  Init_DetectButton_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectButton_Response_u success(::ur_cv_interfaces::srv::DetectButton_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_DetectButton_Response_u(msg_);
  }

private:
  ::ur_cv_interfaces::srv::DetectButton_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::srv::DetectButton_Response>()
{
  return ur_cv_interfaces::srv::builder::Init_DetectButton_Response_success();
}

}  // namespace ur_cv_interfaces

#endif  // UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__BUILDER_HPP_
