// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from village_interfaces:srv/SellNovel.idl
// generated code does not contain a copyright notice
#include "village_interfaces/srv/detail/sell_novel__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
village_interfaces__srv__SellNovel_Request__init(village_interfaces__srv__SellNovel_Request * msg)
{
  if (!msg) {
    return false;
  }
  // money
  return true;
}

void
village_interfaces__srv__SellNovel_Request__fini(village_interfaces__srv__SellNovel_Request * msg)
{
  if (!msg) {
    return;
  }
  // money
}

bool
village_interfaces__srv__SellNovel_Request__are_equal(const village_interfaces__srv__SellNovel_Request * lhs, const village_interfaces__srv__SellNovel_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // money
  if (lhs->money != rhs->money) {
    return false;
  }
  return true;
}

bool
village_interfaces__srv__SellNovel_Request__copy(
  const village_interfaces__srv__SellNovel_Request * input,
  village_interfaces__srv__SellNovel_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // money
  output->money = input->money;
  return true;
}

village_interfaces__srv__SellNovel_Request *
village_interfaces__srv__SellNovel_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Request * msg = (village_interfaces__srv__SellNovel_Request *)allocator.allocate(sizeof(village_interfaces__srv__SellNovel_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interfaces__srv__SellNovel_Request));
  bool success = village_interfaces__srv__SellNovel_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interfaces__srv__SellNovel_Request__destroy(village_interfaces__srv__SellNovel_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interfaces__srv__SellNovel_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interfaces__srv__SellNovel_Request__Sequence__init(village_interfaces__srv__SellNovel_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Request * data = NULL;

  if (size) {
    data = (village_interfaces__srv__SellNovel_Request *)allocator.zero_allocate(size, sizeof(village_interfaces__srv__SellNovel_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interfaces__srv__SellNovel_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interfaces__srv__SellNovel_Request__fini(&data[i - 1]);
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
village_interfaces__srv__SellNovel_Request__Sequence__fini(village_interfaces__srv__SellNovel_Request__Sequence * array)
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
      village_interfaces__srv__SellNovel_Request__fini(&array->data[i]);
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

village_interfaces__srv__SellNovel_Request__Sequence *
village_interfaces__srv__SellNovel_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Request__Sequence * array = (village_interfaces__srv__SellNovel_Request__Sequence *)allocator.allocate(sizeof(village_interfaces__srv__SellNovel_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interfaces__srv__SellNovel_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interfaces__srv__SellNovel_Request__Sequence__destroy(village_interfaces__srv__SellNovel_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interfaces__srv__SellNovel_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interfaces__srv__SellNovel_Request__Sequence__are_equal(const village_interfaces__srv__SellNovel_Request__Sequence * lhs, const village_interfaces__srv__SellNovel_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interfaces__srv__SellNovel_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interfaces__srv__SellNovel_Request__Sequence__copy(
  const village_interfaces__srv__SellNovel_Request__Sequence * input,
  village_interfaces__srv__SellNovel_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interfaces__srv__SellNovel_Request);
    village_interfaces__srv__SellNovel_Request * data =
      (village_interfaces__srv__SellNovel_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interfaces__srv__SellNovel_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          village_interfaces__srv__SellNovel_Request__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interfaces__srv__SellNovel_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `novels`
#include "rosidl_runtime_c/string_functions.h"

bool
village_interfaces__srv__SellNovel_Response__init(village_interfaces__srv__SellNovel_Response * msg)
{
  if (!msg) {
    return false;
  }
  // novels
  if (!rosidl_runtime_c__String__Sequence__init(&msg->novels, 0)) {
    village_interfaces__srv__SellNovel_Response__fini(msg);
    return false;
  }
  return true;
}

void
village_interfaces__srv__SellNovel_Response__fini(village_interfaces__srv__SellNovel_Response * msg)
{
  if (!msg) {
    return;
  }
  // novels
  rosidl_runtime_c__String__Sequence__fini(&msg->novels);
}

bool
village_interfaces__srv__SellNovel_Response__are_equal(const village_interfaces__srv__SellNovel_Response * lhs, const village_interfaces__srv__SellNovel_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // novels
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->novels), &(rhs->novels)))
  {
    return false;
  }
  return true;
}

bool
village_interfaces__srv__SellNovel_Response__copy(
  const village_interfaces__srv__SellNovel_Response * input,
  village_interfaces__srv__SellNovel_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // novels
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->novels), &(output->novels)))
  {
    return false;
  }
  return true;
}

village_interfaces__srv__SellNovel_Response *
village_interfaces__srv__SellNovel_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Response * msg = (village_interfaces__srv__SellNovel_Response *)allocator.allocate(sizeof(village_interfaces__srv__SellNovel_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(village_interfaces__srv__SellNovel_Response));
  bool success = village_interfaces__srv__SellNovel_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
village_interfaces__srv__SellNovel_Response__destroy(village_interfaces__srv__SellNovel_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    village_interfaces__srv__SellNovel_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
village_interfaces__srv__SellNovel_Response__Sequence__init(village_interfaces__srv__SellNovel_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Response * data = NULL;

  if (size) {
    data = (village_interfaces__srv__SellNovel_Response *)allocator.zero_allocate(size, sizeof(village_interfaces__srv__SellNovel_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = village_interfaces__srv__SellNovel_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        village_interfaces__srv__SellNovel_Response__fini(&data[i - 1]);
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
village_interfaces__srv__SellNovel_Response__Sequence__fini(village_interfaces__srv__SellNovel_Response__Sequence * array)
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
      village_interfaces__srv__SellNovel_Response__fini(&array->data[i]);
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

village_interfaces__srv__SellNovel_Response__Sequence *
village_interfaces__srv__SellNovel_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  village_interfaces__srv__SellNovel_Response__Sequence * array = (village_interfaces__srv__SellNovel_Response__Sequence *)allocator.allocate(sizeof(village_interfaces__srv__SellNovel_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = village_interfaces__srv__SellNovel_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
village_interfaces__srv__SellNovel_Response__Sequence__destroy(village_interfaces__srv__SellNovel_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    village_interfaces__srv__SellNovel_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
village_interfaces__srv__SellNovel_Response__Sequence__are_equal(const village_interfaces__srv__SellNovel_Response__Sequence * lhs, const village_interfaces__srv__SellNovel_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!village_interfaces__srv__SellNovel_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
village_interfaces__srv__SellNovel_Response__Sequence__copy(
  const village_interfaces__srv__SellNovel_Response__Sequence * input,
  village_interfaces__srv__SellNovel_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(village_interfaces__srv__SellNovel_Response);
    village_interfaces__srv__SellNovel_Response * data =
      (village_interfaces__srv__SellNovel_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!village_interfaces__srv__SellNovel_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          village_interfaces__srv__SellNovel_Response__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!village_interfaces__srv__SellNovel_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
