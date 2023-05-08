#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"

void windowSetUp(int * cols, int * rows, WINDOW * wnd) {
	// Initialize ncurses window
	noecho();
	keypad(wnd,TRUE);
	curs_set(FALSE);
	start_color();

	// Get screen dimensions
	getmaxyx(stdscr, *rows, *cols);

	// Set up ncurses window to use entire screen
	wnd = newwin(*rows, *cols, 0, 0);
	box(wnd, 0, 0);
	wrefresh(wnd);
  mvprintw(0,0,"rows:%d,cols:%d",*rows,*cols);
}

void getInput(WINDOW * wnd,int key, Player *user, Tile ** map) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, user, map);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, user, map);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, user, map);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, user, map);
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
    updatePlayerPosition(user, map);
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
	int cols, rows, roomsAmount = 0, maxRooms = 30;
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation

	// Setup ncurses window in CLI
	windowSetUp(&cols, &rows, wnd);
  mvprintw(2,2,"cols:%d | rows:%d",cols,rows);
  user = playerSetUp();
  
  // create the whole map
  Tile ** map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);

  updatePlayerPosition(user,map);
  
	// game loop
	while(1) {
    printMap(rows,cols,map);
		if (roomsAmount == maxRooms) break;
		int ch = getch();
    if (ch == 'q') break;
		getInput(wnd, ch, user, map);
	}

	endwin();
	return 0;
}