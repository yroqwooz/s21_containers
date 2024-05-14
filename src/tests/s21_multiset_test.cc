#include <gtest/gtest.h>

#include <set>

#include "../lib/s21_containersplus.h"

TEST(MultisetSuite, InitFromList) {
  std::multiset<int> trueMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  s21::multiset<int> testMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  ASSERT_EQ(testMultiset.size(), trueMultiset.size());
}

TEST(MultisetSuite, InitAssign) {
  std::multiset<int> trueMultiset = {50, 45, 1, 30, 49, 46, 55, 51, 53, 53};
  s21::multiset<int> testMultiset =
      s21::multiset({50, 45, 1, 30, 49, 46, 55, 51, 53, 53});
  s21::multiset<int> testMultiset2 = testMultiset;
  ASSERT_EQ(testMultiset.size(), trueMultiset.size());
  ASSERT_EQ(testMultiset2.size(), trueMultiset.size());
}

TEST(MultisetSuite, InitCopy) {
  s21::multiset<int> trueMultiset({50, 45, 1, 30, 49, 46, 55, 51, 53, 53});
  s21::multiset<int> testMultiset(trueMultiset);

  ASSERT_EQ(testMultiset.size(), trueMultiset.size());
  auto it_1 = trueMultiset.begin();
  auto it_2 = testMultiset.begin();
  for (; it_2 != testMultiset.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, InitMove) {
  s21::multiset<int> moveMultiset({50, 45, 1, 30, 1});
  s21::multiset<int> testMultiset(std::move(moveMultiset));
  s21::multiset<int> trueMultiset({50, 45, 1, 30, 1});
  ASSERT_EQ(testMultiset.size(), trueMultiset.size());
  ASSERT_EQ(0u, moveMultiset.size());
  auto it_1 = trueMultiset.begin();
  auto it_2 = testMultiset.begin();
  for (; it_2 != testMultiset.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Equal) {
  s21::multiset<int> testMultiset1({50, 45, 1, 30});
  s21::multiset<int> testMultiset2({50, 45, 1, 30});
  s21::multiset<int> testMultiset3({49, 46, 55, 51, 53, 53});
  s21::multiset<int> testMultiset4({50, 45, 1, 30, 30});
  ASSERT_TRUE(testMultiset1 == testMultiset2);
  ASSERT_FALSE(testMultiset1 == testMultiset3);
  ASSERT_FALSE(testMultiset1 == testMultiset4);
}

TEST(MultisetSuite, Begin) {
  s21::multiset<int> testMultiset({50, 45, 1, 30});
  std::multiset<int> trueMultiset({50, 45, 1, 30});
  auto it_s21 = testMultiset.begin();
  auto it_std = trueMultiset.begin();
  ASSERT_EQ(*it_s21, *it_std);
}

TEST(MultisetSuite, End) {
  s21::multiset<int> testMultiset({50, 45, 1, 30});
  std::multiset<int> trueMultiset({50, 45, 1, 30});
  auto end_s21 = testMultiset.end();
  auto end_std = trueMultiset.end();
  end_s21--;
  end_std--;
  ASSERT_EQ(end_s21.operator*(), end_std.operator*());
}

TEST(MultisetSuite, Empty) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  s21::multiset<int> s21_empty;
  std::multiset<int> std_empty;
  ASSERT_EQ(s21_filled.empty(), std_filled.empty());
  ASSERT_EQ(s21_empty.empty(), std_empty.empty());
  ASSERT_NE(s21_filled.empty(), std_empty.empty());
}

TEST(MultisetSuite, Size) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  s21::multiset<int> s21_empty;
  std::multiset<int> std_empty;
  ASSERT_EQ(s21_filled.size(), std_filled.size());
  ASSERT_EQ(s21_empty.size(), std_empty.size());
  ASSERT_NE(s21_filled.size(), std_empty.size());
}

TEST(MultisetSuite, Max_size) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  ASSERT_EQ(s21_filled.max_size(), std_filled.max_size());
}

TEST(MultisetSuite, Clear) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  s21_filled.clear();
  std_filled.clear();

  ASSERT_EQ(s21_filled.size(), std_filled.size());
}

TEST(MultisetSuite, Insert) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  s21_filled.insert(123);
  std_filled.insert(123);

  ASSERT_EQ(s21_filled.size(), std_filled.size());

  auto it_1 = s21_filled.begin();
  auto it_2 = std_filled.begin();
  for (; it_1 != s21_filled.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Insert_many) {
  s21::multiset<int> s21_before({50, 45, 1, 30});
  s21::multiset<int> s21_after({50, 45, 1, 1, 2, 3, 4, 30});
  s21_before.insert_many(1, 2, 3, 4);

  ASSERT_EQ(s21_before.size(), s21_after.size());

  auto it_1 = s21_before.begin();
  auto it_2 = s21_after.begin();
  for (; it_1 != s21_before.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Erase_begin) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  auto it_s21 = s21_filled.begin();
  auto it_std = std_filled.begin();
  s21_filled.erase(it_s21);
  std_filled.erase(it_std);

  ASSERT_EQ(s21_filled.size(), std_filled.size());

  auto it_1 = s21_filled.begin();
  auto it_2 = std_filled.begin();
  for (; it_1 != s21_filled.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Erase_mid) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  auto it_s21 = s21_filled.begin();
  auto it_std = std_filled.begin();
  it_s21++;
  it_std++;
  s21_filled.erase(it_s21);
  std_filled.erase(it_std);

  ASSERT_EQ(s21_filled.size(), std_filled.size());

  auto it_1 = s21_filled.begin();
  auto it_2 = std_filled.begin();
  for (; it_1 != s21_filled.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Erase_end) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  std::multiset<int> std_filled({50, 45, 1, 30});
  auto it_s21 = s21_filled.end();
  auto it_std = std_filled.end();
  it_s21--;
  it_std--;

  s21_filled.erase(it_s21);
  std_filled.erase(it_std);

  ASSERT_EQ(s21_filled.size(), std_filled.size());

  auto it_1 = s21_filled.begin();
  auto it_2 = std_filled.begin();
  for (; it_1 != s21_filled.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Erase_mid_large) {
  s21::multiset<int> s21_filled({50, 45, 231, 90, 2, 34, 9, 1, 30});
  std::multiset<int> std_filled({50, 45, 231, 90, 2, 34, 9, 1, 30});
  auto it_s21 = s21_filled.begin();
  auto it_std = std_filled.begin();
  it_s21++;
  it_s21++;
  it_s21++;
  it_s21++;

  it_std++;
  it_std++;
  it_std++;
  it_std++;

  s21_filled.erase(it_s21);
  std_filled.erase(it_std);

  ASSERT_EQ(s21_filled.size(), std_filled.size());

  auto it_1 = s21_filled.begin();
  auto it_2 = std_filled.begin();
  for (; it_1 != s21_filled.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Swap_case1) {
  s21::multiset<int> s21_filled({50, 45, 1, 30});
  s21::multiset<int> s21_empty;

  std::multiset<int> std_filled({50, 45, 1, 30});
  std::multiset<int> std_empty;

  s21_filled.swap(s21_empty);
  std_filled.swap(std_empty);

  ASSERT_EQ(s21_filled.size(), std_filled.size());
  ASSERT_EQ(s21_empty.size(), std_empty.size());

  auto it_1 = s21_empty.begin();
  auto it_2 = std_empty.begin();
  for (; it_1 != s21_empty.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Swap_case2) {
  s21::multiset<int> testMultiset1({50, 45, 1, 30, 1});
  s21::multiset<int> testMultiset2({49, 46, 55, 51, 53, 53});
  s21::multiset<int> resMultiset1({49, 46, 55, 51, 53, 53});
  testMultiset1.swap(testMultiset2);
  ASSERT_EQ(testMultiset1.size(), resMultiset1.size());
  ASSERT_NE(testMultiset2.size(), resMultiset1.size());

  auto it_1 = testMultiset1.begin();
  auto it_2 = testMultiset2.begin();
  auto it_3 = resMultiset1.begin();
  for (; it_1 != testMultiset1.end(); it_1++, it_2++, it_3++) {
    ASSERT_EQ(it_1.operator*(), it_3.operator*());
    ASSERT_EQ(it_1.operator*(), it_3.operator*());
    ASSERT_NE(it_1.operator*(), it_2.operator*());
    ASSERT_NE(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Merge) {
  s21::multiset<int> s21_dst({50, 45, 1, 30});
  s21::multiset<int> s21_donor({32, 10, 421, 90, 9, 2});
  std::multiset<int> std_dst({50, 45, 1, 30});
  std::multiset<int> std_donor({32, 10, 421, 90, 9, 2});
  s21_dst.merge(s21_donor);
  std_dst.merge(std_donor);

  ASSERT_EQ(s21_dst.size(), std_dst.size());

  auto it_1 = s21_dst.begin();
  auto it_2 = std_dst.begin();
  for (; it_1 != s21_dst.end(); it_1++, it_2++) {
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
    ASSERT_EQ(it_1.operator*(), it_2.operator*());
  }
}

TEST(MultisetSuite, Count) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  ASSERT_EQ(s21_mset.count(1), std_mset.count(1));
  ASSERT_EQ(s21_mset.count(2), std_mset.count(2));
  ASSERT_EQ(s21_mset.count(3), std_mset.count(3));
  ASSERT_EQ(s21_mset.count(4), std_mset.count(4));
}

TEST(MultisetSuite, Equal_range) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});

  auto range_s21 = s21_mset.equal_range(1);
  auto range_std = std_mset.equal_range(1);

  auto it_s21 = range_s21.first;
  auto it_std = range_std.first;

  for (; it_std != range_std.second; it_s21++, it_std++) {
    ASSERT_EQ(it_s21.operator*(), it_std.operator*());
    ASSERT_EQ(it_s21.operator*(), it_std.operator*());
  }

  range_s21 = s21_mset.equal_range(3);
  range_std = std_mset.equal_range(3);

  it_s21 = range_s21.first;
  it_std = range_std.first;

  for (; it_std != range_std.second; it_s21++, it_std++) {
    ASSERT_EQ(it_s21.operator*(), it_std.operator*());
    ASSERT_EQ(it_s21.operator*(), it_std.operator*());
  }
}

TEST(MultisetSuite, Find) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});

  ASSERT_EQ(s21_mset.find(4).operator*(), std_mset.find(4).operator*());
  ASSERT_EQ(s21_mset.find(1).operator*(), std_mset.find(1).operator*());
  ASSERT_EQ(s21_mset.find(10).operator*(), std_mset.find(10).operator*());
  ASSERT_EQ(s21_mset.find(7).operator*(), std_mset.find(7).operator*());
  ASSERT_EQ(s21_mset.find(3).operator*(), std_mset.find(3).operator*());
}

TEST(MultisetSuite, Contains) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});

  ASSERT_EQ(s21_mset.contains(4), true);
  ASSERT_EQ(s21_mset.contains(1), true);
  ASSERT_EQ(s21_mset.contains(10), true);
  ASSERT_EQ(s21_mset.contains(123), false);
  ASSERT_EQ(s21_mset.contains(7), true);
  ASSERT_EQ(s21_mset.contains(3), true);
}

TEST(MultisetSuite, Upper_bound) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 7, 10});

  auto it_s21 = s21_mset.upper_bound(10);
  auto it_std = std_mset.upper_bound(10);
  it_std--;
  it_s21--;
  ASSERT_EQ(it_s21.operator*(), it_std.operator*());

  it_s21 = s21_mset.upper_bound(3);
  it_std = std_mset.upper_bound(3);
  it_std--;
  it_s21--;
  ASSERT_EQ(it_s21.operator*(), it_std.operator*());

  it_s21 = s21_mset.upper_bound(1);
  it_std = std_mset.upper_bound(1);
  it_std--;
  it_s21--;
  ASSERT_EQ(it_s21.operator*(), it_std.operator*());
}

TEST(MultisetSuite, Lower_bound) {
  s21::multiset<int> s21_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 10, 7, 11});
  std::multiset<int> std_mset(
      {1, 2, 3, 4, 1, 2, 3, 1, 4, 1, 1, 2, 3, 1, 2, 6, 7, 3, 10, 7, 11});

  auto it_s21 = s21_mset.lower_bound(3);
  auto it_std = std_mset.lower_bound(3);
  it_std++;
  it_s21++;
  ASSERT_EQ(it_s21.operator*(), it_std.operator*());

  it_s21 = s21_mset.lower_bound(1);
  it_std = std_mset.lower_bound(1);
  it_std++;
  it_s21++;
  ASSERT_EQ(it_s21.operator*(), it_std.operator*());
}