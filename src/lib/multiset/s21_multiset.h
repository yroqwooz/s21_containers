#ifndef __CPP_CONTAINERS_SRC_LIB_MULTISET__
#define __CPP_CONTAINERS_SRC_LIB_MULTISET__

#include "../map/s21_map.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <typename T>
class multiset : public map<T, T> {
 public:
  friend class s21::map<T, T>::MapIterator;
  class MultisetIterator;
  class ConstMultisetIterator;

  using key_type = T;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using iterator = MultisetIterator;
  using const_iterator = ConstMultisetIterator;

  class MultisetIterator : public map<T, T>::MapIterator {
   public:
    MultisetIterator();
    MultisetIterator(const typename s21::map<T, T>::MapIterator& it);
    MultisetIterator(typename map<T, T>::Node_t* ptr);
    ~MultisetIterator() = default;

    value_type operator*();
  };

  class ConstMultisetIterator : public MultisetIterator {
   public:
    ConstMultisetIterator();
    ConstMultisetIterator(const MultisetIterator& it);
    ConstMultisetIterator(typename map<T, T>::Node_t* ptr);
    ~ConstMultisetIterator() = default;

    const_reference operator*();
  };

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();
  void operator=(const multiset& ms);
  void operator=(multiset&& ms);
  bool operator==(const multiset& ms);

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const T& key);
  iterator find(const T& key);
  bool contains(const T& key);
  std::pair<iterator, iterator> equal_range(const T& key);
  iterator lower_bound(const T& key);
  iterator upper_bound(const T& key);

 private:
  std::pair<iterator, bool> insert_wrap(const value_type& value);
};
}  // namespace s21

#include "s21_multiset.cc"

#endif  //__CPP_CONTAINERS_SRC_LIB_MAP__
