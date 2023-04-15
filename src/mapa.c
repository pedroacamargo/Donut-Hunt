#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

void createMap(int *cols, int *rows, Player * user) {
  printw("cols:%d rows:%d",*cols, *rows); 
  srand(time(NULL)); // create a random number based in local time

  int normal_rooms_amount = rand() % 10 + 4; // 4 - 10 normal rooms in the map
  // int normal_rooms_amount = 1;

  NormalRoom * normalRooms[normal_rooms_amount]; // array of normal rooms

  // for loop to create the normal rooms
  for (int i = 0; i < normal_rooms_amount; i++) {
    normalRooms[i] = createNormalRoom(rows, cols);
  }

  // for loop to draw the rooms at CLI
  for (int i = 0; i < normal_rooms_amount; i++) {
    NormalRoom * actualRoom = normalRooms[i];
    drawRoom(actualRoom);
  }

  user->pos.y = normalRooms[0]->pos.y + (normalRooms[0]->height/2);
  user->pos.x = normalRooms[0]->pos.x + (normalRooms[0]->width/2);
  updatePlayerPosition(user);

}




NormalRoom * createNormalRoom(int *rows, int *cols) {
  NormalRoom * newRoom;
  newRoom = malloc(sizeof(NormalRoom));

  // Room width/height randomization (width 10 - 20/ height 4 - 14)
  newRoom->width = rand() % 10 + 10;
  newRoom->height = rand() % 10 + 4;

  // position YX axis ( - height for the room doesn't overflow the screen)
  newRoom->pos.y = (rand() % (*rows - newRoom->height) + 1); 
  newRoom->pos.x = (rand() % (*cols - newRoom->width) + 1);

  return newRoom;
}





void drawRoom(NormalRoom * room) {
  // draw top and bottom
  for (int x = room->pos.x; x < room->pos.x + room->width; x++) {
    mvprintw(room->pos.y, x, "-");
    mvprintw(room->pos.y + room->height, x, "-");
  }

  // draw side walls / floor
  for (int y = room->pos.y + 1; y < room->pos.y + room->height; y++) {
    // draw side walls
    mvprintw(y,room->pos.x,"|");
    mvprintw(y,room->pos.x + room->width - 1, "|");

    // draw floors
    for (int x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++) {
      mvprintw(y,x,".");
    }    
  }

}