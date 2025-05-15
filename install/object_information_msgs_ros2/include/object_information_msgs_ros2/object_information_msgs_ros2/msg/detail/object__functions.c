// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from object_information_msgs_ros2:msg/Object.idl
// generated code does not contain a copyright notice
#include "object_information_msgs_ros2/msg/detail/object__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `label`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/pose__functions.h"
// Member `size`
#include "geometry_msgs/msg/detail/vector3__functions.h"

bool
object_information_msgs_ros2__msg__Object__init(object_information_msgs_ros2__msg__Object * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    object_information_msgs_ros2__msg__Object__fini(msg);
    return false;
  }
  // detect_sequence
  // object_total
  // object_sequence
  // label
  if (!rosidl_runtime_c__String__init(&msg->label)) {
    object_information_msgs_ros2__msg__Object__fini(msg);
    return false;
  }
  // probability
  // position
  if (!geometry_msgs__msg__Pose__init(&msg->position)) {
    object_information_msgs_ros2__msg__Object__fini(msg);
    return false;
  }
  // size
  if (!geometry_msgs__msg__Vector3__init(&msg->size)) {
    object_information_msgs_ros2__msg__Object__fini(msg);
    return false;
  }
  return true;
}

void
object_information_msgs_ros2__msg__Object__fini(object_information_msgs_ros2__msg__Object * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // detect_sequence
  // object_total
  // object_sequence
  // label
  rosidl_runtime_c__String__fini(&msg->label);
  // probability
  // position
  geometry_msgs__msg__Pose__fini(&msg->position);
  // size
  geometry_msgs__msg__Vector3__fini(&msg->size);
}

bool
object_information_msgs_ros2__msg__Object__are_equal(const object_information_msgs_ros2__msg__Object * lhs, const object_information_msgs_ros2__msg__Object * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // detect_sequence
  if (lhs->detect_sequence != rhs->detect_sequence) {
    return false;
  }
  // object_total
  if (lhs->object_total != rhs->object_total) {
    return false;
  }
  // object_sequence
  if (lhs->object_sequence != rhs->object_sequence) {
    return false;
  }
  // label
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->label), &(rhs->label)))
  {
    return false;
  }
  // probability
  if (lhs->probability != rhs->probability) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // size
  if (!geometry_msgs__msg__Vector3__are_equal(
      &(lhs->size), &(rhs->size)))
  {
    return false;
  }
  return true;
}

bool
object_information_msgs_ros2__msg__Object__copy(
  const object_information_msgs_ros2__msg__Object * input,
  object_information_msgs_ros2__msg__Object * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // detect_sequence
  output->detect_sequence = input->detect_sequence;
  // object_total
  output->object_total = input->object_total;
  // object_sequence
  output->object_sequence = input->object_sequence;
  // label
  if (!rosidl_runtime_c__String__copy(
      &(input->label), &(output->label)))
  {
    return false;
  }
  // probability
  output->probability = input->probability;
  // position
  if (!geometry_msgs__msg__Pose__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // size
  if (!geometry_msgs__msg__Vector3__copy(
      &(input->size), &(output->size)))
  {
    return false;
  }
  return true;
}

object_information_msgs_ros2__msg__Object *
object_information_msgs_ros2__msg__Object__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  object_information_msgs_ros2__msg__Object * msg = (object_information_msgs_ros2__msg__Object *)allocator.allocate(sizeof(object_information_msgs_ros2__msg__Object), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(object_information_msgs_ros2__msg__Object));
  bool success = object_information_msgs_ros2__msg__Object__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
object_information_msgs_ros2__msg__Object__destroy(object_information_msgs_ros2__msg__Object * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    object_information_msgs_ros2__msg__Object__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
object_information_msgs_ros2__msg__Object__Sequence__init(object_information_msgs_ros2__msg__Object__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  object_information_msgs_ros2__msg__Object * data = NULL;

  if (size) {
    data = (object_information_msgs_ros2__msg__Object *)allocator.zero_allocate(size, sizeof(object_information_msgs_ros2__msg__Object), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = object_information_msgs_ros2__msg__Object__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        object_information_msgs_ros2__msg__Object__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
object_information_msgs_ros2__msg__Object__Sequence__fini(object_information_msgs_ros2__msg__Object__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      object_information_msgs_ros2__msg__Object__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

object_information_msgs_ros2__msg__Object__Sequence *
object_information_msgs_ros2__msg__Object__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  object_information_msgs_ros2__msg__Object__Sequence * array = (object_information_msgs_ros2__msg__Object__Sequence *)allocator.allocate(sizeof(object_information_msgs_ros2__msg__Object__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = object_information_msgs_ros2__msg__Object__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
object_information_msgs_ros2__msg__Object__Sequence__destroy(object_information_msgs_ros2__msg__Object__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    object_information_msgs_ros2__msg__Object__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
object_information_msgs_ros2__msg__Object__Sequence__are_equal(const object_information_msgs_ros2__msg__Object__Sequence * lhs, const object_information_msgs_ros2__msg__Object__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!object_information_msgs_ros2__msg__Object__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
object_information_msgs_ros2__msg__Object__Sequence__copy(
  const object_information_msgs_ros2__msg__Object__Sequence * input,
  object_information_msgs_ros2__msg__Object__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(object_information_msgs_ros2__msg__Object);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    object_information_msgs_ros2__msg__Object * data =
      (object_information_msgs_ros2__msg__Object *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!object_information_msgs_ros2__msg__Object__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          object_information_msgs_ros2__msg__Object__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!object_information_msgs_ros2__msg__Object__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
