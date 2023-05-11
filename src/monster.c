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
void spawnMonster(Tile **map, int cols, int rows) {
    int eCount = 0, gCount = 0, dCount = 0;
    int x, y;
    while (eCount < 5 || gCount < 5 || dCount < 5) {
        do {
            x = rand() % cols;
            y = rand() % rows;
        } while (!map[y][x].walkable);
        
        // choose a random monster type
        char monsterType;
        int count;
        int randNum;
        do {
            randNum = rand() % 3;
            if (randNum == 0) {
                monsterType = 'E';
                count = eCount;
            } else if (randNum == 1) {
                monsterType = 'G';
                count = gCount;
            } else {
                monsterType = 'D';
                count = dCount;
            }
        } while (count >= 5);

        // spawn the monster
        map[y][x].monster = monsterType;
        map[y][x].walkable = false;
        
        // update the monster count
        if (monsterType == 'E') {
            eCount++;
        } else if (monsterType == 'G') {
            gCount++;
        } else {
            dCount++;
        }
    }
}



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






