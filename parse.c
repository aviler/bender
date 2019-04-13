//
// Created by Oliver M Batista on 2019-04-12.
//

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parse.h"

#define bufSize 1024


int invalidValue(int *value) {
  if (errno == EINVAL) {
    printf("Error: Invalid value for number of rows/columns\n");
    return 1;
  }

  if (errno == ERANGE) {
    printf("Error: Row/Column value out of range\n");
    return 1;
  }

  if (*value < 3) {
    printf("Error: Minimum value for rows/columns is 3\n");
    return 1;
  }

  return 0;
}

int extractNumberOfRowsCollumns(char *line, int *row, int *col) {
  char *end;

  *row = strtoul(line, &end, 10);

  if (invalidValue(row)) { return 1; }

  *col = strtoul(end, &end, 10);

  if (invalidValue(col)) { return 1; }

  return 0;
}

int parseFile(int argc, char *argv[], char **map, char **startPoint) {

  FILE* mapFile;
  char buf[bufSize];

  int row = 0;
  int col = 0;

  if (argc != 2) {
    printf("Usage: %s <input_01.map>\n", argv[0]);
    return 1;
  }

  if ((mapFile = fopen(argv[1], "r")) == NULL) {
    perror("Error");
    return 1;
  }

  // Read first line to determine allocation size
  if (fgets(buf, sizeof(buf), mapFile) != NULL) {

    if (extractNumberOfRowsCollumns(buf, &row, &col)) {
      fclose(mapFile);
      return 1;
    }

  }

  printf("Map dimensions: %d x %d\n\n", row, col);

  // Read map from file, allocating char matrix and save starting point
  char ch;
  int r,c = 0;

  *map = (char *)malloc(row * col * sizeof(char));

  while ((ch = fgetc(mapFile)) != EOF) {

    if (ch == '\n') {
      c = 0;
      r++;
    } else {

      if (ch == '@') {
        *startPoint = (*map) + r*col + c;
      }

      *((*map) + r*col + c) = ch;
      c++;
    }
  }

  fclose(mapFile);

  return 0;
}