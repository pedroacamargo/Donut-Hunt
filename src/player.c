#include <stdlib.h>
#include <ncurses.h>
#include "main.h"

Player * playerSetUp(NormalRoom * firstRoom) {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->pos.x = firstRoom->pos.x + (firstRoom->width / 2);
  newPlayer->pos.y = firstRoom->pos.y + (firstRoom->height / 2);

  return newPlayer;
}






void playerMove(int y, int x, Player *user) {

  int newX, newY;

  newY = y + user->pos.y;
  newX = x + user->pos.x;
  
  switch (mvinch(newY,newX)) {
    case '#':
    case '|':
    case '-':
      move(user->pos.y,user->pos.x);
      break;
    case '.':
      mvprintw(user->pos.y, user->pos.x, ".");
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user);
      break;
    case '+':
      mvprintw(user->pos.y, user->pos.x, "+");
      user->pos.x += x;
      user->pos.y += y;
      updatePlayerPosition(user);
      break;
  }
}





void updatePlayerPosition(Player *user) {
  mvprintw(user->pos.y, user->pos.x, "@");
  mvprintw(0,0,"y: %d | x: %d",user->pos.y, user->pos.x);
  move(user->pos.y,user->pos.x);
}