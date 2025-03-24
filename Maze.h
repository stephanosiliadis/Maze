#ifndef MAZE_H
#define MAZE_H

// Struct to represent the Chambers/Nodes in our Maze and store all relevant data related to it.
typedef struct Chamber {
  int index;
  int hasInvertButton;
  int minDistance;
} Chamber;

// Struct to hold the state of the maze (0/1 for normal/inverted) the min distance of the current Chamber/Node and the previously visited node.
typedef struct NodeState {
  Chamber *chamber;
  int state;
  int distance;
  struct NodeState *prev;
} NodeState;

// Struct to represent the Tunnels/Edges in our Maze and store all relevant data related to it (implements a Linked List).
typedef struct Tunnel *TunnelPointer;
typedef struct Tunnel {
  int weight;
  Chamber *to;
  TunnelPointer next;
} Tunnel;

// Struct to represent the Maze/Graph and hold all relevant data related to it.
typedef struct Maze {
  int numberOfChambers;
  int numberOfTunnels;
  Tunnel **tunnels;
  Chamber **chambers;
} Maze;

// ---------- C H A M B E R  R E L A T E D  F U N C T I O N S ----------
/**
 * @brief Creates a Chamber instance with the necessary attributes.
 * @param index The index of the Chamber.
 * @param hasInvertButton A flag to show if the Chamber created has an invert button.
 * @returns A pointer to the newly created Chamber instance with the above attributes.
 */
Chamber *createChamber(int index, int hasInvertButton);

/**
 * @brief Frees the allocated memory for a Chamber instance.
 * @param chamber The Chamber to free the memory of.
 */
void freeChamber(Chamber *chamber);

// ---------- T U N N E L  R E L A T E D  F U N C T I O N S ----------
/**
 * @brief Creates a Tunnel instance with the necessary attributes.
 * @param weight The weight/distance of the Tunnel
 * @param to A pointer to the Chamber that the Tunnel is ending to.
 * @returns A pointer to the newly created Tunnel instance with the above attributes.
 */
Tunnel *createTunnel(int weight, Chamber *to);

/**
 * @brief Adds a Tunnel instance to a Maze instance.
 * @param maze A pointer to the Maze to which we want to add the Tunnel.
 * @param weight The weight of the Tunnel to add to the Maze.
 * @param from The index of the Chamber that the Tunnel starts from.
 * @param to A pointer to the Chamber that the Tunnel ends to.
 */
void addTunnel(Maze *maze, int weight, int from, Chamber *to);

/**
 * @brief Frees the allocated memory for a Tunnel instance.
 * @param tunnel The Tunnel to free the memory of.
 */
void freeTunnel(Tunnel *tunnel);

// ---------- M A Z E  R E L A T E D  F U N C T I O N S ----------
/**
 * @brief Creates a Maze instance with the necessary attributes.
 * @param numberOfChambers The number n, of Chambers in the Maze.
 * @param numberOfTunnels The number m, of Tunnels in the Maze.
 * @returns A pointer to the newly created Maze instance with the above attributes.
 */
Maze *createMaze(int numberOfChambers, int numberOfTunnels);

/**
 * @brief Inverts the given Maze, used when an invert button is pressed in a Chamber.
 * @param maze The Maze instance that we want to invert.
 * @return A pointer to the inverted Maze instance.
 */
Maze *invertMaze(Maze *maze);

/**
 * @brief Prints the information of the Maze in a graphical way - used for debugging.
 * @param maze The Maze instance that we want to print.
 */
void printMaze(Maze *maze);

/**
 * @brief Frees the allocated memory for a Maze instance.
 * @param maze The Maze to free the memory of.
 */
void freeMaze(Maze *maze);

#endif
