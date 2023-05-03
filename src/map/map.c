#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

NormalRoom * createRoom(int col, int row) {

  NormalRoom * room = createNormalRoom(&col,&row);
  drawRoom(room);

  return room;
}

NormalRoom * createNormalRoom(int *rows, int *cols) {
  NormalRoom * newRoom;
  newRoom = malloc(sizeof(NormalRoom) + sizeof('x')); // the x is to fix a bug with the core dump error

  // Room width/height randomization (width 10 - 20/ height 4 - 14)
  newRoom->width = rand() % 10 + 10;
  newRoom->height = rand() % 6 + 4;

  // position YX axis ( - height for the room doesn't overflow the screen)
  newRoom->pos.y = (rand() % (*rows - newRoom->height) + 1); 
  newRoom->pos.x = (rand() % (*cols - newRoom->width) + 1);
  // newRoom->pos.x = 220;
  // newRoom->pos.y = 0;
  // newRoom->pos.y = *rows - newRoom->height - 1;

  return newRoom;
}

void drawRoom(NormalRoom * room) {
  // draw top and bottom
  for (int x = room->pos.x + 1; x < room->pos.x + room->width; x++) {
    if (mvinch(room->pos.y,x) == '.') {
      mvprintw(room->pos.y,x,"."); // overwrite rooms
    } else if(mvinch(room->pos.y,x) == '+') {
      mvprintw(room->pos.y,x,"+");
    } else {
      mvprintw(room->pos.y,x, "#");
    }
     
    if (mvinch(room->pos.y + room->height,x) == '.') {
      mvprintw(room->pos.y + room->height,x,"."); // overwrite rooms
    } else if(mvinch(room->pos.y + room->height,x) == '+') {
      mvprintw(room->pos.y + room->height,x,"+");
    } else {
      mvprintw(room->pos.y + room->height, x, "#");
    }
  }

  // draw side walls / floor
  for (int y = room->pos.y; y <= room->pos.y + room->height; y++) {
    // draw side walls
    if (mvinch(y,room->pos.x) == '.') {
      mvprintw(y,room->pos.x,"."); // overwrite rooms
    } else if(mvinch(y,room->pos.x) != '+') {
      mvprintw(y,room->pos.x,"#");
    } else {
      mvprintw(y,room->pos.x,"+");
    }

    if (mvinch(y,room->pos.x + room->width) == '.') {
      mvprintw(y,room->pos.x + room->width, ".");
    } else if(mvinch(y,room->pos.x + room->width) == '+') {
      mvaddch(y,room->pos.x + room->width,'+');
    } else if(mvinch(y,room->pos.x + room->width) == ' '){
      mvprintw(y,room->pos.x + room->width, "#");
    }

    // draw floors
    for (int x = room->pos.x + 1; x < room->pos.x + room->width; x++) {
      if (y >= room->pos.y + room->height - 1) break; 
      mvprintw(y + 1,x,".");
    }    
  }
}


void createMap(WINDOW * wnd,NormalRoom * firstRoom,NormalRoom * arrayRooms[], int maxRooms, int firstPosition,int cols, int rows) {
  int rooms = 0;
  while (rooms <= maxRooms) {
    rooms++;
    arrayRooms[rooms] = randomizePosition(wnd,firstRoom,cols,rows,firstPosition,0);
    firstRoom = arrayRooms[rooms];
    if (!(mvinch(firstRoom->pos.y,firstRoom->pos.x) == '#' || mvinch(firstRoom->pos.y,firstRoom->pos.x) == '.')) {
        drawRoom(arrayRooms[rooms]);
        drawDoor(arrayRooms[rooms]);
    }
  }
}
