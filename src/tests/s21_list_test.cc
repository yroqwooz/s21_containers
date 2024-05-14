#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../lib/s21_containers.h"

TEST(Constructor_list, Default_list) {
  s21::list<int> s21_int;
  std::list<int> std_int;

  s21::list<double> s21_double;
  std::list<double> std_double;

  s21::list<char> s21_char;
  std::list<char> std_char;

  s21::list<std::string> s21_string;
  std::list<std::string> std_string;

  ASSERT_EQ(s21_int.size(), std_int.size());
  ASSERT_EQ(s21_double.size(), std_double.size());
  ASSERT_EQ(s21_char.size(), std_char.size());
  ASSERT_EQ(s21_string.size(), std_string.size());
}

TEST(Constructor_list, Sized) {
  s21::list<int> s21_int(10);
  std::list<int> std_int(10);
  s21::list<double> s21_double(10);
  std::list<double> std_double(10);
  s21::list<char> s21_char(10);
  std::list<char> std_char(10);
  s21::list<bool> s21_bool(10);
  std::list<bool> std_bool(10);
  s21::list<std::string> s21_string(10);
  std::list<std::string> std_string(10);

  ASSERT_EQ(s21_int.size(), std_int.size());
  ASSERT_EQ(s21_double.size(), std_double.size());
  ASSERT_EQ(s21_char.size(), std_char.size());
  ASSERT_EQ(s21_bool.size(), std_bool.size());
  ASSERT_EQ(s21_string.size(), std_string.size());
}

TEST(Constructor_list, InitList) {
  s21::list<int> s21_int{1, 2, 3, 4};
  std::list<int> std_int{1, 2, 3, 4};
  s21::list<char> s21_char{'a', 'b', 'c', 'd'};
  std::list<char> std_char{'a', 'b', 'c', 'd'};
  s21::list<double> s21_double{2.9f, 1.9f, 4.9f, 6.9f, 7.9f, 0.9f};
  std::list<double> std_double{2.9f, 1.9f, 4.9f, 6.9f, 7.9f, 0.9f};
  s21::list<bool> s21_bool{true, false, false, true, false, true};
  std::list<bool> std_bool{true, false, false, true, false, true};
  s21::list<std::string> s21_string{"Dame", "dane", "dame ", "yo"};
  std::list<std::string> std_string{"Dame", "dane", "dame ", "yo"};

  auto it_std_int = std_int.begin();
  for (auto it_s21 = s21_int.begin(); it_s21 != s21_int.end(); it_s21++) {
    ASSERT_EQ(*it_s21, *it_std_int);
    it_std_int++;
  }

  auto it_std_char = std_char.begin();
  for (auto it_s21 = s21_char.begin(); it_s21 != s21_char.end(); it_s21++) {
    ASSERT_EQ(*it_s21, *it_std_char);
    it_std_char++;
  }
  auto it_std_double = std_double.begin();
  for (auto it_s21 = s21_double.begin(); it_s21 != s21_double.end(); it_s21++) {
    ASSERT_EQ(*it_s21, *it_std_double);
    it_std_double++;
  }
  auto it_std_bool = std_bool.begin();
  for (auto it_s21 = s21_bool.begin(); it_s21 != s21_bool.end(); it_s21++) {
    ASSERT_EQ(*it_s21, *it_std_bool);
    it_std_bool++;
  }
  auto it_std_string = std_string.begin();
  for (auto it_s21 = s21_string.begin(); it_s21 != s21_string.end(); it_s21++) {
    ASSERT_EQ(*it_s21, *it_std_string);
    it_std_string++;
  }

  ASSERT_EQ(s21_int.size(), std_int.size());
  ASSERT_EQ(s21_double.size(), std_double.size());
  ASSERT_EQ(s21_char.size(), std_char.size());
  ASSERT_EQ(s21_bool.size(), std_bool.size());
  ASSERT_EQ(s21_string.size(), std_string.size());
}

TEST(Constructor_list, Copy) {
  s21::list<int> s21_int({1, 2, 3, 4, 5, 6, 7});
  std::list<int> std_int({1, 2, 3, 4, 5, 6, 7});
  s21::list<int> s21_int_copy(s21_int);
  std::list<int> std_int_copy(std_int);

  ASSERT_EQ(s21_int_copy.size(), std_int_copy.size());

  auto it_orig = std_int_copy.begin();
  for (auto it_copy = s21_int_copy.begin(); it_copy != s21_int_copy.end();
       it_copy++, it_orig++) {
    ASSERT_EQ(*it_orig, *it_copy);
  }

  // ------ Empty List ------
  // s21::list<std::string> s21_string;
  // s21::list<std::string> s21_string_copy(s21_string);

  s21::list<int> s21_string;
  s21::list<int> s21_string_copy(s21_string);

  // std::list<std::string> std_string;
  // std::list<std::string> std_string_copy(std_string);

  // ASSERT_EQ(s21_string_copy.size(), std_string_copy.size());
  // ASSERT_EQ(s21_string_copy.front(), std_string_copy.front());
  // ASSERT_EQ(s21_string_copy.back(), std_string_copy.back());
}

TEST(Constructor_list, Move) {
  s21::list<double> s21_int({1.1, 2.2, 3.3, 4.4, 5.5});
  s21::list<double> s21_int_copy(std::move(s21_int));

  ASSERT_DOUBLE_EQ(5, s21_int_copy.size());
  ASSERT_DOUBLE_EQ(0, s21_int.size());

  auto i = 1;
  for (auto iter = s21_int_copy.begin(); iter != s21_int_copy.end();
       ++iter, ++i) {
    ASSERT_DOUBLE_EQ(i * 1.1, *iter);
  }

  for (auto it = s21_int_copy.begin(); it != s21_int_copy.end(); it++) {
    *it = 10.23f;
  }

  for (auto iter = s21_int_copy.begin(); iter != s21_int_copy.end();
       ++iter, ++i) {
    ASSERT_DOUBLE_EQ(10.23f, *iter);
  }
  // ------ Empty List ------
  s21::list<int> s21_int_empty;
  s21::list<int> s21_int_moved(std::move(s21_int_empty));
  std::list<int> std_int_empty;
  std::list<int> std_int_moved(std::move(std_int_empty));

  ASSERT_EQ(s21_int_moved.size(), std_int_moved.size());
}

TEST(Operators_list, CopyAssignment) {
  s21::list<int> test1({1, 2, 3});
  s21::list<int> test2({4, 5, 6, 7});

  test1 = test2;
  ASSERT_EQ(test1.size(), test2.size());

  for (auto it_1 = test1.begin(), it_2 = test2.begin(); it_1 != test1.end();
       ++it_1, ++it_2) {
    ASSERT_EQ(*it_1, *it_2);
  }

  s21::list<int> s21_int_to_fill;
  s21::list<int> s21_int_src{1, 2, 3, 4};
  std::list<int> std_int_to_fill;
  std::list<int> std_int_src{1, 2, 3, 4};

  s21_int_to_fill = s21_int_src;
  std_int_to_fill = std_int_src;

  ASSERT_EQ(s21_int_to_fill.front(), std_int_to_fill.front());
  ASSERT_EQ(s21_int_to_fill.back(), std_int_to_fill.back());
  ASSERT_EQ(s21_int_to_fill.size(), std_int_to_fill.size());

  auto it_std = std_int_to_fill.begin();
  for (auto it_s21 = s21_int_to_fill.begin(); it_s21 != s21_int_to_fill.end();
       it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Operators_list, MoveAssignment) {
  s21::list<int> test1({1, 2, 3});
  s21::list<int> test2({4, 5, 6, 7});

  test1 = std::move(test2);
  ASSERT_EQ(test1.size(), 4);
  int i = 4;
  for (auto it_1 = test1.begin(); it_1 != test1.end(); ++it_1, i++) {
    ASSERT_EQ(*it_1, i);
  }

  s21::list<int> s21_src{1, 2, 3, 4};
  s21::list<int> s21_dst;
  std::list<int> std_src{1, 2, 3, 4};
  std::list<int> std_dst;

  s21_dst = std::move(s21_src);
  std_dst = std::move(std_src);

  auto it_std = std_dst.begin();
  for (auto it_s21 = s21_dst.begin(); it_s21 != s21_dst.end();
       it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
  ASSERT_EQ(s21_dst.front(), std_dst.front());
  ASSERT_EQ(s21_dst.back(), std_dst.back());
  ASSERT_EQ(s21_dst.size(), std_dst.size());
}

TEST(Operators_list, InitListAssignment) {
  s21::list<int> test1({1, 2, 3, 4, 5});
  std::list<int> test2({1, 2, 3, 4, 5});
  test1 = {21, 42, 63};
  test2 = {21, 42, 63};

  auto it_std = test2.begin();
  for (auto it_s21 = test1.begin(); it_s21 != test1.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }

  ASSERT_EQ(test1.front(), test2.front());
  ASSERT_EQ(test1.back(), test2.back());
  ASSERT_EQ(test1.size(), test2.size());
}

TEST(Methods_list, Front) {
  s21::list<int> test1({1, 2, 3, 4});
  s21::list<char> test2({'c', '2', '-', 'W'});
  s21::list<double> test3({1.2f, 1.5f, 6.9f});
  s21::list<bool> test4({false, true, true});
  s21::list<std::string> test5({"Hello", "Farewell"});

  ASSERT_EQ(test1.front(), 1);
  ASSERT_EQ(test2.front(), 'c');
  ASSERT_EQ(test3.front(), 1.2f);
  ASSERT_EQ(test4.front(), false);
  ASSERT_EQ(test5.front(), "Hello");
}

TEST(Methods_list, Back) {
  s21::list<int> test1({1, 2, 3, 4});
  s21::list<char> test2({'c', '2', '-', 'W'});
  s21::list<double> test3({1.2f, 1.5f, 6.9f});
  s21::list<bool> test4({false, false, true});
  s21::list<std::string> test5({"Hello", "Farewell"});

  ASSERT_EQ(test1.back(), 4);
  ASSERT_EQ(test2.back(), 'W');
  ASSERT_EQ(test3.back(), 6.9f);
  ASSERT_EQ(test4.back(), true);
  ASSERT_EQ(test5.back(), "Farewell");
}

TEST(Methods_list, Empty) {
  s21::list<int> s21_int_1;
  s21::list<double> s21_double_1;
  s21::list<char> s21_char_1;
  s21::list<std::string> s21_string_1;

  std::list<int> std_int_1;
  std::list<double> std_double_1;
  std::list<char> std_char_1;
  std::list<std::string> std_string_1;

  ASSERT_EQ(s21_int_1.empty(), std_int_1.empty());
  ASSERT_EQ(s21_char_1.empty(), std_char_1.empty());
  ASSERT_EQ(s21_double_1.empty(), std_double_1.empty());
  ASSERT_EQ(s21_string_1.empty(), std_string_1.empty());

  s21::list<int> s21_int_2{1, 2, 3, 4};
  s21::list<double> s21_double_2{1.2f, 39.9f};
  s21::list<char> s21_char_2{'A', 'b', 'o', 'b', 'a'};
  s21::list<std::string> s21_string_2{"Ti", "novichok", "???"};

  std::list<int> std_int_2{1, 2, 3, 4};
  std::list<double> std_double_2{1.2f, 39.9f};
  std::list<char> std_char_2{'A', 'b', 'o', 'b', 'a'};
  std::list<std::string> std_string_2{"Ti", "novichok", "???"};

  ASSERT_EQ(s21_int_2.empty(), std_int_2.empty());
  ASSERT_EQ(s21_char_2.empty(), std_char_2.empty());
  ASSERT_EQ(s21_double_2.empty(), std_double_2.empty());
  ASSERT_EQ(s21_string_2.empty(), std_string_2.empty());

  std_int_2.clear(), s21_int_2.clear();
  ASSERT_EQ(s21_int_2.empty(), std_int_2.empty());
}

TEST(Methods_list, MaxSize) {
  s21::list<int> s21_int_1;
  s21::list<double> s21_double_1;
  s21::list<char> s21_char_1;
  s21::list<std::string> s21_string_1;

  std::list<int> std_int_1;
  std::list<double> std_double_1;
  std::list<char> std_char_1;
  std::list<std::string> std_string_1;

  ASSERT_EQ(s21_int_1.max_size(), std_int_1.max_size());
  ASSERT_EQ(s21_char_1.max_size(), std_char_1.max_size());
  ASSERT_EQ(s21_double_1.max_size(), std_double_1.max_size());
  ASSERT_EQ(s21_string_1.max_size(), std_string_1.max_size());
}

TEST(Methods_list, InsertInEmpty) {
  s21::list<int> s21_int;
  s21::list<double> s21_double;
  s21::list<char> s21_char;
  s21::list<std::string> s21_string;

  std::list<int> std_int;
  std::list<double> std_double;
  std::list<char> std_char;
  std::list<std::string> std_string;

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  s21_int.insert(it_s21_int, 10), std_int.insert(it_std_int, 10);
  ASSERT_EQ(*(s21_int.begin()), *(std_int.begin()));

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  s21_double.insert(it_s21_double, 12.19f),
      std_double.insert(it_std_double, 12.19f);
  ASSERT_EQ(*(s21_double.begin()), *(std_double.begin()));

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  s21_char.insert(it_s21_char, 'h'), std_char.insert(it_std_char, 'h');
  ASSERT_EQ(*(s21_char.begin()), *(std_char.begin()));

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  s21_string.insert(it_s21_string, "UWAAAAH"),
      std_string.insert(it_std_string, "UWAAAAH");
  ASSERT_EQ(*(s21_string.begin()), *(std_string.begin()));
}

TEST(Methods_list, InsertInFront) {
  s21::list<int> s21_int{1, 3};
  s21::list<double> s21_double{1.0f, 2.0f};
  s21::list<char> s21_char{'h', 'h'};
  s21::list<std::string> s21_string{"Chto-to", "est'"};

  std::list<int> std_int{1, 3};
  std::list<double> std_double{1.0f, 2.0f};
  std::list<char> std_char{'h', 'h'};
  std::list<std::string> std_string{"Chto-to", "est'"};

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  s21_int.insert(it_s21_int, 0), std_int.insert(it_std_int, 0);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  s21_double.insert(it_s21_double, 1.5f),
      std_double.insert(it_std_double, 1.5f);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  s21_char.insert(it_s21_char, 'e'), std_char.insert(it_std_char, 'e');
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  s21_string.insert(it_s21_string, "tut"),
      std_string.insert(it_std_string, "tut");
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, InsertInMiddle) {
  s21::list<int> s21_int{1, 3};
  s21::list<double> s21_double{1.0f, 2.0f};
  s21::list<char> s21_char{'h', 'h'};
  s21::list<std::string> s21_string{"Chto-to", "est'"};

  std::list<int> std_int{1, 3};
  std::list<double> std_double{1.0f, 2.0f};
  std::list<char> std_char{'h', 'h'};
  std::list<std::string> std_string{"Chto-to", "est'"};

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  it_s21_int++, it_std_int++;
  s21_int.insert(it_s21_int, 2), std_int.insert(it_std_int, 2);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  it_s21_double++, it_std_double++;
  s21_double.insert(it_s21_double, 1.5f),
      std_double.insert(it_std_double, 1.5f);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  it_s21_char++, it_std_char++;
  s21_char.insert(it_s21_char, 'e'), std_char.insert(it_std_char, 'e');
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  it_s21_string++, it_std_string++;
  s21_string.insert(it_s21_string, "tut"),
      std_string.insert(it_std_string, "tut");
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, InsertInBack) {
  s21::list<int> s21_int{1, 3};
  s21::list<double> s21_double{1.0f, 2.0f};
  s21::list<char> s21_char{'h', 'h'};
  s21::list<std::string> s21_string{"Chto-to", "est'"};

  std::list<int> std_int{1, 3};
  std::list<double> std_double{1.0f, 2.0f};
  std::list<char> std_char{'h', 'h'};
  std::list<std::string> std_string{"Chto-to", "est'"};

  auto it_s21_int = s21_int.end();
  auto it_std_int = std_int.end();
  s21_int.insert(it_s21_int, 2), std_int.insert(it_std_int, 2);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.end();
  auto it_std_double = std_double.end();
  s21_double.insert(it_s21_double, 1.5f),
      std_double.insert(it_std_double, 1.5f);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.end();
  auto it_std_char = std_char.end();
  s21_char.insert(it_s21_char, 'e'), std_char.insert(it_std_char, 'e');
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.end();
  auto it_std_string = std_string.end();
  s21_string.insert(it_s21_string, "tut"),
      std_string.insert(it_std_string, "tut");
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, EraseFront) {
  s21::list<int> s21_int{1, 3};
  s21::list<double> s21_double{1.0f, 2.0f};
  s21::list<char> s21_char{'h', 'h'};
  s21::list<std::string> s21_string{"Chto-to", "est'"};

  std::list<int> std_int{1, 3};
  std::list<double> std_double{1.0f, 2.0f};
  std::list<char> std_char{'h', 'h'};
  std::list<std::string> std_string{"Chto-to", "est'"};

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  s21_int.erase(it_s21_int), std_int.erase(it_std_int);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  s21_double.erase(it_s21_double), std_double.erase(it_std_double);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  s21_char.erase(it_s21_char), std_char.erase(it_std_char);
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  s21_string.erase(it_s21_string), std_string.erase(it_std_string);
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, EraseMiddle) {
  s21::list<int> s21_int{1, 2, 3};
  s21::list<double> s21_double{1.0f, 1.5f, 2.0f};
  s21::list<char> s21_char{'h', 'e', 'h'};
  s21::list<std::string> s21_string{"Chto-to", "tut", "est'"};

  std::list<int> std_int{1, 2, 3};
  std::list<double> std_double{1.0f, 1.5f, 2.0f};
  std::list<char> std_char{'h', 'e', 'h'};
  std::list<std::string> std_string{"Chto-to", "tut", "est'"};

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  it_s21_int++, it_std_int++;
  s21_int.erase(it_s21_int), std_int.erase(it_std_int);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  it_s21_double++, it_std_double++;
  s21_double.erase(it_s21_double), std_double.erase(it_std_double);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  it_s21_char++, it_std_char++;
  s21_char.erase(it_s21_char), std_char.erase(it_std_char);
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  it_s21_string++, it_std_string++;
  s21_string.erase(it_s21_string), std_string.erase(it_std_string);
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, EraseBack) {
  s21::list<int> s21_int{1, 3, 2, 2, 1, 2, 3, 4};
  s21::list<double> s21_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  s21::list<char> s21_char{'h', 'h', 'b', 'h', 'h', 'b'};
  s21::list<std::string> s21_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  std::list<int> std_int{1, 3, 2, 2, 1, 2, 3, 4};
  std::list<double> std_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  std::list<char> std_char{'h', 'h', 'b', 'h', 'h', 'b'};
  std::list<std::string> std_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  auto it_s21_int = s21_int.end();
  auto it_std_int = std_int.end();
  it_s21_int--, it_std_int--;
  s21_int.erase(it_s21_int), std_int.erase(it_std_int);
  it_s21_int = s21_int.begin(), it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.end();
  auto it_std_double = std_double.end();
  it_s21_double--, it_std_double--;
  s21_double.erase(it_s21_double), std_double.erase(it_std_double);
  it_s21_double = s21_double.begin(), it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.end();
  auto it_std_char = std_char.end();
  it_s21_char--, it_std_char--;
  s21_char.erase(it_s21_char), std_char.erase(it_std_char);
  it_s21_char = s21_char.begin(), it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.end();
  auto it_std_string = std_string.end();
  it_s21_string--, it_std_string--;
  s21_string.erase(it_s21_string), std_string.erase(it_std_string);
  it_s21_string = s21_string.begin(), it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, Sort) {
  s21::list<int> s21_int{1, 3, 2, 2, 1, 2, 3, 4};
  s21::list<double> s21_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  s21::list<char> s21_char{'h', 'h', 'b', 'h', 'h', 'b'};
  s21::list<std::string> s21_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  std::list<int> std_int{1, 3, 2, 2, 1, 2, 3, 4};
  std::list<double> std_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  std::list<char> std_char{'h', 'h', 'b', 'h', 'h', 'b'};
  std::list<std::string> std_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  s21_int.sort(), std_int.sort();
  s21_double.sort(), std_double.sort();
  s21_char.sort(), std_char.sort();
  s21_string.sort(), std_string.sort();

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, PopBack) {
  s21::list<int> s21_int{1, 3, 2, 2, 1, 2, 3, 4};
  s21::list<double> s21_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  s21::list<char> s21_char{'h', 'h', 'b', 'h', 'h', 'b'};
  s21::list<std::string> s21_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  std::list<int> std_int{1, 3, 2, 2, 1, 2, 3, 4};
  std::list<double> std_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  std::list<char> std_char{'h', 'h', 'b', 'h', 'h', 'b'};
  std::list<std::string> std_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  s21_int.pop_back(), std_int.pop_back();
  s21_double.pop_back(), std_double.pop_back();
  s21_char.pop_back(), std_char.pop_back();
  s21_string.pop_back(), std_string.pop_back();
  s21_int.pop_back(), std_int.pop_back();
  s21_double.pop_back(), std_double.pop_back();
  s21_char.pop_back(), std_char.pop_back();
  s21_string.pop_back(), std_string.pop_back();

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, PopFront) {
  s21::list<int> s21_int{1, 3, 2, 2, 1, 2, 3, 4};
  s21::list<double> s21_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  s21::list<char> s21_char{'h', 'h', 'b', 'h', 'h', 'b'};
  s21::list<std::string> s21_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  std::list<int> std_int{1, 3, 2, 2, 1, 2, 3, 4};
  std::list<double> std_double{1.0f, 2.0f, 19.23f, 2.0f, 1.0f, -22.0f};
  std::list<char> std_char{'h', 'h', 'b', 'h', 'h', 'b'};
  std::list<std::string> std_string{"Chto-to", "est'", "interesnoe",
                                    "neponyatnoe"};

  s21_int.pop_front(), std_int.pop_front();
  s21_double.pop_front(), std_double.pop_front();
  s21_char.pop_front(), std_char.pop_front();
  s21_string.pop_front(), std_string.pop_front();
  s21_int.pop_front(), std_int.pop_front();
  s21_double.pop_front(), std_double.pop_front();
  s21_char.pop_front(), std_char.pop_front();
  s21_string.pop_front(), std_string.pop_front();

  auto it_s21_int = s21_int.begin();
  auto it_std_int = std_int.begin();
  for (; it_s21_int != s21_int.end(); it_s21_int++, it_std_int++) {
    ASSERT_EQ(*it_s21_int, *it_std_int);
  }

  auto it_s21_double = s21_double.begin();
  auto it_std_double = std_double.begin();
  for (; it_s21_double != s21_double.end(); it_s21_double++, it_std_double++) {
    ASSERT_EQ(*it_s21_double, *it_std_double);
  }

  auto it_s21_char = s21_char.begin();
  auto it_std_char = std_char.begin();
  for (; it_s21_char != s21_char.end(); it_s21_char++, it_std_char++) {
    ASSERT_EQ(*it_s21_char, *it_std_char);
  }

  auto it_s21_string = s21_string.begin();
  auto it_std_string = std_string.begin();
  for (; it_s21_string != s21_string.end(); it_s21_string++, it_std_string++) {
    ASSERT_EQ(*it_s21_string, *it_std_string);
  }
}

TEST(Methods_list, Swap) {
  s21::list<int> s21_int_1{1, 3, 2, 2, 1, 2, 3, 4};
  s21::list<int> s21_int_2{4, 2, 32, 41, 21, 91, 13};

  std::list<int> std_int_1{1, 3, 2, 2, 1, 2, 3, 4};
  std::list<int> std_int_2{4, 2, 32, 41, 21, 91, 13};

  s21_int_1.swap(s21_int_2);
  std_int_1.swap(std_int_2);

  auto it_s21_1 = s21_int_1.begin();
  auto it_std_1 = std_int_1.begin();
  for (; it_s21_1 != s21_int_1.end(); it_s21_1++, it_std_1++) {
    ASSERT_EQ(*it_s21_1, *it_std_1);
  }

  auto it_s21 = s21_int_1.begin();
  auto it_std = std_int_1.begin();
  for (; it_s21 != s21_int_1.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
  ASSERT_EQ(s21_int_1.size(), std_int_1.size());
  ASSERT_EQ(s21_int_2.size(), std_int_2.size());
}

TEST(Methods_list, MergeFilled) {
  s21::list<int> s21_first{1, 2, 3, 4, 5};
  s21::list<int> s21_second{9, 8, 7, 6, 5};

  std::list<int> std_first{1, 2, 3, 4, 5};
  std::list<int> std_second{9, 8, 7, 6, 5};

  s21_first.merge(s21_second);
  std_first.merge(std_second);

  auto it_std = std_first.begin();
  auto it_s21 = s21_first.begin();
  for (; it_s21 != s21_first.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
  ASSERT_EQ(s21_second.size(), std_second.size());
}

TEST(Methods_list, MergeChaotic) {
  s21::list<int> s21_first{18, 3, 1, 29, 2, 19, 65};
  s21::list<int> s21_second{90, 0, -2, 89, -92, 12};

  std::list<int> std_first{18, 3, 1, 29, 2, 19, 65};
  std::list<int> std_second{90, 0, -2, 89, -92, 12};

  s21_first.merge(s21_second);
  std_first.merge(std_second);

  auto it_std = std_first.begin();
  auto it_s21 = s21_first.begin();
  for (; it_s21 != s21_first.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
  ASSERT_EQ(s21_second.size(), std_second.size());
}

TEST(Methods_list, MergeEmpty) {
  s21::list<char> s21_first;
  s21::list<char> s21_second{'c', 'o', 's', 'i', 'n'};
  std::list<char> std_first;
  std::list<char> std_second{'c', 'o', 's', 'i', 'n'};

  s21_first.merge(s21_second);
  std_first.merge(std_second);

  auto it_s21 = s21_first.begin();
  auto it_std = std_first.begin();

  for (; it_s21 != s21_first.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }

  ASSERT_EQ(s21_first.size(), std_first.size());
  ASSERT_EQ(s21_second.size(), std_second.size());
}

TEST(Methods_list, SpliceFront) {
  s21::list<int> s21_dst{1, 2, 3, 4};
  s21::list<int> s21_src{9, 9, 9, 9};

  std::list<int> std_dst{1, 2, 3, 4};
  std::list<int> std_src{9, 9, 9, 9};

  auto it_s21 = s21_dst.begin();
  auto it_std = std_dst.begin();

  s21_dst.splice(it_s21, s21_src);
  std_dst.splice(it_std, std_src);

  it_s21 = s21_dst.begin();
  it_std = std_dst.begin();

  for (; it_s21 != s21_dst.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Methods_list, SpliceEnd) {
  s21::list<int> s21_dst{1, 2, 3, 4};
  s21::list<int> s21_src{9, 9, 9, 9};

  std::list<int> std_dst{1, 2, 3, 4};
  std::list<int> std_src{9, 9, 9, 9};

  auto it_s21 = s21_dst.end();
  auto it_std = std_dst.end();

  s21_dst.splice(it_s21, s21_src);
  std_dst.splice(it_std, std_src);

  it_s21 = s21_dst.begin();
  it_std = std_dst.begin();

  for (; it_s21 != s21_dst.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Methods_list, SpliceMidSomewhere) {
  s21::list<int> s21_dst{1, 2, 3, 4};
  s21::list<int> s21_src{9, 9, 9, 9};

  std::list<int> std_dst{1, 2, 3, 4};
  std::list<int> std_src{9, 9, 9, 9};

  auto it_s21 = s21_dst.begin();
  auto it_std = std_dst.begin();

  it_s21++, it_std++;
  it_s21++, it_std++;

  s21_dst.splice(it_s21, s21_src);
  std_dst.splice(it_std, std_src);

  it_s21 = s21_dst.begin();
  it_std = std_dst.begin();

  for (; it_s21 != s21_dst.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Methods_list, Reverse) {
  s21::list<int> s21_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 1000};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 1000};

  s21_list.reverse();
  std_list.reverse();

  auto it_s21 = s21_list.begin();
  auto it_std = std_list.begin();

  for (; it_s21 != s21_list.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Methods_list, Unique) {
  s21::list<int> s21_list{1, 2, 3, 3, 4, 4, 4, 4, 4, 4, 5, 1, 2, 1, 1};
  std::list<int> std_list{1, 2, 3, 3, 4, 4, 4, 4, 4, 4, 5, 1, 2, 1, 1};

  s21_list.unique();
  std_list.unique();

  auto it_s21 = s21_list.begin();
  auto it_std = std_list.begin();

  for (; it_s21 != s21_list.end(); it_s21++, it_std++) {
    ASSERT_EQ(*it_s21, *it_std);
  }
}

TEST(Methods_list, Insert_many) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  s21::list<int> s21_res_list = {1, 2, 3, 9, 8, 7, 6, 5, 4, 3, 2, 1, 4};

  auto it = s21_list.end();
  it--;
  s21_list.insert_many(it, 9, 8, 7, 6, 5, 4, 3, 2, 1);

  auto it_s21 = s21_list.begin();
  auto it_res = s21_res_list.begin();

  for (; it_s21 != s21_list.end(); it_s21++, it_res++) {
    ASSERT_EQ(*it_s21, *it_res);
  }
}

TEST(Methods_list, Insert_many_front) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  s21::list<int> s21_res_list = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4};

  s21_list.insert_many_front(9, 8, 7, 6, 5, 4, 3, 2, 1);

  auto it_s21 = s21_list.begin();
  auto it_res = s21_res_list.begin();

  for (; it_s21 != s21_list.end(); it_s21++, it_res++) {
    ASSERT_EQ(*it_s21, *it_res);
  }
}

TEST(Methods_list, Insert_many_back) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  s21::list<int> s21_res_list = {1, 2, 3, 4, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  s21_list.insert_many_back(9, 8, 7, 6, 5, 4, 3, 2, 1);

  auto it_s21 = s21_list.begin();
  auto it_res = s21_res_list.begin();

  for (; it_s21 != s21_list.end(); it_s21++, it_res++) {
    ASSERT_EQ(*it_s21, *it_res);
  }
}

TEST(Methods_list, Iterator_access) {
  s21::list<int> s21_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  auto it_s21 = s21_list.begin();
  auto it_res = std_list.begin();
  *(it_s21) = 10;
  *(it_res) = 10;

  for (; it_s21 != s21_list.end(); it_s21++, it_res++) {
    ASSERT_EQ(*it_s21, *it_res);
  }
}
