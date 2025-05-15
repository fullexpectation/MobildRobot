// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from object_information_msgs_ros2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_H_
#define OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'label'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/pose__struct.h"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.h"

/// Struct defined in msg/Object in the package object_information_msgs_ros2.
/**
  * bounding box with marker positions
 */
typedef struct object_information_msgs_ros2__msg__Object
{
  std_msgs__msg__Header header;
  uint64_t detect_sequence;
  uint16_t object_total;
  uint16_t object_sequence;
  rosidl_runtime_c__String label;
  float probability;
  geometry_msgs__msg__Pose position;
  geometry_msgs__msg__Vector3 size;
} object_information_msgs_ros2__msg__Object;

// Struct for a sequence of object_information_msgs_ros2__msg__Object.
typedef struct object_information_msgs_ros2__msg__Object__Sequence
{
  object_information_msgs_ros2__msg__Object * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} object_information_msgs_ros2__msg__Object__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_H_
