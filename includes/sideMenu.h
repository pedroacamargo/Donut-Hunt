#ifndef __SIDEMENU_H__
#define __SIDEMENU_H__

// This will create the menu structure
void createMenu(int cols2, int rows);

// This will create the menu left border
void createVerticalSeparator(int cols2, int rows);

// Will create a section in the menu
// cols2: cols - 30
// posY: y of the area
// areaHeight: height
// title[]: the area header
void createArea(int cols2, int posY, int areaHeight, char title[]);

// Auxiliar function to create an area, just creates a horizontal border for each area
void createHorizontalSeparator(int cols2, int posX);

void createStats(int cols2);

// This function will add in the actions menu a given action
// cols2: cols - 30
// action: string to be added
// lines in the actions area
int addActions(int cols2, char action[], int lines, int color);

// This function is the same as addActions, but instead will put a variable after a string
// [ action: data ]
int addActionsWithData(int cols2, char action[], int data, int lines, int color);

void updateStats(Player * user, int cols2);

void createOptions(int cols2, int sartPositionY);

void menuSwap(bool * isSideMenuOpened, Player * user, int cols, int rows);

void sideMenuLoop(bool * isSideMenuOpened, Player * user, int cols, int rows);

#endif