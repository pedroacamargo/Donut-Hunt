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
    }

  return map;
}

void resetMap(int rows, int cols, Tile ** map) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      map[i][j].ch = ' ';
      map[i][j].walkable = false;
    }

  printMap(rows,cols,map);

  for (int y = 0; y < rows; y++)
	{
		free(map[y]);
	}
	free(map);
  map = NULL;
}

void printMap(int rows, int cols, Tile ** map){
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      if (map[i][j].visible){
        if(map[i][j].monster == 'G'){
          mvaddch(i, j, 'G' | COLOR_PAIR(5));
        }else if (map[i][j].monster == 'E'){
          mvaddch(i, j, 'E' | COLOR_PAIR(5));
        }else if (map[i][j].monster == 'D'){
          mvaddch(i,j, 'D' | COLOR_PAIR(5));
        } else if (map[i][j].ch == 'v') {
          mvaddch(i,j, 'v' | COLOR_PAIR(3));
        } else {
          mvaddch(i, j, map[i][j].ch | COLOR_PAIR(1));
        }
      } else if (map[i][j].seen){
        mvaddch (i, j, map[i][j].ch | COLOR_PAIR(2));
      } else {
        mvaddch(i,j, ' ');
      }
     // mvaddch(i,j,map[i][j].ch | map[i][j].color);
    }
  }
}


int checkScreenSize(int cols, int rows) {
  /* Debug */
  //mvprintw(0,0,"cols:%d, rows:%d",cols,rows);
  //getch();

  if (cols > 200 && rows > 60) return 14;
  else if ((cols <= 200 && cols > 150) && (rows > 40 && rows <= 60)) return 7;
  else return 4;


  return 0;
}


NormalRoom createRoom(int col, int row, Tile ** map) {

  NormalRoom room = createNormalRoom(&row,&col);
  drawRoom(room,map,col,row);

  return room;
}



NormalRoom createNormalRoom(int *rows, int *cols) {
  NormalRoom newRoom;

  // 1 - Normal room
  // 2 - Vine room
  int randomType = (rand() % 1000); 
  // 90% chance normal / 10% chance vine
  if(randomType < 700) {
    newRoom.width = rand() % 10 + 10;
    newRoom.height = rand() % 6 + 4;
    newRoom.type = 1;
    newRoom.vine = false;
  } else {
    newRoom.width = rand() % 15 + 30;
    newRoom.height = 6;
    newRoom.type = 2;
    newRoom.vine = true;
    newRoom.vinesWidth = (rand() % 5) + 3;
  }

  // position YX axis ( - height for the room doesn't overflow the screen)
  newRoom.pos.y = (rand() % (*rows - (newRoom.height + 3))); 
  newRoom.pos.x = (rand() % (*cols - (newRoom.width + 10)));

  return newRoom;
}


Tile ** createMap(WINDOW * wnd, int maxRooms, int firstPosition,int cols, int rows, Player * user) {
  Tile ** map = matrixSetup(rows,cols);
  NormalRoom firstRoom = createRoom(cols,rows,map);
  drawRoom(firstRoom,map,cols,rows);
  drawDoor(&firstRoom,map);
  user->pos.x = firstRoom.pos.x + (firstRoom.width / 2);
  user->pos.y = firstRoom.pos.y + (firstRoom.height / 2);
  user->color = COLOR_PAIR(1);  
  NormalRoom * rooms = calloc(maxRooms, sizeof(NormalRoom));
  int roomsAmount = 1;
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

    /* DEBUG */
    //debugMap(map,cols,rows);
    //printMap(rows,cols,map);
    //mvprintw(24, 0,"roomsamount: %d",roomsAmount);
    //mvprintw(25, 0,"cols: %d | rows: %d",cols,rows);
    //mvprintw(25,25,"RoomType: %d",firstRoom.type);
    //getch();
  }
  
  int minRooms = checkScreenSize(cols,rows);

  if (roomsAmount < minRooms) {
    resetMap(rows,cols,map);
    if (rooms) free(rooms);
    return createMap(wnd,maxRooms,firstPosition,cols,rows,user);
  } 

  //mvprintw(24, 0,"roomsamount: %d",roomsAmount);
  //getch();

  // This is to connect randomic rooms in the map (just to give some randomization instead of a linear map)
  int random1 = (rand() % (roomsAmount - 1));
  
  /* Debug */
  // debugMap(map,cols,rows);
  // printMap(rows,cols,map);

  drawHallway(&rooms[0],&rooms[random1],map,cols,rows);
  drawHallway(&rooms[3],&rooms[roomsAmount - 1],map,cols,rows);

  //int bossRoom = rand() % roomsAmount;
  drawStairs(&rooms[roomsAmount - 1], map);


  if (rooms) free(rooms);
  return map;
}


int createErosion(Tile ** map, int cols, int rows) {
  int erosion = 0;
  for (int i = 0; i < 20; i++) {
    int randomX = rand() % cols;
    int randomY = rand() % rows;

    if (map[randomY][randomX].ch == '+' || map[randomY][randomX].ch == '.') {
      map[randomY][randomX].ch = '$';
      map[randomY][randomX].walkable = true;
      map[randomY][randomX].transparent = false;
      erosion++;
    }
  }
  return erosion;
}