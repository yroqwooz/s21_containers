#ifndef __CPP_CONTAINERS_SRC_LIB_LIST__
#define __CPP_CONTAINERS_SRC_LIB_LIST__

#include <initializer_list>
#include <iostream>
#include <limits>

#include "../list-like/s21_list_like.h"

namespace s21 {
template <typename T>
class list : public list_like<T> {
 public:
  class ListIterator;
  class ConstListIterator;

  using iterator = ListIterator;
  using const_iterator = ConstListIterator;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using node_type = typename list_like<T>::Node_t;

 public:
  class ListIterator {
   protected:
    node_type* ptr_;

   public:
    friend class list<T>;
    ListIterator() noexcept;
    ListIterator(node_type* node);
    ListIterator(const ListIterator& other) noexcept;
    ~ListIterator() = default;

    T& operator*();
    ListIterator& operator++();
    ListIterator& operator++(int b);
    ListIterator& operator--();
    ListIterator& operator--(int b);
    ListIterator& operator=(const ListIterator& other);
    ListIterator operator+(size_type b);
    bool operator==(ListIterator other);
    bool operator!=(ListIterator other);
  };

  class ConstListIterator : public ListIterator {
   public:
    friend class list<T>;
    ConstListIterator();
    ConstListIterator(ListIterator other);
    ~ConstListIterator() = default;

    const T& operator*();
    ConstListIterator operator++();
    ConstListIterator operator++(int b);
    ConstListIterator operator--();
    ConstListIterator operator--(int b);
  };

  list();             // Стандартный конструктор
  list(size_type n);  // Параметризированный конструктор, создаёт лист размера n
  list(std::initializer_list<value_type> const&
           items);  // Конструктор инициализации, создаёт лист используя
                    // std::initializer_list
  list(const list& l);  // Конструктор копирования // TO DO | REQUIRES ITERATORS
  list(list&& l);  // Конструктор перемещения

  ~list();  // Деконструктор

  // Перегрузки
  list<T>& operator=(const list<T>& l);
  list<T>& operator=(
      list&& l);  // TO DO | REQUIRES COPY CONTRUCTOR // Перегрузка оператора =
  list<T>& operator=(std::initializer_list<value_type> const& items);

  const_reference front() const noexcept;
  const_reference back() const noexcept;

  iterator begin() noexcept;
  const_iterator cbegin() noexcept;
  iterator end() noexcept;
  const_iterator cend() noexcept;

  // Проверяет объект на пустоту
  bool empty() const noexcept;
  size_type size() const noexcept;  // Возвращает текущий размер элементов
  size_type max_size()
      const noexcept;  // Возвращает максимальный размер элементов

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

  void erase(iterator pos) noexcept;
  void push_back(const_reference value);
  void push_front(const_reference value);
  void pop_back();
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other) noexcept;
  void reverse() noexcept;
  void unique();
  void sort();
  void print() noexcept;

 private:
  void MergeSort_(list<T>& left, list<T>& right, list<T>& res);
};
};  // namespace s21

#include "s21_list.cc"
#endif  // __CPP_CONTAINERS_SRC_LIB_LIST__