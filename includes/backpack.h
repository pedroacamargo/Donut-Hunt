#ifndef __BACKPACK_H__
#define __BACKPACK_H__

void openBackpack(int cols, int rows, Tile ** map, Player * user);

void buildSlot(int height, int width, int y, int x, WINDOW * popUp, int color);

void selectSlotBackpack(char ch, int * currentSlot, WINDOW * popUp, Player * user, int cols);

void updateItemStatsBackpack(Player * user, int * currentSlot, WINDOW * popUp);

void updateBackpackSlots(Player * user, WINDOW * popUp);

void printItem(Item * item, WINDOW * popUp);

void printArt(Item * item, WINDOW * popUp);

void cleanMenuBackpack(WINDOW * popUp);

void equipItem(int cols, Item * item, Player * user, int currentSlot);

#endif