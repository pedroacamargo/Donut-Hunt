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

/*
    *
    *   This function will update the stats in the menu 1st section, printing the player stats
    * 
*/
void updateStats(Player * user, int cols2);

/*
    *
    *   Funtion to create the options area
    *   (Y) -> Open inventory
    *   (V) -> Debug map
    *   (Q) -> Quit
    * 
*/
void createOptions(int cols2, int sartPositionY);

/*
    *
    *   Function to change between menu and inventory, it's an important function
    * 
*/
void menuSwap(bool * isSideMenuOpened, Player * user, int cols, int rows);

/*
    *
    *   Function to create the active items inventory design
    * 
*/
void createDesignSideMenu(int cols);

/*
    *
    *   Function to create the item boxes in the inventory
    * 
*/
void buildCheckBox(int cols, int y, char str[]);
void buildwCheckBox(int cols, int y, char str[], WINDOW * wnd);

/*
    *
    *   Important function to update the active items in the inventory menu
    * 
    *   RARITY
    *   1 - White
    *   2 - Blue
    *   3 - Yellow
    *   4 - Green
    *   5 - Red
    * 
    *   Box ID
    *   1 - Armor slot
    *   2 - Sword slot
    *   3 - Special Item slot
    * 
    *   item -> use the player->activeItems struct to put the item in the correct boxID
    * 
*/
void updateInventoryItem(int cols, Item * item);

/*
    *
    *   Simple function just to update all slots in the boxes automaticaly
    * 
*/
void updateInventoryActiveItems(Player * user, int cols);


int selectSlot(int ch, int cols, int rows, int inventoryLine, Tile ** map, Player * user);


void createPopUp(int cols, int rows, Tile ** map, Player * user, int slotID);

/*
  * Line starts
  * Name -> 7
  * Rarity -> 10
  * Buffs -> 9
  * Level -> 9
  * Lore -> 8
  * 
*/
void createPopUpDesign(WINDOW * wnd);


void updatePopUpItemStats(WINDOW * wnd, Player * user, int slotID);


void itemSlotPopUpIcon(int cols,Player * user, WINDOW * wnd, int slotID);


/*
    *
    *   Main loop for the menu, almost everything about the menu will be implemented here
    * 
*/
void sideMenuLoop(bool * isSideMenuOpened, Player * user, int cols, int rows, Tile ** map);

#endif