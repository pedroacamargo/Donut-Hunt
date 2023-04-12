#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "map.h"

void createMainRoom(int randomNumberY, int randomNumberX, int height, int width) {
for (int j = 0; j <= height; j++) {
    for (int i = 0; i <= width; i++) {
      if(i == 0 || j == 0) mvprintw(randomNumberY + j,randomNumberX + i,"#");
      else if (i == width || j == height) mvprintw(randomNumberY + j,randomNumberX + i,"#");
      else mvprintw(randomNumberY + j,randomNumberX + i,".");
    }
  }
}

int createMap(int *cols, int *rows, Player * user) {
  srand(time(NULL)); // create a random number based in local time
  int width = rand() % 10 + 10;
  int height = rand() % 10 + 4;

  int randomNumberY = (rand() % (*rows - height)) + 1;
  int randomNumberX = (rand() % (*cols - width)) + 1;


  printw("cols:%d rows:%d  \nx:%d y:%d",*cols, *rows, randomNumberX, randomNumberY); 
  createMainRoom(randomNumberY,randomNumberX,height,width);

  user->playerY = randomNumberY + (height/2);
  user->playerX = randomNumberX + (width/2);

  return 0;
}