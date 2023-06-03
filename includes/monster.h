#ifndef __MONSTER_H__
#define __MONSTER_H_

void spawnMonster (Tile ** map, NormalRoom room, Player* player);

int manhattanDistance (Monster* monster, Player* player);

void moveMonsters(Tile **map, Player* player, int cols, int rows);

Monster createSkeleton();

Monster createGoblin();

Monster createDragon();
#endif