#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "main.h"

Tile ** matrixSetup(int rows, int cols) {
  Tile **map = (Tile **) calloc(rows, sizeof(Tile *));
  for(int R = 0; R < rows; R++)
    map[R] = (Tile *) calloc(cols, sizeof(Tile));

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      map[i][j].ch = ' ';
      map[i][j].walkable = false;
    }

  return map;
}

void printMap(int rows, int cols, Tile ** map){
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      mvaddch(i,j,map[i][j].ch);
}


NormalRoom createRoom(int col, int row, Tile ** map) {

  NormalRoom room = createNormalRoom(&row,&col);
  drawRoom(room,map,col,row);

  return room;
}



NormalRoom createNormalRoom(int *rows, int *cols) {
  // NormalRoom * newRoom;
  // newRoom = malloc(sizeof(NormalRoom) + sizeof('x')); // the x is to fix a bug with the core dump error

  NormalRoom newRoom;

  // Room width/height randomization (width 10 - 20/ height 6 - 16)
  newRoom.width = rand() % 10 + 10;
  newRoom.height = rand() % 6 + 4;

  // position YX axis ( - height for the room doesn't overflow the screen)
  newRoom.pos.y = (rand() % (*rows - newRoom.height) + 1); 
  newRoom.pos.x = (rand() % (*cols - newRoom.width) + 1);
  // newRoom->pos.x = 220;
  // newRoom->pos.y = 0;
  // newRoom->pos.y = *rows - newRoom->height - 1;

  return newRoom;
}


void drawRoom(NormalRoom room, Tile ** map, int cols, int rows) {

  // draw top and bottom
  for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
    if (x > cols || room.pos.y > rows) break;
    if (map[room.pos.y][x].ch == '.') {
      map[room.pos.y][x].ch = '.'; // overwrite rooms
      map[room.pos.y][x].walkable = true;
    } else if(map[room.pos.y][x].ch == '+') {
      map[room.pos.y][x].ch = '+';
      map[room.pos.y][x].walkable = true;
    } else {
      map[room.pos.y][x].ch = '#';
      map[room.pos.y][x].walkable = false;
    }


    if (map[room.pos.y + room.height][x].ch == '.') {
      map[room.pos.y + room.height][x].ch = '.'; // overwrite rooms
      map[room.pos.y + room.height][x].walkable = true;
    } else if(map[room.pos.y + room.height][x].ch == '+') {
      map[room.pos.y + room.height][x].ch = '+';
      map[room.pos.y + room.height][x].walkable = true;
    } else {
      map[room.pos.y + room.height][x].ch = '#';
      map[room.pos.y + room.height][x].walkable = false;
    }
  }

  // draw side walls / floor
  for (int y = room.pos.y; y <= room.pos.y + room.height; y++) {
    if (y > rows || room.pos.x > cols) break;
    // draw side walls
    if (map[y][room.pos.x].ch == '.') {
      map[y][room.pos.x].ch = '.'; // overwrite rooms
      map[y][room.pos.x].walkable = true;
    } else if(map[y][room.pos.x].ch != '+') {
      map[y][room.pos.x].ch = '#';
      map[y][room.pos.x].walkable = false;
    } else {
      map[y][room.pos.x].ch = '+';
      map[y][room.pos.x].walkable = true;
    }

    if (map[y][room.pos.x + room.width].ch == '.') {
      map[y][room.pos.x + room.width].ch = '.'; // overwrite rooms
      map[y][room.pos.x + room.width].walkable = true;
    } else if(map[y][room.pos.x + room.width].ch == '+') {
      map[y][room.pos.x + room.width].ch = '+';
      map[y][room.pos.x + room.width].walkable = false;
    } else {
      map[y][room.pos.x + room.width].ch = '#';
      map[y][room.pos.x + room.width].walkable = true;
    }

    // draw floors
    for (int x = room.pos.x + 1; x < room.pos.x + room.width; x++) {
      if (y > rows || x > cols) break;
      if (y >= room.pos.y + room.height - 1) break; 
      map[y+1][x].ch = '.';
      map[y+1][x].walkable = true;
    }    
  }
}


void createMap(WINDOW * wnd,NormalRoom firstRoom, int maxRooms, int firstPosition,int cols, int rows,Tile ** map) {
  NormalRoom * rooms = calloc(maxRooms, sizeof(NormalRoom));
  int roomsAmount = 0;
  for (int i = 0; i < maxRooms; i++) {
	  firstPosition = rand() % 12 + 1; // first testing position for the room creation
    printMap(rows,cols,map);
    rooms[i] = randomizePosition(wnd,&firstRoom,cols,rows,firstPosition,0,map);

    // if the rooms are the same, end the map generation
    if (rooms[i].pos.x == rooms[i-1].pos.x && rooms[i].pos.y == rooms[i-1].pos.y) {
      roomsAmount--;
      break;
    }

    firstRoom = rooms[i];

    if (!(map[firstRoom.pos.y][firstRoom.pos.x].ch == '#' || map[firstRoom.pos.y][firstRoom.pos.x].ch == '.')) {
        drawRoom(rooms[i],map,cols,rows);
        drawDoor(&rooms[i],map);
    }
    roomsAmount++;
  }


  //This is to connect randomic rooms in the map (just to give some randomization instead of a linear map)
  int random1 = (rand() % (roomsAmount - 5)) + 5;
  drawHallway(&rooms[0],&rooms[random1],map,cols,rows);
  drawHallway(&rooms[2],&rooms[random1],map,cols,rows);

  free(rooms);

}
