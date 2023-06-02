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
	Item * item;
    int ID = (rand() % 3) + 1; // 1 - 2
	//int randomItem = rand() % 10;


	int randomItem = itemsEquilibrium(user);
	//int ID = 1;
    if (ID == 1) { // create armor
        char ch = '@';

        char name[10][20] = {
			"Leather armor",
			"Stone armor",
			"Iron armor",
			"Steel armor",
			"Gold armor",
			"Tiago's armor",
			"Emerald armor",
			"Jhonny's armor",
			"Pedro's armor",
			"Monix's armor"
		};

		char buffDescription[10][75] = {
			"Useful protection against cuts, +3 defense (x3 floor)",
			"Simple protection against cuts, +5 defense (x3 floor)",
			"Good protection against sharp blades, +10 defense",
			"Excelent protection against any threat, +12 defense",
			"The beauty of this armor gives you strength, +20 defense",
			"Carequinha armor, +30 defense (x3 floor)",
			"Perfect protection, +45 defense (x3 floor)",
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
			"Corte seu cabelo na Navalha do Fidalgo",
			"None",
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
    } else if (ID == 2) {
		char ch = '|';

        char name[10][20] = {
			"Wood sword",
			"Stone sword",
			"Iron sword",
			"Steel sword",
			"Flame sword",
			"Light saber",
			"Nano saber",
			"Quantum sword",
			"God's sword",
			"Monix's sword"
		};

		char buffDescription[10][75] = {
			"Usefull sword, +3 damage",
			"You can rock some monsters with this, +5 damage",
			"Medieval era sword, +10 damage",
			"Good medieval era sword, +12 damage",
			"The heat of this sword is dangerous, +20 damage",
			"May the force be with you, +30 damage",
			"Early's technological sword, +45 damage",
			"Advanced tech sword, +60 damage",
			"Judgement sword, +75 damage",
			"A espada mais util do jogo, +100 damage"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"Essa espada veio dos primordios da antiguidade, a espada dos deuses, todos desejam-na, mas somente os mais uteis possuem-na."
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
			60 + (user->dungeonFloor * 3),
			75 + (user->dungeonFloor * 3),
			100 + (user->dungeonFloor * 5)
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
	} else {
		char ch = 'O';

        char name[10][20] = {
			"Unlucky ring",
			"Lucky ring",
			"Blessing ring",
			"Curse ring",
			"Darkness ring",
			"Brightness ring",
			"Life ring",
			"Hard ring",
			"Blindness ring",
			"Developer's ring"
		};

		char buffDescription[10][75] = {
			"Monsters intelligence increased",
			"Your chances for better items increased",
			"Monsters deal less damage",
			"Monsters deal more damage",
			"Your vision decreased",
			"Your vision increased",
			"+100 Life points",
			"-25 Life points",
			"Just 3 blocks can be spotted in your radius :/",
			"Press <v> for debug mode"
		};

		char lore[10][200] = {
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None",
			"None"
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
			1,
			-1,
			10,
			-5,
			-4, // decrease 4 radius
			4, // increase 4 radius
			100,
			-25,
			3,
			1
		};

		item = createItem(ch,name[randomItem],buffDescription[randomItem],lore[randomItem],rarity[randomItem],buff[randomItem],user->dungeonFloor,ID);
	}


	return item;
}