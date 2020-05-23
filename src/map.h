#ifndef __MAP_H__
#define __MAP_H__

#define RB_TREE_RED      0    
#define RB_TREE_BLACK    1    

typedef struct _Pair{
    char key[10];
    char value[30];
}Pair;
 
typedef struct RBTreeNode{
    unsigned char color;        
    Pair pair;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;
}Node, *RBTree;

typedef struct rb_root{
    Node *node;
}RBRoot;

RBRoot* create_rbtree();

void destroy_rbtree(RBRoot *root);


#ifdef _DEBUG_
void print_rbtree(RBRoot *root);
#endif

void set(RBRoot *root, Pair *pair);
int get(RBRoot *root, char* key, Pair* pair);
#endif