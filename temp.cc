#include "./AvlTree/AvlTree.h"

int main(){
   AvlTree<int, char> a;
   auto res = a.insert("d");
   std::cout << res.second;
}    
   