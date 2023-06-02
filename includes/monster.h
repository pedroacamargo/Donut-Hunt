#ifndef __MONSTER_H__
#define __MONSTER_H_

void spawnMonster (Tile ** map, NormalRoom room, Player* player);

void moveMonsters(Tile **map, int cols, int rows);

Monster createSkeleton();

Monster createGoblin();

Monster createDragon();
#endif