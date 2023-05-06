#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

NormalRoom randomizePosition(WINDOW * wnd,NormalRoom * room, int col, int row, int first, int iterations, Tile ** map) {

  // Variables
  int top = 10, right = 12, bottom = 3, left = 6; // doors positioning
  int x = 0, y = 0; // room positioning
  int distanceX = 13; // gap X axis
  int distance = 5; // gap Y axis

  // If the randomization ran over all the square, stop the function and return the same room
  if (iterations == 12) return *room;
  mvprintw(20,0,"iterations: %d",iterations);
  iterations++;

  // Create a random room
  NormalRoom newRoom = createNormalRoom(&col,&row);
  // Get its position in the screen to facilitate the readability
  Position p = room->pos;
  // mvprintw(0,30,"newRoom -> x:%d | y: %d", p.x, p.y);

  /*
      1   2   3   4
  
      12          5

      11          6

      10  9   8   7
  */
  // Set the room's position
  switch (first) {
    case 1:
      x = p.x - newRoom.width - distanceX;
      y = p.y - newRoom.height - distance;
      makeDoor(top,room);
      first++;
      break;
    case 2:
      x = p.x - (newRoom.width / 4);
      y = p.y - newRoom.height - distance;
      makeDoor(top,room);
      first++;
      break;
    case 3:
      x = p.x + (newRoom.width + (distanceX/2));
      y = p.y - newRoom.height - distance;
      makeDoor(top,room);
      first++;
      break;
    case 4:
      x = p.x + (newRoom.width + distanceX);
      y = p.y - (newRoom.height + distance);
      makeDoor(top,room);
      first++;
      break;
    case 5:
      x = p.x + (newRoom.width + distanceX);
      y = p.y - (newRoom.height / 2);
      makeDoor(right,room);
      first++;
      break;
    case 6:
      x = p.x + (newRoom.width + distanceX);
      y = p.y + (newRoom.height / 2);
      makeDoor(right,room);
      first++;
      break;
    case 7:
      x = p.x + (newRoom.width + distanceX);
      y = p.y + (newRoom.height + distance);
      makeDoor(bottom,room);
      first++;
      break;
    case 8:
      x = p.x + (newRoom.width * 3/4);
      y = p.y + newRoom.height + distance;
      makeDoor(bottom,room);
      first++;
      break;
    case 9:
      x = p.x - newRoom.width;
      y = p.y + newRoom.height + distance;
      makeDoor(bottom,room);
      first++;
      break;
    case 10:
      x = p.x - newRoom.width - distanceX;
      y = p.y + newRoom.height + 2 + distance;
      makeDoor(left,room);
      first++;
      break;
    case 11:
      x = p.x - newRoom.width - distanceX;
      y = p.y + (newRoom.height / 2) + 5;
      makeDoor(left,room);
      first++;
      break;
    case 12:
      x = p.x - newRoom.width - distanceX;
      y = p.y;
      makeDoor(left,room);
      break;
  }
  
  // check if something is overwritten
  getch();
  int has = checkPos(room,y,x,row,col,map);
  mvprintw(21,0,"has: %d",has);
  mvprintw(22,0,"direction: %d",first);
  mvprintw(23,0,"y: %d x:%d",y,x);
  getch();


  if (has == 1) {
    if (first == 12) first = 1;
    return randomizePosition(wnd,room,col,row,first,iterations,map); // recursion
  } else {
    newRoom.pos.x = x;
    newRoom.pos.y = y;
    if (newRoom.pos.x == room->pos.x && newRoom.pos.y == room->pos.y) return *room;
    newRoom = makeDoor(first, &newRoom);
    drawDoor(room,map);
    drawHallway(&newRoom,room,map,col,row);
    return newRoom;
  }
}

int checkPos(NormalRoom * room,int y, int x, int cols, int rows, Tile ** map) {
  int areaXstart = x - 3;
  int areaYstart = y - 3;
  int areaXend = x + room->width + 3;
  int areaYend = y + room->height + 3;

  for (int x = areaXstart;x < areaXend; x++) {
    for (int y = areaYstart; y < areaYend; y++) {
      if (y >= cols - room->height -2 || y <= 0 || x >= rows - room->width - 2 || x <= 0 || map[y][x].ch == '.' || map[y][x].ch == '#'|| map[y][x].ch == '+') return 1;
    }
  }

  return 0;
}