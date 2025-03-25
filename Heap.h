#ifndef HEAP_H
#define HEAP_H

#include "Maze.h"

// Struct to implement a Heap of NodeState instances to use as the To-Do List for Dijkstra's Algorithm.
typedef struct Heap {
  NodeState **nodes;
  int size;
  int capacity;
} Heap;

/**
 * @brief Creates a Heap instance and initializes the size and capacity attributes.
 * @returns A pointer to the newly created Heap instance.
 */
Heap *createHeap();

/**
 * @brief Performs an up-heap operation to insert a NodeState to a Heap.
 * @param heap The Heap that we want to insert to.
 * @param node The NodeState that we want to insert to the Heap.
 */
void insertNodeState(Heap *heap, NodeState *node);

/**
 * @brief Performs a down-heap operation to get the NodeState with the minimum distance attribute from the Heap.
 * @param heap The Heap that we want to pop from.
 * @returns A pointer to the NodeState instance with the minimum distance attribute.
 */
NodeState *popMinNodeState(Heap *heap);

/**
 * @brief Checks if a Heap instance is empty (size=0).
 * @param heap The Heap to check if it is empty.
 * @returns A boolean value of 1 is the Heap is empty or 0 if it is not.
 */
int isHeapEmpty(Heap *heap);

/**
 * @brief Frees the allocated memory for a Heap instance.
 * @param heap The Heap to free the memory of.
 */
void freeHeap(Heap *heap);

#endif
