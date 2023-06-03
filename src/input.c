#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <menu.h>
#include <time.h>
#include "main.h"

Tile ** getInput(int key, Player *user, int cols, int rows, Tile ** map, int *linesActions, bool * sawAVine, bool * sawAMonster, bool * sawAnItem, int firstPosition, int maxRooms, WINDOW * wnd) {
  switch (key) {
  case 'w':
  case 'W':
  case 'A':
  case KEY_UP:
    map = playerMove(-1, 0, cols, rows, user, map, linesActions, sawAVine, sawAMonster, sawAnItem, firstPosition, maxRooms, wnd);
    return map;
  case 'd':
  case 'C':
  case KEY_RIGHT:
    map = playerMove(0, +1, cols, rows, user, map, linesActions, sawAVine, sawAMonster, sawAnItem, firstPosition, maxRooms, wnd);
    return map;
  case 'a':
  case 'D':
  case KEY_LEFT:
    map = playerMove(0, -1, cols, rows , user, map, linesActions, sawAVine, sawAMonster, sawAnItem, firstPosition, maxRooms, wnd);
    return map;
  case 's':
  case 'S':
  case 'B':
  case KEY_DOWN:
    map = playerMove(+1, 0, cols, rows, user, map, linesActions, sawAVine, sawAMonster, sawAnItem, firstPosition, maxRooms, wnd);
    return map;
  case 'v':
  case 'V':
    *linesActions = addActions(cols, "Map debugged", *linesActions,6);
    debugMap(map, cols, rows);
    // printMap(rows, cols, map);
    return map;
  case 'b':
    openBackpack(cols,rows,map,user);
    break;
  default:
    break;
  }
  return map;
}
