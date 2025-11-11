// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ur_cv_interfaces:action/PressButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__BUILDER_HPP_
#define UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ur_cv_interfaces/action/detail/press_button__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_Goal_button
{
public:
  Init_PressButton_Goal_button()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ur_cv_interfaces::action::PressButton_Goal button(::ur_cv_interfaces::action::PressButton_Goal::_button_type arg)
  {
    msg_.button = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_Goal>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_Goal_button();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_Result_message
{
public:
  explicit Init_PressButton_Result_message(::ur_cv_interfaces::action::PressButton_Result & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::action::PressButton_Result message(::ur_cv_interfaces::action::PressButton_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_Result msg_;
};

class Init_PressButton_Result_success
{
public:
  Init_PressButton_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PressButton_Result_message success(::ur_cv_interfaces::action::PressButton_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_PressButton_Result_message(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_Result>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_Result_success();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_Feedback_status
{
public:
  Init_PressButton_Feedback_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ur_cv_interfaces::action::PressButton_Feedback status(::ur_cv_interfaces::action::PressButton_Feedback::_status_type arg)
  {
    msg_.status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_Feedback>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_Feedback_status();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_SendGoal_Request_goal
{
public:
  explicit Init_PressButton_SendGoal_Request_goal(::ur_cv_interfaces::action::PressButton_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::action::PressButton_SendGoal_Request goal(::ur_cv_interfaces::action::PressButton_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_SendGoal_Request msg_;
};

class Init_PressButton_SendGoal_Request_goal_id
{
public:
  Init_PressButton_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PressButton_SendGoal_Request_goal goal_id(::ur_cv_interfaces::action::PressButton_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PressButton_SendGoal_Request_goal(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_SendGoal_Request>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_SendGoal_Request_goal_id();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_SendGoal_Response_stamp
{
public:
  explicit Init_PressButton_SendGoal_Response_stamp(::ur_cv_interfaces::action::PressButton_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::action::PressButton_SendGoal_Response stamp(::ur_cv_interfaces::action::PressButton_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_SendGoal_Response msg_;
};

class Init_PressButton_SendGoal_Response_accepted
{
public:
  Init_PressButton_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PressButton_SendGoal_Response_stamp accepted(::ur_cv_interfaces::action::PressButton_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_PressButton_SendGoal_Response_stamp(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_SendGoal_Response>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_SendGoal_Response_accepted();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_GetResult_Request_goal_id
{
public:
  Init_PressButton_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::ur_cv_interfaces::action::PressButton_GetResult_Request goal_id(::ur_cv_interfaces::action::PressButton_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_GetResult_Request>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_GetResult_Request_goal_id();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_GetResult_Response_result
{
public:
  explicit Init_PressButton_GetResult_Response_result(::ur_cv_interfaces::action::PressButton_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::action::PressButton_GetResult_Response result(::ur_cv_interfaces::action::PressButton_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_GetResult_Response msg_;
};

class Init_PressButton_GetResult_Response_status
{
public:
  Init_PressButton_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PressButton_GetResult_Response_result status(::ur_cv_interfaces::action::PressButton_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_PressButton_GetResult_Response_result(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_GetResult_Response>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_GetResult_Response_status();
}

}  // namespace ur_cv_interfaces


namespace ur_cv_interfaces
{

namespace action
{

namespace builder
{

class Init_PressButton_FeedbackMessage_feedback
{
public:
  explicit Init_PressButton_FeedbackMessage_feedback(::ur_cv_interfaces::action::PressButton_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::ur_cv_interfaces::action::PressButton_FeedbackMessage feedback(::ur_cv_interfaces::action::PressButton_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_FeedbackMessage msg_;
};

class Init_PressButton_FeedbackMessage_goal_id
{
public:
  Init_PressButton_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PressButton_FeedbackMessage_feedback goal_id(::ur_cv_interfaces::action::PressButton_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PressButton_FeedbackMessage_feedback(msg_);
  }

private:
  ::ur_cv_interfaces::action::PressButton_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::ur_cv_interfaces::action::PressButton_FeedbackMessage>()
{
  return ur_cv_interfaces::action::builder::Init_PressButton_FeedbackMessage_goal_id();
}

}  // namespace ur_cv_interfaces

#endif  // UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__BUILDER_HPP_
