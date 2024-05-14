#include "s21_stack.h"

template <class T>
s21::stack<T>::stack() : s21::list_like<T>::list_like() {}

template <class T>
s21::stack<T>::stack(std::initializer_list<value_type> const &items) : stack() {
  for (auto it : items) {
    push(it);
  }
}

template <class T>
s21::stack<T>::stack(const s21::stack<T> &src)
    : s21::list_like<T>::list_like(src) {}

template <class T>
s21::stack<T>::stack(s21::stack<T> &&src) : stack() {
  this->~stack();
  s21::list_like<T>::MovingWrap(std::move(src));
}

template <class T>
s21::stack<T>::~stack() {
  s21::list_like<T>::clear();
  delete s21::list_like<T>::fake_;
}

template <class T>
s21::stack<T> s21::stack<T>::operator=(const s21::stack<T> &src) {
  clear();
  s21::list_like<T>::operator=(src);
}

template <class T>
s21::stack<T> s21::stack<T>::operator=(s21::stack<T> &&src) {
  this->~stack();
  s21::list_like<T>::MovingWrap(std::move(src));
}

template <class T>
void s21::stack<T>::clear() {
  s21::list_like<T>::clear();
}

template <class T>
void s21::stack<T>::pop() {
  s21::list_like<T>::pop_front();
}

template <class T>
void s21::stack<T>::push(const_reference value_type) {
  s21::list_like<T>::push_front(value_type);
}

template <class T>
inline const T &s21::stack<T>::top() {
  return s21::list_like<T>::front();
}

template <class T>
inline bool s21::stack<T>::empty() {
  return s21::list_like<T>::empty();
}

template <class T>
inline size_t s21::stack<T>::size() {
  return s21::list_like<T>::size();
}

template <class T>
void s21::stack<T>::swap(s21::stack<T> &src) {
  s21::list_like<T>::swap(src);
}

template <class T>
template <class... Args>
void s21::stack<T>::insert_many(Args &&...args) {
  for (auto &it : {args...}) {
    push(it);
  }
}