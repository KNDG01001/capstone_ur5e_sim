// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ur_cv_interfaces:srv/DetectButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__TRAITS_HPP_
#define UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ur_cv_interfaces/srv/detail/detect_button__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace ur_cv_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const DetectButton_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectButton_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectButton_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace ur_cv_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use ur_cv_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ur_cv_interfaces::srv::DetectButton_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  ur_cv_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ur_cv_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ur_cv_interfaces::srv::DetectButton_Request & msg)
{
  return ur_cv_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ur_cv_interfaces::srv::DetectButton_Request>()
{
  return "ur_cv_interfaces::srv::DetectButton_Request";
}

template<>
inline const char * name<ur_cv_interfaces::srv::DetectButton_Request>()
{
  return "ur_cv_interfaces/srv/DetectButton_Request";
}

template<>
struct has_fixed_size<ur_cv_interfaces::srv::DetectButton_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ur_cv_interfaces::srv::DetectButton_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ur_cv_interfaces::srv::DetectButton_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace ur_cv_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const DetectButton_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: u
  {
    out << "u: ";
    rosidl_generator_traits::value_to_yaml(msg.u, out);
    out << ", ";
  }

  // member: v
  {
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const DetectButton_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: u
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "u: ";
    rosidl_generator_traits::value_to_yaml(msg.u, out);
    out << "\n";
  }

  // member: v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v: ";
    rosidl_generator_traits::value_to_yaml(msg.v, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const DetectButton_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace ur_cv_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use ur_cv_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ur_cv_interfaces::srv::DetectButton_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  ur_cv_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ur_cv_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const ur_cv_interfaces::srv::DetectButton_Response & msg)
{
  return ur_cv_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<ur_cv_interfaces::srv::DetectButton_Response>()
{
  return "ur_cv_interfaces::srv::DetectButton_Response";
}

template<>
inline const char * name<ur_cv_interfaces::srv::DetectButton_Response>()
{
  return "ur_cv_interfaces/srv/DetectButton_Response";
}

template<>
struct has_fixed_size<ur_cv_interfaces::srv::DetectButton_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ur_cv_interfaces::srv::DetectButton_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ur_cv_interfaces::srv::DetectButton_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ur_cv_interfaces::srv::DetectButton>()
{
  return "ur_cv_interfaces::srv::DetectButton";
}

template<>
inline const char * name<ur_cv_interfaces::srv::DetectButton>()
{
  return "ur_cv_interfaces/srv/DetectButton";
}

template<>
struct has_fixed_size<ur_cv_interfaces::srv::DetectButton>
  : std::integral_constant<
    bool,
    has_fixed_size<ur_cv_interfaces::srv::DetectButton_Request>::value &&
    has_fixed_size<ur_cv_interfaces::srv::DetectButton_Response>::value
  >
{
};

template<>
struct has_bounded_size<ur_cv_interfaces::srv::DetectButton>
  : std::integral_constant<
    bool,
    has_bounded_size<ur_cv_interfaces::srv::DetectButton_Request>::value &&
    has_bounded_size<ur_cv_interfaces::srv::DetectButton_Response>::value
  >
{
};

template<>
struct is_service<ur_cv_interfaces::srv::DetectButton>
  : std::true_type
{
};

template<>
struct is_service_request<ur_cv_interfaces::srv::DetectButton_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ur_cv_interfaces::srv::DetectButton_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__TRAITS_HPP_
