#ifndef __PLAYER_H__
#define __PLAYER_H_

Player * playerSetUp();
// playerSetUp() will just setup the user and allocate memory in the stack for the Player



void playerMove(int y, int x, Player * user, Tile ** map);
// This function will move the player with the WASD instructions, just that simple :)


void updatePlayerPosition(Player * user, Tile ** map);
// This will just update the position printed in the window, just a visual function to save lines of code


#endif