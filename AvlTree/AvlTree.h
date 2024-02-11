#ifndef CPP2_S21_CONTAINERS_SRC_AvlTree_H_
#define CPP2_S21_CONTAINERS_SRC_AvlTree_H_

#include <iostream>
#include <limits>
#include <utility>


namespace s21 {

template <typename T>
class AvlTree {
  struct Node;
  class AvlTreeIterator;

 public:
  using key_type = T;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = AvlTree<T>::AvlTreeIterator;
  using const_iterator = const AvlTree<T>::AvlTreeIterator;
  using size_type = size_t;

  AvlTree();
  explicit AvlTree(std::initializer_list<T> const& items);
  explicit AvlTree(const AvlTree& other);
  AvlTree(AvlTree&& other) noexcept;
  AvlTree& operator=(const AvlTree& other);
  AvlTree& operator=(AvlTree&& other) noexcept;
  ~AvlTree();
  iterator begin() const;
  iterator end() const;


  bool empty() const { return root_ == nullptr; }
  size_type size() const { return size_; }
  size_type max_size() const { return std::numeric_limits<std::size_t>::max(); }


  void clear() { Clear(root_); }
  std::pair<const_iterator, bool> insert(const_reference value,
                                         bool multi = false);
  void erase(iterator pos);
  void swap(AvlTree& other);
  void merge(AvlTree& other);

  iterator find(const value_type& key) const;
  bool contains(const key_type& key) const {
    return FindNode(root_, key) != nullptr;
  }

 protected:
  Node* root_;
  size_type size_;

 
  template <typename K, typename V>
  bool Compare(const std::pair<K, V>& value_1,
               const std::pair<K, V>& value_2) const;

  template <typename V>
  bool Compare(const V& value_1, const V& value_2) const;

  std::pair<const_iterator, bool> Insert(Node*& node, const_reference value,
                                         Node* parentnode = nullptr,
                                         bool multi = false);
  Node* FindNode(Node* node, const_reference value) const;
  void DeleteNode(Node*& node);
  Node* FindMinNode(Node* node) const;
  void Clear(Node*& node);


  int Height(Node* node) const;
  int BalanceFactor(Node* node) const;
  void FixHeight(Node* node);
  Node* RotateRight(Node*& node);
  Node* RotateLeft(Node*& node);
  void Balance(Node*& node);
 
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    Node()
        : data(0), left(nullptr), right(nullptr), parent(nullptr), height(0) {} 
    Node(Node* parent, T value)
        : data(value),
          left(nullptr),
          right(nullptr),
          parent(parent),
          height(1) {}
    ~Node() = default;
    Node& operator=(const Node& other) = default;
    Node(const Node& other) = default;
  };
  class AvlTreeIterator {
    friend class AvlTree;

   public:
    AvlTreeIterator(Node* node) : current_(node), end_(false){};
    AvlTreeIterator(Node* node, bool end) : current_(node), end_(end){};
    AvlTreeIterator(const AvlTreeIterator& other);
    AvlTreeIterator& operator=(const AvlTreeIterator& other);
    T operator*() const { return current_ ? current_->data : value_type(); }
    AvlTreeIterator& operator++();
    AvlTreeIterator& operator++(int);
    AvlTreeIterator& operator--();
    AvlTreeIterator& operator--(int);
    bool operator==(const AvlTreeIterator& other) const;
    bool operator!=(const AvlTreeIterator& other) const;
    value_type& get_value();

   private:
    Node* current_;
    bool end_;
  };
};

}  // namespace s21

#include "AvlTree.tpp"


#endif  // CPP2_S21_CONTAINERS_SRC_AvlTree_H_
