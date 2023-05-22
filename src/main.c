#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <menu.h>
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
Tile ** getInput(int key, Player *user, int cols, int rows, Tile ** map, int *linesActions, bool * sawAVine, bool * sawAMonster, int firstPosition, int maxRooms, WINDOW * wnd) {
  switch (key) {
  case 'w':
  case 'W':
  case 'A':
  case KEY_UP:
    map = playerMove(-1, 0, cols, rows, user, map, linesActions, sawAVine, sawAMonster, firstPosition, maxRooms, wnd);
    return map;
  case 'd':
  case 'C':
  case KEY_RIGHT:
    map = playerMove(0, +1, cols, rows, user, map, linesActions, sawAVine, sawAMonster, firstPosition, maxRooms, wnd);
    return map;
  case 'a':
  case 'D':
  case KEY_LEFT:
    map = playerMove(0, -1, cols, rows , user, map, linesActions, sawAVine, sawAMonster, firstPosition, maxRooms, wnd);
    return map;
  case 's':
  case 'S':
  case 'B':
  case KEY_DOWN:
    map = playerMove(+1, 0, cols, rows, user, map, linesActions, sawAVine, sawAMonster, firstPosition, maxRooms, wnd);
    return map;
  case 'v':
  case 'V':
    *linesActions = addActions(cols, "Map debugged", *linesActions,6);
    debugMap(map, cols, rows);
    // printMap(rows, cols, map);
    return map;
  default:
    break;
  }
  return map;
}


void gameLoop() {
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
  init_pair (5, COLOR_RED, COLOR_BLACK); // cor dos monstros
  init_pair(6, COLOR_CYAN, COLOR_BLACK);

  /* Player memory */
  int mem_sawAVine = 0;
  int mem_sawAMonster = 0;
  int mem_erosion = 0;
  int erosion = 0; // Tiles that were updated during erosion

	// Variables
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation
  int colsWnd1 = cols - 30; // COLS NUMBER MAIN WINDOW
  int colsWnd2 = 30; // COLS NUMBER MENU WINDOW
  int cols2 = cols - colsWnd2; // START POSITION MENU WINDOW
  int linesActions = 1; // Number of lines already used in the actions menu | 1 due to the welcome message
  bool sawAVine = false; // If the user saw a vine
  bool sawAMonster = false; // If the user saw a monster
  WINDOW * wnd = newwin(rows, cols2, 0, 0); // game window
  WINDOW * wnd2 = newwin(rows, 50, 0, cols2); // menu window

	// Setup ncurses window in CLI
	windowSetUp(wnd, wnd2);
  createMenu(cols2,rows);
  user = playerSetUp();
  cols = colsWnd1;
  updateStats(user,cols);

  /* Debug */
  // mvprintw(0,0,"cols:%d, rows:%d",cols,rows);
  // getch();

  // create the whole map
  Tile ** map = createMap(wnd,maxRooms,firstPosition,cols,rows,user);
  spawnMonster(map, cols, rows);
  updatePlayerPosition(user,cols,rows,map,&linesActions,&sawAVine, &sawAMonster);
    
	// game loop
	while(1) {
    printMap(rows,cols,map);
		int ch = getch();
    if (ch == 'q' || ch == 'Q') break;
		map = getInput(ch, user,cols,rows, map,&linesActions, &sawAVine, &sawAMonster,firstPosition,maxRooms,wnd);
    moveMonsters(map, cols, rows); // move os monstros

    /* Player memory */
    if (mem_sawAVine == 20) {
      sawAVine = false;
      mem_sawAVine = 0;
    } else mem_sawAVine++;

    if (mem_sawAMonster == 20) {
      sawAMonster = false;
      mem_sawAMonster = 0;
    } else mem_sawAMonster++;

    if (mem_erosion == 50) {
      erosion = createErosion(map,cols,rows);
      linesActions = addActionsWithData(cols,"Map erosion updated",erosion,linesActions,4);
      mem_erosion = 0;
    } else mem_erosion++;
	}
  
  resetMap(rows,cols,map);
  delwin(wnd);
  delwin(wnd2);

}



void menuLoop() {
  int escolha;
  char *escolhas[] = {"Play", "Instructions", "Quit"};

  while (true) {
    escolha = menu(3, escolhas);

    switch(escolha) {
      case START_GAME :
        gameLoop();
        clear();
        break;
      
      case GAME_HELP :
        help();
        clear();
        break;
      
      case QUIT_GAME:
        return;
        break;

    }
  }
}




int main() {


  inicio();
  

  menuLoop();


  endwin();
	return 0;
}