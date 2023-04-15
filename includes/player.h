#ifndef __PLAYER_H__
#define __PLAYER_H_

Player * playerSetUp();
// playerSetUp() will just setup the user and allocate memory in the stack for the Player


void getInput(int key, Player * user,int *cols, int *rows);
/*  This is an important function, which will handle the input taken from the user keyboard
    Keys: 
    {
      W: Go up
      A: Go left
      S: Go down
      D: Go right
      Q: Quit the game
      P: Delete the actual map and create an entire new map again 
    } 
*/


void playerMove(int y, int x, Player * user);
// This function will move the player with the WASD instructions, just that simple :)


void updatePlayerPosition(Player * user);
// This will just update the position printed in the window, just a visual function to save lines of code


#endif