#include "s21_set.h"

// Set Constructor, Dectructors and operator overload

template <class T>
s21::set<T>::set() : s21::map<T, T>::map() {}

template <class T>
s21::set<T>::set(const std::initializer_list<T> &items) : set() {
  for (auto it : items) {
    insert(it);
  }
}

template <class T>
s21::set<T>::set(const s21::set<T> &s) : set() {
  for (iterator it = s.begin(); it != s.end(); it++) {
    insert((*it));
  }
}

template <class T>
s21::set<T>::set(s21::set<T> &&s) : s21::map<T, T>::map(std::move(s)) {}

// template<class T>
// s21::set<T>::~set() {}

template <class T>
void s21::set<T>::operator=(s21::set<T> &&s) {
  s21::map<T, T>::operator=(std::move(s));
}

template <class T>
typename s21::set<T>::iterator s21::set<T>::begin() const {
  return s21::map<T, T>::begin();
}

template <class T>
typename s21::set<T>::iterator s21::set<T>::end() const {
  return s21::map<T, T>::end();
}

template <class T>
bool s21::set<T>::empty() {
  return s21::map<T, T>::empty();
}

template <class T>
size_t s21::set<T>::size() {
  return s21::map<T, T>::size();
}

template <class T>
size_t s21::set<T>::max_size() {
  return s21::map<T, T>::max_size();
}

template <class T>
void s21::set<T>::clean() {
  s21::map<T, T>::clean();
}

template <class T>
std::pair<typename s21::set<T>::iterator, bool> s21::set<T>::insert(
    const T &value) {
  return s21::map<T, T>::insert(value, value);
}

template <class T>
template <class... Args>
s21::vector<std::pair<typename s21::set<T>::iterator, bool>>
s21::set<T>::insert_many(Args &&...args) {
  s21::vector<std::pair<typename s21::set<T>::iterator, bool>> res;
  for (auto it : {args...}) {
    res.push_back(insert(it));
  }
  return res;
}

template <class T>
void s21::set<T>::erase(s21::set<T>::iterator pos) {
  s21::map<T, T>::erase(pos);
}

template <class T>
void s21::set<T>::swap(s21::set<T> &other) {
  s21::map<T, T>::swap(other);
}

template <class T>
void s21::set<T>::merge(s21::set<T> &other) {
  s21::map<T, T>::merge(other);
}

template <class T>
typename s21::set<T>::iterator s21::set<T>::find(const T &key) {
  return s21::map<T, T>::find(key);
}

template <class T>
bool s21::set<T>::contains(const T &key) {
  return s21::map<T, T>::contains(key);
}

// Set iterator

template <class T>
s21::set<T>::SetIterator::SetIterator() : map<T, T>::Mapiterator() {}

template <class T>
s21::set<T>::SetIterator::SetIterator(typename s21::map<T, T>::MapIterator it)
    : map<T, T>::MapIterator(it) {}

template <class T>
T s21::set<T>::SetIterator::operator*() {
  return map<T, T>::MapIterator::operator*().first;
}

// Const set iterator

template <class T>
s21::set<T>::ConstSetIterator::ConstSetIterator() : SetIterator() {}
