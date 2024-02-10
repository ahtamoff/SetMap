#ifndef TREE
#define TREE

#include <iostream>
#include <limits>
#include <utility>

template <typename Key, typename Value>
class AvlTree {
protected:
  struct Node;

public:
  Node *root_;
  class AvlIterator;
  class ConstAvlIterator;
  using key_type = Key;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = AvlIterator;
  using const_iterator = const AvlIterator;
  using size_type = size_t;

  AvlTree() : root_(nullptr){};
  AvlTree(const AvlTree &other);
  AvlTree(AvlTree&& other) noexcept;
  ~AvlTree();
  AvlTree& operator=(AvlTree&& other) noexcept;
  AvlTree& operator=(const AvlTree& other); 
  Node *CopyTree(Node *node, Node* parent);
  void DeleteNode(Node *node);
  void DeleteTree();
  Node* GetMin(Node *node);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size() const { return std::numeric_limits<std::size_t>::max(); }
  void clear(){DeleteTree();}
  Node* FindNode(Node* node, const Key& key);
  iterator find(const Key& key);
  bool InsertNode(Node* node, const Key& key, Value value);
  std::pair<iterator, bool> insert(const Key& key);
  int height(Node *node);
  int bfactor(Node *node);
  void fixheight(Node *node);
  Node *rotateright(Node *node);
  Node *rotateleft(Node *node);
  Node *balance(Node *node);
 
  class AvlIterator {
  public:
    explicit AvlIterator() : current_(nullptr), end_(false){};
    explicit AvlIterator(Node *node) : current_(node), end_(false){};
    explicit AvlIterator(Node *node, bool end) : current_(node), end_(end){};
    AvlIterator(const AvlIterator &other);
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int); 
    value_type &operator*();
    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);

  private:
    Node *current_;
    bool end_;

  }; // AvlIterator
  class ConstAvlIterator : public AvlIterator {
  public:
    ConstAvlIterator() : AvlIterator(){};
    const_reference operator*() const { return AvlIterator::operator*(); };
  };

protected:
  struct Node {
    key_type key;
    value_type value;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
    int height = 0;
    Node()
        : key(0), value(0), left(nullptr), right(nullptr), parent(nullptr),
          height(0) {}
    Node(key_type key, value_type value)
        : key(key), value(value), left(nullptr), right(nullptr),
          parent(nullptr), height(0) {}
    Node(key_type key, value_type value, Node *parent)
        : key(key), value(value), left(nullptr), right(nullptr), parent(parent),
          height(parent->height + 1) {}
  };

  

}; // AvlTree

#include "AvlTree.tpp"
#endif