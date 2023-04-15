#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct Position {
	double x;
	double y;
} Position;

typedef struct Player {
	Position pos;
	int life;
} Player;

#endif