#ifndef __CPP_CONTAINERS_SRC_LIB_STACK__
#define __CPP_CONTAINERS_SRC_LIB_STACK__

#include "../list-like/s21_list_like.h"

namespace s21 {
template <typename T>
class stack : public list_like<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &src);
  stack(stack &&src);
  ~stack();

  stack<T> operator=(const stack &src);
  stack<T> operator=(stack &&src);

  const_reference top();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(stack &src);
  template <typename... Args>
  void insert_many(Args &&...args);

  void clear();
};

}  // namespace s21

#include "s21_stack.cc"

#endif  // __CPP_CONTAINERS_SRC_LIB_STACK__