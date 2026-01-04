#ifndef LINKLIST_H
#define LINKLIST_H
#include "object.h"

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif



typedef struct linknode
{
    Obj_ptr data;
    struct linknode *next;
    struct linknode *pre;
} linknode;

#define lk_node linknode *
#define lk_node_ptr lk_node *

typedef struct linklist
{
    lk_node head;
    lk_node tail;
    int size;
} linklist;

#define lk_list linklist *
#define lk_list_ptr lk_list *

lk_node create_linknode();
lk_list create_linklist();
void destory_node(lk_node_ptr node_ptr);
void lk_print(lk_list list);
void lk_print_back(lk_list list);
void destory_linklist(lk_list_ptr lk_ptr);
void lk_insert(lk_list list , obj_type type, void* data, int index);
void lk_insert_int(lk_list list, int value, int index);
void lk_insert_float(lk_list list, float value, int index);
void lk_insert_double(lk_list list, double value, int index);
void lk_insert_char(lk_list list, char value, int index);
void lk_insert_char_ptr(lk_list list, const char *value, int index);
int lk_is_out_of_range(lk_list list, int index);
void lk_insert_front_int(lk_list list, int value);
void lk_insert_front_float(lk_list list, float value);
void lk_insert_front_double(lk_list list, double value);
void lk_insert_front_char(lk_list list, char value);
void lk_insert_front_char_ptr(lk_list list, const char *value);
void lk_insert_back_int(lk_list list, int value);
void lk_insert_back_float(lk_list list, float value);
void lk_insert_back_double(lk_list list, double value);
void lk_insert_back_char(lk_list list, char value);
void lk_insert_back_char_ptr(lk_list list, const char *value);
Obj_ptr lk_get(lk_list list, int index);
Obj_ptr lk_get_front(lk_list list);
Obj_ptr lk_get_back(lk_list list);
void lk_remove(lk_list list, int index);
void lk_remove_front(lk_list list);
void lk_remove_back(lk_list list);


lk_node create_linknode()
{
    lk_node node = (lk_node)malloc(sizeof(linknode));
    node->next = NULL;
    node->pre = NULL;
    node->data = create_object();
    return node;
}

lk_list create_linklist()
{
    lk_list list = (lk_list)malloc(sizeof(linklist));
    list->size = 0;
    list->head = list->tail = create_linknode();
    list->head->pre = list->tail;
    list->tail->next = list->head;
    return list;
}

int lk_is_out_of_range(lk_list list, int index)
{
    if (!list || (index > list->size))
        return TRUE;
    return FALSE;
}

void lk_insert(lk_list list ,obj_type type, void* data, int index)
{
    if (lk_is_out_of_range(list, index))
        return;
    SETOBJECT set_func = set_object_funcs[type];
    // 判断index到首位两端的距离, begin: -1, end: size -1
    int to_begin = index + 1;
    int to_end = list->size - 1 - index;
    // 从头节点开始
    if (to_begin <= to_end)
    {
        int j = -1;
        lk_node move = list->head;
        while (move && j++ < index - 1)
            move = move->next;
        if (!move)
            return;
        lk_node node = create_linknode();
        set_func(node->data, data);
        node->pre = move;
        node->next = move->next;
        move->next = node;
        node->next->pre = node;
        if (node->next == list->head)
            list->tail = node;
    }
    // 从尾节点开始
    else
    {
        int j = list->size - 1;
        lk_node move = list->tail;
        while (move && j-- >= index)
            move = move->pre;
        if (!move)
            return;
        lk_node node = create_linknode();
        set_func(node->data, data);
        node->pre = move;
        node->next = move->next;
        move->next = node;
        node->next->pre = node;
        if (node->next == list->head)
            list->tail = node;
    }
    list->size++;
}

void lk_insert_int(lk_list list, int value, int index)
{
    lk_insert(list, INTEGER, &value, index);
}
void lk_insert_float(lk_list list, float value, int index)
{
    lk_insert(list, FLOAT, &value, index);
}
void lk_insert_double(lk_list list, double value, int index)
{
    lk_insert(list, DOUBLE, &value, index);
}
void lk_insert_char(lk_list list, char value, int index)
{
   lk_insert(list, CHAR, &value, index);
}
void lk_insert_char_ptr(lk_list list, const char *value, int index)
{
    if(!value)return;
    lk_insert(list, STRING, (void*)value, index);
}

void lk_print(lk_list list)
{
    if (!list || list->size == 0)
        return;
    lk_node move = list->head->next;
    while (move != list->head)
    {
        PRINT_OBJECT("%O\n", move->data);
        move = move->next;
    }
}

void lk_insert_front_int(lk_list list, int value) { lk_insert_int(list, value, 0); }
void lk_insert_front_float(lk_list list, float value) { lk_insert_float(list, value, 0); }
void lk_insert_front_double(lk_list list, double value) { lk_insert_double(list, value, 0); }
void lk_insert_front_char(lk_list list, char value) { lk_insert_char(list, value, 0); }
void lk_insert_front_char_ptr(lk_list list, const char *value) { lk_insert_char_ptr(list, value, 0); }
void lk_insert_back_int(lk_list list, int value) { lk_insert_int(list, value, list->size); }
void lk_insert_back_float(lk_list list, float value) { lk_insert_float(list, value, list->size); }
void lk_insert_back_double(lk_list list, double value) { lk_insert_double(list, value, list->size); }
void lk_insert_back_char(lk_list list, char value) { lk_insert_char(list, value, list->size); }
void lk_insert_back_char_ptr(lk_list list, const char *value) { lk_insert_char_ptr(list, value, list->size); }

void destory_node(lk_node_ptr node_ptr)
{
    if (!node_ptr || !(*node_ptr))
        return;
    if ((*node_ptr)->data)
        destory_object(&(*node_ptr)->data);
    free(*node_ptr);
    *node_ptr = NULL;
}

void destory_linklist(lk_list_ptr lk_ptr)
{
    if (!lk_ptr || !(*lk_ptr))
        return;
    lk_node move = (*lk_ptr)->head->next;
    while (move != (*lk_ptr)->head)
    {
        lk_node del = move;
        move = move->next;
        destory_node(&del);
    }
    destory_node(&((*lk_ptr)->head));
    (*lk_ptr)->tail = NULL;
    free(*lk_ptr);
    *lk_ptr = NULL;
}

Obj_ptr lk_get(lk_list list, int index)
{
    Obj_ptr obj = NULL;
    if (!list || index < 0 || index >= list->size || list->size == 0)
        return obj;
    int to_begin = index + 1;
    int to_end = list->size - 1 - index;
    if (to_begin <= to_end)
    {
        int j = -1;
        lk_node move = list->head;
        while (move && j++ < index)
            move = move->next;
        if (move)
            obj = move->data;
        return obj;
    }
    else
    {
        int j = list->size - 1;
        lk_node move = list->tail;
        while (move && j-- > index)
            move = move->pre;
        if (move)
            obj = move->data;
        return obj;
    }
}

void lk_remove(lk_list list, int index)
{
    if (!list || index < 0 || index >= list->size || list->size == 0)
        return;
    int to_begin = index + 1;
    int to_end = list->size - 1 - index;
    if (to_begin <= to_end)
    {
        int j = -1;
        lk_node move = list->head;
        while (j++ < index)
            move = move->next;
        move->pre->next = move->next;
        move->next->pre = move->pre;
        if(move->next == list->head)list->tail = move->pre;
        destory_node(&move);
        list->size--;
    }
    else
    {
        int j = list->size - 1;
        lk_node move = list->tail;
        while (j-- > index)
            move = move->pre;
        move->pre->next = move->next;
        move->next->pre = move->pre;
        if(move->next == list->head)list->tail = move->pre;
        destory_node(&move);
        list->size--;
    }
}
void lk_remove_front(lk_list list)
{
    lk_remove(list, 0);
}
void lk_remove_back(lk_list list)
{
    lk_remove(list, list->size - 1);
}

void lk_print_back(lk_list list)
{
    if(!list || list->size == 0)return;
    lk_node move = list->tail;
    while(move != list->head){
        PRINT_OBJECT("%O\n", move->data);
        move = move->pre;
    }
}

Obj_ptr lk_get_front(lk_list list)
{
    return lk_get(list, 0);
}
Obj_ptr lk_get_back(lk_list list)
{
    return lk_get(list, list->size - 1);
}
#endif