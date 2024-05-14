#include "s21_list.h"

template <class T>
s21::list<T>::list() : list_like<T>::list_like() {
  s21::list_like<T>::size_ = 0;
}

template <class T>
s21::list<T>::list(size_type n) : list_like<T>::list_like(n) {}

template <class T>
s21::list<T>::list(const std::initializer_list<T> &items)
    : list_like<T>::list_like(items) {}

template <class T>
s21::list<T>::list(const s21::list<T> &l) : list_like<T>::list_like(l) {}

template <class T>
s21::list<T>::list(s21::list<T> &&l) : list_like<T>::list_like(std::move(l)) {}

template <class T>
s21::list<T>::~list() {
  s21::list_like<T>::clear();
  delete s21::list_like<T>::fake_;
}
template <class T>
s21::list<T> &s21::list<T>::operator=(const s21::list<T> &l) {
  if (this != &l) {
    if (size() != 0) {
      list_like<T>::clear();
    }
    if (!list_like<T>::fake_) {
      list_like<T>::initNull_();
    }
    node_type *temp = l.head_;
    if (temp) {
      while (temp != l.fake_) {
        push_back(temp->data_);
        temp = temp->ptr_next_;
      }
    }
  }
  return *this;
}
template <class T>
s21::list<T> &s21::list<T>::operator=(s21::list<T> &&l) {
  if (this != &l) {
    list<T> temp(std::move(l));
    *this = temp;
  }
  return *this;
}

template <class T>
s21::list<T> &s21::list<T>::operator=(const std::initializer_list<T> &items) {
  if (size()) {
    list_like<T>::clear();
  }
  for (T it : items) {
    push_back(it);
  }
  return *this;
}

template <class T>
const T &s21::list<T>::front() const noexcept {
  return list_like<T>::front();
}

template <class T>
const T &s21::list<T>::back() const noexcept {
  return list_like<T>::back();
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::begin() noexcept {
  return ListIterator(list_like<T>::head_);
}

template <class T>
typename s21::list<T>::const_iterator s21::list<T>::cbegin() noexcept {
  return begin();
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::end() noexcept {
  return ListIterator(list_like<T>::fake_);
}

template <class T>
typename s21::list<T>::const_iterator s21::list<T>::cend() noexcept {
  return end();
}

template <class T>
bool s21::list<T>::empty() const noexcept {
  return list_like<T>::empty();
}

template <class T>
size_t s21::list<T>::size() const noexcept {
  return list_like<T>::size();
}

template <class T>
size_t s21::list<T>::max_size() const noexcept {
  return (std::numeric_limits<std::size_t>::max() / (sizeof(node_type) * 2));
}

template <class T>
void s21::list<T>::clear() noexcept {
  list_like<T>::clear();
}

template <class T>
typename s21::list<T>::iterator s21::list<T>::insert(s21::list<T>::iterator pos,
                                                     const T &value) {
  if (pos.ptr_ == list_like<T>::head_) {
    list_like<T>::push_front(value);
    pos.ptr_ = list_like<T>::head_;
  } else if (pos.ptr_ == list_like<T>::fake_) {
    push_back(value);
    pos.ptr_ = list_like<T>::tail_;
  } else {
    node_type *new_node = s21::list<T>::node_allocator(value);
    node_type *next_node = pos.ptr_;
    node_type *prev_node = next_node->ptr_prev_;

    new_node->ptr_next_ = next_node;
    new_node->ptr_prev_ = prev_node;
    prev_node->ptr_next_ = new_node;
    next_node->ptr_prev_ = new_node;
    pos.ptr_ = new_node;
    this->size_++;
  }
  return pos;
}

template <class T>
template <class... Args>
typename s21::list<T>::iterator s21::list<T>::insert_many(
    s21::list<T>::const_iterator pos, Args &&...args) {
  iterator temp = pos;
  for (auto it : {args...}) {
    temp = insert(temp, it);
    temp++;
  }
  return temp;
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

template <class T>
template <class... Args>
void s21::list<T>::insert_many_front(Args &&...args) {
  insert_many(begin(), args...);
}

template <class T>
void s21::list<T>::erase(s21::list<T>::iterator pos) noexcept {
  node_type *ptr = pos.ptr_;
  if (ptr == list_like<T>::head_) list_like<T>::head_ = ptr->ptr_next_;
  if (ptr == list_like<T>::tail_) list_like<T>::tail_ = ptr->ptr_prev_;
  node_type *prev_node = ptr->ptr_prev_;
  node_type *next_node = ptr->ptr_next_;
  prev_node->ptr_next_ = next_node;
  next_node->ptr_prev_ = prev_node;
  list_like<T>::size_--;
  delete ptr;
}

template <class T>
void s21::list<T>::push_back(const_reference value) {
  list_like<T>::push_back(value);
}

template <class T>
void s21::list<T>::push_front(const T &value) {
  std::cout << "value = " << value << "\n";
  if (!list_like<T>::head_ || list_like<T>::head_ == list_like<T>::fake_) {
    push_back(value);
  } else {
    node_type *new_ptr = new node_type(value);
    new_ptr->ptr_prev_ = list_like<T>::fake_;
    list_like<T>::fake_->ptr_next_ = new_ptr;

    new_ptr->ptr_next_ = list_like<T>::head_;
    list_like<T>::head_->ptr_prev_ = new_ptr;

    list_like<T>::head_ = new_ptr;
  }
  list_like<T>::size_ += 1;
  list_like<T>::fake_->data_ = list_like<T>::size_;
}

template <class T>
void s21::list<T>::pop_back() {
  node_type *ptr = list_like<T>::tail_;
  list_like<T>::tail_ = list_like<T>::tail_->ptr_prev_;
  list_like<T>::tail_->ptr_next_ = list_like<T>::fake_;
  list_like<T>::fake_->ptr_prev_ = list_like<T>::tail_;
  delete ptr;
  list_like<T>::size_--;
}

template <class T>
void s21::list<T>::pop_front() {
  node_type *ptr = list_like<T>::head_;
  list_like<T>::head_ = list_like<T>::head_->ptr_next_;
  list_like<T>::head_->ptr_prev_ = list_like<T>::fake_;
  list_like<T>::fake_->ptr_next_ = list_like<T>::head_;
  delete ptr;
  list_like<T>::size_--;
}

template <class T>
void s21::list<T>::swap(s21::list<T> &other) noexcept {
  node_type *temp_head_ = list_like<T>::head_;
  node_type *temp_tail_ = list_like<T>::tail_;
  node_type *temp_fake_ = list_like<T>::fake_;
  size_t temp_size_ = list_like<T>::size_;

  if (other.head_ || list_like<T>::head_) {
    list_like<T>::head_ = other.head_;
    other.head_ = temp_head_;
  }
  if (other.tail_ || list_like<T>::tail_) {
    list_like<T>::tail_ = other.tail_;
    other.tail_ = temp_tail_;
  }
  list_like<T>::fake_ = other.fake_;
  other.fake_ = temp_fake_;
  list_like<T>::size_ = other.size_;
  other.size_ = temp_size_;
}

template <class T>
void s21::list<T>::merge(s21::list<T> &other) {
  if (this != &other) {
    list<T> temp;
    temp = *this;
    MergeSort_(temp, other, *this);
    other.clear();
  }
}

template <class T>
void s21::list<T>::splice(s21::list<T>::const_iterator pos,
                          s21::list<T> &other) noexcept {
  if (!other.empty()) {
    for (s21::list<T>::ListIterator it = other.begin(); it != other.end();
         ++it) {
      insert(pos, *it);
    }
    other.clear();
  }
}

template <class T>
void s21::list<T>::reverse() noexcept {
  node_type *ptr_it = list_like<T>::head_;
  node_type *ptr_temp = list_like<T>::head_->ptr_next_;
  node_type *temp = list_like<T>::head_;
  list_like<T>::head_ = list_like<T>::tail_;
  list_like<T>::tail_ = temp;

  while (ptr_it != list_like<T>::fake_) {
    ptr_it->ptr_next_ = ptr_it->ptr_prev_;
    ptr_it->ptr_prev_ = ptr_temp;

    ptr_it = ptr_temp;
    ptr_temp = ptr_temp->ptr_next_;
  }
  list_like<T>::fake_->ptr_next_ = list_like<T>::head_;
  list_like<T>::fake_->ptr_prev_ = list_like<T>::tail_;
}

template <class T>
void s21::list<T>::unique() {
  if (list_like<T>::size_ <= 1) return;
  auto it = begin();
  auto it_next = begin()++;
  list<T> temp;
  while (it != end()) {
    if (*it == *it_next) {
      ++it;
      ++it_next;
      continue;
    } else {
      temp.push_back(*it);
    }
    ++it_next;
    ++it;
  }
  *this = std::move(temp);
}

template <class T>
void s21::list<T>::sort() {
  if (list_like<T>::size_ <= 1) return;
  int half = list_like<T>::size_ / 2;
  list<T> left, right;

  for (int i = 0; i < half; i++) {
    auto left_it = begin() + i;
    left.push_back(*left_it);
  }

  for (int i = half; i < static_cast<int>(list_like<T>::size_); i++) {
    auto right_it = begin() + i;
    right.push_back(*right_it);
  }

  left.sort();
  right.sort();
  MergeSort_(left, right, *this);
}

// Private list method

template <class T>
void s21::list<T>::MergeSort_(s21::list<T> &left, s21::list<T> &right,
                              s21::list<T> &res) {
  list<T> temp;
  int l_index = 0, r_index = 0;
  s21::list<T>::ListIterator left_iter = left.begin();
  s21::list<T>::ListIterator right_iter = right.begin();

  while ((l_index < static_cast<int>(left.size_)) &&
         (r_index < static_cast<int>(right.size_))) {
    left_iter = left.begin() + l_index;
    right_iter = right.begin() + r_index;
    if (*left_iter <= *right_iter) {
      temp.push_back(*left_iter);
      ++l_index;
    } else {
      temp.push_back(*right_iter);
      ++r_index;
    }
  }

  while (l_index < static_cast<int>(left.size_)) {
    temp.push_back(*left_iter);
    ++left_iter;
    ++l_index;
  }

  while (r_index < static_cast<int>(right.size_)) {
    temp.push_back(*right_iter);
    ++right_iter;
    ++r_index;
  }
  res = temp;
}

template <class T>
void s21::list<T>::print() noexcept {
  node_type *ptr = this->head_;
  if (ptr != nullptr) {
    while (ptr != list_like<T>::fake_) {
      std::cout << ptr->data_ << " ";
      ptr = ptr->ptr_next_;
    }
    std::cout << "\n";
  }
  std::cout << "Size = " << this->size_ << "\n";
}

// List iterator methods

template <class T>
s21::list<T>::ListIterator::ListIterator() noexcept : ptr_(nullptr) {}

template <class T>
s21::list<T>::ListIterator::ListIterator(s21::list<T>::node_type *node)
    : ptr_(node) {}

template <class T>
s21::list<T>::ListIterator::ListIterator(
    const s21::list<T>::ListIterator &other) noexcept
    : ptr_(other.ptr_) {}

template <class T>
T &s21::list<T>::ListIterator::operator*() {
  return ptr_->data_;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator++() {
  ptr_ = ptr_->ptr_next_;
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator++(
    int b) {
  return operator++();
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator--() {
  ptr_ = ptr_->ptr_prev_;
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator--(
    int b) {
  ptr_ = ptr_->ptr_prev_;
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator &s21::list<T>::ListIterator::operator=(
    const s21::list<T>::ListIterator &other) {
  ptr_ = other.ptr_;
  return *this;
}

template <class T>
typename s21::list<T>::ListIterator s21::list<T>::ListIterator::operator+(
    size_type b) {
  auto temp = *this;
  while (b-- > 0) {
    temp.operator++();
  }
  return temp;
}

template <class T>
bool s21::list<T>::ListIterator::operator==(s21::list<T>::ListIterator other) {
  return ptr_ == other.ptr_;
}

template <class T>
bool s21::list<T>::ListIterator::operator!=(s21::list<T>::ListIterator other) {
  // return ptr_ != other.ptr_;
  return !operator==(other);
}

// Const list iterator methods

template <class T>
s21::list<T>::ConstListIterator::ConstListIterator() : ListIterator() {}

template <class T>
s21::list<T>::ConstListIterator::ConstListIterator(s21::list<T>::iterator other)
    : ListIterator(other) {}

template <class T>
const T &s21::list<T>::ConstListIterator::operator*() {
  return ListIterator::ptr_->data_;
}

template <class T>
typename s21::list<T>::ConstListIterator
s21::list<T>::ConstListIterator::operator++() {
  return ListIterator::operator++();
}

template <class T>
typename s21::list<T>::ConstListIterator
s21::list<T>::ConstListIterator::operator++(int b) {
  return operator++();
}

template <class T>
typename s21::list<T>::ConstListIterator
s21::list<T>::ConstListIterator::operator--() {
  return ListIterator::operator--();
}

template <class T>
typename s21::list<T>::ConstListIterator
s21::list<T>::ConstListIterator::operator--(int b) {
  return operator--();
}
