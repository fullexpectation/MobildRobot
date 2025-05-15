// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from object_information_msgs_ros2:msg/Object.idl
// generated code does not contain a copyright notice

#ifndef OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_HPP_
#define OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'position'
#include "geometry_msgs/msg/detail/pose__struct.hpp"
// Member 'size'
#include "geometry_msgs/msg/detail/vector3__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__object_information_msgs_ros2__msg__Object __attribute__((deprecated))
#else
# define DEPRECATED__object_information_msgs_ros2__msg__Object __declspec(deprecated)
#endif

namespace object_information_msgs_ros2
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Object_
{
  using Type = Object_<ContainerAllocator>;

  explicit Object_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    position(_init),
    size(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detect_sequence = 0ull;
      this->object_total = 0;
      this->object_sequence = 0;
      this->label = "";
      this->probability = 0.0f;
    }
  }

  explicit Object_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    label(_alloc),
    position(_alloc, _init),
    size(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detect_sequence = 0ull;
      this->object_total = 0;
      this->object_sequence = 0;
      this->label = "";
      this->probability = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _detect_sequence_type =
    uint64_t;
  _detect_sequence_type detect_sequence;
  using _object_total_type =
    uint16_t;
  _object_total_type object_total;
  using _object_sequence_type =
    uint16_t;
  _object_sequence_type object_sequence;
  using _label_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _label_type label;
  using _probability_type =
    float;
  _probability_type probability;
  using _position_type =
    geometry_msgs::msg::Pose_<ContainerAllocator>;
  _position_type position;
  using _size_type =
    geometry_msgs::msg::Vector3_<ContainerAllocator>;
  _size_type size;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__detect_sequence(
    const uint64_t & _arg)
  {
    this->detect_sequence = _arg;
    return *this;
  }
  Type & set__object_total(
    const uint16_t & _arg)
  {
    this->object_total = _arg;
    return *this;
  }
  Type & set__object_sequence(
    const uint16_t & _arg)
  {
    this->object_sequence = _arg;
    return *this;
  }
  Type & set__label(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->label = _arg;
    return *this;
  }
  Type & set__probability(
    const float & _arg)
  {
    this->probability = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Pose_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__size(
    const geometry_msgs::msg::Vector3_<ContainerAllocator> & _arg)
  {
    this->size = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    object_information_msgs_ros2::msg::Object_<ContainerAllocator> *;
  using ConstRawPtr =
    const object_information_msgs_ros2::msg::Object_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      object_information_msgs_ros2::msg::Object_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      object_information_msgs_ros2::msg::Object_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__object_information_msgs_ros2__msg__Object
    std::shared_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__object_information_msgs_ros2__msg__Object
    std::shared_ptr<object_information_msgs_ros2::msg::Object_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Object_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->detect_sequence != other.detect_sequence) {
      return false;
    }
    if (this->object_total != other.object_total) {
      return false;
    }
    if (this->object_sequence != other.object_sequence) {
      return false;
    }
    if (this->label != other.label) {
      return false;
    }
    if (this->probability != other.probability) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    return true;
  }
  bool operator!=(const Object_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Object_

// alias to use template instance with default allocator
using Object =
  object_information_msgs_ros2::msg::Object_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace object_information_msgs_ros2

#endif  // OBJECT_INFORMATION_MSGS_ROS2__MSG__DETAIL__OBJECT__STRUCT_HPP_
