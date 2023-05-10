#ifndef __SIDEMENU_H__
#define __SIDEMENU_H__

// This will create the menu structure
void createMenu(int cols2, int rows);

// This will create the menu left border
void createVerticalSeparator(int cols2, int rows);

// Will create a section in the menu
// cols2: cols - 30
// posX: y of the area
// title[]: the area header
void createArea(int cols2, int posX, char title[]);

// Auxiliar function to create an area, just creates a horizontal border for each area
void createHorizontalSeparator(int cols2, int posX);

// This function will add in the actions menu a given action
// cols2: cols - 30
// action: string to be added
// lines in the actions area
int addActions(int cols2, char action[], int lines, int color);

#endif