#ifndef __CPP_CONTAINERS_SRC_LIB_QUEUE__
#define __CPP_CONTAINERS_SRC_LIB_QUEUE__
#include "../list-like/s21_list_like.h"

namespace s21 {
template <typename T>
class queue : private list_like<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using node_type = typename list_like<T>::Node_t;

 private:
 public:
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &other);
  queue(queue &&other);
  ~queue();
  queue<T> operator=(const queue &other);
  queue<T> operator=(queue &&other);

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  template <typename... Args>
  void insert_many_back(Args &&...args);
  void pop();
  void swap(queue &other);
  void clear();
};
};  // namespace s21

#include "s21_queue.cc"

#endif  // __CPP_CONTAINERS_SRC_LIB_QUEUE__
