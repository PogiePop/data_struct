#ifndef STACK_H
#define STACK_H
#include "linklist.h"

//由双向循环链表实现
typedef struct stack{
    lk_list list;
}stack;

#define sk_ptr stack*
#define sk_ptr_ptr sk_ptr*

sk_ptr create_stack();
void destory_stack(sk_ptr_ptr stack_ptr);
void push_int(sk_ptr stack, int value);
void push_float(sk_ptr stack, float value);
void push_double(sk_ptr stack, double value);
void push_char(sk_ptr stack, char value);
void push_char_ptr(sk_ptr stack, const char* value);
void print_stack(sk_ptr stack);
void sk_pop(sk_ptr stack);
Obj_ptr sk_top(sk_ptr stack);
int sk_is_empty(sk_ptr stack);


sk_ptr create_stack()
{
    sk_ptr sk = (sk_ptr)malloc(sizeof(stack));
    sk->list = create_linklist();
    return sk;
}

void destory_stack(sk_ptr_ptr stack_ptr)
{
    if(!stack_ptr || !(*stack_ptr))return;
    destory_linklist(&(*stack_ptr)->list);
    free(*stack_ptr);
    *stack_ptr = NULL;
}


void push_int(sk_ptr stack, int value)
{
    if(!stack)return;
    lk_insert_back_int(stack->list, value);
}
void push_float(sk_ptr stack, float value)
{
    if(!stack)return;
    lk_insert_back_float(stack->list, value);
}
void push_double(sk_ptr stack, double value)
{
    if(!stack)return;
    lk_insert_back_double(stack->list, value);
}
void push_char(sk_ptr stack, char value)
{
    if(!stack)return;
    lk_insert_back_char(stack->list, value);
}
void push_char_ptr(sk_ptr stack, const char* value)
{
    if(!stack)return;
    lk_insert_back_char_ptr(stack->list, value);
}

void print_stack(sk_ptr stack)
{
    if(!stack)return;
    lk_print_back(stack->list);
}

void sk_pop(sk_ptr stack)
{
    if(!stack)return;
    lk_remove_back(stack->list);
}
Obj_ptr sk_top(sk_ptr stack)
{
    if(!stack)return NULL;
    return lk_get_back(stack->list);
}


int sk_is_empty(sk_ptr stack)
{
    if(!stack || !stack->list || stack->list->size == 0)return TRUE;
    return FALSE;
}

#endif