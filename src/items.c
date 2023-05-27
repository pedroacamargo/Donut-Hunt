#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>
#include "main.h"


Item * createItem(char ch, char *name, char *buffDescription, char *lore, int rarity, int buff, int level) {
    Item * item = malloc(sizeof(Item));

    item->rarity = rarity;
    item->ch = ch;
    item->buff = buff;
    item->level = level;

    item->buffDescription = strdup(buffDescription);
    item->lore = strdup(lore);
    item->name = strdup(name);
    
    return item;
}