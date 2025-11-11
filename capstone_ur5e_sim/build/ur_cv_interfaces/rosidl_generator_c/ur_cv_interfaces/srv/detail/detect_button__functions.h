// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ur_cv_interfaces:srv/DetectButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__FUNCTIONS_H_
#define UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ur_cv_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "ur_cv_interfaces/srv/detail/detect_button__struct.h"

/// Initialize srv/DetectButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__srv__DetectButton_Request
 * )) before or use
 * ur_cv_interfaces__srv__DetectButton_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__init(ur_cv_interfaces__srv__DetectButton_Request * msg);

/// Finalize srv/DetectButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Request__fini(ur_cv_interfaces__srv__DetectButton_Request * msg);

/// Create srv/DetectButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__srv__DetectButton_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__srv__DetectButton_Request *
ur_cv_interfaces__srv__DetectButton_Request__create();

/// Destroy srv/DetectButton message.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Request__destroy(ur_cv_interfaces__srv__DetectButton_Request * msg);

/// Check for srv/DetectButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__are_equal(const ur_cv_interfaces__srv__DetectButton_Request * lhs, const ur_cv_interfaces__srv__DetectButton_Request * rhs);

/// Copy a srv/DetectButton message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__copy(
  const ur_cv_interfaces__srv__DetectButton_Request * input,
  ur_cv_interfaces__srv__DetectButton_Request * output);

/// Initialize array of srv/DetectButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__srv__DetectButton_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__Sequence__init(ur_cv_interfaces__srv__DetectButton_Request__Sequence * array, size_t size);

/// Finalize array of srv/DetectButton messages.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Request__Sequence__fini(ur_cv_interfaces__srv__DetectButton_Request__Sequence * array);

/// Create array of srv/DetectButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__srv__DetectButton_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__srv__DetectButton_Request__Sequence *
ur_cv_interfaces__srv__DetectButton_Request__Sequence__create(size_t size);

/// Destroy array of srv/DetectButton messages.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Request__Sequence__destroy(ur_cv_interfaces__srv__DetectButton_Request__Sequence * array);

/// Check for srv/DetectButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__Sequence__are_equal(const ur_cv_interfaces__srv__DetectButton_Request__Sequence * lhs, const ur_cv_interfaces__srv__DetectButton_Request__Sequence * rhs);

/// Copy an array of srv/DetectButton messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Request__Sequence__copy(
  const ur_cv_interfaces__srv__DetectButton_Request__Sequence * input,
  ur_cv_interfaces__srv__DetectButton_Request__Sequence * output);

/// Initialize srv/DetectButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__srv__DetectButton_Response
 * )) before or use
 * ur_cv_interfaces__srv__DetectButton_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__init(ur_cv_interfaces__srv__DetectButton_Response * msg);

/// Finalize srv/DetectButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Response__fini(ur_cv_interfaces__srv__DetectButton_Response * msg);

/// Create srv/DetectButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__srv__DetectButton_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__srv__DetectButton_Response *
ur_cv_interfaces__srv__DetectButton_Response__create();

/// Destroy srv/DetectButton message.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Response__destroy(ur_cv_interfaces__srv__DetectButton_Response * msg);

/// Check for srv/DetectButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__are_equal(const ur_cv_interfaces__srv__DetectButton_Response * lhs, const ur_cv_interfaces__srv__DetectButton_Response * rhs);

/// Copy a srv/DetectButton message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__copy(
  const ur_cv_interfaces__srv__DetectButton_Response * input,
  ur_cv_interfaces__srv__DetectButton_Response * output);

/// Initialize array of srv/DetectButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__srv__DetectButton_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__Sequence__init(ur_cv_interfaces__srv__DetectButton_Response__Sequence * array, size_t size);

/// Finalize array of srv/DetectButton messages.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Response__Sequence__fini(ur_cv_interfaces__srv__DetectButton_Response__Sequence * array);

/// Create array of srv/DetectButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__srv__DetectButton_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__srv__DetectButton_Response__Sequence *
ur_cv_interfaces__srv__DetectButton_Response__Sequence__create(size_t size);

/// Destroy array of srv/DetectButton messages.
/**
 * It calls
 * ur_cv_interfaces__srv__DetectButton_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__srv__DetectButton_Response__Sequence__destroy(ur_cv_interfaces__srv__DetectButton_Response__Sequence * array);

/// Check for srv/DetectButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__Sequence__are_equal(const ur_cv_interfaces__srv__DetectButton_Response__Sequence * lhs, const ur_cv_interfaces__srv__DetectButton_Response__Sequence * rhs);

/// Copy an array of srv/DetectButton messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__srv__DetectButton_Response__Sequence__copy(
  const ur_cv_interfaces__srv__DetectButton_Response__Sequence * input,
  ur_cv_interfaces__srv__DetectButton_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UR_CV_INTERFACES__SRV__DETAIL__DETECT_BUTTON__FUNCTIONS_H_
