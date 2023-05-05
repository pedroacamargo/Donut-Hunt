#ifndef __MAPRANDOMIZATION_H__
#define __MAPRANDOMIZATION_H__

NormalRoom * randomizePosition(WINDOW * wnd,NormalRoom * room, int col, int row, int first, int iterations, Tile ** map);
// This is a recusive function that will randomize the position of a brand new room following the rule:
/*
  The room will try to be generated anywhere of these points (1-12)
  1   2   3   4
  
  12          5

  11          6

  10  9   8   7
*/
// The "first" parameter is the first position the room will try to generate, if it's not possible (there's other object in the given position (This is tested using the checkPos() function)) to create a room, the position will be incremented until it's possible to create a room or the number of 12 iterations is beaten.
// The "iterations" parameter, as the name says, tells the amount of attempts the room tried to be generated.

int checkPos(NormalRoom * room,int y, int x, WINDOW * wnd, int cols, int rows);
// This function will check if the given room (1st parameter) is not overwriting any other room
// 1 -> Has something overwritting the room
// 0 -> Is free to be generated

#endif