#include <stdlib.h>
#include <ncurses.h>
#include "main.h"

Player * playerSetUp() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  // newPlayer->pos.x = firstRoom->pos.x + (firstRoom->width / 2);
  // newPlayer->pos.y = firstRoom->pos.y + (firstRoom->height / 2);

  return newPlayer;
}






void playerMove(int y, int x, int cols, int rows, Player *user, Tile ** map) {

  int newX, newY;

  newY = y + user->pos.y;
  newX = x + user->pos.x;
  
  switch (map[newY][newX].ch) {
    case '#':
    case '|':
    case '-':
      move(user->pos.y,user->pos.x);
      break;
    case '$':
      map[user->pos.y][user->pos.x].ch = '.';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      map[user->pos.y][user->pos.x].transparent = true;
      updatePlayerPosition(user,cols, rows, map);
      break;
    case '.':
      map[user->pos.y][user->pos.x].ch = '.';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map);
      break;
    case '+':
    case ' ':
      map[user->pos.y][user->pos.x].ch = '+';
      map[user->pos.y][user->pos.x].color = COLOR_PAIR(5);
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user,cols, rows, map);
      break;
  }
}





void updatePlayerPosition(Player *user,int cols, int rows, Tile ** map) {
  map[user->pos.y][user->pos.x].ch  = '@';
  map[user->pos.y][user->pos.x].color = COLOR_PAIR(1);
  // mvprintw(0,0,"y: %d | x: %d",user->pos.y, user->pos.x);
  clearFov(user, cols, rows, map);
  move(user->pos.y,user->pos.x);
  makeFov(user, cols, rows, map);
}