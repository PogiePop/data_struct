#include <stdio.h>
#include "tools/object.h"
#include "tools/arraylist.h"
#include "tools/linklist.h"
#include "tools/stack.h"
#include "tools/queue.h"
#include "tools/wamath.h"
#include "tools/wastring.h"


int main()
{
  str_ptr str1 = create_wastring_initstr("hello worldioioioio");
  printf("%s\nindex4 = %c\n", wa_to_string(str1), wa_at(str1, 4));
  str_ptr str2 = create_wastring_initstr("123");
  printf("%d\n", (int)str2->capacity);
  wa_copy_str(str2, str1);
  printf("%d\n", (int)str2->capacity);
  printf("%s\n", wa_to_string(str2));
  wa_erase(str2, 5);
  printf("%s\n", wa_to_string(str2));
  return 0;
}