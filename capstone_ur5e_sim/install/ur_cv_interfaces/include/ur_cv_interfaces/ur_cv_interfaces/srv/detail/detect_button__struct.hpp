// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ur_cv_interfaces:srv/DetectButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_HPP_
#define UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__ur_cv_interfaces__srv__DetectButton_Request __attribute__((deprecated))
#else
# define DEPRECATED__ur_cv_interfaces__srv__DetectButton_Request __declspec(deprecated)
#endif

namespace ur_cv_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetectButton_Request_
{
  using Type = DetectButton_Request_<ContainerAllocator>;

  explicit DetectButton_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
    }
  }

  explicit DetectButton_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : label(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->label = "";
    }
  }

  // field types and members
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;

  // setters for named parameter idiom
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ur_cv_interfaces__srv__DetectButton_Request
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ur_cv_interfaces__srv__DetectButton_Request
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectButton_Request_ & other) const
  {
    if (this->label != other.label) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectButton_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectButton_Request_

// alias to use template instance with default allocator
using DetectButton_Request =
  ur_cv_interfaces::srv::DetectButton_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ur_cv_interfaces


#ifndef _WIN32
# define DEPRECATED__ur_cv_interfaces__srv__DetectButton_Response __attribute__((deprecated))
#else
# define DEPRECATED__ur_cv_interfaces__srv__DetectButton_Response __declspec(deprecated)
#endif

namespace ur_cv_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct DetectButton_Response_
{
  using Type = DetectButton_Response_<ContainerAllocator>;

  explicit DetectButton_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->u = 0l;
      this->v = 0l;
      this->confidence = 0.0f;
    }
  }

  explicit DetectButton_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->u = 0l;
      this->v = 0l;
      this->confidence = 0.0f;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _u_type =
    int32_t;
  _u_type u;
  using _v_type =
    int32_t;
  _v_type v;
  using _confidence_type =
    float;
  _confidence_type confidence;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__u(
    const int32_t & _arg)
  {
    this->u = _arg;
    return *this;
  }
  Type & set__v(
    const int32_t & _arg)
  {
    this->v = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ur_cv_interfaces__srv__DetectButton_Response
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ur_cv_interfaces__srv__DetectButton_Response
    std::shared_ptr<ur_cv_interfaces::srv::DetectButton_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DetectButton_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->u != other.u) {
      return false;
    }
    if (this->v != other.v) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    return true;
  }
  bool operator!=(const DetectButton_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DetectButton_Response_

// alias to use template instance with default allocator
using DetectButton_Response =
  ur_cv_interfaces::srv::DetectButton_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ur_cv_interfaces

namespace ur_cv_interfaces
{

namespace srv
{

struct DetectButton
{
  using Request = ur_cv_interfaces::srv::DetectButton_Request;
  using Response = ur_cv_interfaces::srv::DetectButton_Response;
};

}  // namespace srv

}  // namespace ur_cv_interfaces

#endif  // UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_HPP_
