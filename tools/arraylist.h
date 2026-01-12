#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include "object.h"
#define INIT_SIZE 10
#define STRIDE 20
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
typedef struct arraylist{
    Obj_ptr_ptr data;
    int capacity;
    int size;
}arraylist;

#define ay_list arraylist*
#define ay_list_ptr ay_list*


ay_list create_arraylist(int size);
void ay_add(ay_list list, obj_type type, void* data);
void add_int(ay_list list,int value);
void add_float(ay_list list, float value);
void add_double(ay_list list, double value);
void add_char(ay_list list, char c);
void add_char_ptr(ay_list list, const char* str);
Obj_ptr get(ay_list list, int index);
void print(ay_list list);
void resize_capacity(ay_list list);
int is_out_of_capacity(ay_list list);
int ay_insert(ay_list list, obj_type type, void* data, int index);
int insert_int(ay_list list, int value, int index);
int insert_float(ay_list list, float value, int index);
int insert_double(ay_list list, double value, int index);
int insert_char(ay_list list, char value, int index);
int insert_char_ptr(ay_list list, const char* value, int index);
int delete(ay_list list, int index);
void destroy_arraylist(ay_list_ptr list_ptr);
int get_value(ay_list list, obj_type type, void*data);
int get_value_int(ay_list list, int value);
int get_value_float(ay_list list, float value);
int get_value_double(ay_list list, double value);
int get_value_char(ay_list list, char value);
int get_value_char_ptr(ay_list list, const char* value);





ay_list create_arraylist(int size){
    ay_list list = (ay_list)malloc(sizeof(arraylist));
    list->capacity = size;
    list->size = 0;
    list->data = (Obj_ptr_ptr)malloc(sizeof(Obj_ptr) * size);
    for(int i = 0; i < size; i++)list->data[i] = NULL;
    return list;
}

void ay_add(ay_list list, obj_type type, void* data)
{
    if(is_out_of_capacity(list))resize_capacity(list);
    list->data[list->size] = create_object();
    SETOBJECT set_func = set_object_funcs[type];
    set_func(list->data[list->size++], data);
}

void add_int(ay_list list,int value){
   ay_add(list, INTEGER, &value);
}

void add_float(ay_list list, float value)
{
   ay_add(list, FLOAT, &value);
}
void add_double(ay_list list, double value)
{
    ay_add(list, DOUBLE, &value);
}

void add_char(ay_list list, char c)
{
    ay_add(list, CHAR, &c);
}

void add_char_ptr(ay_list list, const char* str){
    ay_add(list, STRING, (void*)str);
}

Obj_ptr get(ay_list list, int index){
    if(!list || index >= list->size)return NULL;
    return list->data[index];
}


void print(ay_list list){
    if(!list)return;
    for(int i = 0; i < list->size; i++){
        PRINT_OBJECT("%O\n", list->data[i]);
    }
}

void resize_capacity(ay_list list){
    if(!list)return;
    Obj_ptr_ptr arr = list->data;
    list->data = (Obj_ptr_ptr)malloc(sizeof(Obj_ptr) * (list->capacity + STRIDE));
    list->capacity = list->capacity + STRIDE;
    //for (size_t i = 0; i < list->capacity; i++)list->data[i] = NULL;
    for(size_t i = 0; i < list->size; i++){
        list->data[i] = create_object();
        copy_object_value(list->data[i], arr[i]);
        destory_object(&arr[i]);
    }
    free(arr);
}

int is_out_of_capacity(ay_list list){
    if(!list || list->size >= list->capacity)return TRUE;
    return FALSE;
}

int ay_insert(ay_list list, obj_type type, void* data, int index)
{
    if(!list || (index < 0 || index > list->size))return FALSE;
    if(is_out_of_capacity(list))resize_capacity(list);
    list->data[list->size] = create_object();
    for(int i = list->size - 1; i >= index; i--)copy_object_value(list->data[i + 1], list->data[i]);
    SETOBJECT set_func = set_object_funcs[type];
    set_func(list->data[index], data);
    list->size++;
    return TRUE;
}

int insert_int(ay_list list, int value, int index)
{
    return ay_insert(list, INTEGER, &value, index);
}
int insert_float(ay_list list, float value, int index)
{
    return ay_insert(list, FLOAT, &value, index);
}
int insert_double(ay_list list, double value, int index)
{
    return ay_insert(list, DOUBLE, &value, index);
}
int insert_char(ay_list list, char value, int index)
{
    return ay_insert(list, CHAR, &value, index);
}
int insert_char_ptr(ay_list list, const char* value, int index)
{
    return ay_insert(list, STRING, (void*)value, index);
}

int delete(ay_list list, int index)
{
    if(!list || (index < 0 || index >= list->size))return FALSE;
    for(int i = index; i < list->size - 1; i++)copy_object_value(list->data[i], list->data[i + 1]);
    destory_object(&list->data[list->size-1]);
    list->size--;
    return TRUE;
}

void destroy_arraylist(ay_list_ptr list_ptr)
{
    if(!list_ptr || !(*list_ptr))return;
    if((*list_ptr)->data){
        for(size_t i = 0; i < (*list_ptr)->size; i++)destory_object(&(*list_ptr)->data[i]);
        free((*list_ptr)->data);
        (*list_ptr)->data = NULL;
    }
    free(*list_ptr);
    *list_ptr = NULL;
}

int get_value(ay_list list, obj_type type, void*data)
{
    if(is_out_of_capacity(list))return -1;
    for(int i = 0; i < list->size; i++){
        if(list->data[i]->type == type && cmp_object_value(list->data[i], data)){
            return i;
        }
    }
    return -1;
}

int get_value_int(ay_list list, int value)
{
    return get_value(list, INTEGER, &value);
}
int get_value_float(ay_list list, float value)
{
    return get_value(list, FLOAT, &value);
}
int get_value_double(ay_list list, double value)
{
    return get_value(list, DOUBLE, &value);
}
int get_value_char(ay_list list, char value)
{
    return get_value(list, CHAR, &value);
}
int get_value_char_ptr(ay_list list, const char* value)
{
    return get_value(list, STRING, &value);
}






#endif