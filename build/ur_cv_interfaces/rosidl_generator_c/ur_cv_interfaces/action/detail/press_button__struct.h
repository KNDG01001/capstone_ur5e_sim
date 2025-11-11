// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ur_cv_interfaces:action/PressButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__STRUCT_H_
#define UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'button'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_Goal
{
  rosidl_runtime_c__String button;
} ur_cv_interfaces__action__PressButton_Goal;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_Goal.
typedef struct ur_cv_interfaces__action__PressButton_Goal__Sequence
{
  ur_cv_interfaces__action__PressButton_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_Goal__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_Result
{
  bool success;
  rosidl_runtime_c__String message;
} ur_cv_interfaces__action__PressButton_Result;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_Result.
typedef struct ur_cv_interfaces__action__PressButton_Result__Sequence
{
  ur_cv_interfaces__action__PressButton_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_Result__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'status'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_Feedback
{
  rosidl_runtime_c__String status;
} ur_cv_interfaces__action__PressButton_Feedback;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_Feedback.
typedef struct ur_cv_interfaces__action__PressButton_Feedback__Sequence
{
  ur_cv_interfaces__action__PressButton_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_Feedback__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "ur_cv_interfaces/action/detail/press_button__struct.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  ur_cv_interfaces__action__PressButton_Goal goal;
} ur_cv_interfaces__action__PressButton_SendGoal_Request;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_SendGoal_Request.
typedef struct ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence
{
  ur_cv_interfaces__action__PressButton_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} ur_cv_interfaces__action__PressButton_SendGoal_Response;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_SendGoal_Response.
typedef struct ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence
{
  ur_cv_interfaces__action__PressButton_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} ur_cv_interfaces__action__PressButton_GetResult_Request;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_GetResult_Request.
typedef struct ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence
{
  ur_cv_interfaces__action__PressButton_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "ur_cv_interfaces/action/detail/press_button__struct.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_GetResult_Response
{
  int8_t status;
  ur_cv_interfaces__action__PressButton_Result result;
} ur_cv_interfaces__action__PressButton_GetResult_Response;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_GetResult_Response.
typedef struct ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence
{
  ur_cv_interfaces__action__PressButton_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "ur_cv_interfaces/action/detail/press_button__struct.h"

/// Struct defined in action/PressButton in the package ur_cv_interfaces.
typedef struct ur_cv_interfaces__action__PressButton_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  ur_cv_interfaces__action__PressButton_Feedback feedback;
} ur_cv_interfaces__action__PressButton_FeedbackMessage;

// Struct for a sequence of ur_cv_interfaces__action__PressButton_FeedbackMessage.
typedef struct ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence
{
  ur_cv_interfaces__action__PressButton_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__STRUCT_H_
