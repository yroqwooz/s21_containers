#ifndef __CPP_CONTAINERS_SRC_LIB_LIST_LIKE__
#define __CPP_CONTAINERS_SRC_LIB_LIST_LIKE__
#include <initializer_list>
#include <limits>
#include <memory>

namespace s21 {
template <typename T>
class list_like {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 protected:
  // template <typename value_type>
  class Node_t {
   private:
    friend class list_like<value_type>;
    friend class iterator;

   public:
    Node_t *ptr_next_;
    Node_t *ptr_prev_;
    value_type data_;

    Node_t();
    Node_t(const_reference value);
    ~Node_t() = default;
  };

 protected:
  Node_t *head_;
  Node_t *tail_;
  Node_t *fake_;
  size_type size_;

  list_like();
  list_like(size_type n);
  list_like(std::initializer_list<value_type> const &items);
  list_like(const list_like &other);
  list_like(list_like &&other);
  virtual ~list_like();

  list_like<T> &operator=(const list_like<T> &other);
  list_like<T> &operator=(list_like &&other);
  list_like<T> &operator=(std::initializer_list<value_type> const &items);

  size_type size() const;
  bool empty() const noexcept;

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_front();
  void swap(list_like &other);
  void clear();

  Node_t *node_allocator(value_type const &data);
  void initNull_();
  void MovingWrap(list_like<T> &&other);
};
};  // namespace s21

#include "s21_list_like.cc"
#endif  // __CPP_CONTAINERS_SRC_LIB_LIST_LIKE__