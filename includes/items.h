#ifndef __ITEMS_H__
#define __ITEMS_H__

Item * createItem(char ch, char *name, char *buffDescription, char *lore, int rarity, int buff, int level, int ID);

void drawItem(NormalRoom room, Tile ** map, Player * user);

void getItem(Tile ** map, Player * user, int cols);

/*
  *
  *	Floor 1 - 3: 90% chance armor rarity (1 || 2) && 10% chance armor rarity 3
  *	Floor 4 - 8: 90% chance armor rarity (2 || 3) && 10% chance armor rarity 4
  *	Floor 9 - 14: 90% chance armor rarity (3 || 4) && 10% chance armor rarity 5
  * Floor > 14: 100% chance Monix's armor
  * 
*/
int itemsEquilibrium(Player * user);


#endif