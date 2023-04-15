#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
#include "main.h"

int main() {
	Player * user;
	WINDOW *wnd = initscr();


	// Window Setup
	int cols, rows;
	getmaxyx(wnd,rows,cols);
	raw();
	noecho();
	keypad(stdscr,true);
	refresh();
	clear();
	
	// player and first map setups
	user = playerSetUp();
	createMap(&cols,&rows,user);
	updatePlayerPosition(user);

	// game loop
	while(1) {
		int ch = getch();
		getInput(ch, user, &cols, &rows);
	}

	return 0;
}