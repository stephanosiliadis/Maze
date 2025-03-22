#ifndef HEAP_H
#define HEAP_H

#include "Maze.h"

typedef struct Heap {
  Chamber **chambers;
  int size;
  int capacity;
} Heap;

Heap *createHeap();
void insertChamber(Heap *heap, Chamber *chamber);
Chamber *popMinDistanceChamber(Heap *heap);
int isHeapEmpty(Heap *heap);
void freeHeap(Heap *heap);

#endif
