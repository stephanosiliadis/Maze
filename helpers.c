#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>

#include "Heap.h"

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

NodeState *findShortestPath(Maze *maze, Maze *invertedMaze) {
  int n = maze->numberOfChambers;
  int totalNodes = n * 2;
  NodeState **nodes = malloc(totalNodes * sizeof(NodeState *));
  int **visited = calloc(n, sizeof(int *));
  for (int i = 0; i < n; i++) visited[i] = calloc(2, sizeof(int));

  for (int i = 0; i < n; i++) {
    nodes[i * 2] = malloc(sizeof(NodeState));
    nodes[i * 2]->chamber = maze->chambers[i];
    nodes[i * 2]->state = 0;
    nodes[i * 2]->distance = (i == 0) ? 0 : INF;
    nodes[i * 2]->prev = NULL;

    nodes[i * 2 + 1] = malloc(sizeof(NodeState));
    nodes[i * 2 + 1]->chamber = maze->chambers[i];
    nodes[i * 2 + 1]->state = 1;
    nodes[i * 2 + 1]->distance = INF;
    nodes[i * 2 + 1]->prev = NULL;
  }

  Heap *heap = createHeap();
  insertNodeState(heap, nodes[0]);

  while (!isHeapEmpty(heap)) {
    NodeState *current = popMinNodeState(heap);
    int curIndex = current->chamber->index - 1;
    if (visited[curIndex][current->state]) continue;
    visited[curIndex][current->state] = 1;

    Tunnel *tunnel = (current->state == 0) ? maze->tunnels[curIndex] : invertedMaze->tunnels[curIndex];
    while (tunnel) {
      int neighborIndex = tunnel->to->index - 1;
      NodeState *neighbor = nodes[neighborIndex * 2 + current->state];
      int newDistance = current->distance + tunnel->weight;
      if (newDistance < neighbor->distance) {
        neighbor->distance = newDistance;
        neighbor->prev = current;
        insertNodeState(heap, neighbor);
      }
      tunnel = tunnel->next;
    }

    if (current->chamber->hasInvertButton) {
      NodeState *switched = nodes[curIndex * 2 + (1 - current->state)];
      if (current->distance < switched->distance) {
        switched->distance = current->distance;
        switched->prev = current;
        insertNodeState(heap, switched);
      }
    }
  }

  int exitIndex = n - 1;
  NodeState *exitNormal = nodes[exitIndex * 2];
  NodeState *exitInverted = nodes[exitIndex * 2 + 1];
  NodeState *bestExit = (exitNormal->distance <= exitInverted->distance) ? exitNormal : exitInverted;

  if (bestExit->distance == INF) {
    printf("IMPOSSIBLE\n");
    return NULL;
  }

  printf("%d\n", bestExit->distance);
  NodeState **path = NULL;
  int count = 0;
  NodeState *p = bestExit;
  while (p) {
    path = realloc(path, (count + 1) * sizeof(NodeState *));
    path[count++] = p;
    p = p->prev;
  }

  for (int i = count - 1; i >= 0; i--) {
    if (i > 0 && path[i]->chamber->hasInvertButton && path[i]->state != path[i - 1]->state) {
      printf("%d R\n", path[i]->chamber->index);
    } else {
      printf("%d\n", path[i]->chamber->index);
    }
  }
  free(path);
  for (int i = 0; i < n; i++) free(visited[i]);
  free(visited);
  freeHeap(heap);
  return bestExit;
}
