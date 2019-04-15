//
// Created by Oliver M Batista on 2019-04-14.
//

#ifndef BENDER_UTILS_H
#define BENDER_UTILS_H

// Constants
#define BUFFER_SIZE 1024
#define MIN_ROWCOL_VALUE 4

// Enuns
enum directions { SOUTH, EAST, NORTH, WEST };

// Structs
struct map {
  char *firstTile;
  char *startPoint;
  int row;
  int col;
};
typedef struct map Map;

struct bender {
  char *currentTile;
  int isCircuitInverted;
  enum directions currDirection;
};
typedef struct bender Bender;

// Functions
void printMap(Map *map);

#endif //BENDER_UTILS_H
