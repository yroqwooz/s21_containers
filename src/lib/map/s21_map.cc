#include "s21_map.h"

// NODE FUNCTIONS

template <class K, class T>
s21::map<K, T>::Node_t::Node_t()
    : ptr_left_(nullptr), ptr_right_(nullptr), parent_(nullptr) {}

template <class K, class T>
s21::map<K, T>::Node_t::Node_t(K key, T value) : Node_t() {
  key_ = key;
  value_ = value;
}

template <class K, class T>
s21::map<K, T>::Node_t::Node_t(std::pair<K, T> &item) : Node_t() {
  key_ = item.first;
  value_ = item.second;
}

// MAP FUNCTIONS

template <class K, class T>
s21::map<K, T>::map() : head_(nullptr), size_(0) {
  initNull_();
}

template <class K, class T>
s21::map<K, T>::map(const std::initializer_list<std::pair<const K, T>> &items)
    : map() {
  for (auto it = items.begin(); it != items.end(); it++) {
    insert(*it);
  }
}

template <class K, class T>
s21::map<K, T>::map(const s21::map<K, T> &src) : map() {
  for (auto it = src.begin(); it != src.end(); ++it) {
    insert(it.ptr_->key_, it.ptr_->value_);
  }
}

template <class K, class T>
s21::map<K, T>::map(s21::map<K, T> &&src) : map() {
  this->operator=(std::move(src));
}

template <class K, class T>
s21::map<K, T>::~map() {
  if (size_) {
    clear();
  }
  delete fake_;
}

template <class K, class T>
s21::map<K, T> &s21::map<K, T>::operator=(s21::map<K, T> &src) {
  for (auto it = src.begin(); it != src.end(); it++) {
    insert(it.ptr_->key_, it.ptr_->value_);
  }
  return *this;
}

template <class K, class T>
s21::map<K, T> &s21::map<K, T>::operator=(s21::map<K, T> &&src) {
  this->~map();
  this->fake_ = src.fake_;
  this->head_ = src.head_;
  this->size_ = src.size_;
  src.fake_ = nullptr;
  src.head_ = nullptr;
  src.size_ = 0;
  return *this;
}

// MAP PUBLIC METHODS

template <class K, class T>
void s21::map<K, T>::clear() {
  if (head_ != nullptr) {
    Node_t *ptr = head_;
    clear_recursive(ptr);
    head_ = nullptr;
    size_ = 0;
  }
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert(
    const K &key, const T &data) {
  std::pair<iterator, bool> res = {nullptr, false};
  if (head_ == nullptr) {
    head_ = node_allocator(key, data);
    head_->height_ = 0;
    head_->parent_ = fake_;
    head_->ptr_right_ = fake_;
    fake_->parent_ = nullptr;
    fake_->ptr_right_ = head_;
    fake_->ptr_left_ = head_;
    res = {head_, true};
    size_ = 1;
  } else {
    res = insert_recursive(head_, key, data, false);
    if (res.second == true) {
      size_ += 1;
      check_overload(res.first.ptr_);
    }
  }
  return res;
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert(
    const std::pair<const K, T> &value) {
  return insert(value.first, value.second);
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool>
s21::map<K, T>::insert_or_assign(const K &key, const T &data) {
  MapIterator it = find(key);
  std::pair<iterator, bool> res;
  if (it.ptr_ == fake_) {
    res = insert(key, data);
  } else if (it.ptr_ != nullptr) {
    it.ptr_->key_ = key;
    it.ptr_->value_ = data;
    res = {it.ptr_, false};
  }
  return res;
}

template <class K, class T>
template <typename... Args>
s21::vector<std::pair<typename s21::map<K, T>::iterator, bool>>
s21::map<K, T>::insert_many(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> res;
  for (auto &it : {args...}) {
    res.push_back(insert(it));
  }
  return res;
}

template <class K, class T>
T &s21::map<K, T>::at(const K &key) {
  iterator it = find(key);
  if (it.ptr_ == fake_) {
    throw std::out_of_range("Key Not Found");
  }
  return it.ptr_->value_;
}

template <class K, class T>
T &s21::map<K, T>::operator[](const K &key) {
  // std::cout << "dsad\n";
  auto ptr = find(key).ptr_;
  if (ptr == fake_ || ptr == nullptr) {
    ptr = insert(key, 0).first.ptr_;
  }
  return ptr->value_;
}

template <class K, class T>
inline bool s21::map<K, T>::empty() const {
  return (size_ ? false : true);
}

template <class K, class T>
size_t s21::map<K, T>::size() const {
  return size_;
}

template <class K, class T>
size_t s21::map<K, T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         (sizeof(typename map<K, T>::Node_t));
}

template <class K, class T>
void s21::map<K, T>::erase(s21::map<K, T>::MapIterator pos) {
  Node_t *ptr = pos.ptr_;
  erase_recursive(ptr);
  check_overload(ptr);
  if (ptr == head_) {
    auto temp = GetLRHeights(ptr);
    if (temp.second < temp.first) {
      head_ = ptr->ptr_left_;
    } else if (temp.second > temp.first) {
      head_ = ptr->ptr_right_;
    } else {
      head_ = nullptr;
    }
  }
  if (ptr == fake_->ptr_right_) {
    if (ptr->ptr_right_ != nullptr) {
      fake_->ptr_right_ = ptr->ptr_right_;
    } else {
      fake_->ptr_right_ = ptr->parent_;
    }
  }
  delete ptr;
  size_ -= 1;
}

template <class K, class T>
void s21::map<K, T>::swap(map &other) {
  std::swap(this->fake_, other.fake_);
  std::swap(this->head_, other.head_);
  std::swap(this->size_, other.size_);
}

template <class K, class T>
void s21::map<K, T>::merge(s21::map<K, T> &other) {
  for (auto it = other.begin(); it != other.end(); it++) {
    insert(*it);
  }
}

template <class K, class T>
bool s21::map<K, T>::contains(const T &key) {
  return (find(key).ptr_ != fake_ ? true : false);
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::find(const key_type &key) {
  if (head_ == nullptr) return fake_;
  Node_t *ptr = head_;
  while (ptr->key_ != key && ptr != fake_) {
    if (ptr->key_ > key) {
      if (ptr->ptr_left_ == nullptr) {
        ptr = fake_;
      } else {
        ptr = ptr->ptr_left_;
      }
    }
    if (ptr->key_ < key) {
      if (ptr->ptr_right_ == nullptr) {
        ptr = fake_;
      } else {
        ptr = ptr->ptr_right_;
      }
    }
  }
  return ptr;
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::begin() const {
  if (fake_->ptr_right_ == nullptr) {
    throw std::out_of_range("Out of range");
  }
  return fake_->ptr_right_;
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::end() const {
  if (head_ == nullptr) {
    throw std::out_of_range("Out of range");
  }
  return fake_;
}

template <class K, class T>
const typename s21::map<K, T>::const_iterator s21::map<K, T>::cbegin() const {
  return begin();
}

template <class K, class T>
const typename s21::map<K, T>::const_iterator s21::map<K, T>::cend() const {
  return end();
}

// HELPER FUNCIONS

template <class K, class T>
typename s21::map<K, T>::Node_t *s21::map<K, T>::node_allocator(
    const K &key, const T &value) {
  Node_t *ptr = nullptr;
  try {
    ptr = new Node_t(key, value);
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return ptr;
}

template <class K, class T>
void s21::map<K, T>::initNull_() {
  fake_ = node_allocator(K(), T());
  fake_->height_ = 0;
  fake_->ptr_right_ = nullptr;
  fake_->ptr_left_ = nullptr;
  fake_->parent_ = nullptr;
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool>
s21::map<K, T>::insert_recursive(s21::map<K, T>::MapIterator it, const K &key,
                                 const T &value, bool mode) {
  Node_t *ptr = it.ptr_;
  std::pair<iterator, bool> res_pair = {it, false};
  if (ptr->key_ > key) {
    res_pair = insert_left(ptr, key, value, mode);
  } else if (ptr->key_ < key) {
    res_pair = insert_right(ptr, key, value, mode);
  } else if (mode && ptr->key_ == key) {
    Node_t *temp = node_allocator(K(key), T(value));
    if (ptr->ptr_right_ != nullptr) {
      ptr->ptr_right_->parent_ = temp;
    }
    if (ptr->ptr_right_ == fake_) {
      temp->ptr_right_ = fake_;
      fake_->ptr_left_ = temp;
    } else {
      temp->ptr_right_ = ptr->ptr_right_;
    }
    temp->parent_ = ptr;
    ptr->ptr_right_ = temp;
    res_pair = {temp, true};
    update_heights(temp);
    check_overload(temp);
  }
  return res_pair;
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert_right(
    s21::map<K, T>::Node_t *ptr, const K &key, const T &value, bool mode) {
  std::pair<iterator, bool> res_pair = {MapIterator(ptr), false};
  if (ptr->ptr_right_ == nullptr || fake_->ptr_left_ == ptr) {
    ptr->ptr_right_ = node_allocator(K(key), T(value));
    res_pair = {ptr->ptr_right_, true};
    ptr->ptr_right_->height_ = 0;
    ptr->ptr_right_->parent_ = ptr;
    ptr->height_ =
        (ptr->ptr_left_ == nullptr ? 1 : ptr->ptr_left_->height_ + 1);
    fake_links(ptr->ptr_right_);
  } else {
    res_pair = insert_recursive(ptr->ptr_right_, key, value, mode);
    if (ptr->ptr_left_ != nullptr) {
      ptr->height_ = (ptr->ptr_left_->height_ > ptr->ptr_right_->height_
                          ? ptr->height_
                          : ptr->ptr_right_->height_ + 1);
    } else {
      ptr->height_ = ptr->ptr_right_->height_ + 1;
    }
  }
  return res_pair;
}

template <class K, class T>
std::pair<typename s21::map<K, T>::iterator, bool> s21::map<K, T>::insert_left(
    s21::map<K, T>::Node_t *ptr, const K &key, const T &value, bool mode) {
  std::pair<iterator, bool> res_pair = {MapIterator(ptr), false};
  if (ptr->ptr_left_ == nullptr) {
    ptr->ptr_left_ = node_allocator(K(key), T(value));
    res_pair = {ptr->ptr_left_, true};
    ptr->ptr_left_->height_ = 0;
    ptr->ptr_left_->parent_ = ptr;
    ptr->height_ =
        (ptr->ptr_right_ == nullptr ? 1 : ptr->ptr_right_->height_ + 1);
    fake_links(ptr->ptr_left_);
  } else {
    res_pair = insert_recursive(ptr->ptr_left_, key, value, mode);
    if (ptr->ptr_right_ != nullptr) {
      ptr->height_ = (ptr->ptr_right_->height_ > ptr->ptr_left_->height_
                          ? ptr->height_
                          : ptr->ptr_left_->height_ + 1);
    } else {
      ptr->height_ = ptr->ptr_left_->height_ + 1;
    }
  }
  return res_pair;
}

template <class K, class T>
void s21::map<K, T>::clear_recursive(s21::map<K, T>::Node_t *ptr) {
  if (ptr->ptr_left_ != nullptr) {
    clear_recursive(ptr->ptr_left_);
  }
  if (ptr->ptr_right_ != nullptr && ptr->ptr_right_ != fake_) {
    clear_recursive(ptr->ptr_right_);
  }
  if (ptr != nullptr && ptr != fake_) {
    delete ptr;
  }
}

template <class K, class T>
void s21::map<K, T>::erase_recursive(s21::map<K, T>::Node_t *ptr) {
  Node_t *temp = ptr->parent_;
  if (ptr->ptr_left_ == nullptr || ptr->ptr_right_ == nullptr) {
    if (ptr->parent_->ptr_left_ == ptr) {
      ptr->parent_->ptr_left_ =
          (ptr->ptr_left_ == nullptr ? ptr->ptr_right_ : ptr->ptr_left_);
      if (ptr->ptr_left_ != nullptr) {
        ptr->ptr_left_->parent_ = ptr->parent_;
      } else if (ptr->ptr_right_ != nullptr) {
        ptr->ptr_right_->parent_ = ptr->parent_;
      }
    } else {
      ptr->parent_->ptr_right_ =
          (ptr->ptr_right_ == nullptr ? ptr->ptr_left_ : ptr->ptr_right_);
      if (ptr->ptr_right_ != nullptr) {
        if (ptr->ptr_right_ == fake_) {
          fake_->ptr_left_ = ptr->parent_;
        } else {
          ptr->ptr_right_->parent_ = ptr->parent_;
        }
      }
    }
  } else {
    erase_find_next(ptr);
  }
  update_heights(temp);
}

template <class K, class T>
void s21::map<K, T>::erase_find_next(s21::map<K, T>::Node_t *ptr) {
  Node_t *ntr;
  if (ptr->ptr_left_->height_ >= ptr->ptr_right_->height_) {
    ntr = getMax(ptr->ptr_left_);
  } else {
    ntr = getMin(ptr->ptr_right_);
  }
  erase_recursive(ntr);
  ntr->ptr_right_ = ptr->ptr_right_;
  ntr->ptr_left_ = ptr->ptr_left_;

  if (ptr->ptr_left_ != nullptr) {
    ptr->ptr_left_->parent_ = ntr;
  }
  if (ptr->ptr_right_ != nullptr) {
    ptr->ptr_right_->parent_ = ntr;
  }
  if (head_ == ptr) {
    head_ = ntr;
  }
  ntr->height_ = ptr->height_;
  ntr->parent_ = ptr->parent_;
  if (ptr->parent_->ptr_right_ == ptr) {
    ptr->parent_->ptr_right_ = ntr;
  } else {
    ptr->parent_->ptr_left_ = ntr;
  }
}

template <class K, class T>
void s21::map<K, T>::fake_links(s21::map<K, T>::Node_t *ptr) {
  if (fake_->ptr_left_->key_ < ptr->key_) {
    ptr->ptr_right_ = fake_;
    fake_->ptr_left_ = ptr;
  }
  if (fake_->ptr_right_->key_ > ptr->key_) {
    fake_->ptr_right_ = ptr;
  }
}

template <class K, class T>
typename s21::map<K, T>::Node_t *s21::map<K, T>::getMax(
    s21::map<K, T>::Node_t *ptr) {
  Node_t *temp = ptr;
  while (temp->ptr_right_ != nullptr) {
    temp = temp->ptr_right_;
  }
  return temp;
}

template <class K, class T>
typename s21::map<K, T>::Node_t *s21::map<K, T>::getMin(
    s21::map<K, T>::Node_t *ptr) {
  Node_t *temp = ptr;
  while (temp->ptr_left_ != nullptr) {
    temp = temp->ptr_left_;
  }
  return temp;
}

template <class K, class T>
void s21::map<K, T>::update_heights(s21::map<K, T>::Node_t *ptr) {
  while (ptr != fake_) {
    if (ptr->ptr_left_ == nullptr &&
        (ptr->ptr_right_ == nullptr || ptr->ptr_right_ == fake_)) {
      ptr->height_ = 0;
    } else if (ptr->ptr_left_ != nullptr && ptr->ptr_right_ == nullptr) {
      ptr->height_ = ptr->ptr_left_->height_ + 1;
    } else if (ptr->ptr_left_ == nullptr && ptr->ptr_right_ != nullptr) {
      ptr->height_ = ptr->ptr_right_->height_ + 1;
    } else {
      if (ptr->ptr_right_->height_ > ptr->ptr_left_->height_) {
        ptr->height_ = ptr->ptr_right_->height_ + 1;
      } else {
        ptr->height_ = ptr->ptr_left_->height_ + 1;
      }
    }
    ptr = ptr->parent_;
  }
}

template <class K, class T>
void s21::map<K, T>::check_overload(s21::map<K, T>::MapIterator it) {
  Node_t *temp = it.ptr_;
  while (temp != fake_) {
    int status = GetOverloadStatus(temp);
    if (status <= -2) {
      if (temp->ptr_left_->ptr_right_ != nullptr) {
        UpSubRightNode(temp, temp->ptr_left_->ptr_right_);
      }
      OverloadLeft(temp);

    } else if (status >= 2) {
      if (temp->ptr_right_->ptr_left_ != nullptr) {
        UpSubLeftNode(temp, temp->ptr_right_->ptr_left_);
      }
      OverloadRight(temp);
    }
    temp = temp->parent_;
  }
}

template <class K, class T>
std::pair<int, int> s21::map<K, T>::GetLRHeights(s21::map<K, T>::Node_t *ptr) {
  int left = -1, right = -1;
  if (ptr->ptr_left_ != nullptr && ptr->ptr_left_ != fake_) {
    left = ptr->ptr_left_->height_;
  }
  if (ptr->ptr_right_ != nullptr && ptr->ptr_right_ != fake_) {
    right = ptr->ptr_right_->height_;
  }
  return {left, right};
}

template <class K, class T>
int s21::map<K, T>::GetOverloadStatus(s21::map<K, T>::Node_t *ptr) {
  auto res = GetLRHeights(ptr);
  return (res.second - res.first);
}

template <class K, class T>
void s21::map<K, T>::OverloadLeft(Node_t *ptr) {
  Node_t *son = ptr;
  Node_t *dad = ptr->ptr_left_;
  Node_t *brother = ptr->ptr_left_->ptr_left_;
  Node_t *old_son = dad->ptr_right_;

  dad->parent_ = son->parent_;
  if (son->parent_ != nullptr && son->parent_ != fake_) {
    if (son->parent_->ptr_left_ == son) {
      son->parent_->ptr_left_ = dad;
    } else {
      son->parent_->ptr_right_ = dad;
    }
  }
  if (son == head_) {
    head_ = dad;
    fake_->parent_ = dad;
  }
  son->ptr_left_ = dad->ptr_right_;
  if (son->ptr_left_ != nullptr) {
    son->ptr_left_->parent_ = son;
  }

  dad->ptr_right_ = son;
  son->parent_ = dad;

  update_heights(son);
}

template <class K, class T>
void s21::map<K, T>::OverloadRight(Node_t *ptr) {
  Node_t *son = ptr;
  Node_t *dad = ptr->ptr_right_;
  Node_t *brother = ptr->ptr_right_->ptr_right_;

  son->ptr_right_ = dad->ptr_left_;
  if (son->ptr_right_ != nullptr) {
    son->ptr_right_->parent_ = son;
  }

  dad->parent_ = son->parent_;
  if (son->parent_ != fake_) {
    if (son->parent_->ptr_right_ == son) {
      son->parent_->ptr_right_ = dad;
    } else {
      son->parent_->ptr_left_ = dad;
    }
  }
  dad->ptr_left_ = son;
  son->parent_ = dad;

  if (son == head_) {
    head_ = dad;
    fake_->parent_ = dad;
  }
  update_heights(son);
}

template <class K, class T>
void s21::map<K, T>::UpSubLeftNode(s21::map<K, T>::Node_t *ptr_head,
                                   s21::map<K, T>::Node_t *ptr_child) {
  Node_t *child_old = ptr_head->ptr_right_;
  Node_t *right_child_node = ptr_child->ptr_right_;

  child_old->ptr_left_ = right_child_node;
  if (right_child_node != nullptr) {
    right_child_node->parent_ = child_old;
  }

  child_old->parent_ = ptr_child;
  ptr_child->ptr_right_ = child_old;

  ptr_child->parent_ = ptr_head;
  ptr_head->ptr_right_ = ptr_child;

  update_heights(ptr_child->ptr_right_);
}

template <class K, class T>
void s21::map<K, T>::UpSubRightNode(s21::map<K, T>::Node_t *ptr_head,
                                    s21::map<K, T>::Node_t *ptr_child) {
  Node_t *child_old = ptr_head->ptr_left_;
  Node_t *left_child_node = ptr_child->ptr_left_;

  child_old->ptr_right_ = left_child_node;
  if (left_child_node != nullptr) {
    left_child_node->parent_ = child_old;
  }

  child_old->parent_ = ptr_child;
  ptr_child->ptr_left_ = child_old;

  ptr_child->parent_ = ptr_head;
  ptr_head->ptr_left_ = ptr_child;

  update_heights(ptr_child->ptr_left_);
}

// MAPITERATOR PUBLIC METHODS
template <class K, class T>
s21::map<K, T>::MapIterator::MapIterator() : ptr_(nullptr) {}

template <class K, class T>
s21::map<K, T>::MapIterator::MapIterator(s21::map<K, T>::ConstMapIterator it)
    : ptr_(it.MapIterator::ptr_) {}

template <class K, class T>
s21::map<K, T>::MapIterator::MapIterator(const s21::map<K, T>::MapIterator &it)
    : MapIterator() {
  ptr_ = it.ptr_;
}

template <class K, class T>
s21::map<K, T>::MapIterator::MapIterator(s21::map<K, T>::Node_t *ptr)
    : ptr_(ptr) {}

template <class K, class T>
std::pair<const K, T &> s21::map<K, T>::MapIterator::operator*() {
  std::pair<const K, T &> res = {this->ptr_->key_, ptr_->value_};
  return res;
}

template <class K, class T>
void s21::map<K, T>::MapIterator::operator=(std::pair<K, T> item) {
  this->ptr_->key_ = item.first;
  this->ptr_->value_ = item.second;
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::MapIterator::operator++() {
  Node_t *ptr = this->ptr_;

  if (ptr->ptr_right_ != nullptr) {
    Node_t *buff = ptr;
    if (ptr->ptr_right_->ptr_left_ != nullptr) {
      if (ptr->ptr_right_->ptr_left_ == buff) {
        ptr = ptr->ptr_right_;
      }
    }
    if (ptr == buff) {
      ptr = ptr->ptr_right_;
      while (ptr->ptr_left_ != nullptr) {
        ptr = ptr->ptr_left_;
      }
    }
  } else {
    if (ptr->parent_->ptr_left_ == ptr) {
      ptr = ptr->parent_;
    } else {
      while (ptr->parent_->ptr_left_ != ptr) {
        ptr = ptr->parent_;
      }
      ptr = ptr->parent_;
    }
  }
  this->ptr_ = ptr;
  return *this;
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::MapIterator::operator--() {
  Node_t *ptr = this->ptr_;
  Node_t *buff = ptr;

  if (ptr->ptr_left_ != nullptr) {
    if (ptr->ptr_left_->ptr_right_ == ptr) {
      ptr = ptr->ptr_left_;
    }
  }

  if (ptr == buff) {
    if (ptr->ptr_left_ != nullptr) {
      ptr = ptr->ptr_left_;
      while (ptr->ptr_right_ != nullptr) {
        ptr = ptr->ptr_right_;
      }
    } else {
      buff = ptr;
      ptr = ptr->parent_;
      while (ptr->ptr_right_ != buff) {
        buff = ptr;
        ptr = ptr->parent_;
      }
    }
  }
  this->ptr_ = ptr;
  return *this;
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::MapIterator::operator++(
    int b) {
  return this->operator++();
}

template <class K, class T>
typename s21::map<K, T>::MapIterator s21::map<K, T>::MapIterator::operator--(
    int b) {
  return this->operator--();
}

template <class K, class T>
bool s21::map<K, T>::MapIterator::operator==(
    s21::map<K, T>::MapIterator other) {
  return ptr_ == other.ptr_;
}

template <class K, class T>
bool s21::map<K, T>::MapIterator::operator!=(
    const s21::map<K, T>::MapIterator &other) {
  return ptr_ != other.ptr_;
}

// CONSTMAPITERATOR PUBLIC

template <class K, class T>
s21::map<K, T>::ConstMapIterator::ConstMapIterator() : MapIterator() {}

template <class K, class T>
s21::map<K, T>::ConstMapIterator::ConstMapIterator(s21::map<K, T>::Node_t *ptr)
    : MapIterator(ptr) {}

template <class K, class T>
s21::map<K, T>::ConstMapIterator::ConstMapIterator(s21::map<K, T>::iterator it)
    : MapIterator(it.MapIterator::ptr_) {}

template <class K, class T>
s21::map<K, T>::ConstMapIterator::ConstMapIterator(
    const s21::map<K, T>::ConstMapIterator &it) {}

template <class K, class T>
std::pair<const K, T> s21::map<K, T>::ConstMapIterator::operator*() {
  return s21::map<K, T>::MapIterator::operator*();
}

template <class K, class T>
bool s21::map<K, T>::ConstMapIterator::operator==(
    s21::map<K, T>::ConstMapIterator other) {
  return MapIterator::ptr_ == other.ptr_;
}

template <class K, class T>
bool s21::map<K, T>::ConstMapIterator::operator!=(
    s21::map<K, T>::ConstMapIterator other) {
  return MapIterator::ptr_ != other.ptr_;
}
