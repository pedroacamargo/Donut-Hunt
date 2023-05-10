#ifndef __PLAYER_H__
#define __PLAYER_H_

Player * playerSetUp();
// playerSetUp() will just setup the user and allocate memory in the stack for the Player



void playerMove(int y, int x, int cols, int rows, Player * user, Tile ** map, int *linesActions, bool *sawAVine);
// This function will move the player with the WASD instructions, just that simple :)


void updatePlayerPosition(Player * user, int cols, int rows , Tile ** map, int *linesActions, bool *sawAVine);
// This will just update the position printed in the window, just a visual function to save lines of code


#endif