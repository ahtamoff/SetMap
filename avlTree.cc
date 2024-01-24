#include <iostream>

using namespace std;

struct node {
  int data;
  node *left;
  node *right;
  int balance;
};

int Height(node *root) {
  if (!root) return 0;
  int rheight = Height(root->right);
  int lheight = Height(root->left);
  if (rheight > lheight)
    return rheight + 1;
  else
    return lheight + 1;
}

void SetBalance(node *root) {
  if (root) root->balance = Height(root->right) - Height(root->left);
}

void TurnRight(node *(&root)) {
  node *leftSubtree;
  node *leftSubtreerightSubtree;
  leftSubtree = root->left;
  leftSubtreerightSubtree = leftSubtree->right;

  leftSubtree->right = root;
  root->left = leftSubtreerightSubtree;
  root = leftSubtree;
  SetBalance(root->right);
  SetBalance(root);
}

void TurnLeft(node *(&root)) {
  node *rightSubtree;
  node *rightSubtreeleftSubtree;
  rightSubtree = root->right;
  rightSubtreeleftSubtree = rightSubtree->left;

  rightSubtree->left = root;
  root->right = rightSubtreeleftSubtree;
  root = rightSubtree;
  SetBalance(root->left);
  SetBalance(root);
}

void insert(node *(&root), int d) {
  if (!root) {
    root = new node;
    root->data = d;

    root->left = NULL;
    root->right = NULL;
    root->balance = 0;
  } else {
    if (d > root->data) {
      insert(root->right, d);
      if (Height(root->right) - Height(root->left) > 1) {
        if (Height(root->right->right) < Height(root->right->left)) {
          TurnRight(root->right);
        }
        TurnLeft(root);
      }
    } else {
      if (d < root->data) {
        insert(root->left, d);
        if (Height(root->left) - Height(root->right) > 1) {
          if (Height(root->left->left) < Height(root->left->right)) {
            TurnLeft(root->left);
          }
          TurnRight(root);
        }
      }
    }

    SetBalance(root);
  }
}

void output(node *p){
    if(p){
        output(p->left);
        std::cout << p->data << " ";
        output(p->right);
    }
}

void clear(node ** p){
    if(*p){
        clear(&(*p)->left);
        clear(&(*p)->right);
        
        delete *p;
        *p = NULL;
    }
}

int main(){
    int d; 
    char ch;
    node *root;
    root = NULL;
    // do{
    //     std::cout<< "input val" << std::endl;
    //     cin >> d;
    //     insert(root, d);
    //     std::cout << "another one?" << std::endl;
    //     cin >> ch;
    // }while (ch != 'n');
    // std::cout << "output in simmetry order" << std::endl;
    // output(root);
    // std::cout << endl;
    insert(root, 1);
    insert(root, 6);
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 2);
    Height(root);
    output(root);
    
    return 0;
}