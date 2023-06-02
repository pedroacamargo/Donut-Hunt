#include <stdlib.h>
#include <ncurses.h>
#include "main.h"

Player * playerSetUp() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  Inventory * playerInventory;
  playerInventory = malloc(sizeof(Inventory));

  Backpack * backpack = malloc(sizeof(Backpack));
  playerInventory->backpack = backpack;

  Item * defaultArmor = createItem('@', // item appearance
  "Newbie armor", // item name
  "None, superficial protection from monsters bites",  // item buff description
  "Where am I? I'm STARVING, I need to find a donut...", // item lore
   1, // rarity
   0, // buff in number
   1, // level (room floor)
   1  // ID
   );

  newPlayer->life = 100;
  newPlayer->armor = 0;
  newPlayer->damage = 0;
  newPlayer->dungeonFloor = 25;
  newPlayer->monstersKilled = 0;
  newPlayer->activeItems = playerInventory;

  newPlayer->activeItems->armorSlot = defaultArmor;
  newPlayer->activeItems->swordSlot = NULL;
  newPlayer->activeItems->specialSlot = NULL;

  return newPlayer;
}






Tile ** playerMove(int y, int x, int cols, int rows, Player *user, Tile ** map, int *linesActions, bool *sawAVine, bool * sawAMonster, bool * sawAnItem, int firstPosition, int maxRooms, WINDOW * wnd) {

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
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster, sawAnItem);
      break;
    case '.':
      map[user->pos.y][user->pos.x].ch = '.';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster, sawAnItem);
      break;
    case '+':
    case ' ':
      map[user->pos.y][user->pos.x].ch = '+';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster, sawAnItem);
      break;
    case 'v':
      resetMap(rows,cols,map,user);
      map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);
      updatePlayerPosition(user,cols,rows,map,linesActions,sawAVine, sawAMonster,sawAnItem);
      user->dungeonFloor++;
      updateStats(user, cols);
      printMap(rows,cols,map,user);
      *linesActions = addActions(cols,"Difficulty increased!", *linesActions,3);
      return map;
    case '?':
      map[user->pos.y][user->pos.x].ch = '.';
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map, linesActions, sawAVine, sawAMonster, sawAnItem);
      getItem(map,user,cols);
      addItemBackpack(user->activeItems->backpack,map[user->pos.y][user->pos.x].item);
      break;
  }
  return map;
}





void updatePlayerPosition(Player *user,int cols, int rows, Tile ** map, int *linesActions,bool * sawAVine, bool * sawAMonster, bool * sawAnItem) {
  map[user->pos.y][user->pos.x].ch  = '@';
  map[user->pos.y][user->pos.x].color = COLOR_PAIR(user->activeItems->armorSlot->rarity);
  // mvprintw(0,0,"y: %d | x: %d",user->pos.y, user->pos.x);
  clearFov(user, cols, rows, map);
  move(user->pos.y,user->pos.x);
  makeFov(user, cols, rows, map, linesActions, sawAVine, sawAMonster, sawAnItem);
}



// To make the special items functional, just create a function to handle with Items ID 3 below
void updatePlayerStats(Item * item, Player * user) {
  if (item->ch == '@') {
    user->armor = item->buff;
  } else if (item->ch == '|') {
    user->damage = item->buff;
  } if (item->ID == 3) {
    return;
  }
}