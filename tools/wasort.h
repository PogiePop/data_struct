#ifndef _WA_SORT_H
#define _WA_SORT_H

#include <stdbool.h>

typedef bool(*Compare)(int, int);

inline static void wa_swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

inline  static void print_array_int(int arr[], int size) {
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
}

inline static void bubble_sort_int(int arr[], int size, Compare func);
inline static void insert_sort_int(int arr[], int size, Compare func);
inline static void chose_sort_int(int arr[], int size, Compare func);
inline static void hill_sort_int(int arr[], int size, Compare func);
inline static void insert_sort_int_sub(int arr[], int start, int end, int stride, Compare func);
inline static void quick_sort_int(int arr[], int low, int high, Compare func);
inline static int pivot_partition_int(int arr[], int low, int high, Compare func);


///冒泡排序
///@date 2026/2/5
///@author 不吉波普
inline static void bubble_sort_int(int arr[], int size, Compare func) {
    //比较次数
    for (int i = size - 1; i > 0; i--) {
        bool flag = false;
        for (int j = 1; j < size; j++) {
            if (!func(arr[j-1], arr[j])) {
                wa_swap(&arr[j-1], &arr[j]);
                flag = true;
            }
        }
        if (!flag)return;
    }
}

inline static void insert_sort_int(int arr[], int size, Compare func) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        for (j; j >= 0; j--) {
            if (!func(arr[j] , key))
                arr[j+1] = arr[j];
            else break;
        }
        arr[j+1] = key;
    }
}

inline static void chose_sort_int(int arr[], int size, Compare func) {
    for (int i = 0; i < size-1; i++) {
        int key = i;
        for (int j = i+1; j < size; j++) {
            if (!func(arr[key], arr[j]))key = j;
        }
        wa_swap(arr+i, arr+key);
    }
}

inline static void insert_sort_int_sub(int arr[], int start, int end, int stride, Compare func) {
    for (int i = start; i <= end; i+=stride) {
        int key = arr[i];
        int j = i - stride;
        for (j; j >= start; j-=stride) {
            if (!func(arr[j], key))arr[j + stride] = arr[j];
            else break;
        }
        arr[j + stride] = key;
    }
}

inline static void hill_sort_int(int arr[], int size, Compare func) {
    int k = size / 2;
    for (int i = k; i > 0; i/=2) {
        for (int j = 0; j < k; j++) {
            insert_sort_int_sub(arr, j, size - 1, i, func);
        }
    }
}


inline static void quick_sort_int(int arr[], int low, int high, Compare func) {
    if (low >= high)return;
    int pivot = pivot_partition_int(arr, low, high, func);
    //处理左右区间（不包括基准）
    quick_sort_int(arr, low, pivot-1, func);
    quick_sort_int(arr, pivot+1, high, func);
}
inline static int pivot_partition_int(int arr[], int low, int high, Compare func) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (func(arr[j], pivot)) {
            ++i;
            wa_swap(arr+i, arr+j);
        }
    }
    wa_swap(arr+i+1, arr+high);
    return i + 1;
}




#endif