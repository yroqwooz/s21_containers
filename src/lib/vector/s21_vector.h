#ifndef CPP2_S21_CONTAINERS_VECTOR_H_
#define CPP2_S21_CONTAINERS_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>

namespace s21 {
template <class T>
class vector {
 public:
  struct iterator;
  struct const_iterator;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  struct iterator {
   public:
    T* ptr;
    iterator();
    iterator(T* p);

    reference operator*();
    bool operator!=(const iterator& other);
    bool operator==(const iterator& other);
    iterator& operator++();
    iterator& operator--();
    iterator operator++(int);
    iterator operator--(int);
    void operator+=(const size_type& other);
    size_type operator-(const iterator& other);
    size_type operator+(const iterator& other);
  };

  struct const_iterator : public iterator {
   public:
    const_iterator();
    const_iterator(T* p);

    void operator=(iterator src) { this->ptr = src.ptr; }

    const_reference operator*();
    const_iterator& operator--();
  };

  vector() noexcept;
  vector(size_type n);
  vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector();
  vector& operator=(vector&& v) noexcept;

  /*
  Vector Element access
  */

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T* data() noexcept;

  /*
  Vector Iterators
  */

  iterator begin() noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator cend() const noexcept;

  /*
  Vector Capacity
  */

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  /*
  Vector Modifiers
  */

  void kill_vector();
  void clear();
  iterator insert(const_iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other);

  // Dop
  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

 protected:
  void resize(size_type size);
  T* array_;
  size_type size_;
  size_type capacity_;

  std::allocator<value_type> alloc_;
};
}  // namespace s21

#include "s21_vector.cc"
#endif  // CPP2_S21_CONTAINERS_VECTOR_H_