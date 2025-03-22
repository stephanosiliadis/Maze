/**
 * File: main.c
 * Authors: Stefanos Iliadis (s.iliadis@student.rug.nl) - Aristotelis Christoforidis (a.christoforidis@student.rug.nl)
 * S-Numbers: s5885671 - s5962021
 * Date: 20-03-2025
 * Version: 1.0
 * Description: Exit a Maze using Dijkstra's Algorithm with some modifications.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Heap.h"
#include "Maze.h"
#include "dijkstra.c"
#include "readInput.c"

int main(int argc, const char *argv[]) {
  // Create original and inverted Maze based on input and get the entrance.
  Maze *origMaze = readInput();
  Maze *invertedMaze = invertMaze(origMaze);
  Chamber *entrance = origMaze->chambers[0];

  // Solve maze.
  findShortestPath(origMaze, invertedMaze, entrance);

  return 0;
}
