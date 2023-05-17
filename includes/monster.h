#ifndef __MONSTER_H__
#define __MONSTER_H__

Monster * monsterSetUp(Tile ** map, int cols, int rows, NormalRoom room);

Monster * spawnMonster (Tile ** map, int cols, int rows, Monster * monster, NormalRoom room);

void moveMonsters(Tile **map, int cols, int rows);

#endif