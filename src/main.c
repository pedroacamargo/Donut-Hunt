#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"

void windowSetUp(int * cols, int * rows, WINDOW * wnd) {
	// Window Setup
	getmaxyx(wnd,*cols,*rows);
	raw();
	noecho();
	keypad(stdscr,true);
	refresh();
	clear();
}

void getInput(WINDOW * wnd,int key, Player *user,int *cols, int *rows) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, user);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, user);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, user);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, user);
    break;
  case 'q':
  case 'Q':
    refresh();
    endwin();
    break;
  case 'P':
  case 'p':
    // prevRoom[*roomsAmount] = *randomizePosition(wnd, &prevRoom[*roomsAmount - 1],*rows,*cols,firstPosition,0);
    // *roomsAmount++;
    updatePlayerPosition(user);
    break;
  default:
    break;
  }
}
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





int main() {
	Player * user;
	WINDOW *wnd = initscr();
	srand(time(NULL));

	// Variables
	int cols, rows;
	int roomsAmount = 0;
	int maxRooms = 30; // Max rooms in the map
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation

	// Setup ncurses window in CLI
	windowSetUp(&cols, &rows, wnd);
	
	// player and map setups
	NormalRoom * roomsArray[10];
	NormalRoom * firstRoom = createRoom(cols,rows);
	user = playerSetUp(firstRoom);
	roomsArray[roomsAmount] = firstRoom;
	updatePlayerPosition(user);

	NormalRoom * room = roomsArray[0];

  createMap(wnd,room,roomsArray,maxRooms,firstPosition,cols,rows);

	// game loop
	while(1) {
		if (roomsAmount == maxRooms) break;
		int ch = getch();
		getInput(wnd, ch, user, &cols, &rows);
	}

	endwin();
	return 0;
}