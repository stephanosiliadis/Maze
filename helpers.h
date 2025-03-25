#ifndef HELPERS_H
#define HELPERS_H

#include "Maze.h"

/**
 * @brief Read the input and created the described Maze instance.
 * @returns A pointer to the Maze instance with the characteristics of the input.
 */
Maze *readInput();

/**
 * @brief Performs Dijkstra's shortest path algorithm with the necessary modifications
 * to account for the option to press the invert button at certain Chambers.
 * @param maze The Maze that we want to find the shortest path to the exit.
 * @param invertedMaze The inverted version of the Maze, so that we dont have to invert the maze over and over.
 */
void findShortestPath(Maze *maze, Maze *invertedMaze);

#endif
