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
#include "dijkstra.c"  // Or include a header if you separate the function declarations.
#include "readInput.c"

int main(int argc, const char *argv[]) {
   // Create maze based on input.
   Maze *mazeOrig = readInput();
   Maze *mazeInvert = invertMaze(mazeOrig);
   Chamber *entrance = mazeOrig->chambers[0];

   // Solve maze using the modified Dijkstra’s algorithm.
   findShortestPath(mazeOrig, mazeInvert, entrance);

   return 0;
}
