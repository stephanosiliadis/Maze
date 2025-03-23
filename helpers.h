#include "Maze.h"

Maze *readInput();
NodeState *findShortestPath(Maze *maze, Maze *invertedMaze, Chamber *entrance);
