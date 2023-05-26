#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

/*
 * Each area has a 28 chars max length!
 *
 * Stats -> cols2 x (1 - 9)
 * Actions -> cols2 x (11 - 19)
 * 
 * For future updates in the side menu, here is the important variables to pay attention:
 * -> endPositionStats
 * -> endPositionActions
 * -> endPositionOptions
 * -> startInventoryY
*/

void createMenu(int cols2, int rows) {
  int endPositionStats = 10;
  int endPositionActions = 20;
  int endPositionOptions = 27;

  int linesActions = 0;
  // int linesStats = 0;

  createVerticalSeparator(cols2,rows);
  createHorizontalSeparator(cols2, 0);
  

  /* Stats area */
  createArea(cols2, endPositionStats, 9, "Stats");
  createStats(cols2);


  /* Actions area */
  createArea(cols2, endPositionActions, 9, "Actions");
  linesActions = addActions(cols2, "Let's find the donut!",linesActions,6);

  /* Options */
  createArea(cols2, endPositionOptions, 6, "Options");
  createOptions(cols2, endPositionOptions);
}

void createVerticalSeparator(int cols2, int rows) {
  for (int i = 0; i < rows; i++) {
    mvaddch(i,cols2,'|');
  }
}

void createArea(int cols2, int posY, int areaHeight, char title[]) {
  createHorizontalSeparator(cols2, posY);
  attron(COLOR_PAIR(3));
  mvprintw(posY - areaHeight, cols2 + 12,"%s",title);
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

int addActionsWithData(int cols2, char action[], int data, int lines, int color) {
  int startAreaActions = 12;
  // reset the whole line
  mvprintw(lines + startAreaActions,cols2 + 2, "                        ");
  attron(COLOR_PAIR(color));
  mvprintw(startAreaActions + lines,cols2 + 2, "%s: %d", action, data);
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

void createOptions(int cols2, int startPositionY) {
  startPositionY -= 4;
  mvprintw(startPositionY,cols2 + 2,"(Y) Open inventory");
  mvprintw(startPositionY + 1,cols2 + 2,"(Q) Quit game");
  mvprintw(startPositionY + 2,cols2 + 2,"(V) Debug mode");
}

void menuSwap(bool * isSideMenuOpened, Player * user, int cols, int rows) {
  int startInventoryY = 20;
  if (*isSideMenuOpened) {
    *isSideMenuOpened = false;
    mvprintw(startInventoryY + 1,cols + 2, "                        ");
    createMenu(cols,rows);
    updateStats(user,cols);
  } else {
    *isSideMenuOpened = true;
    for (int j = startInventoryY + 1; j < rows; j++) {
      for (int i = cols; i < cols + 30; i++) {
        if (i == cols) mvaddch(j,i,'|');
        else if (j == startInventoryY + 1) {
          attron(COLOR_PAIR(3));
          mvprintw(j, i + 10, "Inventory");
          attroff(COLOR_PAIR(3));
          j++;
        }
        else mvaddch(j,i,' ');
      }
    }
  }
}


void sideMenuLoop(bool * isSideMenuOpened, Player * user, int cols, int rows) {
  menuSwap(isSideMenuOpened,user,cols,rows);
  while (*isSideMenuOpened) {
    int ch = getch();
    if (ch == 'y' || ch == 'Y') {
      menuSwap(isSideMenuOpened,user,cols,rows);
    }
  }
}