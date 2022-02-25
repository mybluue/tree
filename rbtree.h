#ifndef __RBTREE_H__
#define __RBTREE_H__

#define RED 0
#define BLACK 1

typedef int Type;

typedef struct RBNode {
    unsigned char color;
    Type key;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
    RBNode(Type k) {
        color = RED;
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
}RBNode;

class RBTree {
public:
    void left_rotation(RBNode* p);
    void right_rotation(RBNode* p);
    void insert_key(Type key);
    void insert_fixup(RBNode* p); 
    void delete_key(Type key);
    void delete_fixup(RBNode* p);
    void delete_fixup(RBNode *p, bool need_delete);
    void set_red(RBNode *p) {
        p->color = RED;
    }
    void set_black(RBNode *p) {
        p->color = BLACK;
    }
    Type get_key(RBNode *p) {
        if(p==nullptr)
            return -1;
        return p->key;
    }
    void rb_show(RBNode *p);
    void del_leaf(RBNode *p) {
        if(p->parent->left == p)
            p->parent->left = nullptr;
        else
            p->parent->right = nullptr;
        delete p;
    }
    void show() {
        rb_show(root);
    }
private:
    RBNode* root = nullptr;
};



#endif