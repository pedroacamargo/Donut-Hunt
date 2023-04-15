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

	user = playerSetUp();

	createMap(&cols,&rows,user);
	
	mvprintw(user->pos.y,user->pos.x,"@");
  move(user->pos.y,user->pos.x);

	while(1) {
		int ch = getch();

		getInput(ch,user);

		switch (ch) {
			
		}
	}

	return 0;
}