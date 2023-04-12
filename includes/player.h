#ifndef __PLAYER_H__
#define __PLAYER_H_

typedef struct Player {
	int life;
	double playerX;
	double playerY;
} Player;


Player * playerSetUp();
void getInput(int key, Player * user);
void playerMove(int y, int x, Player * user);

#endif