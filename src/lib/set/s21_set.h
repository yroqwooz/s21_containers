#ifndef __CPP_CONTAINERS_SRC_LIB_SET__
#define __CPP_CONTAINERS_SRC_LIB_SET__

#include "../map/s21_map.h"
#include "../vector/s21_vector.h"

namespace s21 {
template <class T>
class set : public map<T, T> {
 public:
  class SetIterator;
  class ConstSetIterator;

  using key_type = T;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = SetIterator;
  using const_iterator = ConstSetIterator;
  using size_type = size_t;

  class SetIterator : public map<T, T>::MapIterator {
   public:
    SetIterator();
    SetIterator(typename map<T, T>::MapIterator it);
    ~SetIterator() = default;

    value_type operator*();
  };

  class ConstSetIterator : public SetIterator {
   public:
    ConstSetIterator();
    ConstSetIterator(typename map<T, T>::ConstMapIterator it);
    ~ConstSetIterator() = default;
  };

  // Constructors
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set() = default;

  void operator=(set &&s);

  // Public methods

  iterator begin() const;
  iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clean();
  std::pair<iterator, bool> insert(const value_type &value);
  template <class... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const key_type &key);
  bool contains(const key_type &key);

 private:
};
};  // namespace s21

#include "s21_set.cc"
#endif  //__CPP_CONTAINERS_SRC_LIB_SET__