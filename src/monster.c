#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>


Monster * spawnMonster(Tile** map, NormalRoom room, Player* player) {
  Monster * monster;
  int chance = rand() % 1000;

  if (player->dungeonFloor >= 1 && player->dungeonFloor < 5) {
    if (chance < 800) monster = createSkeleton();  // 80% de nascer esqueletos 20% goblins
    else monster = createGoblin();
  } else if (player->dungeonFloor >= 5 && player->dungeonFloor < 10){
    if (chance < 700) monster = createSkeleton();
    else if(chance >= 700 && chance < 950) monster = createGoblin();
    else monster = createDragon();
  } else if (player->dungeonFloor >= 10 && player->dungeonFloor < 15){
    if (chance < 500) monster = createSkeleton();
    else if (chance >= 500 && chance < 900) monster = createGoblin();
    else monster = createDragon();
  } else {
    if (chance < 300) monster = createSkeleton();
    else if (chance >= 300 && chance < 600) monster = createGoblin();
    else monster = createDragon();
    
  }

  monster->pos.x = ((rand() % room.width) + 1) + (room.pos.x);
  monster->pos.y = ((rand() % room.height) + 1) + (room.pos.y);

  map[monster->pos.y][monster->pos.x].monster = monster;
  return monster;
}

Monster * createSkeleton() {
  Monster * monster = malloc(sizeof(Monster));
  monster->color = COLOR_PAIR(5);
  monster->type = 'S';
  monster->life = 50;
  monster->damage = 5;

  return monster;
}

Monster * createGoblin(){
  Monster * monster = malloc(sizeof(Monster));;
  monster->color = COLOR_PAIR(12);
  monster->type = 'G';
  monster->life = 75;
  monster->damage = 15;

  return monster;
}

Monster * createDragon(){ 
  Monster * monster = malloc(sizeof(Monster));;
  monster->color = COLOR_PAIR(11);
  monster->type = 'D';
  monster->life = 500;
  monster->damage = 35;

  return monster;
}

int manhattanDistance (Monster* monster, Player* player){
    return abs(monster->pos.x - player->pos.x) + abs(monster->pos.y - player->pos.y);
}


void moveMonsters(Tile **map, Player* player, int cols, int rows, Monster * monsters, int monstersAmount) {
  Monster * monster;
  for (int i = 0; i < monstersAmount; i++) {
    monster = &monsters[i];
    int oldX = monster->pos.x;
    int oldY = monster->pos.y;
    if (mode_combat(map, monster) == 1) { // encontram um monstro

      int distance = manhattanDistance(monster, player);

      map[monster->pos.y][monster->pos.x].monster = NULL;

      if (monster->pos.x < player->pos.x){
        monster->pos.x++;
      } else if (monster->pos.x > player->pos.x) monster->pos.x--;


      if (monster->pos.y < player->pos.y){
        monster->pos.y++;
      } else if (monster->pos.y > player->pos.y) monster->pos.y--;

      if (map[monster->pos.y][monster->pos.x].ch == map[player->pos.y][player->pos.x].ch) {
        map[oldY][oldX].monster = monster;
        monster->pos.x = oldX;
        monster->pos.y = oldY;
      } else {
        map[monster->pos.y][monster->pos.x].monster = monster;
      }
    }
  }
}

// Fixes: Monsters can overwrite others, make a test that if monsters pos == monster2 pos





