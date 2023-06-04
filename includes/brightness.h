#ifndef __BRIGHTNESS_H__
#define __BRIGHTNESS_H__

void makeFov (Player* player, int cols, int rows, Tile** map, int * linesActions, bool * sawAVine, bool * sawAMonster, bool * sawAnItem);

int getDistance (Player* player, Position target);

bool InMap(int y, int x, int cols, int rows);

bool lineOfSight (Player* player, Position target, Tile** map);

void clearFov (Player* player, int cols, int rows, Tile** map);

void debugMap(Tile ** map, int cols, int rows);

#endif