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
  move(user->playerY,user->playerX);

	while(1) {
		int ch = getch();

		getInput(ch,user);

		switch (ch) {
			
		}
	}

	return 0;
}