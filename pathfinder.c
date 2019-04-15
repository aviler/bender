//
// Created by Oliver M Batista on 2019-04-14.
//
#include <stdlib.h>
#include <stdio.h>

#include "pathfinder.h"
#include "utils.h"


void shortCircuit(Bender **bender) {
  if ((*bender)->isCircuitInverted)
    (*bender)->isCircuitInverted = 0;
  else
    (*bender)->isCircuitInverted = 1;
}

void drinkBeer(Bender **bender) {
  if ((*bender)->isBreakerModeOn)
    (*bender)->isBreakerModeOn = 0;
  else
    (*bender)->isBreakerModeOn = 1;
}

void enterTeleporter(Map *map, Bender **bender) {
  if ((*bender)->currentTile == map->teleporterOne)
    (*bender)->currentTile = map->teleporterTwo;
  else
    (*bender)->currentTile = map->teleporterOne;
}

int updateDirection(Bender **bender) {

  if ((*bender)->isCircuitInverted) {
    switch ((*bender)->currDirection)
    {
      case SOUTH:
        (*bender)->currDirection = WEST;
        break;
      case EAST:
        (*bender)->currDirection = SOUTH;
        break;
      case NORTH:
        (*bender)->currDirection = EAST;
        break;
      case WEST:
        (*bender)->currDirection = NORTH;
        break;
    }
  }else{
    switch ((*bender)->currDirection)
    {
      case SOUTH:
        (*bender)->currDirection = EAST;
        break;
      case EAST:
        (*bender)->currDirection = NORTH;
        break;
      case NORTH:
        (*bender)->currDirection = WEST;
        break;
      case WEST:
        (*bender)->currDirection = SOUTH;
        break;
    }
  }

  return 0;
}

int move(Map *map, Bender **bender) {

  char *nextTile = (*bender)->currentTile;
  int nextTrys = 0;

  do {

    switch ((*bender)->currDirection)
    {
      case SOUTH:
        nextTile = (*bender)->currentTile + (map->col * sizeof(char));
        break;
      case EAST:
        nextTile = (*bender)->currentTile + sizeof(char);
        break;
      case NORTH:
        nextTile = (*bender)->currentTile - (map->col * sizeof(char));
        break;
      case WEST:
        nextTile = (*bender)->currentTile - sizeof(char);
        break;
    }

    if(*nextTile == '#')
      updateDirection(bender);

    if( !((*bender)->isBreakerModeOn) && *nextTile == 'X' )
      updateDirection(bender);

    nextTrys++;
    if(nextTrys > 3){
      printf("LOOP\n");
      return 1;
    }

  } while ((*nextTile == '#') || (*nextTile == 'X' && !((*bender)->isBreakerModeOn) ));

  (*bender)->currentTile = nextTile;

  printDirection((*bender)->currDirection);

  return 0;
}

int updateState(Map *map, Bender **bender) {

  // #, X, @, $, S, E, N, W, B, I, T

  switch (*(*bender)->currentTile)
  {
    case ' ':
      break;
    case '$':
      break;
    case '@':
      break;
    case 'X':
      if((*bender)->isBreakerModeOn)
        *((*bender)->currentTile) = ' ';
      break;
    case 'S':
      (*bender)->currDirection = SOUTH;
      break;
    case 'E':
      (*bender)->currDirection = EAST;
      break;
    case 'N':
      (*bender)->currDirection = NORTH;
      break;
    case 'W':
      (*bender)->currDirection = WEST;
      break;
    case 'I':
      shortCircuit(bender);
      break;
    case 'B':
      drinkBeer(bender);
      break;
    case 'T':
      enterTeleporter(map, bender);
      break;
    default:
      printf("ERROR: Founded unexpected symbol -> %c\n", *(*bender)->currentTile);
      return 1;
  }

  return 0;
}

int simulatePath(Map *map) {

  // If Bender makes this amount of movements without reaching the suicidal booth
  // we declare as LOOP and now we can calm down knowing that he will not die today.
  int maxMoves = ((*map).row - 2)*((*map).col - 2);
  int moves = 0;

  Bender bender = {(*map).startPoint, SOUTH, 0, 0};
  Bender *bender_ptr = &bender;

  while (*bender.currentTile != '$') {

    // Make a move
    if (move(map, &bender_ptr)) return 1;

    // Update state based on the current tile
    if (updateState(map, &bender_ptr)) return 1;


    // When didnt reach suicide booth even moving through all the possible map tiles (row-2)*(col-2)
    // we consider that as a LOOP
    moves++;
    if(moves >= maxMoves) {
      printf("LOOP\n");
      return 0;
    }

  }

  return 0;
}