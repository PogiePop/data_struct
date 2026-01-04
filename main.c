#include <stdio.h>
#include "tools/object.h"
#include "tools/arraylist.h"
#include "tools/linklist.h"
#include "tools/stack.h"
#include "tools/queue.h"

int main()
{
  qe_ptr q = create_queue();
  enqueue_char_ptr(q, "wang");
  enqueue_char(q, 'r');
  enqueue_double(q, 12);
  enqueue_double(q, 2.78399);
  enqueue_float(q, 8.9f);
  qe_print(q);
  qe_dequeue(q);
  PRINT_OBJECT("%O\n", qe_front(q));
  qe_dequeue(q);
  qe_dequeue(q);
  qe_dequeue(q);
  qe_dequeue(q);
  qe_dequeue(q);
  qe_print(q);
  destory_queue(&q);
  if(!q)PRINT_OBJECT("queue is free");
}