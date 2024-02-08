#ifndef TREE
#define TREE

#include <iostream>

template <typename Key, typename Value> 
class AvlTree {
protected:
 struct node;
public:
  node *root_;
  class AvlIterator;
  class ConstAvlIterator;
  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_referense = const value_type &;
  using iterator = AvlIterator;
  using const_iterator = const AvlIterator;
  using size_type = size_t;

  AvlTree():root_(nullptr){};

  class AvlIterator {
  public:
    explicit AvlIterator(node *node): current_(node), end_(false) {};
    explicit AvlIterator(node *node, bool end): current_(node), end_(end) {};
    AvlIterator(const AvlIterator& other);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    value_type& operator*();
    bool operator==(const iterator& other);
    bool operator!=(const iterator& other);

  private:
    node *current_;
    bool end_;
  }; // Iterator

protected:
  struct node {
    key_type key;
    value_type value;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
    int height = 0;
    node()
        : key(0), value(0), left(nullptr), right(nullptr), parent(nullptr),
          height(0) {}
    node(key_type key, value_type value)
        : key(key), value(value), left(nullptr), right(nullptr),
          parent(nullptr), height(0) {}
    node(key_type key, value_type value, node *parent)
        : key(key), value(value), left(nullptr), right(nullptr), parent(parent),
          height(parent.height + 1) {}
  };

  

  int height(node *root);
  int bfactor(node *root);
  void fixheight(node *root);
  node *rotateright(node *root);
  node *rotateleft(node *root);
  node *balance(node *p);
  node *insert(node *root);
}; // AvlTree


#include "AvlTree.tpp"
#endif