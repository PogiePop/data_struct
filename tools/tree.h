#ifndef _WA_TREE_H
#define _WA_TREE_H
#include "object.h"


typedef struct treenode
{
    Obj_ptr data;
    struct treenode* left;
    struct treenode* right;
}treenode;

#define t_node treenode*
#define t_node_ptr t_node*


typedef struct tree
{
    t_node root;
    int size;
}tree;

#define wa_tree tree*
#define wa_tree_ptr wa_tree*

wa_tree create_watree();
t_node create_treenode();
//按照完全二叉树
void wa_add_treenode(wa_tree tr, obj_type type, void* data);
void wa_add_treenode_int(wa_tree tr, int data);
void wa_add_treenode_float(wa_tree tr, float data);
void wa_add_treenode_double(wa_tree tr, double data);
void wa_add_treenode_char(wa_tree tr, char data);
void wa_add_treenode_char_ptr(wa_tree tr, const char* data);
void wa_insert_left(wa_tree tr, t_node node, obj_type type, void* data);
void wa_insert_right(wa_tree tr, t_node node, obj_type type, void* data);
void preorder(wa_tree tree);
void preorder_t(t_node node);
void inorder(wa_tree tree);
void postorder(wa_tree tree);
void inorder_t(t_node node);
void postorder_t(t_node node);
void destory_treenode(t_node_ptr node_ptr);
void destory_tree(wa_tree_ptr tree_ptr);
void destory_tree_t(t_node node);
void visit(t_node node);
void level_order(wa_tree tr);

int wa_get_tree_height_t(t_node node);
int wa_get_tree_height(wa_tree tr);
int wa_count_node_totals_t(t_node node);
int wa_count_node_totals(wa_tree tr);
int wa_count_leaf_totals_t(t_node node);
int wa_count_leaf_totals(wa_tree tr);




wa_tree create_watree()
{
   wa_tree tr = (wa_tree)malloc(sizeof(tree));
   tr->root = NULL;
   tr->size = 0;
   return tr;
}

t_node create_treenode()
{
    t_node t = (t_node)malloc(sizeof(treenode));
    t->left = NULL;
    t->right = NULL;
    t->data = create_object();
    return t;
}


void wa_insert_left(wa_tree tr, t_node node, obj_type type, void* data)
{
    if(!tr->root || !node)return;
    t_node tp = create_treenode();
    SETOBJECT set_func = set_object_funcs[type];
    set_func(tp->data, data);
    node->left = tp;
    tr->size++;
}

void wa_insert_right(wa_tree tr, t_node node, obj_type type, void* data)
{
    if(!tr->root || !node)return;
    t_node tp = create_treenode();
    SETOBJECT set_func = set_object_funcs[type];
    set_func(tp->data, data);
    node->right = tp;
    tr->size++;
}

void preorder(wa_tree tree)
{
    if(!tree)return;
    preorder_t(tree->root);
}

void preorder_t(t_node node)
{
    if(!node)return;
    visit(node);
    preorder_t(node->left);
    preorder_t(node->right);
}

void visit(t_node node)
{
    if(!node)return;
    PRINT_OBJECT("%O  ", node->data);
}


void inorder(wa_tree tree)
{
    if(!tree)return;
    inorder_t(tree->root);
}
void postorder(wa_tree tree)
{
    if(!tree)return;
    postorder_t(tree->root);
}
void inorder_t(t_node node)
{
    if(!node)return;
    inorder_t(node->left);
    visit(node);
    inorder_t(node->right);
}
void postorder_t(t_node node)
{
    if(!node)return;
    postorder_t(node->left);
    postorder_t(node->right);
    visit(node);
}

void level_order(wa_tree tr)
{
    if(!tr || !tr->root)return;
    t_node node_queue[100] = {NULL};
    int front = 0, rear = 0;
    node_queue[front++] = tr->root;
    while(front != rear)
    {
        t_node t = node_queue[rear++];
        visit(t);
        if(t->left)node_queue[front++] = t->left;
        if(t->right)node_queue[front++] = t->right;
    }
}


void wa_add_treenode(wa_tree tr, obj_type type, void* data)
{
    if(!tr)return;
    t_node t = create_treenode();
    SETOBJECT set_func = set_object_funcs[type];
    set_func(t->data, data);
    if(!tr->root)
    {
        tr->root = t;
    }
    else
    {
        t_node node_queue[100] = {NULL};
        int top = 0, rear = 0;
        node_queue[top++] = tr->root;
        while(top != rear)
        {
            t_node k = node_queue[rear++];
            if(k->left)node_queue[top++] = k->left;
            else{
                wa_insert_left(tr, k, type, data);
                return;
            }
            if(k->right)node_queue[top++] = k->right;
            else{
                wa_insert_right(tr, k, type, data);
                return;
            }
        }
    }
}


void destory_treenode(t_node_ptr node_ptr)
{
    if(!node_ptr || !(*node_ptr))return;
    destory_object(&(*node_ptr)->data);
    free(*node_ptr);
    *node_ptr = NULL;
}

void destory_tree_t(t_node node)
{
    if(!node)return;
    if(node->left)destory_treenode(&node->left);
    if(node->right)destory_treenode(&node->right);
}

void destory_tree(wa_tree_ptr tree_ptr)
{
    if(!tree_ptr || !(*tree_ptr))return;
    destory_tree_t((*tree_ptr)->root);
    free(*tree_ptr);
    *tree_ptr = NULL;
}

int wa_get_tree_height_t(t_node node)
{
    if(!node)return 0;
    int left = wa_get_tree_height_t(node->left);
    int right = wa_get_tree_height_t(node->right);
    int res = left >= right ? left : right;  
    return res + 1;
}

int wa_get_tree_height(wa_tree tr)
{
    if(!tr)return 0;
    return wa_get_tree_height_t(tr->root);
}

int wa_count_node_totals_t(t_node node)
{
    if(!node)return 0;
    return wa_count_node_totals_t(node->left) + wa_count_node_totals_t(node->right) + 1;
}

int wa_count_node_totals(wa_tree tr)
{
    if(!tr)return 0;
    return wa_count_node_totals_t(tr->root);
}

int wa_count_leaf_totals_t(t_node node)
{
    if(!node)return 0;
    if(!node->left && !node->right)return 1;
    return wa_count_leaf_totals_t(node->left) + wa_count_leaf_totals_t(node->right);
}

int wa_count_leaf_totals(wa_tree tr)
{
    if(!tr)return 0;
    return wa_count_leaf_totals_t(tr->root);
}


void wa_add_treenode_int(wa_tree tr, int data)
{
    if(!tr)return;
    wa_add_treenode(tr, INTEGER, &data);
}
void wa_add_treenode_float(wa_tree tr, float data)
{
    if(!tr)return;
    wa_add_treenode(tr, FLOAT, &data);
}
void wa_add_treenode_double(wa_tree tr, double data)
{
    if(!tr)return;
    wa_add_treenode(tr, DOUBLE, &data);
}
void wa_add_treenode_char(wa_tree tr, char data)
{
    if(!tr)return;
    wa_add_treenode(tr, CHAR, &data);
}
void wa_add_treenode_char_ptr(wa_tree tr, const char* data)
{
    if(!tr)return;
    wa_add_treenode(tr, STRING, (void*)data);
}


#endif