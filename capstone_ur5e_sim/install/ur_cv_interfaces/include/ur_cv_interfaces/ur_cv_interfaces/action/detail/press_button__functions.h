// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ur_cv_interfaces:action/PressButton.idl
// generated code does not contain a copyright notice

#ifndef UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__FUNCTIONS_H_
#define UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ur_cv_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "ur_cv_interfaces/action/detail/press_button__struct.h"

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_Goal
 * )) before or use
 * ur_cv_interfaces__action__PressButton_Goal__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Goal__init(ur_cv_interfaces__action__PressButton_Goal * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Goal__fini(ur_cv_interfaces__action__PressButton_Goal * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_Goal__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Goal *
ur_cv_interfaces__action__PressButton_Goal__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Goal__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Goal__destroy(ur_cv_interfaces__action__PressButton_Goal * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Goal__are_equal(const ur_cv_interfaces__action__PressButton_Goal * lhs, const ur_cv_interfaces__action__PressButton_Goal * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_Goal__copy(
  const ur_cv_interfaces__action__PressButton_Goal * input,
  ur_cv_interfaces__action__PressButton_Goal * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_Goal__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Goal__Sequence__init(ur_cv_interfaces__action__PressButton_Goal__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Goal__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Goal__Sequence__fini(ur_cv_interfaces__action__PressButton_Goal__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_Goal__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Goal__Sequence *
ur_cv_interfaces__action__PressButton_Goal__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Goal__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Goal__Sequence__destroy(ur_cv_interfaces__action__PressButton_Goal__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Goal__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_Goal__Sequence * lhs, const ur_cv_interfaces__action__PressButton_Goal__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_Goal__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_Goal__Sequence * input,
  ur_cv_interfaces__action__PressButton_Goal__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_Result
 * )) before or use
 * ur_cv_interfaces__action__PressButton_Result__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Result__init(ur_cv_interfaces__action__PressButton_Result * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Result__fini(ur_cv_interfaces__action__PressButton_Result * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_Result__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Result *
ur_cv_interfaces__action__PressButton_Result__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Result__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Result__destroy(ur_cv_interfaces__action__PressButton_Result * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Result__are_equal(const ur_cv_interfaces__action__PressButton_Result * lhs, const ur_cv_interfaces__action__PressButton_Result * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_Result__copy(
  const ur_cv_interfaces__action__PressButton_Result * input,
  ur_cv_interfaces__action__PressButton_Result * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_Result__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Result__Sequence__init(ur_cv_interfaces__action__PressButton_Result__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Result__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Result__Sequence__fini(ur_cv_interfaces__action__PressButton_Result__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_Result__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Result__Sequence *
ur_cv_interfaces__action__PressButton_Result__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Result__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Result__Sequence__destroy(ur_cv_interfaces__action__PressButton_Result__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Result__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_Result__Sequence * lhs, const ur_cv_interfaces__action__PressButton_Result__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_Result__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_Result__Sequence * input,
  ur_cv_interfaces__action__PressButton_Result__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_Feedback
 * )) before or use
 * ur_cv_interfaces__action__PressButton_Feedback__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Feedback__init(ur_cv_interfaces__action__PressButton_Feedback * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Feedback__fini(ur_cv_interfaces__action__PressButton_Feedback * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_Feedback__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Feedback *
ur_cv_interfaces__action__PressButton_Feedback__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Feedback__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Feedback__destroy(ur_cv_interfaces__action__PressButton_Feedback * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Feedback__are_equal(const ur_cv_interfaces__action__PressButton_Feedback * lhs, const ur_cv_interfaces__action__PressButton_Feedback * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_Feedback__copy(
  const ur_cv_interfaces__action__PressButton_Feedback * input,
  ur_cv_interfaces__action__PressButton_Feedback * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_Feedback__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Feedback__Sequence__init(ur_cv_interfaces__action__PressButton_Feedback__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Feedback__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Feedback__Sequence__fini(ur_cv_interfaces__action__PressButton_Feedback__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_Feedback__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_Feedback__Sequence *
ur_cv_interfaces__action__PressButton_Feedback__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_Feedback__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_Feedback__Sequence__destroy(ur_cv_interfaces__action__PressButton_Feedback__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_Feedback__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_Feedback__Sequence * lhs, const ur_cv_interfaces__action__PressButton_Feedback__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_Feedback__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_Feedback__Sequence * input,
  ur_cv_interfaces__action__PressButton_Feedback__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_SendGoal_Request
 * )) before or use
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Request__init(ur_cv_interfaces__action__PressButton_SendGoal_Request * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Request__fini(ur_cv_interfaces__action__PressButton_SendGoal_Request * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_SendGoal_Request *
ur_cv_interfaces__action__PressButton_SendGoal_Request__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Request__destroy(ur_cv_interfaces__action__PressButton_SendGoal_Request * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Request__are_equal(const ur_cv_interfaces__action__PressButton_SendGoal_Request * lhs, const ur_cv_interfaces__action__PressButton_SendGoal_Request * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_SendGoal_Request__copy(
  const ur_cv_interfaces__action__PressButton_SendGoal_Request * input,
  ur_cv_interfaces__action__PressButton_SendGoal_Request * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__init(ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__fini(ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence *
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__destroy(ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * lhs, const ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * input,
  ur_cv_interfaces__action__PressButton_SendGoal_Request__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_SendGoal_Response
 * )) before or use
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Response__init(ur_cv_interfaces__action__PressButton_SendGoal_Response * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Response__fini(ur_cv_interfaces__action__PressButton_SendGoal_Response * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_SendGoal_Response *
ur_cv_interfaces__action__PressButton_SendGoal_Response__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Response__destroy(ur_cv_interfaces__action__PressButton_SendGoal_Response * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Response__are_equal(const ur_cv_interfaces__action__PressButton_SendGoal_Response * lhs, const ur_cv_interfaces__action__PressButton_SendGoal_Response * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_SendGoal_Response__copy(
  const ur_cv_interfaces__action__PressButton_SendGoal_Response * input,
  ur_cv_interfaces__action__PressButton_SendGoal_Response * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__init(ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__fini(ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence *
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__destroy(ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * lhs, const ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * input,
  ur_cv_interfaces__action__PressButton_SendGoal_Response__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_GetResult_Request
 * )) before or use
 * ur_cv_interfaces__action__PressButton_GetResult_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Request__init(ur_cv_interfaces__action__PressButton_GetResult_Request * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Request__fini(ur_cv_interfaces__action__PressButton_GetResult_Request * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_GetResult_Request *
ur_cv_interfaces__action__PressButton_GetResult_Request__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Request__destroy(ur_cv_interfaces__action__PressButton_GetResult_Request * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Request__are_equal(const ur_cv_interfaces__action__PressButton_GetResult_Request * lhs, const ur_cv_interfaces__action__PressButton_GetResult_Request * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_GetResult_Request__copy(
  const ur_cv_interfaces__action__PressButton_GetResult_Request * input,
  ur_cv_interfaces__action__PressButton_GetResult_Request * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__init(ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__fini(ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence *
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__destroy(ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * lhs, const ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * input,
  ur_cv_interfaces__action__PressButton_GetResult_Request__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_GetResult_Response
 * )) before or use
 * ur_cv_interfaces__action__PressButton_GetResult_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Response__init(ur_cv_interfaces__action__PressButton_GetResult_Response * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Response__fini(ur_cv_interfaces__action__PressButton_GetResult_Response * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_GetResult_Response *
ur_cv_interfaces__action__PressButton_GetResult_Response__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Response__destroy(ur_cv_interfaces__action__PressButton_GetResult_Response * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Response__are_equal(const ur_cv_interfaces__action__PressButton_GetResult_Response * lhs, const ur_cv_interfaces__action__PressButton_GetResult_Response * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_GetResult_Response__copy(
  const ur_cv_interfaces__action__PressButton_GetResult_Response * input,
  ur_cv_interfaces__action__PressButton_GetResult_Response * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__init(ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__fini(ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence *
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__destroy(ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * lhs, const ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * input,
  ur_cv_interfaces__action__PressButton_GetResult_Response__Sequence * output);

/// Initialize action/PressButton message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ur_cv_interfaces__action__PressButton_FeedbackMessage
 * )) before or use
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_FeedbackMessage__init(ur_cv_interfaces__action__PressButton_FeedbackMessage * msg);

/// Finalize action/PressButton message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_FeedbackMessage__fini(ur_cv_interfaces__action__PressButton_FeedbackMessage * msg);

/// Create action/PressButton message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_FeedbackMessage *
ur_cv_interfaces__action__PressButton_FeedbackMessage__create();

/// Destroy action/PressButton message.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_FeedbackMessage__destroy(ur_cv_interfaces__action__PressButton_FeedbackMessage * msg);

/// Check for action/PressButton message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_FeedbackMessage__are_equal(const ur_cv_interfaces__action__PressButton_FeedbackMessage * lhs, const ur_cv_interfaces__action__PressButton_FeedbackMessage * rhs);

/// Copy a action/PressButton message.
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
ur_cv_interfaces__action__PressButton_FeedbackMessage__copy(
  const ur_cv_interfaces__action__PressButton_FeedbackMessage * input,
  ur_cv_interfaces__action__PressButton_FeedbackMessage * output);

/// Initialize array of action/PressButton messages.
/**
 * It allocates the memory for the number of elements and calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__init(ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * array, size_t size);

/// Finalize array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__fini(ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * array);

/// Create array of action/PressButton messages.
/**
 * It allocates the memory for the array and calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence *
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__create(size_t size);

/// Destroy array of action/PressButton messages.
/**
 * It calls
 * ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
void
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__destroy(ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * array);

/// Check for action/PressButton message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ur_cv_interfaces
bool
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__are_equal(const ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * lhs, const ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * rhs);

/// Copy an array of action/PressButton messages.
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
ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence__copy(
  const ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * input,
  ur_cv_interfaces__action__PressButton_FeedbackMessage__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // UR_CV_INTERFACES__ACTION__DETAIL__PRESS_BUTTON__FUNCTIONS_H_
