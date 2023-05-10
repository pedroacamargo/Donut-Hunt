#include <stdlib.h>
#include <ncurses.h>
#include "main.h"


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
}