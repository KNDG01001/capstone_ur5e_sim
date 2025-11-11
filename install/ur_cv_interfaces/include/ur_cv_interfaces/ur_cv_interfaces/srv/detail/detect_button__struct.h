// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ur_cv_interfaces:srv/DetectButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_H_
#define UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/DetectButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__srv__DetectButton_Request
{
  rosidl_runtime_c__String label;
} ur_cv_interfaces__srv__DetectButton_Request;

// Struct for a sequence of ur_cv_interfaces__srv__DetectButton_Request.
typedef struct ur_cv_interfaces__srv__DetectButton_Request__Sequence
{
  ur_cv_interfaces__srv__DetectButton_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__srv__DetectButton_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/DetectButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__srv__DetectButton_Response
{
  bool success;
  int32_t u;
  int32_t v;
  float confidence;
} ur_cv_interfaces__srv__DetectButton_Response;

// Struct for a sequence of ur_cv_interfaces__srv__DetectButton_Response.
typedef struct ur_cv_interfaces__srv__DetectButton_Response__Sequence
{
  ur_cv_interfaces__srv__DetectButton_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__srv__DetectButton_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__STRUCT_H_
