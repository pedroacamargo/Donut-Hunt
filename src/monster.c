#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>


Monster * spawnMonster(Tile** map, NormalRoom room, Player* player) {
  Monster * monster;
  int chance = rand() % 1000;

  if (player->dungeonFloor >= 1 && player->dungeonFloor < 5) {
    if (chance < 950) monster = createSkeleton();  // 80% de nascer esqueletos 20% goblins
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
  monster->color = COLOR_PAIR(13);
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
  monster->damage = 10;

  return monster;
}

Monster * createDragon(){ 
  Monster * monster = malloc(sizeof(Monster));;
  monster->color = COLOR_PAIR(11);
  monster->type = 'D';
  monster->life = 500;
  monster->damage = 50;

  return monster;
}

int manhattanDistance (Monster* monster, Player* player){
    return abs(monster->pos.x - player->pos.x) + abs(monster->pos.y - player->pos.y);
}


void moveMonsters(Tile **map, Player* player, int cols, Monster * monsters, int monstersAmount, int * mem_monster) {
  Monster * monster;

  // Esse ciclo for vai acessar todos os monstros presentes no mapa, que estão dentro do array monsters
  for (int i = 0; i < monstersAmount; i++) {
    monster = &monsters[i]; // pointer para o monstro
    int oldX = monster->pos.x;
    int oldY = monster->pos.y;
    int randomDirection = rand() % 2; // 0 - horizontal | 1 - vertical
    if (mode_combat(map, monster) == 1 || *mem_monster > 0) { // encontram um monstro
      if(mode_combat(map,monster) == 1) *mem_monster = 10;

      int distance = manhattanDistance(monster, player); // USE THE MANHATTAN DISTANCE TO MAKE THE COMBAT MODE (IF DISTANCE <= 2, DEAL DAMAGE TO THE PLAYER)
    
      if (distance <= 2) {
        if (player->armor > 0) {
          player->activeItems->armorSlot->buff -= monster->damage;

          if(player->activeItems->armorSlot->buff < 0) player->activeItems->armorSlot->buff = 0;
          player->armor = player->activeItems->armorSlot->buff;
        } else {
          player->life -= monster->damage;
          if(player->life < 0) player->life = 0;
        }
        updateStats(player,cols);
      }



      // erase the monster tile in the old position
      map[monster->pos.y][monster->pos.x].monster = NULL;

      if (randomDirection == 0) {
        if (monster->pos.x < player->pos.x) {
          if (map[monster->pos.y][monster->pos.x + 1].monster == NULL && (map[monster->pos.y][monster->pos.x + 1].ch == '.' || map[monster->pos.y][monster->pos.x + 1].ch == '+')) {
            // x movimentation
              monster->pos.x++;
          }
        } else if (monster->pos.x > player->pos.x){
          if (map[monster->pos.y][monster->pos.x - 1].monster == NULL && (map[monster->pos.y][monster->pos.x - 1].ch == '.' || map[monster->pos.y][monster->pos.x - 1].ch == '+')) {
            // x movimentation
            monster->pos.x--;
          } 
        } else {
            int randomX = rand() % 2;
            if (randomX == 0 && (map[monster->pos.y][monster->pos.x + 1].monster == NULL && 
            (map[monster->pos.y + 1][monster->pos.x].monster != NULL || map[monster->pos.y - 1][monster->pos.x].monster != NULL)) && 
            (map[monster->pos.y][monster->pos.x + 1].ch == '.' || map[monster->pos.y][monster->pos.x + 1].ch == '+')) monster->pos.x++;


            else if ((map[monster->pos.y][monster->pos.x - 1].monster == NULL && (map[monster->pos.y + 1][monster->pos.x].monster != NULL || map[monster->pos.y - 1][monster->pos.x].monster != NULL)) && (map[monster->pos.y][monster->pos.x - 1].ch == '.' || map[monster->pos.y][monster->pos.x - 1].ch == '+')) monster->pos.x--;
        }

      } else {
        if (monster->pos.y < player->pos.y) {
          if (map[monster->pos.y + 1][monster->pos.x].monster == NULL && (map[monster->pos.y + 1][monster->pos.x].ch == '.' || map[monster->pos.y + 1][monster->pos.x].ch == '+')) {
            // x movimentation
            monster->pos.y++;
          }
        } else if (monster->pos.y > player->pos.y){
          if (map[monster->pos.y - 1][monster->pos.x].monster == NULL && (map[monster->pos.y - 1][monster->pos.x].ch == '.' || map[monster->pos.y - 1][monster->pos.x].ch == '+')) {
            // x movimentation
            monster->pos.y--;
          } 
        } else {
            int randomY = rand() % 2;
            if (randomY == 0 && (map[monster->pos.y + 1][monster->pos.x].monster == NULL && (map[monster->pos.y][monster->pos.x + 1].monster != NULL || map[monster->pos.y][monster->pos.x - 1].monster != NULL)) && (map[monster->pos.y + 1][monster->pos.x].ch == '.' || map[monster->pos.y + 1][monster->pos.x].ch == '+')) monster->pos.y++;


            else if ((map[monster->pos.y - 1][monster->pos.x].monster == NULL && (map[monster->pos.y][monster->pos.x + 1].monster != NULL || map[monster->pos.y][monster->pos.x - 1].monster != NULL)) && (map[monster->pos.y - 1][monster->pos.x].ch == '.' || map[monster->pos.y - 1][monster->pos.x].ch == '+')) monster->pos.y--;
        }
      }

      // If near the player, won't overwrite player and will replace the tile erased before wit the monster
      if (map[monster->pos.y][monster->pos.x].ch == map[player->pos.y][player->pos.x].ch) {
        map[oldY][oldX].monster = monster;
        monster->pos.x = oldX;
        monster->pos.y = oldY;
      } else {
        map[monster->pos.y][monster->pos.x].monster = monster;
      }
    } /* Else if mode_combat(map,monster) == 0 */

    // fazer um else if para quando o monstro está idle
 


  }
  *mem_monster -= 1;
}

// Fixes: Monsters can overwrite others, make a test that if monsters pos == monster2 pos





