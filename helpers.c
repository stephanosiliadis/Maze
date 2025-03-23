#include <stdio.h>
#include <stdlib.h>

#include "Heap.h"
#include "Maze.h"

#define INF (1 << 30)

Maze *readInput() {
  // Initialize variables and get the values of n, m.
  int numberOfChambers = 0, numberOfTunnels = 0, chamberWithInvertButton = 0, weight = 0, from = 0, toIndex = 0;
  scanf("%d %d", &numberOfChambers, &numberOfTunnels);

  // Create the Maze.
  Maze *maze = createMaze(numberOfChambers, numberOfTunnels);

  // Add the Chambers to the Maze.
  for (int chamberIndex = 1; chamberIndex <= numberOfChambers; chamberIndex++) {
    Chamber *newChamber = createChamber(chamberIndex, 0);
    maze->chambers[chamberIndex - 1] = newChamber;
  }

  // Read which Chambers that have an invert button.
  scanf("%d", &chamberWithInvertButton);
  while (chamberWithInvertButton != -1) {
    maze->chambers[chamberWithInvertButton - 1]->hasInvertButton = 1;
    scanf("%d", &chamberWithInvertButton);
  }

  // Read the connections between the Chambers and the Tunnels.
  for (int tunnel = 0; tunnel < numberOfTunnels; tunnel++) {
    scanf("%d %d %d", &from, &toIndex, &weight);
    Chamber *toChamber = maze->chambers[toIndex - 1];
    addTunnel(maze, weight, from - 1, toChamber);
  }

  return maze;
}

// Note: NodeState is already defined in Heap.h.
NodeState *findShortestPath(Maze *maze, Maze *invertedMaze, Chamber *entrance) {
  int n = maze->numberOfChambers;
  int totalNodes = n * 2;  // Each chamber has 2 states.

  // Allocate an array for all NodeState objects.
  // For chamber i (0-indexed), state 0 is at index i*2, state 1 at i*2 + 1.
  NodeState **nodes = malloc(totalNodes * sizeof(NodeState *));
  for (int i = 0; i < n; i++) {
    // Initialize NodeState for normal state (state 0)
    nodes[i * 2] = malloc(sizeof(NodeState));
    nodes[i * 2]->chamber = maze->chambers[i];
    nodes[i * 2]->state = 0;
    nodes[i * 2]->distance = (i == 0) ? 0 : INF;  // Entrance (chamber index 0) distance is 0.
    nodes[i * 2]->prev = NULL;

    // Initialize NodeState for inverted state (state 1)
    nodes[i * 2 + 1] = malloc(sizeof(NodeState));
    nodes[i * 2 + 1]->chamber = maze->chambers[i];
    nodes[i * 2 + 1]->state = 1;
    nodes[i * 2 + 1]->distance = INF;
    nodes[i * 2 + 1]->prev = NULL;
  }

  // Create the heap for NodeState objects.
  Heap *heap = createHeap();
  // Insert the entrance in normal state.
  insertNodeState(heap, nodes[0]);

  // Main loop: process nodes in order of increasing distance.
  while (!isHeapEmpty(heap)) {
    NodeState *current = popMinNodeState(heap);
    int curIndex = current->chamber->index - 1;  // Adjust for 0-indexed array (assuming chamber->index is 1-indexed).

    // Select the appropriate tunnel list based on current state.
    Tunnel *tunnel;
    if (current->state == 0)
      tunnel = maze->tunnels[curIndex];
    else
      tunnel = invertedMaze->tunnels[curIndex];

    // Relax all outgoing edges from current.
    while (tunnel != NULL) {
      int neighborIndex = tunnel->to->index - 1;  // Adjust for 0-indexed array.
      // Get neighbor's NodeState for the same state as current.
      NodeState *neighbor = nodes[neighborIndex * 2 + current->state];
      int newDistance = current->distance + tunnel->weight;
      if (newDistance < neighbor->distance) {
        neighbor->distance = newDistance;
        neighbor->prev = current;
        insertNodeState(heap, neighbor);
      }
      tunnel = tunnel->next;
    }

    // If current chamber has an invert button, try switching state (zero cost).
    if (current->chamber->hasInvertButton) {
      NodeState *switched = nodes[curIndex * 2 + (1 - current->state)];
      if (current->distance < switched->distance) {
        switched->distance = current->distance;
        switched->prev = current;
        insertNodeState(heap, switched);
      }
    }
  }

  // Determine the best path to the exit (chamber n, index n-1).
  int exitIndex = n - 1;
  NodeState *exitNormal = nodes[exitIndex * 2];        // state 0
  NodeState *exitInverted = nodes[exitIndex * 2 + 1];  // state 1
  NodeState *bestExit = (exitNormal->distance <= exitInverted->distance) ? exitNormal : exitInverted;

  if (bestExit->distance == INF) {
    printf("IMPOSSIBLE\n");
    // Free allocated memory as needed (omitted for brevity).
    return NULL;
  }

  // Print the total shortest distance.
  printf("%d\n", bestExit->distance);

  // Reconstruct the path by backtracking via the prev pointers.
  NodeState **path = NULL;
  int count = 0;
  NodeState *p = bestExit;
  while (p != NULL) {
    path = realloc(path, (count + 1) * sizeof(NodeState *));
    path[count++] = p;
    p = p->prev;
  }
  // Print the path in the correct order (from entrance to exit).
  for (int i = count - 1; i >= 0; i--) {
    printf("%d\n", path[i]->chamber->index);
    // If a state change occurred between consecutive nodes, print 'R' after that chamber.
    if (i > 0 && (path[i]->state != path[i - 1]->state))
      printf("R\n");
  }
  free(path);

  // (Optional) Free all NodeState objects and the nodes array.
  // For clarity, cleanup code is not fully shown here.
  freeHeap(heap);

  return bestExit;  // Return bestExit for further processing if needed.
}