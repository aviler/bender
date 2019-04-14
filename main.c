//
// Created by Oliver M Batista on 2019-04-12.
//

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "parser.h"
#include "pathfinder.h"


int main(int argc, char *argv[]) {

//  char *map = NULL;
  char *startPoint = NULL;

  Map map;
  Map *map_ptr = &map;

  // Parse file, initialize map data structure and set starting point
  if (parseFile(argc, argv, &map_ptr)) return EXIT_FAILURE;

  // Simulate path that Bender would walk
  simulatePath(&map);

  // Printing parsed map for debug
  for (int r = 0; r <  10; r++) {
    for (int c = 0; c < 10; c++)
      printf("%c", *(map.firstTile + r * 10 + c));
    printf("\n");
  }

  printf("%c", *map.startPoint);

  return EXIT_SUCCESS;
}