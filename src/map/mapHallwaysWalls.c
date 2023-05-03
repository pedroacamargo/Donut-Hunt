#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void buildWalls(NormalRoom * room, char axis, int isFirst, int axisSwap) {
  
  int roomX = room->door.x;
  int roomY = room->door.y;
  for (int x = roomX - 1; x <= roomX + 1; x++) {
    for (int y = roomY - 1; y <= roomY + 1; y++) {

      if (axisSwap == 1) {
        if ((x == roomX && y == roomY) || (mvinch(y,x) == '+')) mvaddch(y,x,'+');
        else if (mvinch(y,x) != '#' || mvinch(y,x) != '.' || mvinch(y,x) != '+') mvaddch(y,x,'#');
      }

      if (isFirst == 1 && axis == 'x') {

        if (mvinch(y,x) != '#' && mvinch(y,x) != '.' && mvinch(y,x) != '+') mvaddch(y,x,'#');

      } else if ( axis == 'x' ) {

        if (mvinch(y,x) != '.' && mvinch(y,x) != '#' && mvinch(y,x) != '+') {
          mvaddch(y,x,'#');
        }

      } else if ( axis == 'y' ) {

        if (mvinch(y,x) != '#' && mvinch(y,x) != '+' && mvinch(y,x) != '.') {
          mvaddch(y,x,'#');
        }
      }
    }
  }
}