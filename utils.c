//
// Created by Oliver M Batista on 2019-04-14.
//
#include <stdio.h>

#include "utils.h"


void printMap(Map *map) {
  printf("\n%d %d\n", map->row, map->col);
  for (int r = 0; r <  map->row; r++) {
    for (int c = 0; c < map->col; c++)
      printf("%c", *(map->firstTile + r * map->col + c));
    printf("\n");
  }
}

void printDirection(enum directions currDirection) {
  switch (currDirection)
  {
    case SOUTH:
      printf("SOUTH\n");
      break;
    case EAST:
      printf("EAST\n");
      break;
    case NORTH:
      printf("NORTH\n");
      break;
    case WEST:
      printf("WEST\n");
      break;
  }
}