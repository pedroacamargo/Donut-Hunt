#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void drawRoom(NormalRoom room, Tile ** map, int cols, int rows) {
  // draw top and bottom
  for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
    if (x > cols - 2 || room.pos.y > rows - 2 || x < 0 || room.pos.y < 0) continue;

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
    if (y > rows - 2 || room.pos.x > cols - 2) continue;
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
        if (x == cols) {
          map[y][x].ch = '#';
          map[y][x].color = COLOR_PAIR(1);
          map[y][x].walkable = false;
          map[y][x].seen = false;
          map[y][x].transparent = false;
          map[y][x].visible = false;
          break;
        }
        if (y > rows || x < 0 || room.pos.y < 0 || x > cols) break;
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
              if (room.vineCenter.x + room.vinesWidth >= cols) break;

              if (map[a+i][b+j].ch == '#') break;
              //if ( == '#') break;

              if (j == room.vinesWidth) {
                if (map[a + i][b + j + 6].ch != ' ' && map[a + i][b + j + 6].ch != '#' && (y < rows || x < cols)) {
                  map[a + i][b + j + 6].ch = vine;
                  map[a + i][b + j + 6].walkable = true;
                  map[a + i][b + j + 6].transparent = false;
                } else if ((y < rows || x < cols) && map[a + i][b + j + 3].ch != '#' && map[a + i][b + j + 3].ch != ' ') {
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

void drawStairs(NormalRoom * room, Tile ** map) {
  //int maxIterations = (room->height * room->width) - (2 * room->width) - (2 * room->height);
  //int randomPos = rand() % maxIterations;  
  //int iterations = 0;

  attron(COLOR_PAIR(3));
  map[room->pos.y + room->height/2][room->pos.x + room->width/2].ch = 'v';
  map[room->pos.y + room->height/2][room->pos.x + room->width/2].color = COLOR_PAIR(3);
  attroff(COLOR_PAIR(3));

  /*
  for (int i = room->pos.y; i < room->pos.y + room->width; i++) {
    for (int j = room->pos.x; j < room->pos.x + room->height; j++) {

      if (map[i][j].ch != '#') iterations++;
      
      if (iterations == randomPos) {
        map[i][j].ch = 'v';
        map[i][j].color = COLOR_PAIR(4);

      }
    }
  }
  */
}