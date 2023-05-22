#ifndef __MAIN_MENU_H_
#define __MAIN_MENU_H_

enum {START_GAME, GAME_HELP, QUIT_GAME};

int inicio();

int help();

int menu(int n_escolhas, char *escolhas[]);

#endif