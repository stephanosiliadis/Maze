#ifndef HELPERS_H
#define HELPERS_H

#include "Maze.h"

Maze *readInput();
NodeState *findShortestPath(Maze *maze, Maze *invertedMaze);

#endif
