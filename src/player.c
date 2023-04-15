#include <stdlib.h>
#include <ncurses.h>
#include "main.h"

Player * playerSetUp() {
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  return newPlayer;
}

void getInput(int key, Player *user) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, user);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, user);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, user);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, user);
    break;
  case 'q':
  case 'Q':
    refresh();
    endwin();
  default:
    break;
  }
}

void playerMove(int y, int x, Player *user) {

  int newX, newY;

  newY = y + user->pos.y;
  newX = x + user->pos.x;
  
  switch (mvinch(newY,newX)) {
    case '#':
      move(user->pos.y,user->pos.x);
      break;
    case '.':
      mvprintw(user->pos.y, user->pos.x, ".");
      user->pos.x += x;
      user->pos.y += y;
      mvprintw(user->pos.y, user->pos.x, "@");
      move(user->pos.y, user->pos.x);
      break;
  }
  // fazer checkPosition()
}