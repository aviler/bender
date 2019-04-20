//
// Created by Oliver M Batista on 2019-04-12.
//

#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "parser.h"
#include "pathfinder.h"


int main(int argc, char *argv[]) {

  Map map = {NULL, NULL, 0, 0};
  Map *map_ptr = &map;

  // Parse file and initialize map data structure
  if (parseFile(argc, argv, &map_ptr)) {
    if(map.firstTile != NULL)
      free(map.firstTile);
    return EXIT_FAILURE;
  }

  // Simulate path that Bender would walk
  if (simulatePath(&map)) {
    free(map.firstTile);
    return EXIT_FAILURE;
  }

  // Printing parsed map for debug
  // printMap(map_ptr);

  free(map.firstTile);
  return EXIT_SUCCESS;
}