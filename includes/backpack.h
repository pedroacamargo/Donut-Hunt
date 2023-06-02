#ifndef __BACKPACK_H__
#define __BACKPACK_H__

void openBackpack(int cols, int rows, Tile ** map, Player * user);

void buildSlot(int height, int width, int y, int x, WINDOW * popUp);

void selectSlotBackpack(char ch, int * currentSlot, WINDOW * popUp);

#endif