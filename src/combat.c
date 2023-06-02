/*#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>

int mode_combat(Player* player, Monster* monster){
    int distance_x = player->pos.x - monster->pos.x;
    int distance_y = player->pos.y - monster->pos.y;

    if(distance_x == 0 && distance_y == 0){  // verifica se o jogador está na mesma pos que o monstro
        return 1; // Modo de combate ativado
    }
    if(distance_x >= -1 && distance_x <= 1 && distance_y >= -1 && distance_y <= 1){
        return 1;  // Modo de combate ativado
    }
    return 0; // Modo de combate desativado
}



void combat(Player* player, Monster* monster){

    while (player->HP > 0 || monster->HP > 0){
        
    }

}
*/