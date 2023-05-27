#ifndef __MAPA_H__
#define __MAPA_H__

// Create the 2D matrix
Tile ** matrixSetup(int rows, int cols);

// Print the whole matrix
void printMap(int rows, int cols, Tile ** map, Player * user);

void resetMap(int rows, int cols, Tile ** map, Player * user);

int checkScreenSize(int cols, int rows);

NormalRoom createRoom(int col, int row, Tile ** map);
// This function will create a single room, draw it in the screen and return the created room
// To create a room, the function create() will call createNormalRoom() inside of it

NormalRoom createNormalRoom(int *rows, int *cols);
// This function has the role of creating a normal room (just a standard room)

void drawRoom(NormalRoom room,Tile ** map,int cols, int rows);
// This function will write in the window the given room at the given position, with it's door in a random position

Tile ** createMap(WINDOW * wnd, int maxRooms, int firstPosition, int cols, int rows, Player * user);

int createErosion(Tile ** map, int cols, int rows);

#endif