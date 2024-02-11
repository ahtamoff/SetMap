#ifndef CPP2_S21_CONTAINERS_SRC_SET_H_
#define CPP2_S21_CONTAINERS_SRC_SET_H_

#include "../AvlTree/AvlTree.h"

namespace s21 {

template <typename T>
class set : public AvlTree<T> { 
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  set() : AvlTree<T>(){};
  explicit set(std::initializer_list<T> const& items) : AvlTree<T>(items) {}
  explicit set(const_reference value) : AvlTree<T>(value) {}
  set(const set& other) : AvlTree<T>(other) {}
  set(set&& other) : AvlTree<T>(std::move(other)) {}
  set& operator=(const set& other) {
    AvlTree<T>::operator=(other);
    return *this;
  }
  set& operator=(set&& other) {
    AvlTree<T>::operator=(std::move(other));
    return *this;
  }
};

#include "s21_set.tpp"
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_SET_H_
