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


void gameLoop() {
  initscr();
	Player * user;
	srand(time(NULL));
  start_color();

  // Get screen dimensions
	int cols, rows, maxRooms = 30;
	getmaxyx(stdscr, rows, cols);

  init_color(96,529,372,529);
  init_color(117,529,843,1000);
  init_color(237,227,227,227);
  init_color(138,686,529,529);
  init_color(232,31,31,31);
  init_color (58,372,372,0);
  init_color(119,529,1000,372);
  /* Colors */
  init_pair(1, COLOR_WHITE, COLOR_BLACK);  // cor do que é visivel
  init_pair(2, COLOR_BLUE, COLOR_BLACK); // cor do que foi visto
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // cor menu stats
  init_pair(4, COLOR_GREEN, COLOR_BLACK); 
  init_pair(6, COLOR_CYAN, COLOR_BLACK);
  init_pair(7,96,COLOR_BLACK); // Plum 4
  init_pair(8,117,COLOR_BLACK); // SkyBlue 1
  init_pair(9,237,COLOR_BLACK); // dark grey
  init_pair(10,138,COLOR_BLACK); // Salmon
  init_pair(5,COLOR_RED,COLOR_BLACK); // grey Skeleton
  init_pair(11,58,COLOR_BLACK); // orange dragon
  init_pair(12,119,COLOR_BLACK); // light green goblins
  

  /* Player memory */
  int mem_sawAVine = 0;
  int mem_sawAMonster = 0;
  int mem_erosion = 0;
  int mem_sawAnItem = 0;
  int erosion = 0; // Tiles that were updated during erosion

	// Variables
	int firstPosition = rand() % 12 + 1; // first testing position for the room creation
  int colsWnd1 = cols - 30; // COLS NUMBER MAIN WINDOW
  int colsWnd2 = 30; // COLS NUMBER MENU WINDOW
  int cols2 = cols - colsWnd2; // START POSITION MENU WINDOW
  int linesActions = 1; // Number of lines already used in the actions menu | 1 due to the welcome message
  bool sawAVine = false; // If the user saw a vine
  bool sawAMonster = false; // If the user saw a monster
  bool isSideMenuOpened = false;
  bool sawAnItem = false;
  WINDOW * wnd = newwin(rows, cols2, 0, 0); // game window
  WINDOW * wnd2 = newwin(rows, 50, 0, cols2); // menu window
  Monster monsters[maxRooms * 3];
  int monstersAmount = 0;
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
  Tile ** map = createMap(wnd,maxRooms,firstPosition,cols,rows,user,monsters,&monstersAmount);
  updatePlayerPosition(user,cols,rows,map,&linesActions,&sawAVine, &sawAMonster, &sawAnItem);

	// game loop
	while(1) {
    printMap(rows,cols,map,user);
		int ch = getch();
    if (ch == 'q' || ch == 'Q') break;
    else if (ch == 'y' || ch == 'Y') {
      sideMenuLoop(&isSideMenuOpened,user,cols,rows,map);
    } else if (!isSideMenuOpened) {
		  map = getInput(ch, user,cols,rows, map,&linesActions, &sawAVine, &sawAMonster, &sawAnItem,firstPosition,maxRooms,wnd, monsters, &monstersAmount);
      moveMonsters(map,user, cols, rows, monsters, monstersAmount); // move os monstros
      
    }

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

    if (mem_sawAnItem == 50) {
      sawAnItem = false;
      mem_sawAnItem = 0;
    } else mem_sawAnItem++;
	}
  
  resetMap(rows,cols,map,user);
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