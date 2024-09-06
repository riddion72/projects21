#include "test_header.h"

TEST(s21_stack, test1) {
  s21::stack<int> my_stack;
  std::stack<int> lib_stack;
  my_stack.push(3);
  my_stack.push(5);
  lib_stack.push(3);
  lib_stack.push(5);
  ASSERT_EQ(lib_stack.top(), my_stack.top());
  ASSERT_EQ(lib_stack.size(), my_stack.size());
}

TEST(s21_stack, test2) {
  s21::stack<int> my_stack({1, 2, 3, 4});
  std::stack<int> lib_stack({1, 2, 3, 4});
  ASSERT_EQ(lib_stack.size(), my_stack.size());
  ASSERT_EQ(lib_stack.top(), my_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(lib_stack.top(), my_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(2, my_stack.top());
  ASSERT_EQ(2, lib_stack.top());
}

TEST(s21_stack, test3) {
  s21::stack<int> my_stack;
  my_stack.push(500);
  my_stack.push(1000);
  std::stack<int> lib_stack;
  lib_stack.push(500);
  lib_stack.push(1000);
  ASSERT_EQ(lib_stack.size(), my_stack.size());
  ASSERT_EQ(lib_stack.top(), my_stack.top());
}

TEST(s21_stack, test4) {
  s21::stack<int> test_stack;
  test_stack.push(500);
  test_stack.push(1000);
  s21::stack<int> my_stack = std::move(test_stack);
  std::stack<int> test_stack1;
  test_stack1.push(500);
  test_stack1.push(1000);
  std::stack<int> lib_stack = std::move(test_stack1);
  ASSERT_EQ(lib_stack.size(), my_stack.size());
  ASSERT_EQ(lib_stack.top(), my_stack.top());
  ASSERT_EQ(0, test_stack.size());
  ASSERT_EQ(0, test_stack1.size());
}

TEST(s21_stack, test5) {
  s21::stack<int> my_stack({1, 2, 3, 4});
  std::stack<int> lib_stack({1, 2, 3, 4});
  s21::stack<int> to_swap({15, 125, 20});
  std::stack<int> to_swap1({15, 125, 20});
  my_stack.swap(to_swap);
  lib_stack.swap(to_swap1);
  ASSERT_EQ(3, my_stack.size());
  ASSERT_EQ(3, lib_stack.size());
  ASSERT_EQ(20, my_stack.top());
  ASSERT_EQ(20, lib_stack.top());
  ASSERT_EQ(4, to_swap.size());
  ASSERT_EQ(4, to_swap1.size());
  ASSERT_EQ(4, to_swap.top());
  ASSERT_EQ(4, to_swap1.top());
}

TEST(s21_stack, insert_maney1) {
  s21::stack<int> my_stack({1, 2, 3, 4});
  std::stack<int> lib_stack({1, 2, 3, 4, 5, 6, 7, 8});
  my_stack.insert_many_front(5, 6, 7, 8);
  ASSERT_EQ(my_stack.size(), lib_stack.size());
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
}

TEST(s21_stack, insert_maney2) {
  s21::stack<int> my_stack({1, 2, 3, 4});
  std::stack<int> lib_stack({1, 2, 3, 4, 5});
  my_stack.insert_many_front(5);
  ASSERT_EQ(my_stack.size(), lib_stack.size());
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
}

TEST(s21_stack, insert_maney3) {
  s21::stack<int> my_stack({1, 2, 3, 4});
  std::stack<int> lib_stack({1, 2, 3, 4});
  my_stack.insert_many_front();
  ASSERT_EQ(my_stack.size(), lib_stack.size());
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
  lib_stack.pop();
  my_stack.pop();
  ASSERT_EQ(my_stack.top(), lib_stack.top());
}
