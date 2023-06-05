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
  int endPositionOptions = 28;

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
  createArea(cols2, endPositionOptions, 7, "Options");
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
  mvprintw(startAreaActions + lines,cols2 + 2,  "%s", action);
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
  mvprintw(startAreaStats, line1Start,"        ");
  mvprintw(startAreaStats + 1, line2Start, "        ");
  mvprintw(startAreaStats + 2, line3Start, "        ");
  mvprintw(startAreaStats + 3, line4Start, "        ");
  mvprintw(startAreaStats + 4, line5Start, "        ");
  attron(COLOR_PAIR(3));
  mvprintw(startAreaStats, line1Start,"%d",user->life);
  mvprintw(startAreaStats + 1, line2Start, "%d",user->damage);
  mvprintw(startAreaStats + 2, line3Start, "%d",user->armor);
  mvprintw(startAreaStats + 3, line4Start, "%d",user->monstersKilled);
  mvprintw(startAreaStats + 4, line5Start, "%d",user->dungeonFloor);
  attroff(COLOR_PAIR(3));
}

void createOptions(int cols2, int startPositionY) {
  startPositionY -= 5;
  mvprintw(startPositionY,cols2 + 2,"(Y) Open inventory");
  mvprintw(startPositionY + 1,cols2 + 2,"(B) Open Backpack");
  mvprintw(startPositionY + 2,cols2 + 2,"(Q) Quit game");
  mvprintw(startPositionY + 3,cols2 + 2,"(V) Debug mode");
}

void menuSwap(bool * isSideMenuOpened, Player * user, int cols, int rows) {
  int startInventoryY = 20;
  if (*isSideMenuOpened) {
    *isSideMenuOpened = false;
    for (int i = startInventoryY + 1; i < rows; i++)
      mvprintw(i,cols + 1, "                             ");
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

void createDesignSideMenu(int cols) {
  int startInventoryY = 23;
  buildCheckBox(cols, startInventoryY, "Armor");
  startInventoryY += 6; // add the height of the checkbox
  buildCheckBox(cols, startInventoryY, "Sword");
  startInventoryY += 6; // add the height of the checkbox
  buildCheckBox(cols, startInventoryY, "Special");
  startInventoryY += 6; // add the height of the checkbox
  createHorizontalSeparator(cols,startInventoryY);

  startInventoryY += 2;
  mvprintw(startInventoryY, cols + 2, "(W) -> go up in the menu");
  startInventoryY++;
  mvprintw(startInventoryY, cols + 2, "(S) -> go down in the menu");
  startInventoryY++;
  mvprintw(startInventoryY, cols + 2, "(Enter) -> Access item");
  startInventoryY++;
  mvprintw(startInventoryY, cols + 2, "(B) -> Open backpack");
  startInventoryY++;
  mvprintw(startInventoryY, cols + 2, "(Q) -> Close Inventory");
}

void buildCheckBox(int cols, int y, char str[]) {
  for (int i = y; i < y+5; i++) 
    for (int j = cols + 5; j < cols + 12; j++) {
      if (i == y || i == y+4 || j == cols + 5 || j == cols + 11) mvprintw(i,j,"#");
    }

  attron(COLOR_PAIR(3));
  mvprintw(y+2, cols + 13, "%s",str);
  attroff(COLOR_PAIR(3));
}

void buildwCheckBox(int cols, int y, char str[], WINDOW * wnd) {
  for (int i = y; i < y+5; i++) 
    for (int j = cols + 5; j < cols + 12; j++) {
      if (i == y || i == y+4 || j == cols + 5 || j == cols + 11) mvwprintw(wnd,i,j,"#");
    }

  attron(COLOR_PAIR(3));
  mvwprintw(wnd,y+2, cols + 13, "%s",str);
  attroff(COLOR_PAIR(3));
}

/*
  * Armor ID -> 1
  * Sword ID -> 2
  * Special ID -> 3
*/
void updateInventoryItem(int cols, Item * item) {

  int startInventoryY = 23;
  int boxX = cols + 8; // center of the box in X axis
  switch (item->ID) {
  case 1:
    startInventoryY += 6;
    break;
  case 2:
    startInventoryY += 12;
    break;
  case 3:
    startInventoryY += 18;
    break;
  default:
    break;
  }
  // This will put the Y in the center of the box
  startInventoryY -= 4;

  attron(COLOR_PAIR(item->rarity));
  mvaddch(startInventoryY,boxX,item->ch);
  attroff(COLOR_PAIR(item->rarity));
}

void updateInventoryActiveItems(Player * user, int cols) {

  if (user->activeItems->armorSlot) {
    updateInventoryItem(cols,user->activeItems->armorSlot);
  } 

  if (user->activeItems->swordSlot) {
    updateInventoryItem(cols,user->activeItems->swordSlot);
  } 

  if (user->activeItems->specialSlot) {
    updateInventoryItem(cols,user->activeItems->specialSlot);
  } 

}

int selectSlot(int ch, int cols, int rows, int slotID, Tile ** map, Player * user) {
  int inventoryLine;
  if (slotID == 1) inventoryLine = 25;
  else if (slotID == 2) inventoryLine = 31;
  else inventoryLine = 37;


  //WINDOW * popUp;
  switch (ch) {
  case 's':
  case 'S':
    if (inventoryLine == 37) return slotID;
    mvprintw(inventoryLine, cols+2, "  ");
    inventoryLine += 6;
    slotID++;
    break;
  case 'w':
  case 'W':
    if (inventoryLine == 25) return slotID;
    mvprintw(inventoryLine, cols+2, "  ");
    inventoryLine -= 6;
    slotID--;
    break;
  case 'B':
  case 'b':
    openBackpack(cols,rows,map,user);
    break;
  case 10:
    createPopUp(cols, rows, map, user, slotID);
    break;
  }
  attron(COLOR_PAIR(3));
  mvprintw(inventoryLine, cols+2,"->");
  attroff(COLOR_PAIR(3));
  return slotID;
}

void createPopUp(int cols, int rows, Tile ** map, Player * user, int slotID) {
  WINDOW * popUp = newwin(rows/3, cols/3, rows/2 - rows/4, cols/2 - cols/4 + 30); // +30 because of the sideMenu window width = 30
  wattron(popUp,COLOR_PAIR(3));
  box(popUp, 0, 0);
  mvwprintw(popUp,0,2,"Item Stats");
  wattroff(popUp,COLOR_PAIR(3));

  int xWin = cols/3 - 1;
  int yWin = rows/3 - 1;
  int actualLine = 2;

  mvwprintw(popUp, yWin - 1, 2, "Press (Q) to quit the window");
  wattron(popUp,COLOR_PAIR(3));
  buildwCheckBox(xWin/2 - 7,actualLine,"",popUp);
  for (int i = 1; i < xWin; i++) {
    if (i > xWin/2 - 3 && i < xWin/2 + 5) continue;
    mvwaddch(popUp,4,i,'#');
  }
  // Decorations
  mvwaddch(popUp,3,1,'#');
  mvwaddch(popUp,5,1,'#');
  mvwaddch(popUp,3,xWin - 1,'#');
  mvwaddch(popUp,5,xWin - 1,'#');
  mvwaddch(popUp,3,xWin/2 - 3,'#');
  mvwaddch(popUp,3,xWin/2 + 5,'#');
  mvwaddch(popUp,5,xWin/2 - 3,'#');
  mvwaddch(popUp,5,xWin/2 + 5,'#');
  wattroff(popUp,COLOR_PAIR(3));

  actualLine += 7;

  createPopUpDesign(popUp);
  itemSlotPopUpIcon(xWin,user,popUp,slotID);
  updatePopUpItemStats(popUp, user, slotID);


  char ch = wgetch(popUp);
  while (ch != 'q') {
    ch = wgetch(popUp);
  }
  printMap(rows,cols,map,user);


  endwin();
  delwin(popUp);
}

void createPopUpDesign(WINDOW * wnd) {
  int actualLine = 9;
  wattron(wnd,COLOR_PAIR(6));
  mvwprintw(wnd,actualLine,2,"Name: ");
  mvwprintw(wnd,actualLine + 1, 2, "Rarity: ");
  mvwprintw(wnd,actualLine + 2, 2, "Buffs: ");
  mvwprintw(wnd,actualLine + 3, 2, "Level: ");
  wattroff(wnd,COLOR_PAIR(6));


  wattron(wnd,COLOR_PAIR(5));
  mvwprintw(wnd,actualLine + 5, 2, "Lore: ");
  wattroff(wnd,COLOR_PAIR(5));
}


void updatePopUpItemStats(WINDOW * wnd, Player * user, int slotID) {
  int actualLine = 9;
  if (slotID == 1) {
    if (user->activeItems->armorSlot != NULL) {
      mvwprintw(wnd,actualLine,7," %s",user->activeItems->armorSlot->name);
      wattron(wnd,COLOR_PAIR(user->activeItems->armorSlot->rarity));
      mvwprintw(wnd,actualLine + 1,10,"%d",user->activeItems->armorSlot->rarity);
      wattroff(wnd,COLOR_PAIR(user->activeItems->armorSlot->rarity));
      mvwprintw(wnd,actualLine + 2,9,"%s",user->activeItems->armorSlot->buffDescription);
      mvwprintw(wnd,actualLine + 3,9,"%d",user->activeItems->armorSlot->level);
      mvwprintw(wnd,actualLine + 6,2,"%s",user->activeItems->armorSlot->lore);
    } else {
      mvwprintw(wnd,actualLine,7,"No item equiped");
      mvwprintw(wnd,actualLine + 1,10,"0");
      mvwprintw(wnd,actualLine + 2,9,"Are you naked? :O");
      mvwprintw(wnd,actualLine + 3,9,"0");
    }

  } else if (slotID == 2) {
    if (user->activeItems->swordSlot != NULL) {
      mvwprintw(wnd,actualLine,7," %s",user->activeItems->swordSlot->name);
      wattron(wnd,COLOR_PAIR(user->activeItems->swordSlot->rarity));
      mvwprintw(wnd,actualLine + 1,10,"%d",user->activeItems->swordSlot->rarity);
      wattroff(wnd,COLOR_PAIR(user->activeItems->swordSlot->rarity));
      mvwprintw(wnd,actualLine + 2,9,"%s",user->activeItems->swordSlot->buffDescription);
      mvwprintw(wnd,actualLine + 3,9,"%d",user->activeItems->swordSlot->level);
      mvwprintw(wnd,actualLine + 5,9,"%s",user->activeItems->swordSlot->lore);

    } else {
      mvwprintw(wnd,actualLine,7,"No item equiped");
      mvwprintw(wnd,actualLine + 1,10,"0");
      mvwprintw(wnd,actualLine + 2,9,"Maybe you can punch some monsters with your own fists.");
      mvwprintw(wnd,actualLine + 3,9,"0");
    } 
  } else if (slotID == 3) {
    if (user->activeItems->specialSlot != NULL) {
      mvwprintw(wnd,actualLine,7," %s",user->activeItems->specialSlot->name);
      wattron(wnd,COLOR_PAIR(user->activeItems->specialSlot->rarity));
      mvwprintw(wnd,actualLine + 1,10,"%d",user->activeItems->specialSlot->rarity);
      wattroff(wnd,COLOR_PAIR(user->activeItems->specialSlot->rarity));
      mvwprintw(wnd,actualLine + 2,9,"%s",user->activeItems->specialSlot->buffDescription);
      mvwprintw(wnd,actualLine + 3,9,"%d",user->activeItems->specialSlot->level);
      mvwprintw(wnd,actualLine + 5,9,"%s",user->activeItems->specialSlot->lore);
    } else {
      mvwprintw(wnd,actualLine,7,"No item equiped");
      mvwprintw(wnd,actualLine + 1,10,"0");
      mvwprintw(wnd,actualLine + 2,9,"Try to find any special item! They're incredible.");
      mvwprintw(wnd,actualLine + 3,9,"0");
    }

  }

}


void itemSlotPopUpIcon(int cols,Player * user, WINDOW * wnd, int slotID) {
  int centerX = cols/2 + 1;

  if (slotID == 1) {
    if (user->activeItems->armorSlot) {
      wattron(wnd,COLOR_PAIR(user->activeItems->armorSlot->rarity));
      mvwaddch(wnd,4,centerX,user->activeItems->armorSlot->ch);
      wattroff(wnd,COLOR_PAIR(user->activeItems->armorSlot->rarity));
    } else {
      wattron(wnd,COLOR_PAIR(1));
      mvwaddch(wnd,4,centerX,'X');
      wattroff(wnd,COLOR_PAIR(1));
    }
  } else if (slotID == 2) {

    if (user->activeItems->swordSlot) {
      wattron(wnd,COLOR_PAIR(user->activeItems->swordSlot->rarity));
      mvwaddch(wnd,4,centerX,user->activeItems->swordSlot->ch);
      wattroff(wnd,COLOR_PAIR(user->activeItems->swordSlot->rarity));
    } else {
      wattron(wnd,COLOR_PAIR(1));
      mvwaddch(wnd,4,centerX,'X');
      wattroff(wnd,COLOR_PAIR(1));
    }

  } else if (slotID == 3) {
    if (user->activeItems->specialSlot) {
      wattron(wnd,COLOR_PAIR(user->activeItems->specialSlot->rarity));
      mvwaddch(wnd,4,centerX,user->activeItems->specialSlot->ch);
      wattroff(wnd,COLOR_PAIR(user->activeItems->specialSlot->rarity));
    } else {
      wattron(wnd,COLOR_PAIR(1));
      mvwaddch(wnd,4,centerX,'X');
      wattroff(wnd,COLOR_PAIR(1));
    }
  }
}


void sideMenuLoop(bool * isSideMenuOpened, Player * user, int cols, int rows, Tile ** map) {
  int inventoryLine = 25;
  int slotID = 1;
  menuSwap(isSideMenuOpened,user,cols,rows);
  createDesignSideMenu(cols);
  updateInventoryActiveItems(user, cols);

  attron(COLOR_PAIR(3));
  mvprintw(inventoryLine, cols+2,"->");
  attroff(COLOR_PAIR(3));

  while (*isSideMenuOpened) {
    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
      menuSwap(isSideMenuOpened,user,cols,rows);
    } else if (ch == 's' || ch == 'w' || ch == 'W' || ch == 'S' || ch) {
      slotID = selectSlot(ch, cols, rows, slotID, map, user);
    } 
  }
}