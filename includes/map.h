#ifndef __MAPA_H__
#define __MAPA_H__

NormalRoom * createRoom(int col, int row);
// This function will create a single room, draw it in the screen and return the created room
// To create a room, the function create() will call createNormalRoom() inside of it

NormalRoom * createNormalRoom(int *rows, int *cols);
// This function has the role of creating a normal room (just a standard room)

void drawRoom(NormalRoom * room);
// This function will write in the window the given room at the given position, with it's door in a random position

// void createMap(NormalRoom * firstRoom, int maxRooms, int firstPosition);

#endif