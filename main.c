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
#define str(x) #x


int main()
{
   int arr[] = {4, 1, 6, 5, 8};
   wa_tree tr = create_watree();
   wa_bst_insert_arr(tr, arr, sizeof(arr) / sizeof(int));
   wa_bst_non_remove_value_int(tr, 6);
   preorder(tr);
   printf("\n");
   inorder(tr);
   printf("\n");
   postorder(tr);
   destory_tree(&tr);
    return 0;
}