#ifndef CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#include "../vector/s21_vector.h"

namespace s21 {
template <class T, std::size_t N>
class array : protected vector<T> {
 public:
  // | Member type            | definition
  // | `value_type`             | `T` defines the type of an element (T is
  // template parameter) | `reference`              | `T &` defines the type of
  // the reference to an element | `const_reference`        | `const T &`
  // defines the type of the constant reference | `iterator`               | `T
  // *` defines the type for iterating through the container | `const_iterator`
  // | `const T *` defines the constant type for iterating through the container
  // | `size_type`              | `size_t` defines the type of the container
  // size (standard type is size_t) |
  using value_type = typename s21::vector<T>::value_type;
  using reference = typename s21::vector<T>::reference;
  using const_reference = typename s21::vector<T>::const_reference;
  using iterator = typename s21::vector<T>::iterator;
  using const_iterator = typename s21::vector<T>::const_iterator;
  using size_type = typename s21::vector<T>::size_type;

  // *Array Member functions*

  // | `array()`  | default constructor, creates empty array
  // | `array(std::initializer_list<value_type> const &items)`  | initializer
  // list constructor, creates array initizialized using
  // std::initializer_list<T> | `array(const array &a)`  | copy constructor |
  // `array(array &&a)`  | move constructor | `~array()`  | destructor  | |
  // `operator=(array &&a)`      | assignment operator overload for moving
  // object
  array() : vector<T>(N) {}
  array(std::initializer_list<value_type> const &items) : vector<T>(items) {}
  array(const array &a) : vector<T>(a) {}
  array(array &&a) noexcept : vector<T>(a) {}
  ~array() {}

  array<T, N> &operator=(array &&a) noexcept {
    if (this != &a) {
      std::move(a.array_, a.array_ + size_, array_);
    }
    return *this;
  }

  // *Array Iterators*
  // отнаследовано
  // |----------------|-------------------------------------------------|
  // | `iterator begin()`    | returns an iterator to the beginning            |
  // | `iterator end()`        | returns an iterator to the end |

  // *Array Element access*

  // | `reference at(size_type pos)`                     | access specified
  // element with bounds checking | `reference operator[](size_type pos)` |
  // access specified element | `const_reference front()`          | access the
  // first element | `const_reference back()`           | access the last
  // element

  // отнаследовано
  // | `iterator data()`                   | direct access to the underlying
  // array

  reference at(size_type pos) {
    if (pos >= size_ || size_ == 0) {
      throw std::out_of_range("Index out range");
    }
    return vector<T>::at(pos);
  }
  reference operator[](size_type pos) { return vector<T>::operator[](pos); }
  const_reference front() { return vector<T>::front(); }
  const_reference back() { return vector<T>::back(); }

  // *Array Capacity*
  // отнаследовано
  // | `bool empty()`          | checks whether the container is empty | |
  // `size_type max_size()`       | returns the maximum possible number of
  // elements |

  size_type size() { return size_; }

  void swap(array &other) { vector<T>::swap(other); }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) {
      array_[i] = value;
    }
  }

 private:
  using vector<T>::array_;
  using vector<T>::size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_ARRAY_S21_ARRAY_H_

// s21::vector<char> Vector{'a', 'b', 'c', 'd', 'e'};
// std::vector<char> Vector2{'a', 'b', 'c', 'd', 'e'};