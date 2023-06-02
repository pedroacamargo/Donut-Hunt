#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>
/*
void spawnMonster(Tile **map, int cols, int rows) {
    int x, y;
    do {
        x = rand() % cols;
        y = rand() % rows;
    } while (!map[y][x].walkable);
    map[y][x].monster = 'F';
    map[y][x].walkable = false;

     do {
        x = rand() % cols;
        y = rand() % rows;
    } while (!map[y][x].walkable);
    map[y][x].monster = 'G';
    map[y][x].walkable = false;

    do{
      x = rand() % cols;
      y = rand() % rows;
    } while(!map[y][x].walkable);
    map[y][x].monster = 'D';
    map[y][x].walkable = false;
}
*/

void spawnMonster(Tile** map, NormalRoom room, Player* player){
  Monster monster;
  int chance = rand() % 1000;


  if (chance < 700){ // 70% nascer esqueletos
    monster.color = COLOR_PAIR(5);
    monster.type = 'S';
    monster.life = 50;
    monster.damage = 5;
  }else if (chance >= 700 && chance < 950){ // 25%  nascer goblins
    monster.color = COLOR_PAIR(12);
    monster.type = 'G';
    monster.life = 75;
    monster.damage = 15;
  } else { // 5% nascer dragons
    monster.color = COLOR_PAIR(11);
    monster.type = 'D';
    monster.life = 500;
    monster.damage = 35;
  }

    monster.pos.x = (rand() % room.width) + (room.pos.x);
    monster.pos.y = (rand() % room.height) + (room.pos.y);

  map[monster.pos.y][monster.pos.x].monster = monster;
}


void moveMonsters(Tile **map, int cols, int rows) {
  for (int y = 0; y < rows; y++) { // estes ciclos percorrem o mapa e verifica se existe um monstro nessa posição. 
    for (int x = 0; x < cols; x++) {
      if (map[y][x].monster.type != '\0') { // encontram um monstro
        int newX, newY;
        do {
          // colocam uma nova posição para o monstro
          newX = x + rand() % 3 - 1;
          newY = y + rand() % 3 - 1;
        } while (newX < 0 || newY < 0 || newX >= cols || newY >= rows || !map[newY][newX].walkable); // isto é para verificar se é possivel ir para a nova posição
        // move o monstro para a nova posição
        map[newY][newX].monster = map[y][x].monster;
        map[y][x].monster.type = '\0'; // posição anterior é liberada e é colocado o char correspondente
        map[newY][newX].walkable = false;  // coloca o monstro parado nessa ronda 
        map[y][x].walkable = true; // e coloca o char anterior onde estava o monstro caminhavel 
      }
    }
  }
}







