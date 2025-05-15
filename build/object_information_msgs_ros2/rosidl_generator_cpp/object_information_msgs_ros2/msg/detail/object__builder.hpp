// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from object_information_msgs_ros2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__BUILDER_HPP_
#define OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "object_information_msgs_ros2/msg/detail/object__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace object_information_msgs_ros2
{

namespace msg
{

namespace builder
{

class Init_Object_size
{
public:
  explicit Init_Object_size(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  ::object_information_msgs_ros2::msg::Object size(::object_information_msgs_ros2::msg::Object::_size_type arg)
  {
    msg_.size = std::move(arg);
    return std::move(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_position
{
public:
  explicit Init_Object_position(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_size position(::object_information_msgs_ros2::msg::Object::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_Object_size(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_probability
{
public:
  explicit Init_Object_probability(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_position probability(::object_information_msgs_ros2::msg::Object::_probability_type arg)
  {
    msg_.probability = std::move(arg);
    return Init_Object_position(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_label
{
public:
  explicit Init_Object_label(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_probability label(::object_information_msgs_ros2::msg::Object::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_Object_probability(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_object_sequence
{
public:
  explicit Init_Object_object_sequence(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_label object_sequence(::object_information_msgs_ros2::msg::Object::_object_sequence_type arg)
  {
    msg_.object_sequence = std::move(arg);
    return Init_Object_label(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_object_total
{
public:
  explicit Init_Object_object_total(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_object_sequence object_total(::object_information_msgs_ros2::msg::Object::_object_total_type arg)
  {
    msg_.object_total = std::move(arg);
    return Init_Object_object_sequence(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_detect_sequence
{
public:
  explicit Init_Object_detect_sequence(::object_information_msgs_ros2::msg::Object & msg)
  : msg_(msg)
  {}
  Init_Object_object_total detect_sequence(::object_information_msgs_ros2::msg::Object::_detect_sequence_type arg)
  {
    msg_.detect_sequence = std::move(arg);
    return Init_Object_object_total(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

class Init_Object_header
{
public:
  Init_Object_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Object_detect_sequence header(::object_information_msgs_ros2::msg::Object::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Object_detect_sequence(msg_);
  }

private:
  ::object_information_msgs_ros2::msg::Object msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::object_information_msgs_ros2::msg::Object>()
{
  return object_information_msgs_ros2::msg::builder::Init_Object_header();
}

}  // namespace object_information_msgs_ros2

#endif  // OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__BUILDER_HPP_
