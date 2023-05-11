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
  int linesActions = 0;
  // int linesStats = 0;

  createVerticalSeparator(cols2,rows);
  createHorizontalSeparator(cols2, 0);
  

  /* Stats area */
  createArea(cols2, 10, "Stats");
  createStats(cols2);


  /* Actions area */
  createArea(cols2, 20, "Actions");
  linesActions = addActions(cols2, "Let's find the donut!",linesActions,6);
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

/*
    Start of each line
  Line 1 -> 8
  Line 2 -> 10
  Line 3 -> 9
  Line 4 -> 19
  Line 5 -> 9
*/
void createStats(int cols2) {
  int startAreaStats = 2;
  attron(COLOR_PAIR(6));
  mvprintw(startAreaStats,cols2 + 2,"Life:");
  mvprintw(startAreaStats + 1,cols2 + 2,"Damage:");
  mvprintw(startAreaStats + 2,cols2 + 2,"Armor:");
  mvprintw(startAreaStats + 3,cols2 + 2,"Monsters killed:");
  mvprintw(startAreaStats + 4,cols2 + 2,"Floor:");
  attroff(COLOR_PAIR(6));
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

void updateStats(Player * user, int cols2) {
  int startAreaStats = 2;
  int line1Start = 8 + cols2;
  int line2Start = 10 + cols2;
  int line3Start = 9 + cols2;
  int line4Start = 19 + cols2;
  int line5Start = 9 + cols2;
  attron(COLOR_PAIR(3));
  mvprintw(startAreaStats, line1Start,"%d",user->life);
  mvprintw(startAreaStats + 1, line2Start, "%d",user->damage);
  mvprintw(startAreaStats + 2, line3Start, "%d",user->armor);
  mvprintw(startAreaStats + 3, line4Start, "%d",user->monstersKilled);
  mvprintw(startAreaStats + 4, line5Start, "%d",user->dungeonFloor);
  attroff(COLOR_PAIR(3));
}