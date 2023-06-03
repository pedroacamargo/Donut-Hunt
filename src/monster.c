#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>


void spawnMonster(Tile** map, NormalRoom room, Player* player){
  Monster monster;
  int chance = rand() % 1000;

  if (player->dungeonFloor >= 1 && player->dungeonFloor < 5){
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

  monster.pos.x = (rand() % room.width) + (room.pos.x);
  monster.pos.y = (rand() % room.height) + (room.pos.y);

  map[monster.pos.y][monster.pos.x].monster = monster;

}

Monster createSkeleton(){
  Monster monster;
  monster.color = COLOR_PAIR(5);
  monster.type = 'S';
  monster.life = 50;
  monster.damage = 5;

  return monster;
}

Monster createGoblin(){
  Monster monster;
  monster.color = COLOR_PAIR(12);
  monster.type = 'G';
  monster.life = 75;
  monster.damage = 15;

  return monster;
}

Monster createDragon(){ 
  Monster monster;
  monster.color = COLOR_PAIR(11);
  monster.type = 'D';
  monster.life = 500;
  monster.damage = 35;

  return monster;
}

void moveMonsters(Tile **map, int cols, int rows) {
  for (int y = 0; y < rows; y++) { // estes ciclos percorrem o mapa e verifica se existe um monstro nessa posição. 
    for (int x = 0; x < cols; x++) {
       if (map[y][x].monster.type != '\0'){
        if (mode_combat(map, &(map[y][x].monster)) == 1) { // encontram um monstro
          }
        }
      }
    }
  }







