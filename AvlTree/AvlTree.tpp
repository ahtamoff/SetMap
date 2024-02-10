#include "AvlTree.h"

// AvlIterator

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator &
AvlTree<Key, Value>::AvlIterator::operator++() {
  if (end_ || !current_) {
    return *this;
  }

  if (current_->right) {
    current_ = current_->right;
    while (current_->left) {
      current_ = current_->left;
    }
    end_ = false;
  } else {
    Node *temp = current_;
    while (temp->parent && temp->parent->right == temp) {
      temp = temp->parent;
    }
    if (temp->parent == nullptr) {
      end_ = true;
    } else {
      current_ = temp->parent;
    }
  }
  return *this;
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator
AvlTree<Key, Value>::AvlIterator::operator++(int) {
  ++(*this);
  return *this;
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator &
AvlTree<Key, Value>::AvlIterator::operator--() {
  if (!current_) {
    return *this;
  }

  if (end_) {
    end_ = false;
    return *this;
  }

  if (current_->left) {
    current_ = current_->left;
    while (current_->right) {
      current_ = current_->right;
    }
  } else {
    Node *temp = current_;
    while (temp->parent && temp->parent->left == temp) {
      temp = temp->parent;
    }
    if (temp->parent == nullptr) {
      end_ = true;
    } else {
      current_ = temp->parent;
    }
  }
  return *this;
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator
AvlTree<Key, Value>::AvlIterator::operator--(int) {
  --(*this);
  return *this;
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::AvlIterator::operator*() {
  if (current_ == nullptr) {
    static Value zero_val{};
    return zero_val;
  }
  return current_->key;
}

template <typename Key, typename Value>
bool AvlTree<Key, Value>::AvlIterator::operator==(const AvlIterator &other) {
  return end_ ? (end_ == other.end_)
              : (current_ == other.current_ && end_ == other.end_);
}

template <typename Key, typename Value>
bool AvlTree<Key, Value>::AvlIterator::operator!=(const AvlIterator &other) {
  return end_ ? (end_ != other.end_)
              : (current_ != other.current_ || end_ != other.end_);
}

// Help copy and delete

template <typename Key, typename Value>
typename AvlTree<Key, Value>::Node *
AvlTree<Key, Value>::CopyTree(AvlTree::Node *node, AvlTree::Node *parent) {
  if (node == nullptr) {
    return nullptr;
  }
  Node *new_node = new Node(node->key, node->value, node->parent);
  new_node->left = CopyTree(node->left, new_node);
  new_node->right = CopyTree(node->right, new_node);
  return new_node;
}

template <typename Key, typename Value>
void AvlTree<Key, Value>::DeleteNode(AvlTree::Node *node) {
  if (node == nullptr) {
    return;
  }
  DeleteNode(node->left);
  DeleteNode(node->right);
  delete node;
}

template <typename Key, typename Value> void AvlTree<Key, Value>::DeleteTree() {
  DeleteNode(root_);
  root_ = nullptr;
}

// AvlTree public

template <typename Key, typename Value>
AvlTree<Key, Value>::AvlTree(const AvlTree &other) {
  root_ = CopyTree(other.root_, nullptr);
}

template <typename Key, typename Value>
AvlTree<Key, Value>::AvlTree(AvlTree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename Key, typename Value> AvlTree<Key, Value>::~AvlTree() {
  DeleteTree();
}

template <typename Key, typename Value>
AvlTree<Key, Value> &AvlTree<Key, Value>::operator=(AvlTree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename Value>
AvlTree<Key, Value> &AvlTree<Key, Value>::operator=(const AvlTree &other) {
  if (this != &other) {
    AvlTree temp(other);
    DeleteNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator AvlTree<Key, Value>::begin() {
  return root_ ? AvlIterator(GetMin(root_)) : AvlIterator(nullptr, true);
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator AvlTree<Key, Value>::end() {
  if (!root_) {
    return AvlIterator(nullptr, true);
  }
  Node *node = root_;
  while (node->right != nullptr) {
    node = node->right;
  }
  return AvlIterator(node, true);
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::Node *
AvlTree<Key, Value>::GetMin(AvlTree::Node *node) {
  return node->left ? GetMin(node->left) : node;
}

template <typename Key, typename Value> bool AvlTree<Key, Value>::empty() {
  return root_ == nullptr;
}

template <typename Key, typename Value> size_t AvlTree<Key, Value>::size() {
  if (root_ == nullptr)
    return 0;
  size_t left_size = RecursiveSize(root_->left_);
  size_t right_size = RecursiveSize(root_->right_);
  return 1 + left_size + right_size;
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::Node *
AvlTree<Key, Value>::FindNode(AvlTree::Node *node, const Key &key) {
  if (node == nullptr || node->key == key)
    return node;
  if (key > node->key) {
    return FindNode(node->right, key);
  } else {
    return FindNode(node->left, key);
  }
}

template <typename Key, typename Value>
typename AvlTree<Key, Value>::AvlIterator
AvlTree<Key, Value>::find(const Key &key) {
  Node *node_to_find = FindNode(root_, key);
  return AvlIterator(node_to_find);
}

template <typename Key, typename Value>
std::pair<typename AvlTree<Key, Value>::AvlIterator, bool>
AvlTree<Key, Value>::insert(const Key &key) {
  std::pair<AvlIterator, bool> res;
  if (root_ == nullptr) {
    root_ = new Node(key, key);
    res.first = AvlIterator(root_);
    res.second = true;
  } else {
    bool check_insert = InsertNode(root_, key, key);
    res.first = find(key);
    res.second = check_insert;
  }
  return res;
}

template <typename Key, typename Value>
int AvlTree<Key, Value>::height(AvlTree::Node *node) {
  return node ? node->height : 0;
}

template<typename K, typename V>
int AvlTree<K, V>::bfactor(AvlTree::Node* node){
    return height(node->right) - height(node->left);
}

template<typename K, typename V>
void AvlTree<K, V>::fixheight(Node* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr?hl:hr) + 1;
}


template<typename K, typename V>
typename AvlTree<K, V>::Node* AvlTree<K, V>::rotateright(Node* node){
    Node* left = node->left;
    node->left = left->right;
    left->right = node;
    fixheight(node);
 fixheight(left);
 return left;
}

template<typename K, typename V>
typename AvlTree<K, V>::Node* AvlTree<K, V>::rotateleft(Node* node){
    Node* right = node->right;
    node->right = right->left;
    right->left = node;
    fixheight(node);
 fixheight(right);
 return right;
}

template<typename K, typename V>
typename AvlTree<K, V>::Node* AvlTree<K, V>::balance(Node* node){
    fixheight(node);
 if( bfactor(node)==2 )
 {
  if( bfactor(node->right) < 0 )
   node->right = rotateright(node->right);
  return rotateleft(node);
 }
 if( bfactor(node)==-2 )
 {
  if( bfactor(node->left) > 0  )
   node->left = rotateleft(node->left);
  return rotateright(node);
 }
 return node; 
}

template<typename Key, typename Value>
bool AvlTree<Key, Value>::InsertNode(Node* node, const Key& key, Value value){
  bool check_insert = false;
  if (key < node->key) {
    if (node->left == nullptr) {
      node->left = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = InsertNode(node->left, key, value);
    }
  } else if (key > node->key) {
    if (node->right== nullptr) {
      node->right = new Node(key, value, node);
      check_insert = true;
    } else {
      check_insert = InsertNode(node->right, key, value);
    }
  } else if (key == node->key) {
    return check_insert;  // инсерт не произошел потому что такой ключ был в
                          // дереве
  }
  balance(node); 
  return check_insert;

}
