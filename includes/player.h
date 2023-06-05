#ifndef __PLAYER_H__
#define __PLAYER_H_

// playerSetUp() will just setup the user and allocate memory in the stack for the Player
Player * playerSetUp();


// This function will move the player with the WASD instructions, just that simple :)
Tile ** playerMove(int y, int x, int cols, int rows, Player * user, Tile ** map, int *linesActions, bool *sawAVine, bool * sawAMonster, bool * sawAnItem, int firstPosition, int maxRooms, WINDOW * wnd, Monster * monsters, int * monstersAmount);


// This will just update the position printed in the window, just a visual function to save lines of code
void updatePlayerPosition(Player * user, int cols, int rows , Tile ** map, int *linesActions, bool *sawAVine, bool * sawAMonster, bool * sawAnItem);

void updatePlayerStats(Item * item, Player * user);


#endif