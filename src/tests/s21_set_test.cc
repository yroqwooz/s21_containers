#include <gtest/gtest.h>

#include <set>

#include "../lib/s21_containers.h"

TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Initializer_list) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  ASSERT_EQ(s21_set.size(), std_set.size());
  ASSERT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Copy) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  s21::set<char> s21_set_2 = s21_set_1;
  std::set<char> std_set_2 = std_set_1;

  ASSERT_EQ(s21_set_1.size(), s21_set_2.size());
  ASSERT_EQ(std_set_1.size(), std_set_2.size());
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Constructor_Move) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd'};
  s21::set<char> s21_set_2 = std::move(s21_set_1);
  std::set<char> std_set_2 = std::move(std_set_1);

  ASSERT_EQ(s21_set_2.size(), std_set_2.size());
  ASSERT_EQ(s21_set_1.size(), std_set_1.size());
  ASSERT_EQ(s21_set_1.empty(), std_set_1.empty());
  auto it1 = s21_set_2.begin();
  auto it2 = std_set_2.begin();
  while (it1 != s21_set_2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Modifier_Insert_1) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  ASSERT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  ASSERT_EQ(s21_set.size(), size_t(1));
}

TEST(Set, Modifier_Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  ASSERT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, Modifier_Erase) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_set_2.begin();
  ++it;
  s21_set_2.erase(it);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  ASSERT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Swap) {
  s21::set<char> s21_set_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::set<char> s21_set_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_set_1.swap(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  auto it3 = s21_set_3.begin();
  auto it4 = s21_set_4.begin();
  while (it1 != s21_set_1.end()) {
    ASSERT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_set_2.end()) {
    ASSERT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  ASSERT_EQ(s21_set_1.size(), s21_set_4.size());
  ASSERT_EQ(s21_set_2.size(), s21_set_3.size());
}

TEST(Set, Modifier_Merge) {
  s21::set<int> s21_set_1 = {1, 2, 3};
  s21::set<int> s21_set_2 = {3, 4, 5, 6};
  s21::set<int> s21_set_3 = {1, 2, 3, 4, 5, 6};
  s21_set_1.merge(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it3 = s21_set_3.begin();
  while (it1 != s21_set_1.end()) {
    ASSERT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  ASSERT_EQ(s21_set_1.size(), s21_set_3.size());
}

TEST(Set, Lookup_Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  ASSERT_EQ(s21_set.contains(1), true);
  ASSERT_EQ(s21_set.contains(2), true);
  ASSERT_EQ(s21_set.contains(3), true);
  ASSERT_EQ(s21_set.contains(4), true);
  ASSERT_EQ(s21_set.contains(7), false);
  ASSERT_EQ(s21_set.contains(-2), false);
  ASSERT_EQ(s21_set.contains(0), false);
}

TEST(Set, Lookup_Find) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  auto it_end = s21_set.end();
  ASSERT_EQ(*(s21_set.find(1)), 1);
  ASSERT_EQ(*(s21_set.find(3)), 3);
  ASSERT_EQ(*(s21_set.find(4)), 4);
  ASSERT_EQ(*(s21_set.find(2)), 2);
}
