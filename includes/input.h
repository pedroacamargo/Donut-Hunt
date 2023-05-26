#ifndef __INPUT_H__
#define __INPUT_H__


/*  This is an important function, which will handle the input taken from the user keyboard
    Keys: 
    {
      W: Go up
      A: Go left
      S: Go down
      D: Go right
      Q: Quit the game
      V: Debug map
    } 
*/
Tile ** getInput(int key, Player *user, int cols, int rows, Tile ** map, int *linesActions, bool * sawAVine, bool * sawAMonster, int firstPosition, int maxRooms, WINDOW * wnd);

#endif