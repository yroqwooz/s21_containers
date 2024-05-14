#include <stack>

#include "../lib/s21_containers.h"
#include "gtest/gtest.h"

TEST(StackSuite, default) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  ASSERT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackSuite, init_list) {
  std::stack<int> std_stack({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});

  ASSERT_EQ(std_stack.size(), s21_stack.size());
  for (int i = 0; i < std_stack.size(); i++) {
    ASSERT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackSuite, copy) {
  std::stack<int> std_stack({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});

  std::stack<int> std_stack_copy(std_stack);
  s21::stack<int> s21_stack_copy(s21_stack);

  for (int i = 0; i < std_stack_copy.size(); i++) {
    ASSERT_EQ(std_stack_copy.top(), s21_stack_copy.top());
    std_stack_copy.pop();
    s21_stack_copy.pop();
  }
}

TEST(StackSuite, move) {
  std::stack<int> std_stack({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});

  std::stack<int> std_stack_copy(std::move(std_stack));
  s21::stack<int> s21_stack_copy(std::move(s21_stack));

  for (int i = 0; i < std_stack_copy.size(); i++) {
    ASSERT_EQ(std_stack_copy.top(), s21_stack_copy.top());
    std_stack_copy.pop();
    s21_stack_copy.pop();
  }
}

TEST(StackSuite, equal) {
  std::stack<int> std_stack({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});

  std::stack<int> std_stack_moved = std_stack;
  s21::stack<int> s21_stack_moved = s21_stack;

  for (int i = 0; i < std_stack_moved.size(); i++) {
    ASSERT_EQ(std_stack_moved.top(), s21_stack_moved.top());
    std_stack_moved.pop();
    s21_stack_moved.pop();
  }
}

TEST(StackSuite, top_filled) {
  std::stack<int> std_stack({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack({1, 2, 3, 4, 5});

  for (int i = 0; i < std_stack.size(); i++) {
    ASSERT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackSuite, top_empty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  for (int i = 0; i < std_stack.size(); i++) {
    ASSERT_EQ(std_stack.top(), s21_stack.top());
    std_stack.pop();
    s21_stack.pop();
  }
}

TEST(StackSuite, empty) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  ASSERT_EQ(std_stack.empty(), s21_stack.empty());

  std::stack<int> std_stack_second({1, 2, 3, 4});
  s21::stack<int> s21_stack_second({1, 2, 3, 4});

  ASSERT_EQ(std_stack.empty(), s21_stack.empty());
}

TEST(StackSuite, size) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  ASSERT_EQ(std_stack.size(), s21_stack.size());

  std::stack<int> std_stack_second({1, 2, 3, 4});
  s21::stack<int> s21_stack_second({1, 2, 3, 4});

  ASSERT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackSuite, swap) {
  std::stack<int> std_stack_1({1, 2, 3, 4, 5});
  s21::stack<int> s21_stack_1({1, 2, 3, 4, 5});

  std::stack<int> std_stack_2({4, 1, 6, 2, 87, 6, 0});
  s21::stack<int> s21_stack_2({4, 1, 6, 2, 87, 6, 0});

  std_stack_1.swap(std_stack_2);
  s21_stack_1.swap(s21_stack_2);

  for (int i = 0; i < std_stack_1.size(); i++) {
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    std_stack_1.pop();
    s21_stack_1.pop();
  }

  for (int i = 0; i < std_stack_2.size(); i++) {
    ASSERT_EQ(std_stack_2.top(), s21_stack_2.top());
    std_stack_2.pop();
    s21_stack_2.pop();
  }
}

TEST(StackSuite, swap_empty) {
  std::stack<int> std_stack_1;
  s21::stack<int> s21_stack_1;

  std::stack<int> std_stack_2({4, 1, 6, 2, 87, 6, 0});
  s21::stack<int> s21_stack_2({4, 1, 6, 2, 87, 6, 0});

  std_stack_1.swap(std_stack_2);
  s21_stack_1.swap(s21_stack_2);

  for (int i = 0; i < std_stack_1.size(); i++) {
    ASSERT_EQ(std_stack_1.top(), s21_stack_1.top());
    std_stack_1.pop();
    s21_stack_1.pop();
  }

  for (int i = 0; i < std_stack_2.size(); i++) {
    ASSERT_EQ(std_stack_2.top(), s21_stack_2.top());
    std_stack_2.pop();
    s21_stack_2.pop();
  }
}

TEST(StackSuite, push) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  std_stack.push(2);
  s21_stack.push(2);

  ASSERT_EQ(std_stack.top(), s21_stack.top());
  ASSERT_EQ(std_stack.size(), s21_stack.size());
}

TEST(StackSuite, pop) {
  std::stack<int> std_stack({1});
  s21::stack<int> s21_stack({1});

  std_stack.pop();
  s21_stack.pop();

  ASSERT_EQ(std_stack.size(), s21_stack.size());
  ASSERT_EQ(std_stack.empty(), s21_stack.empty());
}

TEST(StackSuite, insert_many) {
  s21::stack<int> s21_stack({1, 1, 2});

  s21_stack.insert_many(1, 2, 3, 4, 5, 10);

  ASSERT_EQ(10, s21_stack.top());
  ASSERT_EQ(9, s21_stack.size());
}

TEST(StackSuite, Overload_copy) {
  s21::stack<int> s21_stack({2, 3, 4, 5, 1, 6, 10});
  s21::stack<int> s21_copied = s21_stack;

  ASSERT_EQ(s21_stack.size(), s21_copied.size());
  for (int i = 0; i < s21_stack.size(); i++) {
    ASSERT_EQ(s21_stack.top(), s21_stack.top());
    s21_stack.pop();
    s21_stack.pop();
  }
}