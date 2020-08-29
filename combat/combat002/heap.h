#ifndef HEAP_H_
#define HEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// A simple struct of min-heap.
typedef struct {
  int size;
  int capacity;
  int* data;
} Heap;

// Researve space for heap.
int reserve_heap(Heap* heap, int cap);
// Always remember to free pointer space after using.
void free_heap(Heap* heap);
// Insert an element into the heap.
int insert_heap(Heap* heap, int val);
// Pop the top element (minimal one) of heap and reconstruct.
int pop_heap(Heap* heap);
// Get the top value only without modifying the heap.
int peek_heap(const Heap* heap);
// Print heap elements.
void print_heap(Heap* heap);

#endif

