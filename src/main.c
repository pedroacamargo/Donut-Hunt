#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "map.h"

int main() {
	Player * user;


	// Window Setup
	WINDOW *wnd = initscr();
	int cols, rows;
	getmaxyx(wnd,rows,cols);
	raw();
	noecho();
	keypad(stdscr,true);
	refresh();

	user = playerSetUp();

	createMap(&cols,&rows,user);
	
	mvprintw(user->playerY,user->playerX,"@");
	// st.playerX = middle[0];
	// st.playerY = middle[1];

	while(1) {
		int ch = getch();

		switch (ch) {
			case 'w':
				break;
			case 'q':
				refresh();
				endwin();
		}
	}

	return 0;
}