#ifndef __MAPA_H__
#define __MAPA_H__

#include "player.h"

int createMap(int *cols, int *rows, Player * user);
void createMainRoom(int randomNumberY, int randomNumberX, int height, int width);

#endif