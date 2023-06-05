#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "main.h"


Item * createItem(char ch, char *name, char *buffDescription, char *lore, int rarity, int buff, int level, int ID) {
    Item * item = malloc(sizeof(Item));

    item->rarity = rarity;
    item->ch = ch;
    item->buff = buff;
    item->level = level;
    item->ID = ID;

    item->buffDescription = strdup(buffDescription);
    item->lore = strdup(lore);
    item->name = strdup(name);
    
    return item;
}

void drawItem(NormalRoom room, Tile ** map, Player * user) {
    Item * item = createRandomItem(user);

    int randVines = rand() % 1000;
    int randNormal = rand() % 1000;
    int randomPosY = room.pos.y + 1 + (rand() % (room.height - 1));
    int randomPosX = room.pos.x + 1 + (rand() % (room.width - 1));

    // 70% chance to spawn an item inside vines
    // 30% chance to spawn an item inside a Normal room
    if (room.type == 2 && randVines < 700 && map[room.vineCenter.y][room.vineCenter.x].ch != '#') {
        map[room.vineCenter.y][room.vineCenter.x].item = item;
        map[room.vineCenter.y][room.vineCenter.x].ch = '?';
    } else if (room.type == 1 && randNormal < 300){
        map[randomPosY][randomPosX].item = item;        
        map[randomPosY][randomPosX].ch = '?';        
    }


    return;
}

void getItem(Tile ** map, Player * user, int cols) {
    Item * item = map[user->pos.y][user->pos.x].item;
    if (item) {
        if (item->ch == '@') {
            user->activeItems->armorSlot = item;
            updatePlayerStats(item,user);
            updateStats(user,cols);
        } else if (item->ch == '|') {
            user->activeItems->swordSlot = item;
            updatePlayerStats(item,user);
            updateStats(user,cols);
        } else if (item->ch == 'O') {
            user->activeItems->specialSlot = item;
            updatePlayerStats(item,user);
            updateStats(user,cols);
        }
    }
}

int itemsEquilibrium(Player * user) {
	int chance = rand() % 1000;
	if (user->dungeonFloor >= 1 && user->dungeonFloor < 4) {
		if (chance > 100) {
			return rand() % 4;
		} else if (chance <= 100) {
			return 4;
		}
	} else if (user->dungeonFloor >= 4 && user->dungeonFloor < 9) {
		if (chance > 100) {
			return (rand() % 4) + 2;
		} else if (chance <= 100) {
			return 7;
		}
	} else if (user->dungeonFloor >= 9 && user->dungeonFloor < 15) {
		if (chance > 100) {
			return (rand() % 4) + 4;
		} else if (chance <= 100) {
			return 8;
		}
	} else {
		return 9;
	}

	return 9;
}

void addItemBackpack(Backpack * backpack, Item * item) {
    if (backpack->slot1 == NULL) {
        backpack->slot1 = item;
    } else if (backpack->slot2 == NULL) {
        backpack->slot2 = item;
    } else if (backpack->slot3 == NULL) {
        backpack->slot3 = item;
    } else if (backpack->slot4 == NULL) {
        backpack->slot4 = item;
    } else if (backpack->slot5 == NULL) {
        backpack->slot5 = item;
    } else if (backpack->slot6 == NULL) {
        backpack->slot6 = item;
    } else if (backpack->slot7 == NULL) {
        backpack->slot7 = item;
    } else if (backpack->slot8 == NULL) {
        backpack->slot8 = item;
    } 
}