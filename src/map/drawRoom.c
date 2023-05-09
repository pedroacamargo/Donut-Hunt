#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void drawRoom(NormalRoom room, Tile ** map, int cols, int rows) {


  // draw top and bottom
  for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
    if (x > cols || room.pos.y > rows || x < 0 || room.pos.y < 0) break;

    // TOP
    if (map[room.pos.y][x].ch == '.') {
      map[room.pos.y][x].ch = '.'; // overwrite rooms
      map[room.pos.y][x].walkable = true;
      map[room.pos.y][x].transparent = true;
    } else if(map[room.pos.y][x].ch == '+') {
      map[room.pos.y][x].ch = '+';
      map[room.pos.y][x].walkable = true;
      map[room.pos.y][x].transparent = true;
    } else {
      map[room.pos.y][x].ch = '#';
      map[room.pos.y][x].color = COLOR_PAIR(1);
      map[room.pos.y][x].walkable = false;
      map[room.pos.y][x].seen = false;
      map[room.pos.y][x].transparent = false;
      map[room.pos.y][x].visible = false;
    }

    // BOTTOM
    if (map[room.pos.y + room.height][x].ch == '.') {
      map[room.pos.y + room.height][x].ch = '.'; // overwrite rooms
      map[room.pos.y + room.height][x].walkable = true;
      map[room.pos.y + room.height][x].transparent = true;
    } else if(map[room.pos.y + room.height][x].ch == '+') {
      map[room.pos.y + room.height][x].ch = '+';
      map[room.pos.y + room.height][x].walkable = true;
      map[room.pos.y + room.height][x].transparent = true;
    } else {
      map[room.pos.y + room.height][x].ch = '#';
      map[room.pos.y + room.height][x].color = COLOR_PAIR(1);
      map[room.pos.y + room.height][x].walkable = false;
      map[room.pos.y + room.height][x].seen = false;
      map[room.pos.y + room.height][x].transparent = false;
      map[room.pos.y + room.height][x].visible = false;
    }
  }

  // draw side walls / floor
  for (int y = room.pos.y; y <= room.pos.y + room.height; y++) {
    if (y > rows || room.pos.x > cols) break;
    // draw side walls
    // LEFT
    if (map[y][room.pos.x].ch == '.') {
      map[y][room.pos.x].ch = '.'; // overwrite rooms
      map[y][room.pos.x].walkable = true;
      map[y][room.pos.x].transparent = true;
    } else if(map[y][room.pos.x].ch != '+') {
      map[y][room.pos.x].ch = '#';
      map[y][room.pos.x].color = COLOR_PAIR(1);
      map[y][room.pos.x].walkable = false;
      map[y][room.pos.x].seen = false;
      map[y][room.pos.x].transparent = false;
      map[y][room.pos.x].visible = false;
    } else {
      map[y][room.pos.x].ch = '+';
      map[y][room.pos.x].walkable = true;
      map[y][room.pos.x].transparent = true;
    }

    // RIGHT
    if (map[y][room.pos.x + room.width].ch == '.') {
      map[y][room.pos.x + room.width].ch = '.'; // overwrite rooms
      map[y][room.pos.x + room.width].walkable = true;
      map[y][room.pos.x + room.width].transparent = true;
    } else if(map[y][room.pos.x + room.width].ch == '+') {
      map[y][room.pos.x + room.width].ch = '+';
      map[y][room.pos.x + room.width].walkable = true;
      map[y][room.pos.x + room.width].transparent = true;
    } else {
      map[y][room.pos.x + room.width].ch = '#';
      map[y][room.pos.x + room.width].color = COLOR_PAIR(1);
      map[y][room.pos.x + room.width].walkable = false;
      map[y][room.pos.x + room.width].seen = false;
      map[y][room.pos.x + room.width].transparent = false;
      map[y][room.pos.x + room.width].visible = false;
    }

    // FLOOR

    // Normal Room
    if (room.type == 1) {
      for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
        if (y > rows || x > cols) break;
        if (y >= room.pos.y + room.height - 1) break; 
        map[y+1][x].ch = '.';;
        map[y+1][x].walkable = true;
        map[y+1][x].transparent = true;

      }    
    } else {
      // Vine room

      char vine = '$';

      y++;
      for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
        if (x >= cols) {
          map[y][room.pos.x + room.width].ch = '#';
          map[y][room.pos.x + room.width].color = COLOR_PAIR(1);
          map[y][room.pos.x + room.width].walkable = false;
          map[y][room.pos.x + room.width].seen = false;
          map[y][room.pos.x + room.width].transparent = false;
          map[y][room.pos.x + room.width].visible = false;
          break;
        }
        if (room.pos.y > rows || x < 0 || room.pos.y < 0) break;
        if (y > rows || x > cols) break;
        if (y >= room.pos.y + room.height) break;
        if (x == room.vineCenter.x && y == room.vineCenter.y) {
          map[y][x].ch = vine;
          map[y][x].walkable = true;
          map[y][x].transparent = false;
        
          int a = room.vineCenter.y - 2;
          int b = room.vineCenter.x - (room.vinesWidth/2);
          // vine room height in floor = 5
          for (int i = 0; i < 5; i++) {
            for (int j = 0; j <= room.vinesWidth; j++) {
              if (map[a+i][b+j].ch == '#') break;

              if (j == room.vinesWidth) {
                if (map[a + i][b + j + 6].ch != ' ') {
                  map[a + i][b + j + 6].ch = vine;
                  map[a + i][b + j + 6].walkable = true;
                  map[a + i][b + j + 6].transparent = false;
                } else {
                  map[a + i][b + j + 3].ch = vine;
                  map[a + i][b + j + 3].walkable = true;
                  map[a + i][b + j + 3].transparent = false;
                  
                }
              }
              map[a + i][b + j].ch = vine;
              map[a + i][b + j].walkable = true;
              map[a + i][b + j].transparent = false;
              
              /* Debug for vines appearance */
              //getch();
              //printMap(rows,cols,map);


              /* NOTES */
              // Criar um spawn de monstros dentro das vinhas, além de ter também um item raro dentro das vinhas
            }
          }






        } else if (map[y][x].ch != '$'){
          map[y][x].ch = '.';
          map[y][x].walkable = true;
          map[y][x].transparent = true;
        }

      }
      y--;
    }
  }
}