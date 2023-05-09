#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void buildWalls(NormalRoom * room, char axis, int isFirst, int axisSwap, Tile ** map) {
  // ### 
  // #+#
  // ###
  int roomX = room->door.x;
  int roomY = room->door.y;
  for (int x = roomX - 1; x <= roomX + 1; x++) {
    for (int y = roomY - 1; y <= roomY + 1; y++) {

      if (axisSwap == 1) {
        if (map[y][x].ch == '.') continue;
        else if (map[y][x].ch == '+') continue;

        if ((x == roomX && y == roomY) || map[y][x].ch == '+') {
          map[y][x].ch = '+';
          map[y][x].walkable = true;
          map[y][x].transparent = true;
        }
        else if (map[y][x].ch != '#' || map[y][x].ch != '.' || map[y][x].ch != '+') {
          map[y][x].ch = '#';
          map[y][x].walkable = false;
          map[y][x].color = COLOR_PAIR(1);
          map[y][x].seen = false;
          map[y][x].transparent = false;
          map[y][x].visible = false;
        } 
      }

      if (isFirst == 1 && axis == 'x') {

        if (map[y][x].ch != '#' && map[y][x].ch != '.' && map[y][x].ch != '+' && map[y][x].ch != '$') 
        {
          map[y][x].ch = '#';
          map[y][x].walkable = false;
          map[y][x].color = COLOR_PAIR(1);
          map[y][x].seen = false;
          map[y][x].transparent = false;
          map[y][x].visible = false;
        }

      } else if ( axis == 'x' ) {
        if (map[y][x].ch == '.') continue;
        else if (map[y][x].ch == '+') continue;
        else if (map[y][x].ch != '.' && map[y][x].ch != '#' && map[y][x].ch != '+' && map[y][x].ch != '$') {
          map[y][x].ch = '#';
          map[y][x].walkable = false;
          map[y][x].color = COLOR_PAIR(1);
          map[y][x].seen = false;
          map[y][x].transparent = false;
          map[y][x].visible = false;
        }



      } else if ( axis == 'y' ) {

        if (map[y][x].ch == '.') continue;
        else if (map[y][x].ch == '+') continue;
        else if (map[y][x].ch != '.' && map[y][x].ch != '#' && map[y][x].ch != '+' && map[y][x].ch != '$') {
          map[y][x].ch = '#';
          map[y][x].walkable = false;
          map[y][x].color = COLOR_PAIR(1);
          map[y][x].seen = false;
          map[y][x].transparent = false;
          map[y][x].visible = false;
        }

      }
    }
  }
}