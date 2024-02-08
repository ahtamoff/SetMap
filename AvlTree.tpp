#include "AvlTree.h"

template <typename Key, typename Value>
AvlTree<Key, Value>::AvlIterator::AvlIterator(const AvlIterator &other) {
  current_ = other.current_;
  end_ = other.end_;
}

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
    node *temp = current_;
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
  AvlIterator temp = *this;
  operator++();
  return temp;
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
    node *temp = current_;
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
  AvlIterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
Value &AvlTree<Key, Value>::AvlIterator::operator*() {
  if (current_ == nullptr) {
    static Value zero_val{};
    return zero_val;
  }
  return current_->value;
}

template <typename Key, typename Value>
bool AvlTree<Key, Value>::AvlIterator::operator==(const AvlIterator &other) {
  return current_ == other->current_;
}

template <typename Key, typename Value>
bool AvlTree<Key, Value>::AvlIterator::operator!=(const AvlIterator &other) {
  return current_ != other->current_;
}

// template<typename K, typename V>
// int AvlTree<K, V>::height(AVLTree::node* root){
//     return root_?root_->height:0;
// }

// template<typename K, typename V>
// int AvlTree<K, V>::bfactor(AVLTree::node* root){
//     return height(root->right) - height(root->left);
// }

// template<typename K, typename V>
// void AvlTree<K, V>::fixheight(node* root){
//     int hl = height(root->left);
//     int hr = height(root->right);
//     root->height = (hl>hr?hl:hr) + 1;
// }

// template<typename K, typename V>
// AvlTree<K, V>::AVLTree() : root_(nullptr){}

// template<typename K, typename V>
// bool AvlTree<K, V>::empty(){
//     return root_?true:false;
// }

// template<typename K, typename V>
// typename AvlTree<K, V>::node* AvlTree<K, V>::rotateright(node* root){
//     node* left = root->left;
//     root->left = left->right;
//     left->right = root;
//     fixheight(root);
//  fixheight(left);
//  return left;
// }

// template<typename K, typename V>
// typename AvlTree<K, V>::node* AvlTree<K, V>::rotateleft(node* root){
//     node* right = root->right;
//     root->right = left->left;
//     right->left = root;
//     fixheight(root);
//  fixheight(right);
//  return right;
// }

// template<typename K, typename V>
// typename AvlTree<K, V>::node* AvlTree<K, V>::balance(node* root){
//     fixheight(root);
//  if( bfactor(root)==2 )
//  {
//   if( bfactor(root->right) < 0 )
//    root->right = rotateright(root->right);
//   return rotateleft(root);
//  }
//  if( bfactor(root)==-2 )
//  {
//   if( bfactor(root->left) > 0  )
//    root->left = rotateleft(root->left);
//   return rotateright(root);
//  }
//  return p; // балансировка не нужна
// }

// template<typename K, typename V>
// typename AvlTree<K, V>::node* AvlTree<K, T>::insert(node* root){
//  if( !p ) return new node(k);
//  if( k<p->key )
//   p->left = insert(p->left,k);
//  else
//   p->right = insert(p->right,k);
//  return balance(p);

// }
