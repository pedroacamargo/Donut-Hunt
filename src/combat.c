#include <stdlib.h>
#include <ncurses.h>
#include "main.h"
#include <math.h>

int isAdjacent(Position pos1, Position pos2) {
    // Verifica se a posição 1 está diretamente acima, abaixo, à esquerda, à direita ou nas diagonais da posição 2
    if ((pos1.x == pos2.x && abs(pos1.y - pos2.y) == 1) ||
        (pos1.y == pos2.y && abs(pos1.x - pos2.x) == 1) ||
        (abs(pos1.x - pos2.x) == 1 && abs(pos1.y - pos2.y) == 1)) {
        return 1;
    } else {
        return 0;
    }
}

void combat(Player* user, Monster* monster) {
    if (isAdjacent(user->pos, monster->pos)) {
        int playerTurn = rand() % 2; // Sorteia quem começa atacando

        while (user->life > 0 && monster->life > 0) {
            if (playerTurn) {
                //printf("É a vez do jogador atacar.\n");
                int attackRoll = user->damage + (rand() % 20 + 1);
                int defenseRoll = monster->armor + (rand() % 20 + 1);
                if (attackRoll > defenseRoll) {
                    int damage = user->damage + (rand() % 6 + 1) - monster->armor;
                    if (damage < 0) {
                        damage = 0;
                    }
                    //printf("O jogador acertou o monstro e causou %d de dano.\n", damage);
                    monster->life -= damage;
                } else {
                    //printf("O jogador errou o ataque.\n");
                }
                playerTurn = 0; // Passa a vez para o monstro
            } else {
                //printf("É a vez do monstro atacar.\n");
                int attackRoll = monster->attack + (rand() % 20 + 1);
                int defenseRoll = user->armor + (rand() % 20 + 1);
                if (attackRoll > defenseRoll) {
                    int damage = monster->damage + (rand() % 6 + 1) - user->armor;
                    if (damage < 0) {
                        damage = 0;
                    }
                    //printf("O monstro acertou o jogador e causou %d de dano.\n", damage);
                    user->life -= damage;
                } else {
                    //printf("O monstro errou o ataque.\n");
                }
                playerTurn = 1; // Passa a vez para o jogador
            }
        }

        if (user->life <= 0) {
            //printf("O jogador foi derrotado pelo monstro.\n");
            // Faz algo para reiniciar o jogo
        } else {
            //printf("O jogador derrotou o monstro.\n");
            user->monstersKilled++;
            // Faz algo para continuar o jogo
        }
    } else {
        //printf("Os jogadores não estão próximos o suficiente para lutar.\n");
    }
}


void waitForCombat(Player* user, Monster* monster) {
    char input;

    while (1) {
        // Lê a entrada do usuário
        input = getch();

        // Se o usuário pressionar K e o jogador e o monstro estiverem ao lado um do outro, inicia o combate
        if ((input == 'k' || input == 'K') && isAdjacent(user->pos, monster->pos)) {
            combat(user, monster);
            break;
        }
    }
}