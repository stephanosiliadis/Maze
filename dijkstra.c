#include <stdio.h>
#include <stdlib.h>

#include "Heap.h"
#include "Maze.h"

/**
 * @brief Function to perform Dijkstra's Shortest Path Algorithm to compute the minimum distance to exit the maze.
 * @param maze The Maze instance that we want to exit.
 * @param invertedMaze The inverted version of the Maze instance.
 * @param entrance The first Chamber of the maze - which is also the entrance to the m aze.
 * @returns An array with the minimum distance of each Chamber from the entrance.
 */
int *findShortestPath(Maze *maze, Maze *invertedMaze, Chamber *entrance) {
  // Create a To-Do Heap (Min-Heap).
  Heap *toDo = createHeap();

  // Create the array that will store the minimum distance to each Chamber.
  int *minDistances = calloc(maze->numberOfChambers, sizeof(int));

  // Initialize distances and insert chambers into the heap.
  for (int i = 0; i < maze->numberOfChambers; i++) {
    maze->chambers[i]->minDistance = (maze->chambers[i] == entrance) ? 0 : (1 << 30);
    minDistances[i] = maze->chambers[i]->minDistance;
    insertChamber(toDo, maze->chambers[i]);
  }

  // Dijkstra's algorithm
  while (!isHeapEmpty(toDo)) {
    // Get the chamber with the smallest minDistance.
    Chamber *current = popMinDistanceChamber(toDo);

    // Traverse all tunnels (edges) from this chamber.
    Tunnel *tunnel = maze->tunnels[current->index];
    while (tunnel) {
      // Update the min distance if a shorter path is found.
      if (!current->hasInvertButton) {
        Chamber *neighbor = tunnel->to;
        int newDistance = current->minDistance + tunnel->weight;
        if (newDistance < neighbor->minDistance) {
          neighbor->minDistance = newDistance;
          minDistances[neighbor->index] = newDistance;
          insertChamber(toDo, neighbor);
        }
      } else {
        Chamber *neighbor = tunnel->to;
        int newDistance = current->minDistance + tunnel->weight;
        if (newDistance < neighbor->minDistance) {
          neighbor->minDistance = newDistance;
          minDistances[neighbor->index] = newDistance;
          insertChamber(toDo, neighbor);
        }
      }

      // Move to the next Tunnel.
      tunnel = tunnel->next;
    }
  }
  freeHeap(toDo);

  return minDistances;
}
