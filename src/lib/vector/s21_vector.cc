#include "s21_vector.h"

#include <cstring>
template <class T>
s21::vector<T>::vector() noexcept : array_(nullptr), size_(0), capacity_(0) {}

/**
 * @brief Construct a new s21::vector<T>::vector object
 * тесты ошибок не выдают
 * @tparam T
 * @param n
 */
template <class T>
s21::vector<T>::vector(size_type n) : size_(n), capacity_(n) {
  array_ = alloc_.allocate(n);
  for (size_type i = 0; i < size_; ++i) {
    new (array_ + i) T{};
  }
}

/**
 * @brief Construct a new s21::vector<T>::vector object
 * конструктор по initializer list
 * тесты ошибок не выдают
 * @tparam T
 * @param items
 */
template <class T>
s21::vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(items.size()) {
  array_ = alloc_.allocate(capacity_);
  if (array_ != nullptr) {
    std::uninitialized_copy(items.begin(), items.end(), array_);
  }
}

/**
 * @brief Construct a new s21::vector<T>::vector object
 * конструктор преноса
 * тесты ошибок не выдают
 */
template <class T>
s21::vector<T>::vector(vector &&v) noexcept
    : array_(nullptr), size_(0), capacity_(0) {
  std::swap(capacity_, v.capacity_);
  std::swap(size_, v.size_);
  std::swap(array_, v.array_);
}

/**
 * @brief Construct a new s21::vector<T>::vector object
 * конструктор копирования
 * тесты ошибок не выдают
 * @tparam T
 * @param v
 */
template <class T>
s21::vector<T>::vector(const vector &v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  if (v.capacity_ != 0) {
    array_ = alloc_.allocate(capacity_);
  }
  if (v.size_ != 0) {
    // std::memcpy(array_, v.array_, sizeof(value_type) * size_);
    std::uninitialized_copy(v.array_, v.array_ + v.size_, array_);
  }
}

/**
 * @brief Destroy the s21::vector<T>::vector object
 * ни утечек, ни ошибок
 * @tparam T
 */
template <class T>
s21::vector<T>::~vector() {
  if (array_ != nullptr) {
    kill_vector();
  };
}

/**
 * @brief nuff said
 * деаллокатор в контексте очистки памяти из под вектора

 */
template <class T>
void s21::vector<T>::kill_vector() {
  if (array_ != nullptr) {
    alloc_.deallocate(array_, capacity_);
    array_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }
}

/**
 * @brief
 * оператор =
 * ни утечек ни ошибок
 * @tparam T
 * @param v
 * @return s21::vector<T>&
 */
template <class T>
s21::vector<T> &s21::vector<T>::operator=(s21::vector<T> &&v) noexcept {
  kill_vector();
  std::swap(capacity_, v.capacity_);
  std::swap(size_, v.size_);
  std::swap(array_, v.array_);
  v.array_ = nullptr;
  v.capacity_ = 0;
  v.size_ = 0;

  return *this;
}

// Vector Iterators

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::cbegin()
    const noexcept {
  return const_iterator(array_);
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::begin() noexcept {
  return iterator(array_);
}

template <class T>
typename s21::vector<T>::const_iterator s21::vector<T>::cend() const noexcept {
  return const_iterator(array_ + size_);
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::end() noexcept {
  return const_iterator(array_ + size_);
}

// Vector Capacity

/**
 * @brief
 * is empty?
 * ошибок и утечек нет
 * @tparam T
 * @return true
 * @return false
 */
template <class T>
bool s21::vector<T>::empty() const noexcept {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief
 * ни утечек ни ошибок
 * @tparam T
 * @return size_t
 */
template <class T>
size_t s21::vector<T>::size() const noexcept {
  return size_;
}

template <class T>
size_t s21::vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
}

template <class T>
void s21::vector<T>::reserve(size_type new_cap) {
  if (new_cap <= size_) return;
  resize(new_cap);
  capacity_ = new_cap;
}

/**
 * @brief
 * capacity
 * ни утечек ни ошибок
 * @tparam T
 * @return size_t
 */
template <class T>
size_t s21::vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
void s21::vector<T>::shrink_to_fit() {
  if (size_ == capacity_) {
    return;
  }
  resize(size_);
  capacity_ = size_;
}

// Vector Element access

/**
 * @brief
 * @param pos позиция элементы значение которого нужно вывести
 * @return s21::vector<T>::reference - ссылка T&
 */
template <class T>
typename s21::vector<T>::reference s21::vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("(at()) error");
  } else {
    return array_[pos];
  }
}

/**
 * @brief
 * оператор []
 * @param pos позиция элементы значение которого нужно вывести
 * @return s21::vector<T>::reference ссылка T&
 */
template <class T>
typename s21::vector<T>::reference s21::vector<T>::operator[](size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("([]) error");
  } else {
    return array_[pos];
  }
}

/**
 * @brief
 * начало
 * @tparam T
 * @return const T& -- ссылка на начало массива
 */
template <class T>
const T &s21::vector<T>::front() {
  return *array_;
}

/**
 * @brief
 * последний элемент массива
 * @tparam T
 * @return const T& -- ссылка на конец массива
 */
template <class T>
const T &s21::vector<T>::back() {
  return *(array_ + size_ - 1);
}

/**
 * @brief
 * возвращает указатель на первый элемент вектора(?)
 * @tparam T
 * @return T*
 */
template <class T>
T *s21::vector<T>::data() noexcept {
  return array_;
}

// Vector Modifiers

/**
 * @brief
 * clear - делает size = 0
 * утечек и ошибок нет
 * @tparam T
 */
template <class T>
void s21::vector<T>::clear() {
  size_ = 0;
}

/**
 * @brief
 *
 * @tparam T
 * @param pos позиция для вставки
 * @param value значение для вставки
 * @return s21::vector<T>::iterator - итератор на вставленный элемент
 */
template <class T>
typename s21::vector<T>::iterator s21::vector<T>::insert(
    const_iterator pos, const_reference value) {
  size_type index = pos - cbegin();
  if (index > size_) {
    throw std::out_of_range("Аут оф ренж позишн \n position > size");
  }

  if (capacity_ == 0) {
    reserve(1);
  } else if (capacity_ == size_) {
    reserve(capacity_ * 2);
  }
  for (size_type i = size_; i != index; --i) {
    array_[i] = array_[i - 1];
  }
  ++size_;
  iterator it = begin();
  it += index;
  *it = value;
  return it;
}

/**
 * @brief
 *
 * @tparam T
 * @param pos
 */
template <class T>
void s21::vector<T>::erase(iterator pos) {
  if (pos == end()) throw("Error");
  size_type index = pos - begin();
  if (size_ != 0) {
    for (size_type i = index; i < (size_ - 1); ++i) {
      array_[i] = array_[i + 1];
    }
  }
  pop_back();
}

/**
 * @brief
 * вставить элемент в конец
 * @tparam T
 * @param value
 */
template <class T>
void s21::vector<T>::push_back(const_reference value) {
  if (capacity_ * 2 > this->max_size()) {
    throw std::out_of_range("Error in memory from push_back()");
  }
  if (!capacity_) {
    reserve(1);
  }
  if (size_ == capacity_) {
    reserve(2 * capacity_);
  }
  ++size_;
  array_[size_ - 1] = value;
}

/**
 * @brief
 * убрать элемент из конца
 * @tparam T
 */
template <class T>
void s21::vector<T>::pop_back() {
  if (!size_) {
    return;
  }
  --size_;
}

/**
 * @brief
 * обмен
 * @tparam T
 * @param other
 */
template <class T>
void s21::vector<T>::swap(vector &other) {
  std::swap(*this, other);
}

/**
 * @brief
 * функция помощник фукнциям reserve и shrink_to_fit
 * @tparam T
 * @param size
 */
template <class T>
void s21::vector<T>::resize(size_type size) {
  T *new_arr = alloc_.allocate(size);
  std::uninitialized_move(array_, array_ + size_, new_arr);
  alloc_.deallocate(array_, capacity_);
  array_ = new_arr;
  capacity_ = size;
}

template <class T>
s21::vector<T>::iterator::iterator() : ptr(nullptr) {}

template <class T>
s21::vector<T>::iterator::iterator(T *p) : ptr(p) {}

template <class T>
T &s21::vector<T>::iterator::operator*() {
  return *ptr;
}

template <class T>
bool s21::vector<T>::iterator::operator!=(
    const s21::vector<T>::iterator &other) {
  return ptr != other.ptr;
}

template <class T>
bool s21::vector<T>::iterator::operator==(
    const s21::vector<T>::iterator &other) {
  return ptr == other.ptr;
}

template <class T>
typename s21::vector<T>::iterator &s21::vector<T>::iterator::operator++() {
  ++ptr;
  return *this;
}

template <class T>
typename s21::vector<T>::iterator &s21::vector<T>::iterator::operator--() {
  --ptr;
  return *this;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator++(int) {
  auto copy_it = *this;
  ptr++;
  return copy_it;
}

template <class T>
typename s21::vector<T>::iterator s21::vector<T>::iterator::operator--(int) {
  auto copy_it = *this;
  ptr--;
  return copy_it;
}

template <class T>
void s21::vector<T>::iterator::operator+=(const size_type &other) {
  ptr += other;
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::iterator::operator-(
    const iterator &other) {
  return this->ptr - other.ptr;
}

template <class T>
typename s21::vector<T>::size_type s21::vector<T>::iterator::operator+(
    const iterator &other) {
  return this->ptr + other.ptr;
}

template <class T>
s21::vector<T>::const_iterator::const_iterator() : iterator() {}

template <class T>
s21::vector<T>::const_iterator::const_iterator(T *p) : iterator(p) {}

template <class T>
const T &s21::vector<T>::const_iterator::operator*() {
  return s21::vector<T>::iterator::operator*();
}

template <class T>
typename s21::vector<T>::const_iterator &
s21::vector<T>::const_iterator::operator--() {
  --(this->ptr);
  return *this;
}

template <class T>
template <class... Args>
typename s21::vector<T>::iterator s21::vector<T>::insert_many(
    s21::vector<T>::const_iterator pos, Args &&...args) {
  for (auto it : {args...}) {
    pos = insert(pos, it);
    pos++;
  }
  return pos;
}

template <class T>
template <class... Args>
void s21::vector<T>::insert_many_back(Args &&...args) {
  vector<T> copy{args...};
  for (auto it = copy.begin(); it != copy.end(); ++it) {
    push_back(*it);
  }
}
