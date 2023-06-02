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

typedef struct Item {
	char ch;
	char *name;
	char *buffDescription;
	char *lore;

	int rarity;
	int buff;
	int level;
	int ID;
} Item;


typedef struct Monster
{
	Position pos;
	int color;
	int life;
	char type;
	int damage;
} Monster;

typedef struct {
	char ch;
	int color;
	bool walkable;
	bool transparent;  // usado para a função lineOfSight
	bool visible; // usado para o makeFOV
	bool seen;  // usado para o clearFOV
	Item * item;
	Monster monster;
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
	Position itemPos; // Random Item Position
	int vinesWidth; // amounts of vines in a room
	Monster monster;
} NormalRoom;
// Normal room stats


typedef struct Inventory {
	Item * armorSlot;
	Item * swordSlot;
	Item * specialSlot;
} Inventory;


typedef struct Player
{
	Position pos;
	int color;
	int life;
	int damage;
	int armor;
	int monstersKilled;
	int dungeonFloor;
	Inventory * activeItems;
} Player;
// Player stats

//variaveis globais 
extern Player* user;
extern Monster* monster;

#endif