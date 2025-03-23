#include "Heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap *createHeap() {
  Heap *heap = calloc(1, sizeof(Heap));
  heap->capacity = 10;
  heap->size = 0;
  
  // Allocate an array of NodeState* pointers
  heap->nodes = calloc(heap->capacity, sizeof(NodeState *));

  return heap;
}

// Helper functions for index calculation (0-indexed)
static int parent(int index) {
  return (index - 1) / 2;
}

static int left(int index) {
  return 2 * index + 1;
}

static int right(int index) {
  return 2 * index + 2;
}

void insertNodeState(Heap *heap, NodeState *node) {
  // Grow the heap array if needed.
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    heap->nodes = realloc(heap->nodes, heap->capacity * sizeof(NodeState *));
  }
  int currentIndex = heap->size;
  heap->nodes[currentIndex] = node;
  heap->size++;

  // Bubble up to maintain min-heap property based on node->distance.
  while (currentIndex > 0) {
    int p = parent(currentIndex);
    if (heap->nodes[p]->distance > heap->nodes[currentIndex]->distance) {
      NodeState *temp = heap->nodes[p];
      heap->nodes[p] = heap->nodes[currentIndex];
      heap->nodes[currentIndex] = temp;
      currentIndex = p;
    } else {
      break;
    }
  }
}

NodeState *popMinNodeState(Heap *heap) {
  if (heap->size == 0)
    return NULL;
  // The root node holds the minimum distance.
  NodeState *min = heap->nodes[0];
  heap->size--;
  // Move the last element to the root.
  heap->nodes[0] = heap->nodes[heap->size];
  int index = 0;
  // Bubble down to restore the heap property.
  while (1) {
    int l = left(index);
    int r = right(index);
    int smallest = index;
    if (l < heap->size && heap->nodes[l]->distance < heap->nodes[smallest]->distance)
      smallest = l;
    if (r < heap->size && heap->nodes[r]->distance < heap->nodes[smallest]->distance)
      smallest = r;
    if (smallest != index) {
      NodeState *temp = heap->nodes[index];
      heap->nodes[index] = heap->nodes[smallest];
      heap->nodes[smallest] = temp;
      index = smallest;
    } else {
      break;
    }
  }
  return min;
}

int isHeapEmpty(Heap *heap) {
  return heap->size == 0;
}

void freeHeap(Heap *heap) {
  free(heap->nodes);
  free(heap);
}