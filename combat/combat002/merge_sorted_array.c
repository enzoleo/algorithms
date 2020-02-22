#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main() {

  Heap heap;
  reserve_heap(&heap, 7);
  insert_heap(&heap, 1);
  insert_heap(&heap, 3);
  insert_heap(&heap, 7);
  insert_heap(&heap, 10);
  insert_heap(&heap, 2);
  insert_heap(&heap, 8);
  insert_heap(&heap, 11);
  print_heap(&heap);
  printf("pop res: %d\n", pop_heap(&heap));
  print_heap(&heap);
  free_heap(&heap);
  
  return 0;
}
