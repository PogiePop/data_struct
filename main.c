#include <stdio.h>
#include "tools/object.h"
#include "tools/arraylist.h"
#include "tools/linklist.h"
#include "tools/stack.h"
#include "tools/queue.h"
#include "tools/wamath.h"
#include "tools/wastring.h"
#include "tools/tree.h"
#include "tools/graph.h"
#include "tools/search.h"
#include "tools/wasort.h"
#define str(x) #x

bool Comp1(int a, int b) {
    return a < b;
}

int main()
{
   int arr[] = {4, 1, 6, 5, 8, 6};
    quick_sort_int(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1, Comp1);
    print_array_int(arr, sizeof(arr) / sizeof(arr[0]));
    return 0;
}