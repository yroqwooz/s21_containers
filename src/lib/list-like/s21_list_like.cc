#include "s21_list_like.h"

template <class T>
s21::list_like<T>::list_like() : head_(nullptr), tail_(nullptr), size_(0) {
  initNull_();
}

template <class T>
s21::list_like<T>::list_like(size_t n) : list_like<T>::list_like() {
  while (n-- > 0) {
    push_back(T());
  }
}

template <class T>
s21::list_like<T>::list_like(const std::initializer_list<T> &items)
    : list_like<T>::list_like() {
  for (T it : items) {
    push_back(it);
  }
}

template <class T>
s21::list_like<T>::list_like(const s21::list_like<T> &other)
    : list_like<T>::list_like() {
  // *this = other;
  if (other.head_ != nullptr) {
    for (auto it = other.head_; it != other.fake_;) {
      push_back(it->data_);
      it = it->ptr_next_;
    }
  }
}

template <class T>
s21::list_like<T>::list_like(s21::list_like<T> &&other) {
  MovingWrap(std::move(other));
}

template <class T>
s21::list_like<T>::~list_like() {}

template <class T>
size_t s21::list_like<T>::size() const {
  return size_;
}

template <class T>
bool s21::list_like<T>::empty() const noexcept {
  return size() ? false : true;
}

template <class T>
const T &s21::list_like<T>::front() const noexcept {
  return head_ ? head_->data_ : fake_->data_;
}

template <class T>
const T &s21::list_like<T>::back() const noexcept {
  return tail_ ? tail_->data_ : fake_->data_;
}

template <class T>
void s21::list_like<T>::push_back(const T &value) {
  Node_t *new_ptr = node_allocator(value);
  if (head_ == nullptr || head_ == fake_) {
    head_ = new_ptr;
    head_->ptr_next_ = fake_;
    head_->ptr_prev_ = fake_;
    fake_->ptr_next_ = head_;
    fake_->ptr_prev_ = head_;
    tail_ = head_;
  } else if (tail_ == head_) {
    tail_ = new_ptr;
    tail_->ptr_next_ = fake_;
    tail_->ptr_prev_ = head_;
    fake_->ptr_prev_ = tail_;
    head_->ptr_next_ = tail_;
  } else {
    new_ptr->ptr_prev_ = tail_;
    tail_->ptr_next_ = new_ptr;
    tail_ = new_ptr;
    fake_->ptr_prev_ = tail_;
    tail_->ptr_next_ = fake_;
  }
  size_ += 1;
  fake_->data_ = size_;
}

template <class T>
void s21::list_like<T>::push_front(const T &value) {
  if (!head_ || head_ == fake_) {
    push_back(value);
  } else {
    Node_t *new_ptr = new Node_t(value);
    new_ptr->ptr_prev_ = fake_;
    fake_->ptr_next_ = new_ptr;

    new_ptr->ptr_next_ = head_;
    head_->ptr_prev_ = new_ptr;

    head_ = new_ptr;
    size_ += 1;
  }
  fake_->data_ = size_;
}
template <class T>
void s21::list_like<T>::pop_front() {
  Node_t *ptr = head_;
  head_ = head_->ptr_next_;
  head_->ptr_prev_ = fake_;
  fake_->ptr_next_ = head_;
  delete ptr;
  --size_;
}

template <class T>
void s21::list_like<T>::swap(s21::list_like<T> &other) {
  Node_t *temp_head_ = head_;
  Node_t *temp_tail_ = tail_;
  Node_t *temp_fake_ = fake_;
  size_t temp_size_ = size_;

  if (other.head_ || head_) {
    head_ = other.head_;
    other.head_ = temp_head_;
  }
  if (other.tail_ || tail_) {
    tail_ = other.tail_;
    other.tail_ = temp_tail_;
  }
  fake_ = other.fake_;
  other.fake_ = temp_fake_;
  size_ = other.size_;
  other.size_ = temp_size_;
}

template <class T>
void s21::list_like<T>::clear() {
  while (this->size_) {
    pop_front();
  }
}

template <class T>
s21::list_like<T> &s21::list_like<T>::operator=(
    const s21::list_like<T> &other) {
  if (this != &other) {
    if (size() != 0) {
      clear();
    }
    if (!fake_) {
      initNull_();
    }
    Node_t *temp = other.head_;
    if (temp) {
      while (temp != other.fake_) {
        push_back(temp->data_);
        temp = temp->ptr_next_;
      }
    }
  }
  return *this;
}

template <class T>
typename s21::list_like<T>::Node_t *s21::list_like<T>::node_allocator(
    const T &data) {
  Node_t *ptr = nullptr;
  try {
    ptr = new Node_t(data);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return ptr;
}

template <class T>
void s21::list_like<T>::initNull_() {
  fake_ = node_allocator(T());
}

template <class T>
void s21::list_like<T>::MovingWrap(s21::list_like<T> &&other) {
  if (this != &other) {
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    fake_ = other.fake_;

    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.fake_ = nullptr;

    other.initNull_();
  }
}

// Node_t methods

template <class T>
s21::list_like<T>::Node_t::Node_t() : ptr_next_(nullptr), ptr_prev_(nullptr) {}

template <class T>
s21::list_like<T>::Node_t::Node_t(const_reference value)
    : ptr_next_(nullptr), ptr_prev_(nullptr), data_(value) {}
