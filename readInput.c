#include "Maze.h"

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
