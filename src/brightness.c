#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "main.h"

void makeFov (Player *user, int cols, int rows, Tile** map){
    int y, x , raio = 3, distancia;
    Position target; // usado para pegar as coordenadas do y e do x

    map[user->pos.y][user->pos.x].visible = true;
    map[user->pos.y][user->pos.x].seen = true;

    for (y = user->pos.y - raio; y < user->pos.y + raio; y++){ // verifica nas coordenas y tudo o que está à sua volta num certo raio
        for (x = user->pos.x - raio; x < user->pos.x + raio; x++){ //  verifica nas coordenas x tudo o que está à sua volta num certo raio
            target.y = y;
            target.x = x;
            distancia = getDistance(user->pos, target);

           if (distancia < raio){
            if (InMap (y, x, cols, rows) && lineOfSight(user->pos, target, map)){
                map[y][x].visible = true;
                map[y][x].seen = true;
            }
           }
        }
    }
}

int getDistance (Position origin, Position target){
    double y, x;
    int distancia;
    y = target.y - origin.y;
    x = target.x - origin.x;
    distancia = floor(sqrt((x * x) + (y * y)));

    return distancia;
} 

bool InMap(int y , int x, int cols , int rows){
    
    if ((y > 0 && y < rows - 1) && (x > 0 && x < cols - 1)){
        return true;
    }
    return false;
}

bool lineOfSight(Position origin, Position target, Tile** map)
{
    int y = origin.y;
    int x = origin.x;
    int abs_y = abs(target.y - origin.y);
    int abs_x = abs(target.x - origin.x);
    int sign_y = (origin.y < target.y) ? 1 : -1;
    int sign_x = (origin.x < target.x) ? 1 : -1;
    int error = abs_x - abs_y;

    while (x != target.x || y != target.y){
        if(!map[y][x].transparent){
            return false;
        }
        int error2 = error * 2;
        if (error2 > -abs_y){
            error -= abs_y;
            x += sign_x;
        }
        if (error2 < abs_x){
            error += abs_x;
            y += sign_y;
        }
    }
    return true;
}

void clearFov (Player * user, int cols, int rows, Tile** map){
    int y, x, raio = 5;

    for (y = user->pos.y - raio; y < user->pos.y + raio; y++ ){
        for (x = user->pos.x - raio; x < user->pos.x + raio; x++){
            if (InMap(y, x, cols, rows)) map[y][x].visible = false;
        }
    }
}
