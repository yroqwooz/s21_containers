#include <gtest/gtest.h>

#include "../lib/s21_containersplus.h"

TEST(VectorTest900, DefaultСonstructor) {
  s21::vector<double> Vector;
  std::vector<double> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest901, СonstructorSetSize) {
  s21::vector<double> Vector(10);
  std::vector<double> Vector2(10);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest902, СonstructorSetSize) {
  s21::vector<double> Vector(10);
  std::vector<double> Vector2(10);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest903, СonstructorInitializerList) {
  s21::vector<unsigned long long> Vector{1, 2, 3, 4, 5};
  std::vector<unsigned long long> Vector2{1, 2, 3, 4, 5};
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<unsigned long long>::iterator it2 = Vector2.begin();
  for (s21::vector<unsigned long long>::iterator it = Vector.begin();
       it != Vector.end(); it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest904, СonstructorCopy) {
  s21::vector<long long> Copy_Vector{1, 2, 3, 4, 5};
  s21::vector<long long> Vector(Copy_Vector);
  std::vector<long long> Copy_Vector2{1, 2, 3, 4, 5};
  std::vector<long long> Vector2(Copy_Vector2);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<long long>::iterator it2 = Vector2.begin();
  for (s21::vector<long long>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest905, СonstructorMove) {
  s21::vector<unsigned int> Copy_Vector{1, 2, 3, 4, 5};
  s21::vector<unsigned int> Vector(std::move(Copy_Vector));
  std::vector<unsigned int> Copy_Vector2{1, 2, 3, 4, 5};
  std::vector<unsigned int> Vector2(std::move(Copy_Vector2));
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<unsigned int>::iterator it2 = Vector2.begin();
  for (s21::vector<unsigned int>::iterator it = Vector.begin();
       it != Vector.end(); it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest906, OperatorEq) {
  s21::vector<char> Copy_Vector{'a', 'b', 'c', 'd', 'e'};
  s21::vector<char> Vector = std::move(Copy_Vector);
  std::vector<char> Copy_Vector2{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2 = std::move(Copy_Vector2);
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.empty(), Vector2.empty());
  std::vector<char>::iterator it2 = Vector2.begin();
  for (s21::vector<char>::iterator it = Vector.begin(); it != Vector.end();
       it++) {
    ASSERT_EQ(*it, *it2++);
  }
}

TEST(VectorTest, At) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector.at(i), Vector2.at(i));
  }
}

TEST(VectorTest908, At) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector.at(i), Vector2.at(i));
  }
}

TEST(VectorTest909, At) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector.at(i), Vector2.at(i));
  }
}

TEST(VectorTest910, At) {
  s21::vector<double> Vector{0, 10, 20, 30, 40};
  std::vector<double> Vector2{0, 10, 20, 30, 40};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector.at(i), Vector2.at(i));
  }
}

TEST(VectorTest911, OperatorBrackets) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector[i], Vector2[i]);
  }
}

TEST(VectorTest912, OperatorBrackets) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector[i], Vector2[i]);
  }
}

TEST(VectorTest913, OperatorBrackets) {
  s21::vector<double> Vector{0, 10, 20, 30, 40};
  std::vector<double> Vector2{0.0, 10.0, 20.0, 30.0, 40.0};
  for (size_t i = 0; i < Vector.size(); i++) {
    ASSERT_EQ(Vector[i], Vector2[i]);
  }
}

TEST(VectorTest914, Front) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  ASSERT_EQ(Vector.front(), Vector2.front());
}

TEST(VectorTest915, Front) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  ASSERT_EQ(Vector.front(), Vector2.front());
}

TEST(VectorTest916, Front) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(Vector.front(), Vector2.front());
}

TEST(VectorTest917, Back) {
  s21::vector<double> Vector{0, 10, 20, 30, 40};
  std::vector<double> Vector2{0.0, 10.0, 20.0, 30.0, 40.0};
  ASSERT_EQ(Vector.back(), Vector2.back());
}

TEST(VectorTest918, Back) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(Vector.back(), Vector2.back());
}

TEST(VectorTest919, Back) {
  s21::vector<int> Vector{0, 10, 20, 30, 40};
  std::vector<int> Vector2{0, 10, 20, 30, 40};
  ASSERT_EQ(Vector.back(), Vector2.back());
}

TEST(VectorTest920, Data) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.data(), Vector2.data());
}

TEST(VectorTest921, Data) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  ASSERT_EQ(Vector.data(), Vector2.data());
}

TEST(VectorTest922, Data2) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  for (size_t i = 0; i < Vector.size(); ++i) {
    ASSERT_EQ(Vector.data()[i], Vector2.data()[i]);
  }
}

TEST(VectorTest923, Data2) {
  s21::vector<int> Vector{1, 2, 3, 4, 5, 666, 333, 444};
  std::vector<int> Vector2{1, 2, 3, 4, 5, 666, 333, 444};
  for (size_t i = 0; i < Vector.size(); ++i) {
    ASSERT_EQ(Vector.data()[i], Vector2.data()[i]);
  }
}

TEST(VectorTest925, Empty) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}
TEST(VectorTest926, Empty) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest927, Empty2) {
  s21::vector<int> Vector{1};
  std::vector<int> Vector2{1};
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest928, Empty3) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  Vector.reserve(1);
  Vector2.reserve(1);
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest929, Empty3) {
  s21::vector<bool> Vector;
  std::vector<bool> Vector2;
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest930, Empty3) {
  s21::vector<bool> Vector;
  std::vector<bool> Vector2;
  Vector.reserve(1);
  Vector2.reserve(1);
  ASSERT_EQ(Vector.empty(), Vector2.empty());
}

TEST(VectorTest931, Size) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest932, Size) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest933, Size) {
  s21::vector<bool> Vector;
  std::vector<bool> Vector2;
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest934, Size2) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest935, Size2) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest936, Size2) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest937, MaxSize) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.max_size(), Vector2.max_size());
}

TEST(VectorTest938, MaxSize) {
  s21::vector<double> Vector;
  std::vector<double> Vector2;
  ASSERT_EQ(Vector.max_size(), Vector2.max_size());
}

TEST(VectorTest939, MaxSize) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  ASSERT_EQ(Vector.max_size(), Vector2.max_size());
}

TEST(VectorTest940, Reserve) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  Vector.reserve(0);
  Vector2.reserve(0);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest941, Reserve) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  Vector.reserve(0);
  Vector2.reserve(0);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest942, Reserve2) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  Vector.reserve(6);
  Vector2.reserve(6);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
  auto i2 = Vector.begin();
  for (auto i = Vector.begin(); i != Vector.end(); ++i) {
    ASSERT_EQ(*i, *i2++);
  }
}

TEST(VectorTest943, Reserve2) {
  s21::vector<char> Vector{'a', 'b', 'c'};
  std::vector<char> Vector2{'a', 'b', 'c'};
  Vector.reserve(6);
  Vector2.reserve(6);
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
  auto i2 = Vector.begin();
  for (auto i = Vector.begin(); i != Vector.end(); ++i) {
    ASSERT_EQ(*i, *i2++);
  }
}

TEST(VectorTest944, Capacity) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest945, Capacity) {
  s21::vector<char> Vector{'a', 'b', 'c'};
  std::vector<char> Vector2{'a', 'b', 'c'};
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest946, Capacity2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest947, Capacity2) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest948, ShrinkToFit) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  Vector.reserve(10);
  Vector2.reserve(10);
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}
TEST(VectorTest949, ShrinkToFit) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  Vector.reserve(10);
  Vector2.reserve(10);
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest950, ShrinkToFit) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  Vector.reserve(10);
  Vector2.reserve(10);
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest951, ShrinkToFit) {
  s21::vector<double> Vector{1, 2, 3, 4, 5};
  std::vector<double> Vector2{1, 2, 3, 4, 5};
  Vector.reserve(10);
  Vector2.reserve(10);
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest952, ShrinkToFit2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest9521, ShrinkToFit2) {
  s21::vector<double> Vector;
  std::vector<double> Vector2;
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest953, ShrinkToFit2) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  Vector.shrink_to_fit();
  Vector2.shrink_to_fit();
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
  ASSERT_EQ(Vector.size(), Vector2.size());
}

TEST(VectorTest954, Begin) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(*(Vector.begin()), *(Vector2.begin()));
}

TEST(VectorTest955, Begin) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(*(Vector.begin()), *(Vector2.begin()));
}
TEST(VectorTest9551, Begin) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  ASSERT_EQ(*(Vector.begin()), *(Vector2.begin()));
}

TEST(VectorTest956, End) {
  s21::vector<int> Vector{1, 2, 3};
  std::vector<int> Vector2{1, 2, 3};
  ASSERT_EQ(*(--Vector.end()), *(--Vector2.end()));
}

TEST(VectorTest957, End) {
  s21::vector<double> Vector{1, 2, 3};
  std::vector<double> Vector2{1, 2, 3};
  ASSERT_EQ(*(--Vector.end()), *(--Vector2.end()));
}

TEST(VectorTest958, End) {
  s21::vector<bool> Vector{true, true, true, true, true};
  std::vector<bool> Vector2{true, true, true, true, true};
  ASSERT_EQ(*(--Vector.end()), *(--Vector2.end()));
}

TEST(VectorTest959, End) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  ASSERT_EQ(*(--Vector.end()), *(--Vector2.end()));
}

/**
 * @brief Construct a new TEST object
 * capacity должен остаться без изменений, измениться должен size
 */
TEST(VectorTest960, Clear) {
  s21::vector<int> Vector{5, 6, 7};
  std::vector<int> Vector2{5, 6, 7};
  Vector.clear();
  Vector2.clear();
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest962, Clear) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  Vector.clear();
  Vector2.clear();
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest963, Insert) {
  s21::vector<int> Vector{5, 6, 7};
  std::vector<int> Vector2{5, 6, 7};
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  ++it, ++it2;
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest964, Insert) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  ++it, ++it2;
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<char>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest965, Insert) {
  s21::vector<double> Vector{5, 6, 7};
  std::vector<double> Vector2{5, 6, 7};
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  ++it, ++it2;
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<double>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest966, Insert2) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest967, Insert2) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<char>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest968, Insert2) {
  s21::vector<double> Vector;
  std::vector<double> Vector2;
  auto it = Vector.cbegin();
  auto it2 = Vector2.cbegin();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  auto it4 = Vector2.cbegin();
  for (s21::vector<double>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest969, Insert3) {
  s21::vector<int> Vector;
  std::vector<int> Vector2;
  auto it = Vector.cend();
  auto it2 = Vector2.cend();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  it = Vector.cend();
  it2 = Vector2.cend();
  Vector.insert(it, 67);
  Vector2.insert(it2, 67);
  auto it4 = Vector2.cbegin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest970, Insert3) {
  s21::vector<double> Vector;
  std::vector<double> Vector2;
  auto it = Vector.cend();
  auto it2 = Vector2.cend();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  it = Vector.cend();
  it2 = Vector2.cend();
  Vector.insert(it, 67);
  Vector2.insert(it2, 67);
  auto it4 = Vector2.cbegin();
  for (s21::vector<double>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest971, Insert3) {
  s21::vector<char> Vector;
  std::vector<char> Vector2;
  auto it = Vector.cend();
  auto it2 = Vector2.cend();
  Vector.insert(it, 21);
  Vector2.insert(it2, 21);
  it = Vector.cend();
  it2 = Vector2.cend();
  Vector.insert(it, 67);
  Vector2.insert(it2, 67);
  auto it4 = Vector2.cbegin();
  for (s21::vector<char>::iterator it3 = Vector.begin(); it3 != Vector.end();
       it3++) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest972, Erase) {
  s21::vector<int> Vector{21, 22, 23, 22, 21};
  std::vector<int> Vector2{21, 22, 23, 22, 21};
  auto it = Vector.begin();
  auto it2 = Vector2.begin();
  Vector2.erase(it2);
  Vector.erase(it);
  auto it4 = Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest973, Erase) {
  s21::vector<double> Vector{21, 22, 23, 22, 21};
  std::vector<double> Vector2{21, 22, 23, 22, 21};
  auto it = Vector.begin();
  auto it2 = Vector2.begin();
  Vector2.erase(it2);
  Vector.erase(it);
  auto it4 = Vector2.begin();
  for (s21::vector<double>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest974, Erase) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  auto it = Vector.begin();
  auto it2 = Vector2.begin();
  Vector2.erase(it2);
  Vector.erase(it);
  auto it4 = Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest975, PushBack) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
  std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};
  Vector2.push_back(1);
  Vector.push_back(1);
  auto it4 = Vector2.begin();
  for (s21::vector<char>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest976, PushBack) {
  s21::vector<int> Vector{1, 2, 3, 4, 5};
  std::vector<int> Vector2{1, 2, 3, 4, 5};
  Vector2.push_back(1);
  Vector.push_back(1);
  auto it4 = Vector2.begin();
  for (s21::vector<int>::iterator it3 = Vector.begin(); it3 != Vector.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), Vector2.size());
  ASSERT_EQ(Vector.capacity(), Vector2.capacity());
}

TEST(VectorTest977, Swap) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  s21::vector<int> Copy_Vector{21, 22, 23, 22, 21, 1};
  s21::vector<int> Vector2{15, 1};
  s21::vector<int> Copy_Vector2{15, 1};

  Vector.swap(Copy_Vector2);
  Vector2.swap(Copy_Vector);

  auto it1 = Copy_Vector.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

TEST(VectorTest978, Swap) {
  s21::vector<double> Vector{21, 22, 23, 22, 21, 1};
  s21::vector<double> Copy_Vector{21, 22, 23, 22, 21, 1};
  s21::vector<double> Vector2{15, 1};
  s21::vector<double> Copy_Vector2{15, 1};

  Vector.swap(Copy_Vector2);
  Vector2.swap(Copy_Vector);

  auto it1 = Copy_Vector.begin();
  for (s21::vector<double>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
  auto it4 = Copy_Vector2.begin();
  for (s21::vector<double>::iterator it3 = Vector2.begin();
       it3 != Vector2.end(); ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), 2);
  ASSERT_EQ(Vector2.size(), 6);
}

TEST(VectorTest979, Swap) {
  s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e', 'f'};
  s21::vector<char> Copy_Vector{'a', 'b', 'c', 'd', 'e', 'f'};
  s21::vector<char> Vector2{'z', 'y'};
  s21::vector<char> Copy_Vector2{'z', 'y'};

  Vector.swap(Copy_Vector2);
  Vector2.swap(Copy_Vector);

  auto it1 = Copy_Vector.begin();
  for (s21::vector<char>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
  auto it4 = Copy_Vector2.begin();
  for (s21::vector<char>::iterator it3 = Vector2.begin(); it3 != Vector2.end();
       ++it3) {
    ASSERT_EQ(*it3, *it4++);
  }
  ASSERT_EQ(Vector.size(), 2);
  ASSERT_EQ(Vector2.size(), 6);
}

TEST(VectorTest980, InsertManyBack) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  std::vector<int> Vector_Ans{21, 22, 23, 22, 21, 1, 2, 3, 4};
  Vector.insert_many_back(2, 3, 4);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

TEST(VectorTest981, InsertManyBack) {
  s21::vector<double> Vector{21, 22, 23, 22, 21, 1};
  std::vector<double> Vector_Ans{21, 22, 23, 22, 21, 1, 2, 3, 4};
  Vector.insert_many_back(2.0, 3.0, 4.0);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<double>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}

TEST(VectorTest, InsertMany2) {
  s21::vector<int> Vector{21, 22, 23, 22, 21, 1};
  std::vector<int> Vector_Ans{21, 22, 23, 22, 21, 2, 3, 4, 1};
  s21::vector<int>::const_iterator it = --(Vector.cend());
  Vector.insert_many(it, 2, 3, 4);
  auto it1 = Vector_Ans.begin();
  for (s21::vector<int>::iterator it2 = Vector.begin(); it2 != Vector.end();
       ++it2) {
    ASSERT_EQ(*it2, *it1++);
  }
}