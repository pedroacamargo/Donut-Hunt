#ifndef __MAPA_H__
#define __MAPA_H__

void createMap(int *cols, int *rows, Player * user); 
// This function will create the whole map, is the main function which will setup the map
// Furthermore, it will create the random amount of rooms and update the player position in the end of the function


NormalRoom * createNormalRoom(int *rows, int *cols);
// This function has the role of creating a normal room (just a standard room)


void drawRoom(NormalRoom * room);
// This function will write in the window the given room at the given position, with it's door in a random position


#endif