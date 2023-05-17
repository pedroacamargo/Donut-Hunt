#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>

Monster * monsterSetUp(Tile ** map, int cols, int rows, NormalRoom room) {
  Monster * newMonster;
  newMonster = malloc(sizeof(Monster));

  newMonster->life = 100;
  newMonster->armor = 0;
  newMonster->damage = 0;
  newMonster->attack = 1;
  newMonster->defense = 1;

  newMonster = spawnMonster(map,cols,rows,newMonster,room); // vai ser para definir o type e a posicao do monstro na sala

  // newMonster->pos.x = firstRoom->pos.x + (firstRoom->width / 2);
  // newMonster->pos.y = firstRoom->pos.y + (firstRoom->height / 2);

  return newMonster;
}

Monster * spawnMonster(Tile **map, int cols, int rows, Monster *monster, NormalRoom room) {
    // Gera posição aleatória na sala para o monstro
    monster->pos.x = (rand() % room.width) + room.pos.x;
    monster->pos.y = (rand() % room.height) + room.pos.y;

    // Gera tipo aleatório de monstro
    int monsterType = rand() % 3;
    switch (monsterType) {
        case 0:
            monster->type = 'E'; // Esqueleto
            monster->color = COLOR_PAIR(5);
            break;
        case 1:
            monster->type = 'G'; // Goblin
            monster->color = COLOR_PAIR(5);
            break;
        case 2:
            monster->type = 'D'; // Dragão
            monster->color = COLOR_PAIR(5);
            break;
        default:
            break;
    }

    
    return monster;
}
    // posicao aleatoria na sala  -> monster->pos.x e o y
    //monster->type
    // rand() % 3 -> E G D
    // return monster    
    //monster->pos.x = (rand() % room.width)  + room.pos.x

    //while (eCount < 5 || gCount < 5 || dCount < 5) {
    //    do {
    //        x = rand() % cols;
    //        y = rand() % rows;
    //    } while (!map[y][x].walkable);
    //    
    //    // choose a random monster type
    //    char monsterType;
    //    int count;
    //    int randNum;
    //    do {
    //        randNum = rand() % 3;
    //        if (randNum == 0) {
    //            monsterType = 'E';
    //            count = eCount;
    //        } else if (randNum == 1) {
    //            monsterType = 'G';
    //            count = gCount;
    //        } else {
    //            monsterType = 'D';
    //            count = dCount;
    //        }
    //    } while (count >= 5);
    //
    //    // spawn the monster
    //    map[y][x].monster = monsterType;
    //    map[y][x].walkable = false;
    //    
    //    // update the monster count
    //    if (monsterType == 'E') {
    //        eCount++;
    //    } else if (monsterType == 'G') {
    //        gCount++;
    //    } else {
    //        dCount++;
    //    }
    //}



void moveMonsters(Tile **map, int cols, int rows) {
  for (int y = 0; y < rows; y++) { // estes ciclos percorrem o mapa e verifica se existe um monstro nessa posição. 
    for (int x = 0; x < cols; x++) {
      if (map[y][x].monster != '\0') { // encontram um monstro
        int newX, newY;
        do {
          // colocam uma nova posição para o monstro
          newX = x + rand() % 3 - 1;
          newY = y + rand() % 3 - 1;
        } while (newX < 0 || newY < 0 || newX >= cols || newY >= rows || !map[newY][newX].walkable); // isto é para verificar se é possivel ir para a nova posição
        // move o monstro para a nova posição
        map[newY][newX].monster = map[y][x].monster;
        map[y][x].monster = '\0'; // posição anterior é liberada e é colocado o char correspondente
        map[newY][newX].walkable = false;  // coloca o monstro parado nessa ronda 
        map[y][x].walkable = true; // e coloca o char anterior onde estava o monstro caminhavel 
      }
    }
  }
}






