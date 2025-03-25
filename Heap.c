#include "Heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap *createHeap() {
  Heap *heap = calloc(1, sizeof(Heap));
  heap->capacity = 10;
  heap->size = 0;
  heap->nodes = calloc(heap->capacity, sizeof(NodeState *));

  return heap;
}

// Helper functions for index calculation (0-indexed).
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
    int parentIndex = parent(currentIndex);
    if (heap->nodes[parentIndex]->distance > heap->nodes[currentIndex]->distance) {
      NodeState *temp = heap->nodes[parentIndex];
      heap->nodes[parentIndex] = heap->nodes[currentIndex];
      heap->nodes[currentIndex] = temp;
      currentIndex = parentIndex;
    } else {
      break;
    }
  }
}

NodeState *popMinNodeState(Heap *heap) {
  if (heap->size == 0) {
    return NULL;
  }

  // The root node holds the minimum distance.
  NodeState *min = heap->nodes[0];
  heap->size--;

  // Move the last element to the root.
  heap->nodes[0] = heap->nodes[heap->size];
  int index = 0;

  // Bubble down to restore the heap property.
  while (1) {
    int leftIndex = left(index);
    int rightIndex = right(index);
    int currentIndex = index;
    if (leftIndex < heap->size && heap->nodes[leftIndex]->distance < heap->nodes[currentIndex]->distance) {
      currentIndex = leftIndex;
    }
    if (rightIndex < heap->size && heap->nodes[rightIndex]->distance < heap->nodes[currentIndex]->distance) {
      currentIndex = rightIndex;
    }
    if (currentIndex != index) {
      NodeState *aux = heap->nodes[index];
      heap->nodes[index] = heap->nodes[currentIndex];
      heap->nodes[currentIndex] = aux;
      index = currentIndex;
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
