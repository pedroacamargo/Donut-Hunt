#ifndef __COMBAT_H__
#define __COMBAT_H__

int mode_combat(Tile** map, Monster* monster);

void removeMonster(Tile** map, Monster* monster);

void combat(Tile** map, Player* player, Monster* monster);

#endif