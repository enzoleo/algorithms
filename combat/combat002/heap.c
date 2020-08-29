#include <assert.h>
#include "heap.h"

// Researve space for heap.
int reserve_heap(Heap* heap, int cap) {
  assert(cap > 0);
  heap->capacity = cap;
  heap->size = 0;
  // Use C malloc to allocate space.
  heap->data = (int*)malloc(cap * sizeof(int));
  return heap->data == NULL;
}

// Always remember to free pointer space after using.
void free_heap(Heap* heap) {
  free(heap->data);
  heap->data = NULL;
};

// Insert an element into the heap.
int insert_heap(Heap* heap, int val) {
  int i = heap->size++;
  assert(i < heap->capacity);
  while (i > 0) {
    // Find the index of parent node.
    int j = (i - 1) >> 1;
    if (heap->data[j] > val) {
      // If the parent node value is larger than the current one, just swap
      // them and then compare to grandfather.
      heap->data[i] = heap->data[j];
      i = j;
    } // Break if everything finishes.
    else break;
  }
  heap->data[i] = val;
  return i;
}

// Pop the top element (minimal one) of heap and reconstruct.
int pop_heap(Heap* heap) {
  // Only non-empty heaps are allowed.
  assert(heap->size > 0);
  int size = --heap->size;
  // The iteration terminates when encountering leaves.
  int i = 0, bound = size >> 1;
  
  // The target element and the last one.
  int res = heap->data[0], val = heap->data[size];
  heap->data[i] = val;
  while (i < bound) {
    int child = (i << 1) + 1;
    // Find child index (children indices).
    if (child + 1 < size && heap->data[child + 1] < heap->data[child]) {
      ++child;
    }
    if (heap->data[child] < val) heap->data[i] = heap->data[child];
    else break;
    // Dive into next layer of this heap.
    i = child;
  }
  // The index i here is safe.
  heap->data[i] = val;
  return res;
}

// Get the top value only without modifying the heap.
int peek_heap(const Heap* heap) {
  assert(heap->size > 0);
  return heap->data[0];
}

// Print heap elements.
void print_heap(Heap* heap) {
  for (int i = 0, size = heap->size; i < size; ++i)
    printf("%d ", heap->data[i]);
  printf("\n");
}

