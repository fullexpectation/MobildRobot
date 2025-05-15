// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from object_information_msgs_ros2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__TRAITS_HPP_
#define OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "object_information_msgs_ros2/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/pose__traits.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace object_information_msgs_ros2
{

namespace msg
{

inline void to_flow_style_yaml(
  const Object & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: detect_sequence
  {
    out << "detect_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.detect_sequence, out);
    out << ", ";
  }

  // member: object_total
  {
    out << "object_total: ";
    rosidl_generator_traits::value_to_yaml(msg.object_total, out);
    out << ", ";
  }

  // member: object_sequence
  {
    out << "object_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.object_sequence, out);
    out << ", ";
  }

  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: probability
  {
    out << "probability: ";
    rosidl_generator_traits::value_to_yaml(msg.probability, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: size
  {
    out << "size: ";
    to_flow_style_yaml(msg.size, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: detect_sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detect_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.detect_sequence, out);
    out << "\n";
  }

  // member: object_total
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_total: ";
    rosidl_generator_traits::value_to_yaml(msg.object_total, out);
    out << "\n";
  }

  // member: object_sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "object_sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.object_sequence, out);
    out << "\n";
  }

  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }

  // member: probability
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "probability: ";
    rosidl_generator_traits::value_to_yaml(msg.probability, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: size
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size:\n";
    to_block_style_yaml(msg.size, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Object & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace object_information_msgs_ros2

namespace rosidl_generator_traits
{

[[deprecated("use object_information_msgs_ros2::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const object_information_msgs_ros2::msg::Object & msg,
  std::ostream & out, size_t indentation = 0)
{
  object_information_msgs_ros2::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use object_information_msgs_ros2::msg::to_yaml() instead")]]
inline std::string to_yaml(const object_information_msgs_ros2::msg::Object & msg)
{
  return object_information_msgs_ros2::msg::to_yaml(msg);
}

template<>
inline const char * data_type<object_information_msgs_ros2::msg::Object>()
{
  return "object_information_msgs_ros2::msg::Object";
}

template<>
inline const char * name<object_information_msgs_ros2::msg::Object>()
{
  return "object_information_msgs_ros2/msg/Object";
}

template<>
struct has_fixed_size<object_information_msgs_ros2::msg::Object>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<object_information_msgs_ros2::msg::Object>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<object_information_msgs_ros2::msg::Object>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__TRAITS_HPP_
