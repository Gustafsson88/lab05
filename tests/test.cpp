// Copyright 2021 Alexandr Guchkov <firer.a45@gmail.ru>

#include <gtest/gtest.h>
#include "Stack.hpp"
#include "NoCopyStack.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(Test_push, Push_rvalue){
  Stack<int> first;
  first.push(5);
  EXPECT_EQ(first.head(), 5);
}

TEST(Test_push, Push_lvalue){
  Stack<double> second;
  double a = 1.1;
  second.push(a);
  EXPECT_EQ(second.head(), 1.1);
}

TEST(Test_stack, Func_pop){
  Stack<int> first;
  first.push(7);
  first.pop();
  EXPECT_THROW(first.head(),std::runtime_error);
  first.push(5);
  first.push(6);
  first.pop();
  EXPECT_EQ(first.head(), 5);
}

TEST(Test_stack, Test_move){
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
}

TEST(Test_stack, Test_copy) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

template <typename T>
struct Struct
{
  T data1;
  T data2;
  T data3;
};
TEST(NoCopyStack, Test_Push_Pop){
  NoCopyStack<int> first;
  first.push(5);
  EXPECT_EQ(first.head(), 5);
  EXPECT_EQ(first.pop(),5);

  Struct<int> test_struct{1, 2, 3};
  NoCopyStack<Struct<int>>second;
  second.push(std::move(test_struct));
  Struct<int> test_struct2 = second.pop();
  EXPECT_EQ(test_struct2.data1, test_struct.data1);
  EXPECT_EQ(test_struct2.data3, test_struct.data3);
}

TEST(NoCopyStack, Test_push_emplace_and_head) {
  NoCopyStack<Struct<int>> first;
  Struct<int> test_struct1 {1, 2, 3};
  first.push_emplace(1, 2, 3);
  Struct<int> test_struct2 = first.head();
  EXPECT_EQ(test_struct2.data2, test_struct1.data2);
}

TEST(NoCopyableStack, Is_Move) {
  EXPECT_TRUE(std::is_move_constructible
                  <NoCopyStack<Struct<std::string>>>::value);
}

TEST(NoCopyableStack, Is_Copy) {
  EXPECT_FALSE(std::is_copy_constructible
                   <NoCopyStack<Struct<int>>>::value);
  EXPECT_FALSE(std::is_copy_assignable
                   <NoCopyStack<Struct<int>>>::value);
}
