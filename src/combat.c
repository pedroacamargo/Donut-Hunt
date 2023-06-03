#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

//p(0,0) = p2(2.2) =
int mode_combat(Tile** map, Monster* monster){
    //int distance_x = abs(player->pos.x - monster->pos.x); // 0 - 2 = 2
    //int distance_y = abs(player->pos.y - monster->pos.y);  // 0 - 2 = 2

    //int distancia = floor(sqrt((player->pos.x * player->pos.x) + (player->pos.y * player->pos.y)));

    if (map[monster->pos.y][monster->pos.x].visible) return 1; // Modo de combate 
    
    return 0;
}

void combat(Player* player, Monster* monster){

    while (player->life > 0 || monster->life > 0){
        
    }

}


