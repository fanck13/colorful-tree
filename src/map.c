#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

#define get_parent(r)       ((r)->parent)
#define get_color(r)        ((r)->color)
#define check_if_red(r)     ((r)->color==RB_TREE_RED)
#define check_if_black(r)   ((r)->color==RB_TREE_BLACK)
#define set_black(r)        do { (r)->color = RB_TREE_BLACK; } while (0)
#define set_red(r)          do { (r)->color = RB_TREE_RED; } while (0)
#define set_parent(r,p)     do { (r)->parent = (p); } while (0)
#define set_color(r,c)      do { (r)->color = (c); } while (0)


RBRoot* create_rbtree(){
    RBRoot *root = (RBRoot*)malloc(sizeof(RBRoot));
    if(root == NULL){
        return NULL;
    }
    root->node = NULL;
    return root;
}

Node* _search(RBTree x, char* key){
    if (x == NULL || strcasecmp(x->pair.key, key) == 0) return x;

    if (strcasecmp(x->pair.key, key) > 0){
        return _search(x->left, key);
    }
    else{
        return _search(x->right, key);
    }
}

int search(RBRoot *root, char* key){
    if (root == NULL) return -1;
    return _search(root->node, key)? 0 : -1;
}

Node* _iterative_search(RBTree x, char* key){
    while ((x != NULL) && (strcasecmp(x->pair.key, key)!=0)){
        if (strcasecmp(key, x->pair.key) < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }   
    }
    return x;
}

int iterative_search(RBRoot *root, char* key){
    if (root == NULL) return -1;
    return _iterative_search(root->node, key) ? 0 : -1;
}

Node* _minimum(RBTree tree){
    if (tree == NULL){
        return NULL;
    }
    while(tree->left != NULL){
        tree = tree->left;
    }

    return tree;
}

int minimum(RBRoot *root, char* *val){
    Node *node;

    if (root != NULL){
        node = _minimum(root->node);
    }
    
    if (node == NULL){
        return -1;
    }
        
    *val = node->pair.value;
    return 0;
}

Node* _maximum(RBTree tree){
    if (tree == NULL){
        return NULL;
    }

    while(tree->right != NULL){
        tree = tree->right;
    }
        
    return tree;
}

int maximum(RBRoot *root, char* *val){
    Node *node;
    if (root != NULL){
        node = _maximum(root->node);
    }

    if (node == NULL){
        return -1;
    }
    *val = node->pair.value;
    return 0;
}

Node* rbtree_successor(RBTree x){
    if (x->right != NULL){
        return _minimum(x->right);
    }
        
    Node* y = x->parent;
    while ((y!=NULL) && (x==y->right)){
        x = y;
        y = y->parent;
    }

    return y;
}


Node* rbtree_predecessor(RBTree x){
    if (x->left != NULL){
        return _maximum(x->left);
    }

    Node* y = x->parent;
    while ((y!=NULL) && (x==y->left)){
        x = y;
        y = y->parent;
    }

    return y;
}

/*
 *         px                                      px
 *        /                                        /
 *       x                                        y
 *      /  \      --(left rotation)-->           / \    
 *     lx   y                                   x  ry
 *        /   \                                /  \
 *       ly   ry                              lx  ly
 *
 *
 */
void rbtree_left_rotate(RBRoot *root, Node *x){
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == NULL){
        root->node = y;
    }
    else{
        if (x->parent->left == x){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
    }

    y->left = x;
    x->parent = y;
}

/*
 *            py                                        py
 *           /                                          /
 *          y                                          x
 *         /  \      --(right rotation)-->            /  \ 
 *        x   ry                                     lx   y
 *       / \                                             / \
 *      lx  rx                                          rx  ry
 *
 */
void rbtree_right_rotate(RBRoot *root, Node *y){
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL){
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == NULL){        
        root->node = x;
    }
    else{
        if (y == y->parent->right){
            y->parent->right = x;
        }
        else{
            y->parent->left = x;
        }
    }
    x->right = y;
    y->parent = x;
}

void rbtree_insert_fixup(RBRoot *root, Node *node){
    Node *parent, *gparent;
    while ((parent = get_parent(node)) && check_if_red(parent)){
        gparent = get_parent(parent);
        if (parent == gparent->left){
            Node *uncle = gparent->right;
            if (uncle && check_if_red(uncle)){
                set_black(uncle);
                set_black(parent);
                set_red(gparent);
                node = gparent;
                continue;
            }
            
            if (parent->right == node){
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            set_black(parent);
            set_red(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else{
            Node *uncle = gparent->left;
            if (uncle && check_if_red(uncle)){
                set_black(uncle);
                set_black(parent);
                set_red(gparent);
                node = gparent;
                continue;
            }
            
            if (parent->left == node){
                Node *tmp;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            set_black(parent);
            set_red(gparent);
            rbtree_left_rotate(root, gparent);
        }
    }
    set_black(root->node);
}

void rbtree_insert(RBRoot *root, Node *node){
    Node *y = NULL;
    Node *x = root->node;

    while (x != NULL){
        y = x;
        if (strcasecmp(node->pair.key, x->pair.key) < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    get_parent(node) = y;

    if (y != NULL){
        if (strcasecmp(node->pair.key, y->pair.key)<0){
            y->left = node;
        } 
        else{
            y->right = node;
        }
    }
    else{
        root->node = node;
    }

    node->color = RB_TREE_RED;
    rbtree_insert_fixup(root, node);
}

Node* create_rbtree_node(Pair *pair, Node *parent, Node *left, Node* right){
    Node* p;
    if ((p = (Node *)malloc(sizeof(Node))) == NULL){
        return NULL;
    }
    strcpy(p->pair.key, pair->key);
    strcpy(p->pair.value, pair->value);
    p->left = left;
    p->right = right;
    p->parent = parent;
    p->color = RB_TREE_BLACK; 
    return p;
}

int insert_rbtree(RBRoot *root, Pair *pair)
{
    Node *node;
    if (_search(root->node, pair->key) != NULL){
        return -1;
    }

    node = create_rbtree_node(pair, NULL, NULL, NULL);
    if (node == NULL){
        return -1;
    }
    rbtree_insert(root, node);
    return 0;
}

void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *other;

    while ((!node || check_if_black(node)) && node != root->node){
        if (parent->left == node){
            other = parent->right;
            if (check_if_red(other)){
                set_black(other);
                set_red(parent);
                rbtree_left_rotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || check_if_black(other->left)) &&
                (!other->right || check_if_black(other->right))){
                set_red(other);
                node = parent;
                parent = get_parent(node);
            }
            else{
                if (!other->right || check_if_black(other->right)){
                    set_black(other->left);
                    set_red(other);
                    rbtree_right_rotate(root, other);
                    other = parent->right;
                }
                set_color(other, get_color(parent));
                set_black(parent);
                set_black(other->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else{
            other = parent->left;
            if (check_if_red(other)){
                set_black(other);
                set_red(parent);
                rbtree_right_rotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || check_if_black(other->left)) &&
                (!other->right || check_if_black(other->right))){
                set_red(other);
                node = parent;
                parent = get_parent(node);
            }
            else{
                if (!other->left || check_if_black(other->left)){
                    set_black(other->right);
                    set_red(other);
                    rbtree_left_rotate(root, other);
                    other = parent->left;
                }
                set_color(other, get_color(parent));
                set_black(parent);
                set_black(other->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node){
        set_black(node);
    }
}

void rbtree_delete(RBRoot *root, Node *node){
    Node *child, *parent;
    int color;
    if ( (node->left!=NULL) && (node->right!=NULL) ){
        Node *replace = node;
        replace = replace->right;
        while (replace->left != NULL){
            replace = replace->left;
        }

        if (get_parent(node)){
            if (get_parent(node)->left == node){
                get_parent(node)->left = replace;
            }
            else{
                get_parent(node)->right = replace;
            }
        }
        else{
            root->node = replace;
        }

        child = replace->right;
        parent = get_parent(replace);
        color = get_color(replace);

        if (parent == node){
            parent = replace;
        }
        else{
            if (child){
                set_parent(child, parent);
            }
            parent->left = child;
            replace->right = node->right;
            set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == RB_TREE_BLACK){
            rbtree_delete_fixup(root, child, parent);
        }
        free(node);
        return ;
    }

    if (node->left !=NULL){
        child = node->left;
    }
    else{
        child = node->right;
    }

    parent = node->parent;
    color = node->color;
    if (child){
        child->parent = parent;
    }

    if (parent){
        if (parent->left == node){
            parent->left = child;
        }
        else{
            parent->right = child;
        }
    }
    else{
        root->node = child;
    }

    if (color == RB_TREE_BLACK){
        rbtree_delete_fixup(root, child, parent);
    }
    free(node);
}

void delete_rbtree(RBRoot *root, char* key){
    Node *z, *node;
    if ((z = _search(root->node, key)) != NULL){
        rbtree_delete(root, z);
    }
}

void rbtree_destroy(RBTree tree){
    if (tree==NULL) return ;

    if (tree->left != NULL){
        rbtree_destroy(tree->left);
    }
        
    if (tree->right != NULL){
        rbtree_destroy(tree->right);
    }

    free(tree);
}

void destroy_rbtree(RBRoot *root){
    if (root != NULL){
        rbtree_destroy(root->node);
    }

    free(root);
}

#ifdef _DEBUG_
void rbtree_print(RBTree tree, KEY key, int direction){
    if(tree != NULL){
        if(direction==0){
            printf("%2d(B) is root\n", tree->key);
        }
        else{
            printf("%2d(%s) is %2d's %6s child\n", tree->key, check_if_red(tree)?"R":"B", key, direction==1?"right" : "left");
        }
        rbtree_print(tree->left, tree->key, -1);
        rbtree_print(tree->right,tree->key,  1);
    }
}

void print_rbtree(RBRoot *root){
    if (root!=NULL && root->node!=NULL){
        rbtree_print(root->node, root->node->key, 0);
    }
}
#endif

void set(RBRoot *root, Pair *pair){
    Node* ans = _search(root->node, pair->key);
    if(ans == NULL){
        Node* new_node = create_rbtree_node(pair, NULL, NULL, NULL);
        rbtree_insert(root,new_node);
    }
    else{
        if(strcasecmp(ans->pair.value, pair->value)!=0){
            strcpy(ans->pair.value, pair->value);
        }
    }
}


int get(RBRoot *root, char* key, Pair* pair){
    Node* ans = _search(root->node, key);
    if(ans!=NULL){
        strcpy(pair->key, ans->pair.key);
        strcpy(pair->value, ans->pair.value);
        return 0;
    }

    return -1;
}

