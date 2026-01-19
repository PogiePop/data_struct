#ifndef _SEARCH_H
#define _SEARCH_H
#include "object.h"
#include "tree.h"

typedef struct chunk
{
    int max_value;
    int low, high;
}chunk;


int order_search_int(int* arr, int size, int value);
int binary_search_int(int* arr, int size, int value);
int chunk_search_int(int* arr, chunk* cks, int ck_size, int value);
int bst_search_int(wa_tree tr, int value);

int order_search_int(int* arr, int size, int value)
{
    if(!arr)return -1;
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == value)return i;
    }
    return -1;
}


int binary_search_int(int* arr, int size, int value)
{
    if(!arr)return -1;
    int left = 0, right = size - 1, mid = 0;
    while(left <= right)
    {
        mid = (left + right) / 2;
        if(value == arr[mid])return mid;
        else if(value < arr[mid])right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}


int chunk_search_int(int* arr, chunk* cks, int ck_size, int value)
{
    if(!arr || !cks)return -1;
    int left = 0, right = ck_size - 1;
    while(left <= right)
    {
        int mid = (left + right) / 2;
        if(cks[mid].max_value == value)
        {
            left = mid;
            break;
        }
        else if(cks[mid].max_value < value)left = mid + 1;
        else right = mid - 1;
    }

    if(left >= ck_size)return -1;

    int start = cks[left].low;
    int end = cks[left].high;
    for(int i = start; i <= end; i++)
    {
        if(arr[i] == value)return i;
    }
    return -1;
}



#endif