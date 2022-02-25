#include "avltree.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <math.h>

AVLNode* AVLTree::ll_rotation(AVLNode *p) {
    AVLNode *newRoot = p->left; 
    AVLNode *q = newRoot->right;
    p->left = q;
    newRoot->right = p;
    p->height = treeheight_after_rotation(p);
    newRoot->height = treeheight_after_rotation(newRoot);
    return newRoot;
}


AVLNode* AVLTree::rr_rotation(AVLNode *p) {
    AVLNode *newRoot = p->right;
    AVLNode *q = newRoot->left;
    p->right = q;
    newRoot->left = p;
    p->height = treeheight_after_rotation(p);
    newRoot->height = treeheight_after_rotation(newRoot);
    return newRoot;
}

AVLNode* AVLTree::lr_rotation(AVLNode *p) {
    // rr单旋
    p->left = rr_rotation(p->left);
    // ll单旋
    return ll_rotation(p);
}

AVLNode* AVLTree::rl_rotation(AVLNode *p) {
    p->right = ll_rotation(p->right);
    return rr_rotation(p);
}

// 允许插入相同值的节点，但后来者必须在右子树
AVLNode* AVLTree::insert_node(AVLNode *p, Type key) {
    if(p==nullptr) {
        p = new AVLNode(key);
        return p;
    }
    else if(key<p->key) {
        p->left = insert_node(p->left, key);
        if(get_height(p->left) - get_height(p->right) == 2) {
            if(key < p->left->key)
                p = ll_rotation(p);
            else
                p = lr_rotation(p);
        }
    }
    else {
        p->right = insert_node(p->right, key);
        if(get_height(p->right) - get_height(p->left) == 2) {
            if(key < p->right->key)
                p = rl_rotation(p);
            else
                p = rr_rotation(p);
        }
    }
    p->height = std::max(get_height(p->left), get_height(p->right)) + 1;
    return p;
}

AVLNode* AVLTree::delete_node(AVLNode *p, Type key) {
    if(p==nullptr)
        return nullptr;
    // std::cout << p->key << ", " << key << std::endl;
    if(key < p->key) {
        p->left = delete_node(p->left, key);
        if(get_height(p->right) - get_height(p->left) == 2) {
            AVLNode *q = p->right;
            assert(get_height(q->left) != get_height(q->right));
            if(get_height(q->left) < get_height(q->right))
                p = rr_rotation(p);
            else if(get_height(q->left) > get_height(q->right))
                p = rl_rotation(p);
        }
    }
    else if(key > p->key) {
        p->right = delete_node(p->right, key);
        if(get_height(p->left) - get_height(p->right) == 2) {
            AVLNode *q = p->left;
            assert(get_height(q->left) != get_height(q->right));
            if(get_height(q->left) > get_height(q->right))
                p = ll_rotation(p);
            else if(get_height(q->left) < get_height(q->right))
                p = lr_rotation(p);
        }
    }
    else {
        if(p->left && p->right) {
            if(p->left->height > p->right->height) {
                int newKey = max_key(p->left);
                p->key = newKey;
                p->left = delete_node(p->left, newKey);
            }
            else {
                int newKey = min_key(p->right);
                p->key = newKey;
                p->right = delete_node(p->right, newKey);
            }
        }
        else {
            AVLNode *tmp = p;
            p = p->left ? p->left : p->right;
        }
    }
    if(p)
        p->height = std::max(get_height(p->left), get_height(p->right)) + 1;
    else {
        // std::cout << "!!!" << std::endl;
    }
    return p;
}


void AVLTree::show() {
    std::queue<AVLNode*> Q;
    std::queue<std::string> C;
    Q.push(root);
    Q.push(nullptr);
    while(!Q.empty()) {
        AVLNode* node = Q.front();
        Q.pop();
        if(node) {
            std::cout << node -> key << " ";
            if(node->left) {
                Q.push(node->left);
                C.push("/");
            }
            if(node->right) {
                Q.push(node->right);
                C.push("\\");
            }
        }
        else if(!Q.empty()) {
            std::cout << std::endl;
            while(C.size() != 0) {
                std::cout << C.front() << " ";
                C.pop();
            }
            Q.push(nullptr);
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

void AVLTree::print_tree(AVLNode *p) {
    static int level = -1;
    int i;

    if(p==nullptr)
        return;
    
    level++;
    print_tree(p->right);
    level--;

    level++;
    for(int i=0;i<level;++i)
        printf("\t");
    printf("%2d\n", p->key);

    print_tree(p->left);
    level--;
}

void AVLTree::_show() {
    int h = get_height(root);
    int width = pow(2,h)-1;
    std::vector<std::vector<std::string>> tree_matrix(h, std::vector<std::string>(width, " "));
    

}