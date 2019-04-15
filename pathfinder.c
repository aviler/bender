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

void printCurrentDirection(enum directions currDirection) {
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

    // TODO: check for beer mode
    // in beer mode it breaks X obstacles otherwise X is like #
    if(*nextTile == '#')
      updateDirection(bender);

    nextTrys++;
    if(nextTrys > 3){
      printf("LOOP\n");
      return 1;
    }

  } while (*nextTile == '#');

  (*bender)->currentTile = nextTile;

  printCurrentDirection((*bender)->currDirection);

  return 0;
}

void updateState(Bender **bender) {

  // #, X, @, $, S, E, N, W, B, I, T

  switch (*(*bender)->currentTile)
  {
    case ' ':
      break;
    case '$':
      break;
    case '@':
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
      printf("Implement beer");
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

  // If Bender makes this amount of movements without reaching the suicidal booth
  // we declare as LOOP and now we can calm down knowing that he will not die today.
  int maxMoves = ((*map).row - 2)*((*map).col - 2);
  int moves = 0;

  Bender bender = {(*map).startPoint, 0, SOUTH};
  Bender *bender_ptr = &bender;

  while (*bender.currentTile != '$') {

    // Make a move
    if (move(map, &bender_ptr)) return 1;

    // Update state based on the current tile
    updateState(&bender_ptr);


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