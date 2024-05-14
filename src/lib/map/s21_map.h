#ifndef __CPP_CONTAINERS_SRC_LIB_MAP__
#define __CPP_CONTAINERS_SRC_LIB_MAP__
#include <string>

#include "../vector/s21_vector.h"

namespace s21 {
template <class K, class T>
class map {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = T &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = const ConstMapIterator;
  using size_type = size_t;

 protected:
  class Node_t {
   public:
    friend class map<K, T>;
    Node_t();
    Node_t(key_type key, T value);
    Node_t(std::pair<K, T> &item);

   protected:
    key_type key_;
    mapped_type value_;
    int height_;
    Node_t *ptr_left_;
    Node_t *ptr_right_;
    Node_t *parent_;
  };

 public:
  class MapIterator {
   public:
    friend class map<K, T>;

   protected:
    Node_t *ptr_;

   public:
    MapIterator();
    MapIterator(ConstMapIterator it);
    MapIterator(const MapIterator &it);
    MapIterator(Node_t *ptr);
    ~MapIterator() = default;

    std::pair<const key_type, reference> operator*();
    void operator=(std::pair<K, T> item);
    MapIterator operator++();
    MapIterator operator--();
    MapIterator operator++(int b);
    MapIterator operator--(int b);
    bool operator==(MapIterator other);
    bool operator!=(const MapIterator &other);
  };

  class ConstMapIterator : public MapIterator {
   public:
    ConstMapIterator();
    ConstMapIterator(Node_t *ptr);
    ConstMapIterator(MapIterator it);
    ConstMapIterator(ConstMapIterator const &it);
    value_type operator*();

    bool operator==(ConstMapIterator other);
    bool operator!=(ConstMapIterator other);
  };

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &src);
  map(map &&src);
  map &operator=(map &src);
  map &operator=(map &&src);
  virtual ~map();

 protected:
  Node_t *fake_;
  Node_t *head_;
  size_type size_;

  Node_t *node_allocator(const key_type &key, const mapped_type &value);
  void initNull_();
  std::pair<iterator, bool> insert_recursive(MapIterator it,
                                             const key_type &key,
                                             const mapped_type &value,
                                             bool mode);
  std::pair<iterator, bool> insert_right(Node_t *ptr, const key_type &key,
                                         const mapped_type &value, bool mode);
  std::pair<iterator, bool> insert_left(Node_t *ptr, const key_type &key,
                                        const mapped_type &value, bool mode);
  void clear_recursive(Node_t *ptr);
  void erase_recursive(Node_t *ptr);
  void erase_find_next(Node_t *ptr);
  void fake_links(Node_t *ptr);
  Node_t *getMax(Node_t *ptr);
  Node_t *getMin(Node_t *ptr);
  void update_heights(Node_t *ptr);
  void check_overload(iterator it);
  std::pair<int, int> GetLRHeights(Node_t *ptr);
  int GetOverloadStatus(Node_t *ptr);
  void OverloadLeft(Node_t *ptr);
  void OverloadRight(Node_t *ptr);
  void UpSubLeftNode(Node_t *ptr_head, Node_t *ptr_child);
  void UpSubRightNode(Node_t *ptr_head, Node_t *ptr_child);
  MapIterator insert_before(const MapIterator it, const K &key, const T &value);

 public:
  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &data);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &data);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  T &at(const key_type &key);
  T &operator[](const key_type &key);

  bool empty() const;
  size_type size() const;
  size_type max_size();

  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);
  bool contains(const T &key);
  MapIterator find(const key_type &key);
  MapIterator begin() const;
  MapIterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
};
};  // namespace s21
#include "s21_map.cc"
#endif  // __CPP_CONTAINERS_SRC_LIB_MAP__