#include "AvlTree.h"

int main(){
    AvlTree<int, char> Tree;
    AvlTree<int, char> ::AvlIterator a (Tree.root_);
    a++;
    --a;
 
}    