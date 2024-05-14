#include <gtest/gtest.h>

#include "../lib/s21_containersplus.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<double, 5> arr = {0, 0, 0, 0, 0};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr.back(), 0);
}

TEST(ArrayTest200, InitializerListConstructor) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest301, InitializerListConstructor) {
  s21::array<long unsigned int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest300, InitializerListConstructor) {
  s21::array<bool, 4> arr = {0, 0, 0, 1};
  EXPECT_EQ(arr.size(), 4);
  EXPECT_EQ(arr[2], false);
  EXPECT_EQ(arr.back(), true);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
}

TEST(ArrayTest302, CopyConstructor) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2(arr1);
  s21::array<int, 3> arr3(arr2);
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
  EXPECT_EQ(arr3.front(), 10);
  EXPECT_EQ(arr3.back(), 30);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
  EXPECT_EQ(arr1.size(), 3);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 3> arr1 = {10, 20, 30};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.front(), 10);
  EXPECT_EQ(arr2.back(), 30);
  EXPECT_EQ(arr1.size(), 3);
}

TEST(ArrayTest, At) {
  s21::array<double, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_THROW(arr.at(-5), std::out_of_range);
}

TEST(ArraySwapTest99, Swap) {
  s21::array<long unsigned int, 2> arr1 = {1, 2};
  s21::array<long unsigned int, 2> arr2 = {4, 5};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr2[0], 1);
}
TEST(ArraySwapTest100, Swap) {
  s21::array<bool, 3> arr1 = {0, 0, 0};
  s21::array<bool, 3> arr2 = {1, 1, 1};
  arr1.swap(arr2);
  EXPECT_EQ(arr1[1], 1);
  EXPECT_EQ(arr2[1], 0);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(42);
  EXPECT_EQ(arr.front(), 42);
  EXPECT_EQ(arr.back(), 42);
  EXPECT_EQ(arr[2], 42);
  EXPECT_THROW(arr[10], std::out_of_range);
}

TEST(ArrayTest101, Fill) {
  s21::array<bool, 5> arr;
  arr.fill(true);
  EXPECT_EQ(arr.front(), true);
  EXPECT_EQ(arr.back(), true);
  EXPECT_EQ(arr[2], true);
  EXPECT_THROW(arr[10], std::out_of_range);
}

TEST(ArrayTest102_Fill_Test, Fill) {
  s21::array<long unsigned int, 5> arr;
  arr.fill(5);
  EXPECT_EQ(arr.front(), 5);
  EXPECT_EQ(arr.back(), 5);
  EXPECT_EQ(arr[2], 5);
  EXPECT_THROW(arr[10], std::out_of_range);
}