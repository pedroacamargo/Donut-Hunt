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
}

void getInput(int key, Player *user, int cols, int rows, Tile ** map) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, cols, rows, user, map);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, cols, rows, user, map);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, cols, rows , user, map);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, cols, rows, user, map);
    break;
  case 'v':
  case 'V':
    debugMap(map, cols, rows);
    // printMap(rows, cols, map);
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
      V: Debug map
    } 
*/





int main() {
	Player * user;
	WINDOW *wnd = initscr();
	srand(time(NULL));
  start_color();

  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // cor do que é visivel
  init_pair (2, COLOR_BLUE, COLOR_BLACK); // cor do que foi visto

	// Variables
	int cols, rows, maxRooms = 30;
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation

	// Setup ncurses window in CLI
	windowSetUp(&cols, &rows, wnd);
  user = playerSetUp();
  
  // create the whole map
  Tile ** map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);

  updatePlayerPosition(user,cols,rows,map);
  
	// game loop
	while(1) {
    printMap(rows,cols,map);
		int ch = getch();
    if (ch == 'q' || ch == 'Q') break;
		getInput(ch, user,cols,rows, map);
	}

  endwin();
	return 0;
}