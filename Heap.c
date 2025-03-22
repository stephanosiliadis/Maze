#include "Heap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Heap *createHeap() {
  Heap *heap = calloc(1, sizeof(Heap));
  heap->capacity = 10;
  heap->size = 0;
  heap->chambers = calloc(heap->capacity, sizeof(Chamber *));

  return heap;
}

// 0-indexed helper functions:
static int parent(int index) {
  return (index - 1) / 2;
}

static int left(int index) {
  return 2 * index + 1;
}

static int right(int index) {
  return 2 * index + 2;
}

void insertChamber(Heap *heap, Chamber *chamber) {
  if (heap->size == heap->capacity) {
    heap->capacity *= 2;
    heap->chambers = realloc(heap->chambers, heap->capacity * sizeof(Chamber *));
  }
  int currentIndex = heap->size;
  heap->chambers[currentIndex] = chamber;
  heap->size++;
  while (currentIndex > 0) {
    int parentIndex = parent(currentIndex);
    if (heap->chambers[parentIndex]->minDistance > heap->chambers[currentIndex]->minDistance) {
      Chamber *temp = heap->chambers[parentIndex];
      heap->chambers[parentIndex] = heap->chambers[currentIndex];
      heap->chambers[currentIndex] = temp;
      currentIndex = parentIndex;
    } else {
      break;
    }
  }
}

Chamber *popMinDistanceChamber(Heap *heap) {
  if (heap->size == 0) {
    return NULL;
  }
  Chamber *min = heap->chambers[0];
  heap->size--;
  heap->chambers[0] = heap->chambers[heap->size];
  int index = 0;
  while (1) {
    int l = left(index);
    int r = right(index);
    int smallest = index;
    if (l < heap->size && heap->chambers[l]->minDistance < heap->chambers[smallest]->minDistance) {
      smallest = l;
    }
    if (r < heap->size && heap->chambers[r]->minDistance < heap->chambers[smallest]->minDistance) {
      smallest = r;
    }
    if (smallest != index) {
      Chamber *temp = heap->chambers[index];
      heap->chambers[index] = heap->chambers[smallest];
      heap->chambers[smallest] = temp;
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
  free(heap->chambers);
  free(heap);
}
