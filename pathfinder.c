//
// Created by Oliver M Batista on 2019-04-14.
//
#include <stdlib.h>
#include <stdio.h>

#include "pathfinder.h"

enum directions { SOUTH, EAST, NORTH, WEST }; // put in utils.h after
int isCircuitInverted = 0; // maybe a robot structure?
enum directions currDirection = SOUTH;

void shortCircuit() {
  if (isCircuitInverted)
    isCircuitInverted = 0;
  else
    isCircuitInverted = 1;
}

void printCurrentDirection() {
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

// update direction when a move is made
int updateDirection() {

  if (isCircuitInverted) {
    switch (currDirection)
    {
      case SOUTH:
        currDirection = WEST;
        break;
      case EAST:
        currDirection = SOUTH;
        break;
      case NORTH:
        currDirection = EAST;
        break;
      case WEST:
        currDirection = NORTH;
        break;
    }
  }else{
    switch (currDirection)
    {
      case SOUTH:
        currDirection = EAST;
        break;
      case EAST:
        currDirection = NORTH;
        break;
      case NORTH:
        currDirection = WEST;
        break;
      case WEST:
        currDirection = SOUTH;
        break;
    }
  }

  return 0;
}

int move(Map *map, char **currentTile) {

  char *nextTile = *currentTile;
  int nextTrys = 0;

  do {

    switch (currDirection)
    {
      case SOUTH:
        nextTile = *currentTile + (map->col * sizeof(char));
        break;
      case EAST:
        nextTile = *currentTile + sizeof(char);
        break;
      case NORTH:
        nextTile = *currentTile - (map->col * sizeof(char));
        break;
      case WEST:
        nextTile = *currentTile - sizeof(char);
        break;
    }

    // TODO: check for beer mode
    // in beer mode it breaks X obstacles otherwise X is like #
    if(*nextTile == '#')
      updateDirection();

    nextTrys++;
    if(nextTrys > 3){
      printf("LOOP\n");
      return 1;
    }

  } while (*nextTile == '#');

  *currentTile = nextTile;

  printCurrentDirection();

  return 0;
}

void updateState(char *currentTile) {

  // #, X, @, $, S, E, N, W, B, I, T

  switch (*currentTile)
  {
    case ' ':
      break;
    case '$':
      break;
    case '@':
      break;
    case 'S':
      currDirection = SOUTH;
      break;
    case 'E':
      currDirection = EAST;
      break;
    case 'N':
      currDirection = NORTH;
      break;
    case 'W':
      currDirection = WEST;
      break;
    case 'I':
      shortCircuit();
      break;
    case 'B':
      currDirection = WEST;
      break;
    case 'T':
      printf("Implement Teleporter");
      break;
    default:
      printf("ERROR\n");
      break;
  }
}

int simulatePath(Map *map) {

  // If Bender makes this ammount of movements without reaching the suicidal booth
  // we declare as LOOP and now we can calm down knowing that he will not die today.
  int maxMoves = ((*map).row - 2)*((*map).col - 2);
  int moves = 0;

  char *currentTile = (*map).startPoint;


  while (*currentTile != '$') {

    // Make a move
    if (move(map, &currentTile)) return 1;

    // Update state based on the current tile
    updateState(currentTile);


    // When didnt reach suicide booth even moving through all the possible map tiles (row-2)*(col-2)
    // we consider that as a LOOP
    moves++;
    if(moves >= maxMoves) {
      printf("LOOP\n");
      printf("Bender will never reach the suicide booth\n");
      return 0;
    }

  }

  printf("Bender did reach $\n");

  return 0;

}