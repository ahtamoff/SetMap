#ifndef CPP2_S21_CONTAINERS_SRC_AvlTree_TPP_
#define CPP2_S21_CONTAINERS_SRC_AvlTree_TPP_

namespace s21 {
template <typename T>
AvlTree<T>::iterator::AvlTreeIterator(const AvlTreeIterator& other) {
  current_ = other.current_;
  end_ = other.end_;
}

template <typename T>
typename AvlTree<T>::AvlTreeIterator& AvlTree<T>::iterator::operator=(
    const AvlTreeIterator& other) {
  current_ = other.current_;
  return *this;
}

template <typename T>
typename AvlTree<T>::AvlTreeIterator& AvlTree<T>::iterator::operator++() {
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
    Node* ptr = current_;
    while (ptr->parent && ptr->parent->right == ptr) {
      ptr = ptr->parent;
    }
    if (ptr->parent == nullptr) {
      end_ = true;
    } else {
      current_ = ptr->parent;
    }
  }
  return *this;
}

template <typename T>
typename AvlTree<T>::AvlTreeIterator& AvlTree<T>::iterator::operator++(int) {
  ++(*this);
  return *this;
}


template <typename T>
typename AvlTree<T>::AvlTreeIterator& AvlTree<T>::iterator::operator--() {
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
    Node* ptr = current_;
    while (ptr->parent && ptr->parent->left == ptr) {
      ptr = ptr->parent;
    }
    if (ptr->parent == nullptr) {
      end_ = true;
    } else {
      current_ = ptr->parent;
    }
  }
  return *this;
}

template <typename T>
typename AvlTree<T>::AvlTreeIterator& AvlTree<T>::iterator::operator--(int) {
  --(*this);
  return *this;
}

template <typename T>
bool AvlTree<T>::AvlTreeIterator::operator==(const AvlTreeIterator& other) const {
  return end_ ? (end_ == other.end_)
              : (current_ == other.current_ && end_ == other.end_);
}

template <typename T>
bool AvlTree<T>::AvlTreeIterator::operator!=(const AvlTreeIterator& other) const {
  return end_ ? (end_ != other.end_)
              : (current_ != other.current_ || end_ != other.end_);
}
template <typename T>
T& AvlTree<T>::AvlTreeIterator::get_value() {
  if (current_) {
    return current_->data;
  }
  throw std::out_of_range("Iterator is not pointing to a valid node");
}
  
//* Конструкторы
template <typename T>
AvlTree<T>::AvlTree() : root_(nullptr), size_(0) {}

template <typename T>
AvlTree<T>::AvlTree(std::initializer_list<T> const& items)
    : root_(nullptr), size_(0) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename T>
AvlTree<T>::AvlTree(const AvlTree& other) : root_(nullptr), size_(0) {
  Clear(root_);
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <typename T>
AvlTree<T>::AvlTree(AvlTree&& other) noexcept
    : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename T>
AvlTree<T>& AvlTree<T>::operator=(const AvlTree& other) {
  if (&other != this) {
    AvlTree tmp(other);
    this = std::move(tmp);
  }
  return *this;
}

template <typename T>
AvlTree<T>& AvlTree<T>::operator=(AvlTree&& other) noexcept {
  if (&other != this) {
    Clear(root_);
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
AvlTree<T>::~AvlTree() {
  Clear(root_);
}


template <typename T>
std::pair<typename AvlTree<T>::const_iterator, bool> AvlTree<T>::insert(
    const_reference value, bool multi) {
  return Insert(root_, value, nullptr, multi);
}

template <typename T>
void AvlTree<T>::erase(iterator pos) {
  DeleteNode(pos.current_);
}

template <typename T>
void AvlTree<T>::swap(AvlTree& other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
}

template <typename T>
void AvlTree<T>::merge(AvlTree& other) {
  AvlTree<T> tmp;
  for (auto it = other.begin(); it != other.end(); ++it) {
    if (!insert(*it).second) {
      tmp.insert(*it);
    }
  }
  other = std::move(tmp);
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::begin() const {
  return root_ ? AvlTreeIterator(FindMinNode(root_))
               : AvlTreeIterator(nullptr, true);
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::end() const {
  if (!root_) {
    return AvlTreeIterator(nullptr, true);
  }
  Node* node = root_;
  while (node->right != nullptr) {
    node = node->right;
  }
  return AvlTreeIterator(node, true);
}

template <typename T>
typename AvlTree<T>::iterator AvlTree<T>::find(const value_type& key) const {
  Node* node = FindNode(root_, key);
  return node ? AvlTreeIterator(node) : AvlTreeIterator(nullptr, true);
}

//* Вспомогательные приватные методы

template <typename T>
void AvlTree<T>::Clear(Node*& node) {
  if (node) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
  node = nullptr;
  size_ = 0;
}

template <typename T>
template <typename K, typename V>  // map
bool AvlTree<T>::Compare(const std::pair<K, V>& value_1,
                       const std::pair<K, V>& value_2) const {
  if (value_1.first < value_2.first) return true;
  return false;
}

template <typename T>
template <typename V>
bool AvlTree<T>::Compare(const V& value_1, const V& value_2) const {
  if (value_1 < value_2) return true;
  return false;
}


template <typename T>
std::pair<typename AvlTree<T>::const_iterator, bool> AvlTree<T>::Insert(
    Node*(&node), const_reference value, Node* parent_node, bool multi) {
  auto res = std::make_pair(const_iterator(nullptr), false);
  if (node == nullptr) {
    Node* new_node = new Node(parent_node, value);
    node = new_node;
    res = std::make_pair(const_iterator(node), true);
    ++size_;
  } else {
    if (Compare(value, node->data)) {
      res = Insert(node->left, value, node, multi);
      
    } else if (Compare(node->data, value)) {
      res = Insert(node->right, value, node, multi);
     
    } else if (multi) {
      res = Insert(node->left, value, node, multi);
     
    }
  }
  Balance(node);
  return res;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::FindNode(Node* node,
                                            const_reference value) const {
  while (node != nullptr) {
    if (Compare(value, node->data)) {
      node = node->left;
    } else if (Compare(node->data, value)) {
      node = node->right;
    } else {
      return node;
    }
  }
  return nullptr;
}

template <typename T>
void AvlTree<T>::DeleteNode(Node*& node) {
  if (!node) {
    return;
  }
  if (node->right) {
    Node* min_node = FindMinNode(node->right);
    node->data = min_node->data;
    DeleteNode(min_node);
  } else if (node->left) {
    // Если справа нет узла, то по свойству AVL дерева слева не может быть
    // больше одного узла
    node->data = node->left->data;
    DeleteNode(node->left);
  } else {
    Node* p = node->parent;
    if (p) {
      p->left == node ? p->left = nullptr : p->right = nullptr;
    } else {
      root_ = nullptr;
    }
    delete node;
    --size_;
    while (p) {
      Balance(p);
      if (p->parent == nullptr) {
        root_ = p;
      }
      p = p->parent;
    }
  }
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::FindMinNode(Node* node) const {
  if (node) {
    while (node->left != nullptr) {
      node = node->left;
    }
  }
  return node;
}

template <typename T>
int AvlTree<T>::Height(Node* node) const {
  return node ? node->height : 0;
}

template <typename T>
int AvlTree<T>::BalanceFactor(Node* node) const {
  return Height(node->right) - Height(node->left);
}

template <typename T>
void AvlTree<T>::FixHeight(Node* node) {
  int hl = Height(node->left);
  int hr = Height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::RotateRight(Node*(&node)) {
  Node* node2 = node->left;
  node->left = node2->right;
  if (node->left) {
    node->left->parent = node;
  }
  node2->right = node;
  node2->parent = node->parent;
  node->parent = node2;
  FixHeight(node);
  FixHeight(node2);
  return node2;
}

template <typename T>
typename AvlTree<T>::Node* AvlTree<T>::RotateLeft(Node*& node) {
  Node* node2 = node->right;
  node->right = node2->left;
  if (node->right) {
    node->right->parent = node;
  }
  node2->left = node;
  node2->parent = node->parent;
  node->parent = node2;
  FixHeight(node);
  FixHeight(node2);
  return node2;
}

template <typename T>
void AvlTree<T>::Balance(Node*& node) {
  FixHeight(node);
  if (BalanceFactor(node) == 2) {
    if (BalanceFactor(node->right) < 0) {
      node->right = RotateRight(node->right);
    }
    node = RotateLeft(node);
  } else if (BalanceFactor(node) == -2) {
    if (node->right && BalanceFactor(node->right) > 0) {
      node->right = RotateLeft(node->right);
    }
    node = RotateRight(node);
  }
}
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_AvlTree_TPP_