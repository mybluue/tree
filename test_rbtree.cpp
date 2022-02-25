#include "rbtree.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<Type> nodeli = {1, 4, 7, 11, 15, 2, 8, 6, 3, 9};
    // nodeli = {1, 4, 7, 11};
    nodeli = {3, 7, 9, 11, 14, 15, 16, 18, 26, 3, 23, 2, 23, 26,24, 98, 43, 45, 32, 23, 19, 18 ,17, 16};
    RBTree t;
    for(int x:nodeli) {
        t.insert_key(x);
        std::cout << x << "插入成功" << std::endl;
        t.show();
    }
    for(int i=0;i<nodeli.size();++i) {
        if(i%2) {
            std::cout << nodeli[i];
            t.delete_key(nodeli[i]);
            t.show();
        }
    }
    
    return 0;
}