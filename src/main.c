#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"

void windowSetUp(WINDOW * wnd, WINDOW * wnd2) {
	// Initialize ncurses window
	noecho();
	curs_set(FALSE);


	box(wnd, 0, 0);
	box(wnd2, 0, 0);
	keypad(wnd,TRUE);
	keypad(wnd2,TRUE);
  wrefresh(wnd);
  wrefresh(wnd2);
}

void getInput(int key, Player *user, int cols, int rows, Tile ** map, int *linesActions, bool * sawAVine) {
  switch (key) {
  case 'w':
  case 'W':
    playerMove(-1, 0, cols, rows, user, map, linesActions, sawAVine);
    break;
  case 'd':
  case 'D':
    playerMove(0, +1, cols, rows, user, map, linesActions, sawAVine);
    break;
  case 'a':
  case 'A':
    playerMove(0, -1, cols, rows , user, map, linesActions, sawAVine);
    break;
  case 's':
  case 'S':
    playerMove(+1, 0, cols, rows, user, map, linesActions, sawAVine);
    break;
  case 'v':
  case 'V':
    *linesActions = addActions(cols, "Map debugged", *linesActions,6);
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
  initscr();
	Player * user;
	srand(time(NULL));
  start_color();

  // Get screen dimensions
	int cols, rows, maxRooms = 30;
	getmaxyx(stdscr, rows, cols);

  /* Colors */
  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // cor do que é visivel
  init_pair(2, COLOR_BLUE, COLOR_BLACK); // cor do que foi visto
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // cor menu stats
  init_pair(4, COLOR_GREEN, COLOR_BLACK); 
  init_pair(5, COLOR_RED, COLOR_BLACK); 
  init_pair(6, COLOR_CYAN, COLOR_BLACK);

  /* Player memory */
  int mem_sawAVine = 0;

	// Variables
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation
  int colsWnd1 = cols - 30; // COLS NUMBER MAIN WINDOW
  int colsWnd2 = 30; // COLS NUMBER MENU WINDOW
  int cols2 = cols - colsWnd2; // START POSITION MENU WINDOW
  int linesActions = 1; // Number of lines already used in the actions menu | 1 due to the welcome message
  bool sawAVine = false; // If the user saw a vine
  WINDOW * wnd = newwin(rows, cols2, 0, 0); // game window
  WINDOW * wnd2 = newwin(rows, 50, 0, cols2); // menu window

	// Setup ncurses window in CLI
	windowSetUp(wnd, wnd2);
  createMenu(cols2,rows);
  user = playerSetUp();
  cols = colsWnd1;


  /* Debug */
  mvprintw(0,0,"cols:%d, rows:%d",cols,rows);
  getch();

  // create the whole map
  Tile ** map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);

  updatePlayerPosition(user,cols,rows,map, &linesActions, &sawAVine);
  
	// game loop
	while(1) {
    printMap(rows,cols,map);
		int ch = getch();
    if (ch == 'q' || ch == 'Q') break;
		getInput(ch, user,cols,rows, map,&linesActions, &sawAVine);

    /* Player memory */
    if (mem_sawAVine == 20) {
      sawAVine = false;
      mem_sawAVine = 0;
    } else mem_sawAVine++;
	}
  
  resetMap(rows,cols,map);
  delwin(wnd);
  delwin(wnd2);


  endwin();
	return 0;
}