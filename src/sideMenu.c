#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

/*
        Each area has a 28 chars max length!

        Stats -> cols2 x (1 - 9)
        Actions -> cols2 x (11 - 19)
*/

void createMenu(int cols2, int rows) {
  int lines = 0;

  createVerticalSeparator(cols2,rows);
  createHorizontalSeparator(cols2, 0);
  

  /* Stats area */
  createArea(cols2, 10, "Stats");


  /* Actions area */
  createArea(cols2, 20, "Actions");
  lines = addActions(cols2, "Let's find the donut!",lines,6);
}

void createVerticalSeparator(int cols2, int rows) {
  for (int i = 0; i < rows; i++) {
    mvaddch(i,cols2,'|');
  }
}

void createArea(int cols2, int posX, char title[]) {
  createHorizontalSeparator(cols2, posX);
  attron(COLOR_PAIR(3));
  mvprintw(posX - 9, cols2 + 12,"%s",title);
  attroff(COLOR_PAIR(3));
}

void createHorizontalSeparator(int cols2, int posX) {
  for (int i = cols2; i < cols2 + 30; i++) {
    if (mvinch(posX,i) == '|') mvaddch(posX,i,'#');
    else mvaddch(posX,i,'_');
  }
}

int addActions(int cols2, char action[], int lines, int color) {
  int startAreaActions = 12;
  // reset the whole line
  mvprintw(lines + startAreaActions,cols2 + 2, "                        ");
  attron(COLOR_PAIR(color));
  mvprintw(startAreaActions + lines,cols2 + 2, action);
  attroff(COLOR_PAIR(color));
  if (lines == 7) return 0;
  return lines + 1;
}