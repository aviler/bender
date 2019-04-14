//
// Created by Oliver M Batista on 2019-04-14.
//
#include <stdlib.h>
#include <stdio.h>

#include "pathfinder.h"


char* nextTile(char *currentTile) {

  return currentTile;
}

int simulatePath(Map *map) {

  // If Bender makes this ammount of movements without reaching the suicidal booth
  // we declare as LOOP and now we can calm down knowing that he will not die today.
  int maxMoves = ((*map).row - 2)*((*map).col - 2);
  int moves = 0;

  char *currentTile = (*map).startPoint;



  while (*nextTile(currentTile) != '$') {


    printf("did move\n");
    moves++;

    // when didnt reach suicide booth even moving through all the possible map tiles (row-2)*(col-2)
    // we consider that as a LOOP
    if(moves >= maxMoves) {
      printf("LOOP\n");
      return 0;
    }


    // we reach the starting point again (NO INVERTERS MAKE THIS PREMISSE WRONG)




  }


  return 0;

}