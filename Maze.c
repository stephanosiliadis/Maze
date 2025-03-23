// --- File: Maze.c ---
#include "Maze.h"
#include <stdio.h>
#include <stdlib.h>

Chamber *createChamber(int index, int hasInvertButton) {
  Chamber *chamber = calloc(1, sizeof(Chamber));
  chamber->index = index;
  chamber->hasInvertButton = hasInvertButton;
  chamber->minDistance = 1 << 30;
  return chamber;
}

void freeChamber(Chamber *chamber) {
  if (!chamber) return;
  free(chamber);
}

Tunnel *createTunnel(int weight, Chamber *to) {
  Tunnel *newTunnel = calloc(1, sizeof(Tunnel));
  newTunnel->weight = weight;
  newTunnel->to = to;
  newTunnel->next = NULL;
  return newTunnel;
}

void freeTunnel(Tunnel *tunnel) {
  if (!tunnel) return;
  free(tunnel);
}

Maze *createMaze(int numberOfChambers, int numberOfTunnels) {
  Maze *maze = calloc(1, sizeof(Maze));
  maze->numberOfChambers = numberOfChambers;
  maze->numberOfTunnels = numberOfTunnels;
  maze->chambers = calloc(numberOfChambers, sizeof(Chamber *));
  maze->tunnels = calloc(numberOfChambers, sizeof(Tunnel *));
  return maze;
}

void addTunnel(Maze *maze, int weight, int from, Chamber *to) {
  Tunnel *newTunnel = createTunnel(weight, to);
  newTunnel->next = maze->tunnels[from];
  maze->tunnels[from] = newTunnel;
}

void printMaze(Maze *maze) {
  for (int i = 0; i < maze->numberOfChambers; i++) {
    printf("Chamber %d: ", i);
    Tunnel *tunnel = maze->tunnels[i];
    while (tunnel != NULL) {
      printf("-> %d(w=%d) ", tunnel->to->index, tunnel->weight);
      tunnel = tunnel->next;
    }
    printf("\n");
  }
}

void freeMaze(Maze *maze) {
  if (!maze) return;
  for (int i = 0; i < maze->numberOfChambers; i++) {
    Tunnel *tunnel = maze->tunnels[i];
    while (tunnel) {
      Tunnel *temp = tunnel;
      tunnel = tunnel->next;
      free(temp);
    }
  }
  free(maze->tunnels);
  free(maze->chambers);
  free(maze);
}

Maze *invertMaze(Maze *maze) {
  int n = maze->numberOfChambers;
  int m = maze->numberOfTunnels;
  Maze *invertedMaze = createMaze(n, m);
  for (int i = 0; i < n; i++) {
    invertedMaze->chambers[i] = maze->chambers[i];
  }
  for (int i = 0; i < n; i++) {
    Tunnel *current = maze->tunnels[i];
    while (current != NULL) {
      int from = current->to->index - 1;
      Chamber *to = maze->chambers[i];
      addTunnel(invertedMaze, current->weight, from, to);
      current = current->next;
    }
  }
  return invertedMaze;
}