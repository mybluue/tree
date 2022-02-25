#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <algorithm>
#include <assert.h>
#include <vector>
#include <queue>

typedef int Type;

typedef struct AVLNode {
    Type key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
    AVLNode(Type k) {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
}AVLNode;

// static int tree_height(AVLNode* p) {
//     if(p==nullptr)
//         return 0;
//     return std::max(tree_height(p->left), tree_height(p->right)) + 1;
// }

static int max_key(AVLNode* p) {
    assert(p!=nullptr);
    AVLNode *q = p;
    while(q->right != nullptr)
        q = q->right;
    return q->key;
}

static int min_key(AVLNode* p) {
    assert(p!=nullptr);
    AVLNode *q = p;
    while(q->left != nullptr)
        q = q->left;
    return q->key;
}



class AVLTree {
public:
    void insert_key(Type key) {
        root = insert_node(root, key);
    }
    void delete_key(Type key) {
        root = delete_node(root, key);
    }
    void show();
    void show_tree() {
        print_tree(root);
    }
    void print_tree(AVLNode *p);
    void _show();
private:
    int treeheight_after_rotation(AVLNode *p) {
        return std::max(get_height(p->left), get_height(p->right)) + 1;
    }
    // 统一了子节点为0时求子树高度的操作
    int get_height(AVLNode *p) {
        if(p==nullptr)
            return 0;
        
        return p->height;
    }
    AVLNode* ll_rotation(AVLNode *p);
    AVLNode* rr_rotation(AVLNode *p);
    AVLNode* lr_rotation(AVLNode *p);
    AVLNode* rl_rotation(AVLNode *p);

    AVLNode* insert_node(AVLNode *p, Type key);
    AVLNode* delete_node(AVLNode *p, Type key);

private:
    AVLNode *root = nullptr;
};

#endif