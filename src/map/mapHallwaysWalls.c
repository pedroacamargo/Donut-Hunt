#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void buildWalls(NormalRoom * room, char axis, int isFirst, int axisSwap, Tile ** map) {
  
  int roomX = room->door.x;
  int roomY = room->door.y;
  for (int x = roomX - 1; x <= roomX + 1; x++) {
    for (int y = roomY - 1; y <= roomY + 1; y++) {

      if (axisSwap == 1) {
        if ((x == roomX && y == roomY) || map[y][x].ch == '+') map[y][x].ch = '+';
        else if (map[y][x].ch != '#' || map[y][x].ch != '.' || map[y][x].ch != '+') map[y][x].ch = '#';
      }

      if (isFirst == 1 && axis == 'x') {

        if (map[y][x].ch != '#' && map[y][x].ch != '.' && map[y][x].ch != '+') map[y][x].ch = '#';

      } else if ( axis == 'x' ) {

        if (map[y][x].ch != '.' && map[y][x].ch != '#' && map[y][x].ch != '+') {
          map[y][x].ch = '#';
        }

      } else if ( axis == 'y' ) {

        if (map[y][x].ch != '#' && map[y][x].ch != '+' && map[y][x].ch != '.') {
          map[y][x].ch = '#';
        }
      }
    }
  }
}