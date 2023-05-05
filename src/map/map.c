#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

Tile ** matrixSetup(int rows, int cols) {
  Tile **map = (Tile **) calloc(rows, sizeof(Tile *));
  for(int R = 0; R < rows; R++)
    map[R] = (Tile *) calloc(cols, sizeof(Tile));
  

  return map;
}



NormalRoom * createRoom(int col, int row, Tile ** map) {

  NormalRoom * room = createNormalRoom(&col,&row);
  drawRoom(room,map);

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

void drawRoom(NormalRoom * room, Tile ** map) {
  // draw top and bottom
  for (int x = room->pos.x + 1; x < room->pos.x + room->width; x++) {
    if (map[room->pos.y][x].ch == '.') {
      map[room->pos.y][x].ch = '.'; // overwrite rooms
      map[room->pos.y][x].walkable = true;
    } else if(map[room->pos.y][x].ch == '+') {
      map[room->pos.y][x].ch = '+';
      map[room->pos.y][x].walkable = true;
    } else {
      map[room->pos.y][x].ch = '#';
      map[room->pos.y][x].walkable = false;
    }


    if (map[room->pos.y + room->height][x].ch == '.') {
      map[room->pos.y + room->height][x].ch = '.'; // overwrite rooms
      map[room->pos.y + room->height][x].walkable = true;
    } else if(map[room->pos.y + room->height][x].ch == '+') {
      map[room->pos.y + room->height][x].ch = '+';
      map[room->pos.y + room->height][x].walkable = true;
    } else {
      map[room->pos.y + room->height][x].ch = '#';
      map[room->pos.y + room->height][x].walkable = false;
    }
  }

  // draw side walls / floor
  for (int y = room->pos.y; y <= room->pos.y + room->height; y++) {
    // draw side walls
    if (map[y][room->pos.x].ch == '.') {
      map[y][room->pos.x].ch = '.'; // overwrite rooms
      map[y][room->pos.x].walkable = true;
    } else if(map[y][room->pos.x].ch != '+') {
      map[y][room->pos.x].ch = '#';
      map[y][room->pos.x].walkable = false;
    } else {
      map[y][room->pos.x].ch = '+';
      map[y][room->pos.x].walkable = true;
    }

    if (map[y][room->pos.x + room->width].ch == '.') {
      map[y][room->pos.x + room->width].ch = '.'; // overwrite rooms
      map[y][room->pos.x + room->width].walkable = true;
    } else if(map[y][room->pos.x + room->width].ch != '+') {
      map[y][room->pos.x + room->width].ch = '#';
      map[y][room->pos.x + room->width].walkable = false;
    } else {
      map[y][room->pos.x + room->width].ch = '+';
      map[y][room->pos.x + room->width].walkable = true;
    }

    // draw floors
    for (int x = room->pos.x + 1; x < room->pos.x + room->width; x++) {
      if (y >= room->pos.y + room->height - 1) break; 
      map[y+1][x].ch = '.';
      map[y+1][x].walkable = true;
    }    
  }
}


void createMap(WINDOW * wnd,NormalRoom * firstRoom,NormalRoom * arrayRooms[], int maxRooms, int firstPosition,int cols, int rows,Tile ** map) {
  int rooms = 0;
  while (rooms <= maxRooms) {
    rooms++;
    arrayRooms[rooms] = randomizePosition(wnd,firstRoom,cols,rows,firstPosition,0,map);
    firstRoom = arrayRooms[rooms];
    if (!(mvinch(firstRoom->pos.y,firstRoom->pos.x) == '#' || mvinch(firstRoom->pos.y,firstRoom->pos.x) == '.')) {
        drawRoom(arrayRooms[rooms],map);
        drawDoor(arrayRooms[rooms]);
    }
  }

  // This is to connect randomic rooms in the map (just to give some randomization instead of a linear map)
  int random1 = (rand() % (rooms - 5)) + 5;
  drawHallway(arrayRooms[0],arrayRooms[random1],map);
  drawHallway(arrayRooms[2],arrayRooms[random1],map);
  
}
