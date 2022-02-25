#include "rbtree.h"
#include "assert.h"
#include <iostream>

// 要注意父节点的调整
void RBTree::left_rotation(RBNode *p) {
    RBNode *q = p -> right;
    if(q==nullptr)
        return;
    p -> right = q -> left;
    if(q->left != nullptr)
        q->left->parent = p;
    
    if(p->parent==nullptr) {
        q -> parent = nullptr;
        root = q;
    }
    else {
        q -> parent = p -> parent;
        if(p->parent->left == p)
            p->parent->left = q;
        else if(p->parent->right ==p)
            p->parent->right = q;
    }
    q -> left = p;
    p -> parent = q;
}

void RBTree::right_rotation(RBNode *p) {
    RBNode *q = p -> left;
    if(q==nullptr)
        return;
    p -> left = q -> right;
    if(q->right!=nullptr)
        q->right->parent = p;
    if(p->parent == nullptr) {
        q -> parent == nullptr;
        root = q;
    }
    else {
        q -> parent = p -> parent;
        if(p->parent->left == p)
            p->parent->left = q;
        else if(p->parent->right == p)
            p->parent->right = q;
        q->right = p;
        p->parent = q;
    }
}

void RBTree::insert_key(Type key) {
    RBNode *node = new RBNode(key);
    // 插入的节点是根节点，直接涂黑
    if(root==nullptr) {
        root = node;
        root->color = BLACK;
        return;
    }
    RBNode *p = root;
    RBNode *q = p->parent;
    while(p) {
        q = p;
        if(key < p->key) {
            p = p->left;
        }
        else
            p = p->right;
    }
    
    node->parent = q;
    if(key<q->key) {
        q->left = node;
    }
    else {
        q->right = node;
    }
    // 插入节点的父节点是黑色，直接插入
    if(q->color == BLACK)
        return;
    insert_fixup(node);
}

void RBTree::insert_fixup(RBNode* p) {
    RBNode *parent,*gparent;
    while((parent = p->parent) && parent->color == RED) {
        gparent = parent -> parent;
        if(parent == gparent->left) {
            RBNode *uncle = gparent->right;
            // 叔叔节点存在且是红色
            if(uncle && uncle->color == RED) {
                set_black(parent);
                set_black(uncle);
                set_red(gparent);
                p = gparent;
                continue;
            }
            // cond:叔叔节点不存在或叔叔节点存在是黑色

            // // cond+当前节点是左孩子
            // if(parent->left == p){
            //     set_black(parent);
            //     set_red(gparent);
            //     right_rotation(gparent);
            // }
            // // cond+当前节点是右孩子
            // else if(parent->right == p) {
            //     RBNode* tmp = parent;
            //     left_rotation(parent);
            //     p = tmp;
            //     continue;
            // }
            if(parent->right == p) {
                RBNode *tmp;
                left_rotation(parent);
                tmp = parent;
                parent = p;
                p = tmp;
            }
            set_black(parent);
            set_red(gparent);
            right_rotation(gparent);
        }
        else {
            RBNode *uncle = gparent->left;
            if(uncle && uncle->color == RED) {
                set_black(parent);
                set_black(uncle);
                set_red(gparent);
                p = gparent;
                continue;
            }
            // if(parent->right == p) {
            //     set_black(parent);
            //     set_red(gparent);
            //     left_rotation(gparent);
            // }
            // else if(parent->left == p) {
            //     RBNode *tmp = parent;
            //     right_rotation(parent);
            //     p = tmp;
            //     continue;
            // }
            if(parent->left == p) {
                RBNode *tmp;
                right_rotation(parent);
                tmp = parent;
                parent = p;
                p = tmp;
            }
            set_black(parent);
            set_red(gparent);
            left_rotation(gparent);

        }
    }
    if(p==root) {
        std::cout << "!!!" << std::endl;
        p->color = BLACK;
    }
}

void RBTree::delete_key(Type key) {
    if(root==nullptr)
        return;
    RBNode *p = root;
    RBNode *q = p->parent;
    while(p->key != key) {
        q = p;
        if(key < p->key)
            p = p->left;
        else
            p = p->right;   
    }
    assert(p!=nullptr);
    while(p->left || p->right) { 
        // 删除p的后继节点r
        if(p->right) {
            RBNode *r = p->right;
            while(r->left)
                r = r->left;
            p->key = r->key;
            p = r;
        }
        // 删除p的前驱节点r
        else if(p->left) {
            RBNode *r = p->left;
            while(r->right)
                r = r->right;
            p->key = r->key;
            p = r;
        }
    }
    // 删除p
    
    delete_fixup(p, true);
}

// p不可能同时有左右孩子
void RBTree::delete_fixup(RBNode *p) {
    std::cout << "要删除的是：" << p->key << std::endl;
    // p为红，则p必是叶子节点，直接删除即可
    if(p->color == RED) {
        if(p->parent->left == p)
            p->parent->left = nullptr;
        else
            p->parent->right = nullptr;
        return;
    }

    // p是根节点，p只可能无左右孩子
    if(p->parent==nullptr) {
        root = nullptr;
        return;
    }

    // 如果p为黑，且有右孩子，则右孩子一定为红
    if(p->right) {
        p->right->parent = p->parent;
        if(p->parent->left == p)
            p->parent->left = p->right;
        else
            p->parent->right = p->right;
        delete(p);
        return;
    }
    // p为黑，且有左孩子，则左孩子一定为红
    if(p->left) {
        p->left->parent = p->parent;
        if(p->parent->left == p)
            p->parent->left = p->left;
        else
            p->parent->right = p->left;
        delete(p);
        return;
    }



    // p为黑叶子节点,p一定有兄弟节点
    // p是左孩子
    if(p->parent->left == p) {
        // 兄弟节点为红，父节点为黑，有两个黑的侄子节点
        if(p->parent->color == BLACK && p->parent->right->color == RED) {
            set_red(p->parent);
            set_black(p->parent->right);
            left_rotation(p->parent);
            // 要处理的节点没变
        }
        // p的兄弟节点为黑，父节点为红或黑（为黑只可能是根节点）
        RBNode *br = p->parent->right;
        set_red(p->parent);
        std::cout << "???" << p->parent->color << std::endl;
        // 兄弟节点无左孩子，左旋并删除p（父节点为黑的时候要先涂红）
        if(br->left==nullptr) {
            left_rotation(p->parent);
            if(p->parent->left==p)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
        }
        // 兄弟节点有左孩子，左旋并删除p(父节点为黑的时候要先涂红)，并对旋转后p的右孩子(原先兄弟的左孩子)进行调整
        else {
            RBNode *brl = br->left;
            left_rotation(p->parent);
            if(p->parent->left==p)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
            insert_fixup(brl);
        }
    }
    // p是右孩子
    else {
        // 兄弟节点为红，父节点为黑，有两个黑的侄子节点
        if(p->parent->color == BLACK && p->parent->left->color==RED) {
            set_red(p->parent);
            set_black(p->parent->left);
            right_rotation(p->parent);
        }
        // p的兄弟节点为黑，父节点为红或黑
        RBNode *br = p->parent->left;
        set_red(p->parent);
        // 左兄弟节点无右孩子,右旋并删除p（父节点为黑的时候要先涂红）
        if(br->right==nullptr) {
            right_rotation(p->parent);
            if(p->parent->left==p)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
        }
        // 左兄弟节点有右孩子
        else {
            RBNode *brr = br->right;
            right_rotation(p->parent);
            if(p->parent->left==p)
                p->parent->left = nullptr;
            else
                p->parent->right = nullptr;
            insert_fixup(brr);
        }
    }   
}

void RBTree::delete_fixup(RBNode *p, bool need_delete) {
    std::cout << "删除的是：" << p->key << std::endl;
    if(p->color == RED) {
        if(need_delete)
            del_leaf(p);
        return;
    }
    if(p == root) {
        if(need_delete)
            root = nullptr;
        return;
    }

    RBNode *pa = p->parent;
    if(pa->left == p) {
        RBNode *rbr = pa->right;
        if(pa->color == RED) {
            if(rbr->left == nullptr) {
                left_rotation(pa);
                if(need_delete)
                    del_leaf(p);
            }
            else {
                left_rotation(pa);
                if(need_delete)
                    del_leaf(p);
                insert_fixup(rbr->left);
            }
            return;
        }
        // 以下是父节点为黑
        // 右兄弟为红
        if(rbr->color == RED) {
            set_red(pa);
            set_black(rbr);
            left_rotation(pa);
            delete_fixup(p, need_delete);      // 理论上只需调用一次
            return;
        }
        // 右兄弟为黑
        else {
            if(rbr->right) {
                left_rotation(pa);
                if(need_delete)
                    del_leaf(p);
                rbr->right->color = BLACK;
            }
            else if(rbr->left) {
                set_black(rbr->left);
                right_rotation(rbr);
                left_rotation(pa);
                if(need_delete)
                    del_leaf(p);
            }
            else {
                if(need_delete)
                    del_leaf(p);
                if(pa == root) {
                    rbr->color = RED;
                }
                else {
                    set_red(rbr);
                    delete_fixup(pa, false);
                }
            }
        }    
    }
    // p是右孩子
    else {
        RBNode *lbr = pa->left;
        if(pa->color == RED) {
            if(lbr->right == nullptr) {
                right_rotation(pa);
                if(need_delete)
                    del_leaf(p);
            }
            else {
                right_rotation(pa);
                if(need_delete)
                    del_leaf(p);
                insert_fixup(lbr->right);
            }
            return;
        }
        // 以下是父节点为黑色
        // 左兄弟为红
        if(lbr->color == RED) {
            set_red(pa);
            set_black(lbr);
            right_rotation(pa);
            delete_fixup(p, need_delete);      // 理论上只需调用一次
            return;
        }
        // 左兄弟为黑
        else {
            if(lbr->left) {
                right_rotation(pa);
                set_black(lbr->left);
                if(need_delete)
                    del_leaf(p);
            }
            else if(lbr->right) {
                set_black(lbr->right);
                left_rotation(lbr);
                right_rotation(pa);
                if(need_delete)
                    del_leaf(p);
            }
            else {
                if(need_delete)
                    del_leaf(p);
                if(pa == root) {
                    lbr->color = RED;
                    return;
                }
                set_red(lbr);
                delete_fixup(pa, false);
            }
        }

    }
    

}

void RBTree::rb_show(RBNode *p) {
    static int level = -1;
    int i;

    if(p==nullptr)
        return;
    
    level++;
    rb_show(p->right);
    level--;

    level++;
    for(int i=0;i<level;++i)
        printf("\t");
    printf("%2d-%d-%d\n", p->key, p->color, get_key(p->parent));

    rb_show(p->left);
    level--;
}