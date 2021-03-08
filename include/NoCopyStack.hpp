// Copyright 2021 Danil Postvaykin <postvaykin01@mail.ru>

#ifndef TEMPLATE_NOCOPYSTACK_HPP_
#define TEMPLATE_NOCOPYSTACK_HPP_

#include<iostream>
#include<type_traits>

template <typename T>
struct  stack_no_copy_element
{
  T data;
  stack_no_copy_element *ptr;
};

template <typename T>
class NoCopyStack
{
 public:
  NoCopyStack()
  {
    _head = nullptr;
  }
  explicit NoCopyStack(const NoCopyStack& stack) = delete;

  NoCopyStack(NoCopyStack&& stack) noexcept = default;

  auto operator = (NoCopyStack&& stack) noexcept -> NoCopyStack& = default;

  ~NoCopyStack()
  {
    while(_head)
    {
      stack_no_copy_element<T> *new_head = _head -> ptr;
      delete _head;
      _head = new_head;
    }

  }

  explicit NoCopyStack(T& _head) = delete;

  template <typename ... Args>
  void push_emplace(Args&&... value)
  {
    _head = new stack_no_copy_element<T>{{std::forward<Args>(value)...}, _head};
  }
  void push(T&& value)
  {
    _head = new stack_no_copy_element<T>{std::forward<T>(value), _head};
  }

  const T& head() const
  {
    if(_head)
      return _head->data;
    else
      throw std::runtime_error("The stack is empty");
  }

  T pop()
  {
    if (_head)
    {
      stack_no_copy_element<T> *new_head = _head->ptr;
      T data = std::move(_head->data);
      delete _head;
      _head = new_head;
      return data;
    }
    else
    {
      throw std::runtime_error("The stack is empty");
    }
  }
 private:
  stack_no_copy_element<T> *_head;
};

#endif  // TEMPLATE_NOCOPYSTACK_HPP_
