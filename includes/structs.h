#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define VISIBLE 1
#define SEEN 2

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
	bool transparent;  // usado para a função lineOfSight
	bool visible; // usado para o makeFOV
	bool seen;  // usado para o clearFOV
	char monster;
} Tile;

typedef struct NormalRoom
{
	/* Main stats */
	Position pos;
	int height;
	int width;
	Position door; // Door position
	char doorAxis; // x/y -> This is just to help in the hallway connection


	/* Room type section */
	int type; // Type 1 -> Normal room | Type 2 -> Circle room
	bool vine; // if true, use Vine rooms section

	/* Vine room section */
	Position vineCenter; // spread begining coords 
	int vinesWidth; // amounts of vines in a room

} NormalRoom;
// Normal room stats

typedef struct Player
{
	Position pos;
	int color;
	int life;
	int damage;
	int armor;
	int monstersKilled;
	int dungeonFloor;
} Player;
// Player stats

typedef struct Monster
{
	Position pos;
	int color;
	int life;
} Monster;

//variaveis globais 
extern Player* user;
extern Monster* monster;

#endif