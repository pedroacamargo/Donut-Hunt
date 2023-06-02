#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

/*
 *
 *   X coords
 *  Slot1 -> 4
 *  Slot2 -> 16
 *  Slot3 -> 28
 *  Slot4 -> 40
 *  Slot5 -> 52
 *  Slot6 -> 64
 *  Slot7 -> 76
 *  Slot8 -> 88
 * 
 * 
*/

void openBackpack(int cols, int rows, Tile ** map, Player * user) {
    WINDOW * popUp = newwin(30, 100, rows/2 - rows/4, cols/2 - cols/4); // +30 because of the sideMenu window width = 30
    wattron(popUp,COLOR_PAIR(3));
    box(popUp, 0, 0);
    mvwprintw(popUp,0,2,"Backpack");
    mvwprintw(popUp,28,2,"Press (q) to close the backpack");
    wattroff(popUp,COLOR_PAIR(3));

    int y = 2, x = 4;
    int height = 6;
    int width = 8;
    int currentSlot = 1;

    // Create the slots
    for (int i = 0; i < 8; i++) {
        buildSlot(height,width,y,x,popUp);
        x += width + 4;
    }

    char ch = wgetch(popUp);
    while (ch != 'q') {
        ch = wgetch(popUp);
        selectSlotBackpack(ch,&currentSlot,popUp);
    }
    printMap(rows,cols,map,user);

    endwin();
    delwin(popUp);
}

void buildSlot(int height, int width, int y, int x, WINDOW * popUp) {
    for (int i = y; i < height + y; i++) {
        mvwaddch(popUp,i,x,'#');
        mvwaddch(popUp,i,x + width,'#');
    }

    for (int i = x; i <= width + x; i++) {
        mvwaddch(popUp,y,i,'#');
        mvwaddch(popUp,y + height,i,'#');
    }
}

void selectSlotBackpack(char ch, int * currentSlot, WINDOW * popUp) {
    int y = 9;
    int jump = 12;
    int x = (*currentSlot * jump) + 4;

    if (ch == 'D' || ch == 'd') {
        *currentSlot += 1;
    }
    else if (ch == 'A' || ch == 'a') {
        *currentSlot -= 1;
    }

    mvwaddch(popUp,y,x + 4,'^');
}

/*
void buildwCheckBox(int cols, int y, char str[], WINDOW * wnd) {
  for (int i = y; i < y+5; i++) 
    for (int j = cols + 5; j < cols + 12; j++) {
      if (i == y || i == y+4 || j == cols + 5 || j == cols + 11) mvwprintw(wnd,i,j,"#");
    }

  attron(COLOR_PAIR(3));
  mvwprintw(wnd,y+2, cols + 13, "%s",str);
  attroff(COLOR_PAIR(3));
}

*/
