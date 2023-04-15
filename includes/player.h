#ifndef __PLAYER_H__
#define __PLAYER_H_

Player * playerSetUp();
void getInput(int key, Player * user);
void playerMove(int y, int x, Player * user);

#endif