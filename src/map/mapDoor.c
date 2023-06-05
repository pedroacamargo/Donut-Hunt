#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

NormalRoom makeDoor(int first,NormalRoom * room) {
  first--;
  if (first == 0) first = 1;
  // mvprintw(2,4,"Direction:%d  ",first);
  int randomX = rand() % (room->width - 2) + 1; // 1 - width
  int randomY = rand() % (room->height - 1) + 1; // 1 - height
  if (first == 10 || first == 9 || first == 8 || first == 7) {
    // top
    room->door.x = randomX + room->pos.x; // -1 is to forbid spawn doors in the corner
    room->door.y = room->pos.y;
    room->doorAxis = 'x';
  } else if (first == 12 || first == 11) {
    // right
    room->door.x = room->pos.x + room->width;
    room->door.y = randomY + room->pos.y;
    room->doorAxis = 'y';
  } else if (first == 1 || first == 2 || first == 3 || first == 4) {
    // bottom
    room->door.x = randomX + room->pos.x;
    room->door.y = room->pos.y + room->height;
    room->doorAxis = 'x';
  } else {
    // left
    room->door.x = room->pos.x;
    room->door.y = randomY + room->pos.y;
    room->doorAxis = 'y';
  }
  return *room;
}



void drawDoor(NormalRoom * room, Tile ** map) {
  map[room->door.y][room->door.x].ch = '+';
  map[room->door.y][room->door.x].walkable = true;
  map[room->door.y][room->door.x].transparent = true;
}