#include "s21_queue.h"

template <class T>
s21::queue<T>::queue() : s21::list_like<T>::list_like() {}

template <class T>
s21::queue<T>::queue(const std::initializer_list<T> &items)
    : list_like<T>::list_like(items) {}

template <class T>
s21::queue<T>::queue(const queue &other) : list_like<T>::list_like(other) {}

template <class T>
s21::queue<T>::queue(s21::queue<T> &&other)
    : list_like<T>::list_like(std::move(other)) {}

template <class T>
s21::queue<T>::~queue() {
  clear();
  if (list_like<T>::fake_ != nullptr) {
    delete list_like<T>::fake_;
  }
}

template <class T>
s21::queue<T> s21::queue<T>::operator=(const s21::queue<T> &other) {
  if (this != &other) {
    clear();
    node_type *ptr = other.head_;
    while (ptr != other.fake_) {
      push(ptr->data_);
      ptr = ptr->ptr_next_;
    }
  }
  return *this;
}

template <class T>
s21::queue<T> s21::queue<T>::operator=(s21::queue<T> &&other) {
  if (this != &other) {
    this->~queue();
    list_like<T>::MovingWrap(std::move(other));
  }
  return *this;
}

template <class T>
const T &s21::queue<T>::front() const {
  return list_like<T>::front();
}

template <class T>
const T &s21::queue<T>::back() const {
  return list_like<T>::back();
}

template <class T>
inline bool s21::queue<T>::empty() const {
  return list_like<T>::empty();
}

template <class T>
size_t s21::queue<T>::size() const {
  return list_like<T>::size();
}

template <class T>
void s21::queue<T>::push(const_reference value) {
  list_like<T>::push_back(value);
}

template <class T>
template <class... Args>
void s21::queue<T>::insert_many_back(Args &&...args) {
  for (auto &it : {args...}) {
    push(it);
  }
}

template <class T>
void s21::queue<T>::pop() {
  list_like<T>::pop_front();
}

template <class T>
void s21::queue<T>::swap(queue &other) {
  s21::list_like<T>::swap(other);
}

template <class T>
void s21::queue<T>::clear() {
  while (list_like<T>::size_) {
    pop();
  }
}