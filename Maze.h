#ifndef MAZE_H
#define MAZE_H

typedef struct Chamber {
  int index;
  int hasInvertButton;
  int minDistance;
} Chamber;

typedef struct NodeState {
  Chamber *chamber;
  int state;
  int distance;
  struct NodeState *prev;
} NodeState;

typedef struct Tunnel *TunnelPointer;
typedef struct Tunnel {
  int weight;
  Chamber *to;
  TunnelPointer next;
} Tunnel;

typedef struct Maze {
  int numberOfChambers;
  int numberOfTunnels;
  Tunnel **tunnels;
  Chamber **chambers;
} Maze;

Maze *createMaze(int numberOfChambers, int numberOfTunnels);
Maze *invertMaze(Maze *maze);
void printMaze(Maze *maze);
void freeMaze(Maze *maze);

Tunnel *createTunnel(int weight, Chamber *to);
void addTunnel(Maze *maze, int weight, int from, Chamber *to);
void freeTunnel(Tunnel *tunnel);

Chamber *createChamber(int index, int hasInvertButton);
void freeChamber(Chamber *chamber);

#endif
