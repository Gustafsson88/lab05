// Copyright 2021 Danil Postvaykin <postvaykin01@mail.ru>

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include<iostream>
#include<type_traits>

template <typename T>
struct  stack_element
{
  T data;
  stack_element *ptr;
};

template <typename T>
class Stack
{
 public:
  Stack()
  {
    _head = nullptr;
  }
  explicit Stack(const Stack& _stack) = delete;
  Stack(Stack&& _stack) = default;
  auto operator=(Stack&& stack) -> Stack& = default;
  ~Stack()
  {
    while (_head)
    {
      stack_element<T> *new_head = _head->ptr;
      delete _head;
      _head = new_head;
    }
  }

  void push(T&& value)
  {
    _head = new stack_element<T> {value, _head};
  }

  void push(const T& value)
  {
    _head = new stack_element<T> {value, _head};
  }

  void pop()
  {
    if(_head)
    {
      stack_element<T> *new_head = _head->ptr;
      delete _head;
      _head = new_head;
    }
    else
    {
      throw std::runtime_error("The stack is empty");
    }
  }

  const T& head() const
  {
    if(_head)
      return _head->data;
    else
      throw std::runtime_error("The stack is empty");
  }

 private:
  stack_element<T> *_head;
};

#endif // INCLUDE_STACK_HPP_
