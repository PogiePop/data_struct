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

int wa_bst_insert(wa_tree tr, int value);

int wa_bst_insert_arr(wa_tree tr, int* arr, int size);
int wa_bst_remove_value_int(wa_tree tr, int value);
int wa_bst_remove_value_t(t_node pre, t_node node);
int wa_bst_remove_value_t_root(t_node_ptr node_pre);

int wa_bst_non_remove_value_int(wa_tree tr, int value);
int wa_bst_non_remove_root(t_node_ptr node_ptr);
int wa_bst_non_remove_value_t(t_node father, t_node node);

/// @brief 
/// @param tr 二叉排序树
/// @param value 想要删除的值
/// @return 0表示删除失败, 1表示删除成功
/// @note 1.如果删除的是叶子节点则直接删除,
/// @note 2.如果删除的节点有左子树或者右子树, 则将左子树或者右子树提上来,
/// @note 3.如果删除的节点既有左子树也有右子树, 则将对应的前驱或后继提上来, 改为删除前驱或后继
int wa_bst_remove_value_int(wa_tree tr, int value)
{
    if(!tr)return 0;
    t_node move = tr->root;
    t_node pre = NULL;
    while(move)
    {
        int v = get_object_int(move->data);
        if(v == value)break;
        else if(v > value)
        {
            pre = move;
            move = move->left;
        }
        else
        {
            pre = move;
            move = move->right;
        }
    }
    if(!move)return 0;
    int res = 0;
    if(!pre)res = wa_bst_remove_value_t_root(&tr->root);
    else res = wa_bst_remove_value_t(pre, move);
    return res;
}

int wa_bst_remove_value_t_root(t_node_ptr node_ptr)
{
    if(!node_ptr || !(*node_ptr))return 0;
    t_node node = *node_ptr;
    if(!node->left && !node->right)
    {
        destory_treenode(node_ptr);
        return 1;
    }
    else if(node->left && node->right)
    {
        //中序遍历node的前驱
        t_node m_pre = node->left;
        //m_pre的父节点
        t_node m_pre_pt = node;
        while(m_pre)
        {
            if(!m_pre->right)break;
            m_pre_pt = m_pre;
            m_pre = m_pre->right;
        }
        copy_object_value(m_pre_pt->data, m_pre->data);
        wa_bst_remove_value_t(m_pre_pt, m_pre);
    }
    else
    {
        if(node->left)
        {
            //中序遍历node的前驱
            t_node m_pre = node->left;
            //m_pre的父节点
            t_node m_pre_pt = node;
            while(m_pre)
            {
                if(!m_pre->right)break;
                m_pre_pt = m_pre;
                m_pre = m_pre->right;
            }
            copy_object_value(m_pre_pt->data, m_pre->data);
            wa_bst_remove_value_t(m_pre_pt, m_pre);
        }
        else
        {
            //中序遍历node的前驱
            t_node m_pre = node->right;
            //m_pre的父节点
            t_node m_pre_pt = node;
            while(m_pre)
            {
                if(!m_pre->left)break;
                m_pre_pt = m_pre;
                m_pre = m_pre->left;
            }
            copy_object_value(m_pre_pt->data, m_pre->data);
            wa_bst_remove_value_t(m_pre_pt, m_pre);
        }
    }
    return 1;
}


int wa_bst_remove_value_t(t_node pre, t_node node)
{
    if(!pre || !node)return 0;
    if(!node->left && !node->right)
    {
        if(pre->left == node)destory_treenode(&pre->left);
        else destory_treenode(&pre->right);
        return 1;
    }
    else if(node->left && node->right)
    {
        //中序遍历node的前驱
        t_node m_pre = node->left;
        //m_pre的父节点
        t_node m_pre_pt = node;
        while(m_pre)
        {
            if(!m_pre->right)break;
            m_pre_pt = m_pre;
            m_pre = m_pre->right;
        }
        copy_object_value(m_pre_pt->data, m_pre->data);
        wa_bst_remove_value_t(m_pre_pt, m_pre);
    }
    else
    {
        if(node->left)
        {
            //中序遍历node的前驱
            t_node m_pre = node->left;
            //m_pre的父节点
            t_node m_pre_pt = node;
            while(m_pre)
            {
                if(!m_pre->right)break;
                m_pre_pt = m_pre;
                m_pre = m_pre->right;
            }
            copy_object_value(m_pre_pt->data, m_pre->data);
            wa_bst_remove_value_t(m_pre_pt, m_pre);
        }
        else
        {
            //中序遍历node的前驱
            t_node m_pre = node->right;
            //m_pre的父节点
            t_node m_pre_pt = node;
            while(m_pre)
            {
                if(!m_pre->left)break;
                m_pre_pt = m_pre;
                m_pre = m_pre->left;
            }
            copy_object_value(m_pre_pt->data, m_pre->data);
            wa_bst_remove_value_t(m_pre_pt, m_pre);
        }
    }
    return 1;
}


int wa_bst_insert_arr(wa_tree tr, int* arr, int size)
{
    if(!tr)return 0;
    int i = 0;
    while(i < size)
    {
        wa_bst_insert(tr, arr[i++]);
    }
    return 1;
}


int wa_bst_insert(wa_tree tr, int value)
{
    if(!tr)return 0;
    if(!tr->root)
    {
        tr->root = create_treenode();
        set_object_int(tr->root->data, value);   
    }
    else{
        t_node move = tr->root;
        t_node pre = tr->root;
        while(move)
        {
            pre = move;
            int dt = get_object_int(move->data);
            if(dt == value)return 0;
            else if(dt > value)move = move->left;
            else move = move->right;
        }
        if(get_object_int(pre->data) > value)wa_insert_left(tr, pre, INTEGER, &value);
        else wa_insert_right(tr, pre, INTEGER, &value);
    }
      return 1;
}


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




int wa_bst_non_remove_value_int(wa_tree tr, int value)
{
    if(!tr)return 0;
    t_node move = tr->root;
    t_node pt = NULL;
    while(move)
    {
        int v = get_object_int(move->data);
        if(v == value)break;
        pt = move;
        if(v > value)move = move->left;
        else move = move->right;
    }
    if(!move)return 0;
    if(!pt)
    {
        return wa_bst_non_remove_root(&tr->root);
    }
    else
    {
        return wa_bst_non_remove_value_t(pt, move);
    }
}

int wa_bst_non_remove_root(t_node_ptr node_ptr)
{
    if(!node_ptr || !(*node_ptr))return 0;
    t_node t = *node_ptr;
    t_node cur = NULL;
    if(!t->left && !t->right){ destory_treenode(node_ptr); return 1; }
    else if(t->left && t->right)
    {
        //找到中序遍历中t的前驱
        cur = t->left;
        while(cur)
        {
            if(!cur->right)break;
            t = cur;
            cur = cur->right;
        }        
    }
    else
    {
        //只有左子树
        if(t->left)
        {
            cur = t->left;
            while(cur)
            {
                if(!cur->right)break;
                t = cur;
                cur = cur->right;
            }
        }
        //只有右子树
        else
        {
            cur = t->right;
            while(cur)
            {
                if(!cur->left)break;
                t = cur;
                cur = cur->left;
            }
        }
    }
    copy_object_value((*node_ptr)->data, cur->data);
    if(t->left == cur)
    destory_treenode(&t->left);
    else
    destory_treenode(&t->right);
    return 1;
}


int wa_bst_non_remove_value_t(t_node father, t_node node)
{
    if(!father || !node)return 0;
    t_node cur = NULL;
    if(!node->left && !node->right)
    {
        if(father->left == node)
        destory_treenode(&father->left);
        else
        destory_treenode(&father->right);
        return 1;
    }
    else if(node->left && node->right)
    {
        father = node;
        //找到中序遍历中t的前驱
        cur = node->left;
        while(cur)
        {
            if(!cur->right)break;
            father = cur;
            cur = cur->right;
        }      
    }
    else
    {
        father = node;
        //只有左子树
        if(father->left)
        {
            cur = father->left;
            while(cur)
            {
                if(!cur->right)break;
                father = cur;
                cur = cur->right;
            }
        }
        //只有右子树
        else
        {
            cur = father->right;
            while(cur)
            {
                if(!cur->left)break;
                father = cur;
                cur = cur->left;
            }
        }
    }
    copy_object_value(node->data, cur->data);
    if(father->left == cur)
    destory_treenode(&father->left);
    else
    destory_treenode(&father->right);
    return 1;
}

#endif