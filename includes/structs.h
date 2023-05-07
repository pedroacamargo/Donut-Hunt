#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define VISIBLE_COlOR 1
#define SEEN_COLOR 2



typedef struct Position
{
	int x;
	int y;
} Position;
// Position in X/Y axis for player, rooms...

typedef struct {
	char ch;
	int color;
	bool walkable;
	bool transparent;  // usado para a função lineOfSight()
	bool visible; // usado para o makeFOV()
	bool seen;  // usado para o clearFOV()
} Tile;

typedef struct NormalRoom
{
	Position pos;
	int height;
	int width;
	Position door; // Door position
	char doorAxis; // x/y -> This is just to help in the hallway connection
	// int loot; 1-rara 2-comum
	// int monsters;
	// int difficulty;
} NormalRoom;
// Normal room stats

typedef struct Player
{
	Position pos;
	int color;
	int life;
	// floor
} Player;
// Player stats

//variaveis globais 
extern Player* user;


#endif