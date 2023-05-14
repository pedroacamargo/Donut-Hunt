#ifndef __BRIGHTNESS_H__
#define __BRIGHTNESS_H__

#include "structs.h"

void makeFov (Player *user, int cols, int rows, Tile** map, int * linesActions, bool * sawAVine, bool * sawAMonster);


int getDistance (Position origion, Position target);

bool InMap(int y, int x, int cols, int rows);

bool lineOfSight (Position origin, Position target, Tile** map);

void clearFov (Player * user, int cols, int rows, Tile** map);

void debugMap(Tile ** map, int cols, int rows);

#endif