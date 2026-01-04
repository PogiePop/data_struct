#ifndef QUEUE_H
#define QUEUE_H
#include "linklist.h"

//双向链表实现
typedef struct queue{
    lk_list list;
}queue;

#define qe_ptr queue*
#define qe_ptr_ptr qe_ptr*

qe_ptr create_queue();
void destory_queue(qe_ptr_ptr queue_ptr);
void enqueue_int(qe_ptr queue, int value);
void enqueue_float(qe_ptr queue, float value);
void enqueue_double(qe_ptr queue, double value);
void enqueue_char(qe_ptr queue, char value);
void enqueue_char_ptr(qe_ptr queue, const char* value);
void qe_dequeue(qe_ptr queue);
Obj_ptr qe_front(qe_ptr queue);
void qe_print(qe_ptr queue);


qe_ptr create_queue()
{
    qe_ptr qe = (qe_ptr)malloc(sizeof(queue));
    qe->list = create_linklist();
    return qe;
}
void destory_queue(qe_ptr_ptr queue_ptr)
{
    if(!queue_ptr || !(*queue_ptr))return;
    destory_linklist(&(*queue_ptr)->list);
    free(*queue_ptr);
    *queue_ptr = NULL;
}


void enqueue_int(qe_ptr queue, int value)
{
    if(!queue)return;
    lk_insert_back_int(queue->list, value);
}
void enqueue_float(qe_ptr queue, float value)
{
    if(!queue)return;
    lk_insert_back_float(queue->list, value);
}
void enqueue_double(qe_ptr queue, double value)
{
    if(!queue)return;
    lk_insert_back_double(queue->list, value);
}
void enqueue_char(qe_ptr queue, char value)
{
    if(!queue)return;
    lk_insert_back_char(queue->list, value);
}
void enqueue_char_ptr(qe_ptr queue, const char* value)
{
    if(!queue)return;
    lk_insert_back_char_ptr(queue->list, value);
}

void qe_dequeue(qe_ptr queue)
{
    if(!queue)return;
    lk_remove_front(queue->list);
}
Obj_ptr qe_front(qe_ptr queue)
{
    if(!queue)return NULL;
    return lk_get_front(queue->list);
}

void qe_print(qe_ptr queue)
{
    if(!queue)return;
    lk_print(queue->list);
}

#endif