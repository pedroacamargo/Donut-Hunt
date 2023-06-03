#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

/*
 *
 *   X coords
 *  Slot1 -> 4
 *  Slot2 -> 16
 *  Slot3 -> 28
 *  Slot4 -> 40
 *  Slot5 -> 52
 *  Slot6 -> 64
 *  Slot7 -> 76
 *  Slot8 -> 88
 * 
 *            
 * 
*/

void openBackpack(int cols, int rows, Tile ** map, Player * user) {
    WINDOW * popUp = newwin(30, 100, rows/2 - rows/4, cols/2 - cols/4); // +30 because of the sideMenu window width = 30
    wattron(popUp,COLOR_PAIR(3));
    box(popUp, 0, 0);
    mvwprintw(popUp,0,2,"Backpack");
    mvwprintw(popUp,28,2,"(Q) - Close Backpack | (Enter) - Equip item | (T) - Destroy item ");

    for (int i = 1; i < 99; i++) mvwaddch(popUp,11,i,'_');
    for (int i = 1; i < 99; i++) mvwaddch(popUp,27,i,'-');
    for (int i = 12; i < 27; i++) mvwaddch(popUp,i,30,'|');

    wattroff(popUp,COLOR_PAIR(3));

    int y = 2, x = 4;
    int height = 6;
    int width = 8;
    int currentSlot = 0;

    // Create the slots
    for (int i = 0; i < 8; i++) {
        buildSlot(height,width,y,x,popUp,1);
        x += width + 4;
    }
    updateBackpackSlots(user,popUp);
    updateItemStatsBackpack(user,&currentSlot,popUp);
    wattron(popUp,COLOR_PAIR(5));
    mvwaddch(popUp,10,8,'^');
    wattroff(popUp,COLOR_PAIR(5));

    buildSlot(height,width,y,4,popUp,2);
    char ch = wgetch(popUp);
    while (ch != 'q') {
        selectSlotBackpack(ch,&currentSlot,popUp,user, cols);
        updateItemStatsBackpack(user,&currentSlot,popUp);
        ch = wgetch(popUp);
    }
    printMap(rows,cols,map,user);

    endwin();
    delwin(popUp);
}

void buildSlot(int height, int width, int y, int x, WINDOW * popUp, int color) {
    wattron(popUp,COLOR_PAIR(color));
    for (int i = y; i < height + y; i++) {
        mvwaddch(popUp,i,x,'#');
        mvwaddch(popUp,i,x + width,'#');
    }

    for (int i = x; i <= width + x; i++) {
        mvwaddch(popUp,y,i,'#');
        mvwaddch(popUp,y + height,i,'#');
    }
    wattroff(popUp,COLOR_PAIR(color));
}

void selectSlotBackpack(char ch, int * currentSlot, WINDOW * popUp, Player * user, int cols) {
    int y = 10;
    int height = 6;
    int width = 8;
    int jump = width + 4;
    int x = (*currentSlot * jump) + 4;

    if ((ch == 'D' || ch == 'd') && *currentSlot < 7) {
        mvwprintw(popUp,y,x + 4,"   ");
        *currentSlot += 1;
    } else if ((ch == 'A' || ch == 'a') && *currentSlot >= 1) {
        mvwprintw(popUp,y,x + 4,"   ");
        *currentSlot -= 1;
    } else if (ch == 10) {

        /* Equip Items */

        if (*currentSlot == 0 && user->activeItems->backpack->slot1) {
            updatePlayerStats(user->activeItems->backpack->slot1,user);
            equipItem(cols,user->activeItems->backpack->slot1,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 1 && user->activeItems->backpack->slot2) {
            updatePlayerStats(user->activeItems->backpack->slot2,user);
            equipItem(cols,user->activeItems->backpack->slot2,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 2 && user->activeItems->backpack->slot3) {
            updatePlayerStats(user->activeItems->backpack->slot3,user);
            equipItem(cols,user->activeItems->backpack->slot3,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 3 && user->activeItems->backpack->slot4) {
            updatePlayerStats(user->activeItems->backpack->slot4,user);
            equipItem(cols,user->activeItems->backpack->slot4,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 4 && user->activeItems->backpack->slot5) {
            updatePlayerStats(user->activeItems->backpack->slot5,user);
            equipItem(cols,user->activeItems->backpack->slot5,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 5 && user->activeItems->backpack->slot6) {
            updatePlayerStats(user->activeItems->backpack->slot6,user);
            equipItem(cols,user->activeItems->backpack->slot6,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 6 && user->activeItems->backpack->slot7) {
            updatePlayerStats(user->activeItems->backpack->slot7,user);
            equipItem(cols,user->activeItems->backpack->slot7,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 7 && user->activeItems->backpack->slot8) {
            updatePlayerStats(user->activeItems->backpack->slot8,user);
            equipItem(cols,user->activeItems->backpack->slot8,user,*currentSlot);
            updateBackpackSlots(user,popUp);
        }
    } else if (ch == 't' || ch == 'T') {

        /* Destroy items */

        if (*currentSlot == 0 && user->activeItems->backpack->slot1) {
            free(user->activeItems->backpack->slot1);
            user->activeItems->backpack->slot1 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 1 && user->activeItems->backpack->slot2) {
            free(user->activeItems->backpack->slot2);
            user->activeItems->backpack->slot2 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 2 && user->activeItems->backpack->slot3) {
            free(user->activeItems->backpack->slot3);
            user->activeItems->backpack->slot3 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 3 && user->activeItems->backpack->slot4) {
            free(user->activeItems->backpack->slot4);
            user->activeItems->backpack->slot4 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 4 && user->activeItems->backpack->slot5) {
            free(user->activeItems->backpack->slot5);
            user->activeItems->backpack->slot5 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 5 && user->activeItems->backpack->slot6) {
            free(user->activeItems->backpack->slot6);
            user->activeItems->backpack->slot6 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 6 && user->activeItems->backpack->slot7) {
            free(user->activeItems->backpack->slot7);
            user->activeItems->backpack->slot7 = NULL;
            updateBackpackSlots(user,popUp);
        } else if (*currentSlot == 7 && user->activeItems->backpack->slot8) {
            free(user->activeItems->backpack->slot8);
            user->activeItems->backpack->slot8 = NULL;
            updateBackpackSlots(user,popUp);
        }
    }

    y = 2;
    buildSlot(height,width,y,x,popUp,1); // change color to white
    
    wattron(popUp,COLOR_PAIR(5));
    y = 10;
    x = (*currentSlot * jump) + 4;
    mvwaddch(popUp,y,x + 4,'^');
    wattroff(popUp,COLOR_PAIR(5));
    
    y = 2;
    buildSlot(height,width,y,x,popUp,2); // change color to blue
}

void updateBackpackSlots(Player * user, WINDOW * popUp) {
    int jump = 12;
    int x = 8;
    if (user->activeItems->backpack->slot1 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot1->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot1->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot1->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot2 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot2->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot2->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot2->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot3 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot3->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot3->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot3->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot4 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot4->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot4->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot4->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot5 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot5->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot5->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot5->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot6 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot6->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot6->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot6->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot7 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot7->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot7->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot7->rarity));
    }
    x += jump;
    if (user->activeItems->backpack->slot8 == NULL) {
        mvwaddch(popUp,5,x,'X');
    } else {
        wattron(popUp,COLOR_PAIR(user->activeItems->backpack->slot8->rarity));
        mvwaddch(popUp,5,x,user->activeItems->backpack->slot8->ch);
        wattroff(popUp,COLOR_PAIR(user->activeItems->backpack->slot8->rarity));
    }
}

void updateItemStatsBackpack(Player * user, int * currentSlot, WINDOW * popUp) {
    switch (*currentSlot) {
        case 0:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot1, popUp);
            printItem(user->activeItems->backpack->slot1, popUp);
            break;
        case 1:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot2, popUp);
            printItem(user->activeItems->backpack->slot2, popUp);
            break;
        case 2:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot3, popUp);
            printItem(user->activeItems->backpack->slot3, popUp);
        break;
        case 3:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot4, popUp);
            printItem(user->activeItems->backpack->slot4, popUp);
            break;
        case 4:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot5, popUp);
            printItem(user->activeItems->backpack->slot5, popUp);
            break;
        case 5:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot6, popUp);
            printItem(user->activeItems->backpack->slot6, popUp);
            break;    
        case 6:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot7, popUp);
            printItem(user->activeItems->backpack->slot7, popUp);
            break;    
        case 7:
            cleanMenuBackpack(popUp);
            printArt(user->activeItems->backpack->slot8, popUp);
            printItem(user->activeItems->backpack->slot8, popUp);
            break;    
        default:
            break;
    }
}

void printItem(Item * item, WINDOW * popUp) {
    if (item) {
        mvwprintw(popUp,14,35,"Name: %s",item->name);
        mvwprintw(popUp,15,35,"Rarity: %d",item->rarity);
        mvwprintw(popUp,16,35,"Buffs: %s",item->buffDescription);
        mvwprintw(popUp,17,35,"Level: %d",item->level);
    } else {
        mvwprintw(popUp,14,35,"Name: ");
        mvwprintw(popUp,15,35,"Rarity: ");
        mvwprintw(popUp,16,35,"Buffs: ");
        mvwprintw(popUp,17,35,"Level: ");
    }
}

void printArt(Item * item, WINDOW * popUp) {
    if (item) {
        if (item->ch == '@') {
            wattron(popUp,COLOR_PAIR(item->rarity));
            mvwprintw(popUp,15,9," .d8888888b.  ");
            mvwprintw(popUp,16,9,"d88P.   .Y88b ");
            mvwprintw(popUp,17,9,"888  d8b  888 ");
            mvwprintw(popUp,18,9,"888  888  888 ");
            mvwprintw(popUp,19,9,"888  888bd88P ");
            mvwprintw(popUp,20,9,"888  Y8888P'  ");
            mvwprintw(popUp,21,9,"Y88b.     .d8 ");
            mvwprintw(popUp,22,9,"  Y88888888P  ");
            wattroff(popUp,COLOR_PAIR(item->rarity));
        } else if (item->ch == '|') {
            wattron(popUp,COLOR_PAIR(item->rarity));
            mvwprintw(popUp,14,12,"  ,---, ");
            mvwprintw(popUp,15,12,",---.'| ");
            mvwprintw(popUp,16,12,"|   | : ");
            mvwprintw(popUp,17,12,"|   | : ");
            mvwprintw(popUp,18,12,"'   : ' ");
            mvwprintw(popUp,19,12,":   | | ");
            mvwprintw(popUp,20,12,"|   ' : ");
            mvwprintw(popUp,21,12,";   ; | ");
            mvwprintw(popUp,22,12,";   : ; ");
            mvwprintw(popUp,23,12,"|   ,/  ");
            mvwprintw(popUp,24,12,"'---'   ");
            wattroff(popUp,COLOR_PAIR(item->rarity));
        } else if (item->ch == 'O') {
            wattron(popUp,COLOR_PAIR(item->rarity));
            mvwprintw(popUp,12,8,"    ,----..    ");
            mvwprintw(popUp,13,8,"   /   /   \\   ");
            mvwprintw(popUp,14,8,"  /   .     :  ");
            mvwprintw(popUp,15,8," .   /   ;.  \\ ");
            mvwprintw(popUp,16,8,".   ;   /  ` ; ");
            mvwprintw(popUp,17,8,";   |  ; \\ | ");
            mvwprintw(popUp,18,8,";   |  ; \\ ; | ");
            mvwprintw(popUp,19,8,"|   :  | ; | ' ");
            mvwprintw(popUp,20,8,".   |  ' ' ' : ");
            mvwprintw(popUp,21,8,"'   ;  \\; /  | ");
            mvwprintw(popUp,22,8," \\   \\  ',  /  ");
            mvwprintw(popUp,23,8,"  ;   :    /   ");
            mvwprintw(popUp,24,8,"   \\   \\ .'    ");
            mvwprintw(popUp,25,8,"    `---`      ");
            wattroff(popUp,COLOR_PAIR(item->rarity));
        }
    } else {
        cleanMenuBackpack(popUp);
        wattron(popUp,COLOR_PAIR(10));
        mvwprintw(popUp,12,8," ,--,     ,--,  ");
        mvwprintw(popUp,13,8," |'. \\   / .`| ");
        mvwprintw(popUp,14,8," ; \\ `\\ /' / ;  ");
        mvwprintw(popUp,15,8," `. \\  /  / .'  ");
        mvwprintw(popUp,16,8,"  \\  \\/  / ./   ");
        mvwprintw(popUp,17,8,"   \\  \\.'  /   ");
        mvwprintw(popUp,18,8,"   \\  \\.'  /    ");
        mvwprintw(popUp,19,8,"    \\  ;  ;     ");
        mvwprintw(popUp,20,8,"   / \\  \\  \\    ");
        mvwprintw(popUp,21,8,"  ;  /\\  \\  \\   ");
        mvwprintw(popUp,22,8,"  ;  /\\  \\  \\   ");
        mvwprintw(popUp,23,8,"./__;  \\  ;  \\  ");
        mvwprintw(popUp,24,8,"|   : / \\  \\  ; ");
        mvwprintw(popUp,25,8,";   |/   \\  ' | ");
        mvwprintw(popUp,26,8,"`---'     `--`  ");
        wattroff(popUp,COLOR_PAIR(10));
    }
}

void cleanMenuBackpack(WINDOW * popUp) {
    for (int i = 1; i < 30; i++) {
        for (int j = 12; j < 27; j++) {
            mvwaddch(popUp,j,i,' ');
        }
    }

    for (int j = 31; j < 99; j++) {
        for (int i = 12; i < 27; i++) {
            mvwaddch(popUp,i,j,' ');
        }
    }
}

void equipItem(int cols, Item * item, Player * user, int currentSlot) {
    if (currentSlot == 0) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot1 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot1 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot1 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 1) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot2 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot2 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot2 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 2) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot3 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot3 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot3 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 3) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot4 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot4 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot4 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 4) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot5 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot5 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot5 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 5) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot6 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot6 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot6 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 6) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot7 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot7 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot7 = temp;
            updateStats(user,cols);
        }
    } else if (currentSlot == 7) {
        int ID = item->ID;
        if (ID == 1) {
            Item * temp = user->activeItems->armorSlot;
            user->activeItems->armorSlot = item;
            user->activeItems->backpack->slot8 = temp;
            updateStats(user,cols);    
        } else if (ID == 2) {
            Item * temp = user->activeItems->swordSlot;
            user->activeItems->swordSlot = item;
            user->activeItems->backpack->slot8 = temp;
            updateStats(user,cols);
        } else if (ID == 3) {
            Item * temp = user->activeItems->specialSlot;
            user->activeItems->specialSlot = item;
            user->activeItems->backpack->slot8 = temp;
            updateStats(user,cols);
        }
    }
}