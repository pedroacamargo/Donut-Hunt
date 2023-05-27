#include <stdlib.h>
#include <ncurses.h>
#include "main.h"

Player * playerSetUp() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  Inventory * playerInventory;
  playerInventory = malloc(sizeof(Inventory));

  Item * defaultArmor = createItem('@',"Newbie armor", "None, superficial protection from monsters bites", 
  "Where am I? I'm STARVING, I need to find a donut...",
   1, 0, 1);

  newPlayer->life = 100;
  newPlayer->armor = 0;
  newPlayer->damage = 0;
  newPlayer->dungeonFloor = 1;
  newPlayer->monstersKilled = 0;
  newPlayer->activeItems = playerInventory;

  newPlayer->activeItems->armorSlot = defaultArmor;
  newPlayer->activeItems->swordSlot = NULL;
  newPlayer->activeItems->specialSlot = NULL;

  return newPlayer;
}






Tile ** playerMove(int y, int x, int cols, int rows, Player *user, Tile ** map, int *linesActions, bool *sawAVine, bool * sawAMonster, int firstPosition, int maxRooms, WINDOW * wnd) {

  int newX, newY;

  newY = y + user->pos.y;
  newX = x + user->pos.x;
  
  switch (map[newY][newX].ch) {
    case '#':
      *linesActions = addActions(cols,"Can't pass", *linesActions, 5);
      break;
    case '|':
    case '-':
      move(user->pos.y,user->pos.x);
      break;
    case '$':
      *linesActions = addActions(cols,"You cut a vine", *linesActions, 4);
      map[user->pos.y][user->pos.x].ch = '.';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      map[user->pos.y][user->pos.x].transparent = true;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster);
      break;
    case '.':
      map[user->pos.y][user->pos.x].ch = '.';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster);
      break;
    case '+':
    case ' ':
      map[user->pos.y][user->pos.x].ch = '+';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster);
      break;
    case 'v':
      resetMap(rows,cols,map,user);
      map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);
      updatePlayerPosition(user,cols,rows,map,linesActions,sawAVine, sawAMonster);
      spawnMonster(map, cols, rows);
      user->dungeonFloor++;
      updateStats(user, cols);
      printMap(rows,cols,map,user);
      *linesActions = addActions(cols,"Difficulty increased!", *linesActions,3);
      return map;
  }
  return map;
}





void updatePlayerPosition(Player *user,int cols, int rows, Tile ** map, int *linesActions,bool * sawAVine, bool * sawAMonster) {
  map[user->pos.y][user->pos.x].ch  = '@';
  map[user->pos.y][user->pos.x].color = COLOR_PAIR(user->activeItems->armorSlot->rarity);
  // mvprintw(0,0,"y: %d | x: %d",user->pos.y, user->pos.x);
  clearFov(user, cols, rows, map);
  move(user->pos.y,user->pos.x);
  makeFov(user, cols, rows, map, linesActions, sawAVine, sawAMonster);
}