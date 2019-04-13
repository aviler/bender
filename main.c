//
// Created by Oliver M Batista on 2019-04-12.
//

#include <stdlib.h>
#include <stdio.h>

#include "parse.h"


int main(int argc, char *argv[]) {

  char *map = NULL;
  char *startPoint = NULL;

  // Parse file, initialize map data structure and set starting point
  if (parseFile(argc, argv, &map, &startPoint)) return EXIT_FAILURE;


  // Printing parsed map
  for (int r = 0; r <  10; r++) {
    for (int c = 0; c < 10; c++)
      printf("%c", *(map + r * 10 + c));
    printf("\n");
  }

  printf("%c", *startPoint);

  return EXIT_SUCCESS;
}