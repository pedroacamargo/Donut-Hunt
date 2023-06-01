#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "main.h"

/*
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
*/

Item * createRandomItem(Player * user) {
    //int ID = (rand() % 3) + 1; // 1 - 3
	//int randomItem = rand() % 10;


	int randomItem = itemsEquilibrium(user);
	int ID = 1;
	Item * item;
    if (ID == 1) { // create armor
        char ch = '@';

        char name[10][20] = {
			"Leather armor",
			"Stone armor",
			"Iron armor",
			"Gold armor",
			"Emerald armor",
			"Steel armor",
			"Tiago's armor",
			"Jhonny's armor",
			"Pedro's armor",
			"Monix's armor"
		};

		char buffDescription[10][75] = {
			"Useful protection against cuts, +3 defense (x3 floor)",
			"Simple protection against cuts, +5 defense (x3 floor)",
			"Good protection against sharp blades, +10 defense",
			"The beauty of this armor gives you strength, +12 defense",
			"Excelent protection against any threat, +20 defense",
			"Perfect protection, +30 defense (x3 floor)",
			"Carequinha armor, +45 defense (x3 floor)",
			"Pivot armor, +50 defense (x3 floor)",
			"Brazilian armor, +75 defense (x3 floor)",
			"A armadura mais util do jogo, +100 defense (x5 floor)"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"Corte seu cabelo na Navalha do Fidalgo",
			"None",
			"None",
			"Essa armadura veio dos primordios da antiguidade, a armadura dos deuses, todos desejam-na, mas somente os mais uteis possuem-na."
		};

		int rarity[10] = {
			1,
			1,
			2,
			2,
			3,
			3,
			4,
			4,
			5,
			5
		};

		int buff[10] = {
			3 + (user->dungeonFloor * 3),
			5 + (user->dungeonFloor * 3),
			10 + (user->dungeonFloor * 3),
			12 + (user->dungeonFloor * 3),
			20 + (user->dungeonFloor * 3),
			30 + (user->dungeonFloor * 3),
			45 + (user->dungeonFloor * 3),
			50 + (user->dungeonFloor * 3),
			75 + (user->dungeonFloor * 3),
			100 + (user->dungeonFloor * 5)
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
    }
	return item;
}