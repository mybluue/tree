#include "avltree.h"
#include <vector>
#include <iostream>

int main() {
    AVLTree mt;
    std::vector<int> t = {1, 4, 7, 11, 15,15,15,15,15, 19, 3, 2, 8, 17, 12};
    for(int x:t) {
        mt.insert_key(x);
        std::cout << x << " 插入成功" << std::endl;
        mt.show_tree();
    }
    mt.delete_key(15);
    std::cout << "**************" << std::endl;
    mt.show_tree();
    return 0;
}