#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef struct Position {
	int x;
	int y;
} Position;
// Position in X/Y axis for player, rooms...


typedef struct NormalRoom {
	Position pos;
	int height;
	int width;
	int doors;
	// int loot; 1-rara 2-comum 
	// int monsters;
	// int difficulty;
} NormalRoom;
// Normal room stats


typedef struct Player {
	Position pos;
	int life;
	// floor
} Player;
// Player stats


#endif