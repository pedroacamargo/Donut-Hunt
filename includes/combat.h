#ifndef __COMBAT_H__
#define __COMBAT_H__

int isAdjacent(Position pos1, Position pos2);

void combat(Player* user, Monster* monster);

void waitForCombat(Player* user, Monster* monster);

#endif