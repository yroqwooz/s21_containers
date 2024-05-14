#include "s21_multiset.h"

template <class T>
s21::multiset<T>::multiset() : s21::map<T, T>::map() {}

template <class T>
s21::multiset<T>::multiset(const std::initializer_list<T> &items) : multiset() {
  for (auto it : items) {
    insert(it);
  }
}

template <class T>
s21::multiset<T>::multiset(const s21::multiset<T> &ms) : multiset() {
  for (iterator it = ms.begin(); it != ms.end(); it++) {
    insert((*it));
  }
}

template <class T>
s21::multiset<T>::multiset(s21::multiset<T> &&ms)
    : s21::map<T, T>::map(std::move(ms)) {}

template <class T>
s21::multiset<T>::~multiset() {
  clear();
  // check in valgrind
}

template <class T>
void s21::multiset<T>::operator=(const s21::multiset<T> &ms) {
  if (map<T, T>::size_) clear();
  for (auto it : ms) {
    insert(it.first);
  }
}

template <class T>
void s21::multiset<T>::operator=(s21::multiset<T> &&ms) {
  this = s21::map<T, T>::operator=(std::move(ms));
}

template <class T>
bool s21::multiset<T>::operator==(const s21::multiset<T> &ms) {
  bool status = true;
  auto it_this = begin();
  auto it_ms = ms.begin();

  for (; it_this != end() && it_ms != ms.end() && status == true;
       it_this++, it_ms++) {
    if (*it_this != *it_ms) {
      status = false;
    }
  }
  return status;
}

template <class T>
typename s21::multiset<T>::iterator s21::multiset<T>::begin() const {
  return s21::map<T, T>::begin();
}

template <class T>
typename s21::multiset<T>::iterator s21::multiset<T>::end() const {
  return s21::map<T, T>::end();
}

template <class T>
typename s21::multiset<T>::const_iterator s21::multiset<T>::cbegin() const {
  return s21::map<T, T>::cbegin();
}

template <class T>
typename s21::multiset<T>::const_iterator s21::multiset<T>::cend() const {
  return s21::map<T, T>::cend();
}

template <class T>
bool s21::multiset<T>::empty() {
  return s21::map<T, T>::empty();
}

template <class T>
size_t s21::multiset<T>::size() {
  return s21::map<T, T>::size();
}

template <class T>
size_t s21::multiset<T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         (sizeof(typename s21::map<T, T>::Node_t) * 2);
}

template <class T>
void s21::multiset<T>::clear() {
  s21::map<T, T>::clear();
}

template <class T>
typename s21::multiset<T>::MultisetIterator s21::multiset<T>::insert(
    const T &value) {
  return (insert_wrap(value).first);
}

template <class T>
template <class... Args>
s21::vector<std::pair<typename s21::multiset<T>::iterator, bool>>
s21::multiset<T>::insert_many(Args &&...args) {
  s21::vector<std::pair<typename s21::multiset<T>::iterator, bool>> res;
  for (auto &it : {args...}) {
    res.push_back(insert_wrap(it));
    // this->print();
  }
  return res;
}

template <class T>
void s21::multiset<T>::erase(s21::multiset<T>::iterator pos) {
  s21::map<T, T>::erase(pos);
}

template <class T>
void s21::multiset<T>::swap(s21::multiset<T> &other) {
  s21::map<T, T>::swap(other);
}

template <class T>
void s21::multiset<T>::merge(s21::multiset<T> &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    insert((*it));
  }
}

template <class T>
size_t s21::multiset<T>::count(const T &key) {
  auto range = equal_range(key);
  auto it_start = range.first;
  size_t res = 0;
  if (it_start.operator*() == key) {
    res = 1;
  }
  for (; it_start != range.second; it_start++) {
    if ((*it_start) == key) {
      res += 1;
    }
  }
  return res;
}

template <class T>
typename s21::multiset<T>::iterator s21::multiset<T>::find(const T &key) {
  return s21::map<T, T>::find(key);
}

template <class T>
bool s21::multiset<T>::contains(const T &key) {
  return s21::map<T, T>::contains(key);
}

template <class T>
std::pair<typename s21::multiset<T>::iterator,
          typename s21::multiset<T>::iterator>
s21::multiset<T>::equal_range(const T &key) {
  auto it = upper_bound(key);
  if (it.operator*() != key) {
    it--;
  }
  return {lower_bound(key), it};
}

template <class T>
typename s21::multiset<T>::iterator s21::multiset<T>::lower_bound(
    const T &key) {
  auto it = s21::map<T, T>::find(key);
  auto stop = begin();
  while (it.operator*().first == key && it != stop) {
    it--;
  }

  if (it.operator*().first != key) {
    it++;
  }
  return it;
}

template <class T>
typename s21::multiset<T>::iterator s21::multiset<T>::upper_bound(
    const T &key) {
  auto it = s21::map<T, T>::find(key);
  auto stop = end();
  while (it.operator*().first == key && it != stop) {
    it++;
  }
  return it;
}

// Multiset iterator
template <class T>
s21::multiset<T>::MultisetIterator::MultisetIterator()
    : map<T, T>::MapIterator() {}

template <class T>
s21::multiset<T>::MultisetIterator::MultisetIterator(
    const typename s21::map<T, T>::MapIterator &it)
    : map<T, T>::MapIterator(it) {}

template <class T>
s21::multiset<T>::MultisetIterator::MultisetIterator(
    typename s21::map<T, T>::Node_t *ptr)
    : map<T, T>::Mapiterator(ptr) {}

template <class T>
T s21::multiset<T>::MultisetIterator::operator*() {
  return map<T, T>::MapIterator::operator*().first;
}

// Multiset const iterator

template <class T>
s21::multiset<T>::ConstMultisetIterator::ConstMultisetIterator()
    : MultisetIterator() {}

template <class T>
s21::multiset<T>::ConstMultisetIterator::ConstMultisetIterator(
    const s21::multiset<T>::iterator &it)
    : MultisetIterator(it) {}

template <class T>
s21::multiset<T>::ConstMultisetIterator::ConstMultisetIterator(
    typename s21::map<T, T>::Node_t *ptr)
    : MultisetIterator(ptr) {}

template <class T>
const T &s21::multiset<T>::ConstMultisetIterator::operator*() {
  return map<T, T>::MapIterator::operator*().first;
}
// Private multiset methods

template <class T>
std::pair<typename s21::multiset<T>::iterator, bool>
s21::multiset<T>::insert_wrap(const T &value) {
  // std::cout << "try to insert " << value << "\n" ;
  std::pair<typename s21::map<T, T>::MapIterator, bool> temp =
      s21::map<T, T>::insert(value, value);
  if (temp.second == false) {
    // s21::cout << "failed, already exist, try"
    temp = s21::map<T, T>::insert_recursive(temp.first, value, value, 1);
    s21::map<T, T>::size_ += 1;
  }
  return temp;
}