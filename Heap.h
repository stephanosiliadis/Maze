#ifndef HEAP_H
#define HEAP_H

#include "Maze.h"

typedef struct Heap {
  NodeState **nodes;
  int size;
  int capacity;
} Heap;

Heap *createHeap();
void insertNodeState(Heap *heap, NodeState *node);
NodeState *popMinNodeState(Heap *heap);
int isHeapEmpty(Heap *heap);
void freeHeap(Heap *heap);

#endif
