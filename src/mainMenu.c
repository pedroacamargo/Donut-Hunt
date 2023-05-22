#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>
#include "main.h"

void closeMenu(int n_escolhas, MENU *menu, ITEM **itens) {

    unpost_menu(menu);
    free_menu(menu);

    for(int i = 0; i < n_escolhas; i++) {
        free_item(itens[i]);
    }

    endwin();
}

int help() {

    curs_set(FALSE);
    raw();
	noecho();
	keypad(stdscr,true);
	refresh();
	clear();

    start_color();
    init_pair(3, COLOR_WHITE, COLOR_BLACK);

    int c;
    attron(COLOR_PAIR(3));
    mvprintw(0,0, "Help");
    while (( c = getch()) != 'q') {
        mvprintw(0,0,"Help");
    }
    attroff(COLOR_PAIR(3));

    return 0;
}



int inicio() {
    
    curs_set(FALSE);
    initscr(); //determina o tipo de terminal e inicializa todas as data structures do curses
    cbreak();
    noecho();
    keypad(stdscr, TRUE);


    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int c ;

    attron(COLOR_PAIR(1));
    mvprintw(16,70,"######    #####   ###  ##  ##   ##  ########          ### ###  ##   ##  ###  ##  ########");
    mvprintw(17,70," ## ###  ### ###   ### ##   #   ##  ## ## ##           ## ##    #   ##   ### ##  ## ## ##");
    mvprintw(18,70," ##  ##  ##   ##   ######  ##   ##     ##              ## ##   ##   ##   ######     ##   ");
    mvprintw(19,70," ##  ##  ##   ##   ## ###  ##   ##     ##              #####   ##   ##   ## ###     ##   ");
    mvprintw(20,70," ##  ##  ##   ##   ##  ##  ##   ##     ##              #  ##   ##   ##   ##  ##     ##   ");
    mvprintw(21,70," ## ###  ### ###   ##  ##  ### ###     ##              ## ##   ### ###   ##  ##     ##   ");
    mvprintw(22,70,"######    #####   ###  ##   #####     ####            ### ###   #####   ###  ##    ####  ");
 
    mvprintw(28,105, "Press ENTER");


    while((c = getch()) != 10) {
        mvprintw(16,70,"######    #####   ###  ##  ##   ##  ########          ### ###  ##   ##  ###  ##  ########");
        mvprintw(17,70," ## ###  ### ###   ### ##   #   ##  ## ## ##           ## ##    #   ##   ### ##  ## ## ##");
        mvprintw(18,70," ##  ##  ##   ##   ######  ##   ##     ##              ## ##   ##   ##   ######     ##   ");
        mvprintw(19,70," ##  ##  ##   ##   ## ###  ##   ##     ##              #####   ##   ##   ## ###     ##   ");
        mvprintw(20,70," ##  ##  ##   ##   ##  ##  ##   ##     ##              #  ##   ##   ##   ##  ##     ##   ");
        mvprintw(21,70," ## ###  ### ###   ##  ##  ### ###     ##              ## ##   ### ###   ##  ##     ##   ");
        mvprintw(22,70,"######    #####   ###  ##   #####     ####            ### ###   #####   ###  ##    ####  ");
        mvprintw(28,105, "Press ENTER");
    }
    attroff(COLOR_PAIR(1));
    clear();
    return 0;
}



int menu(int n_escolhas, char *escolhas[]) {
    ITEM **itens = malloc(sizeof(**itens) *n_escolhas); //criar um array de n_choices ponteiros para estruturas ITEM de tamanho variável, permite criar um menu com um número flexível de opções 
    WINDOW *menu_win; //criar a variável para a janela
    MENU *menu; //criar a variável para o menu
    ITEM *current; //criar uma variável para o item atual
    int index;



    //Iniciar o Curses

    curs_set(FALSE);
    initscr(); //determina o tipo de terminal e inicializa todas as data structures do curses
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLACK);


    //Criar os itens

    for(int i = 0; i < n_escolhas; i++) {
        itens[i] = new_item(escolhas[i], "");

    }

    itens[n_escolhas] = (ITEM *)NULL;




    //Criar o menu
    menu = new_menu((ITEM **)itens);



    //Criar a janela do menu

    menu_win = newwin(10, 40, 20, 105);
    keypad(menu_win, TRUE);


    set_menu_win(menu, menu_win);
    set_menu_sub(menu, derwin(menu_win, 6, 38, 3, 1));

    wattron(menu_win, COLOR_PAIR(2));



    set_menu_mark(menu, " >");


    refresh();
  



    


    post_menu(menu);
    wrefresh(menu_win);


    //MENU DRIVER


    while(TRUE) {
        int c;
        c = getch();

        switch(c) {
            case KEY_DOWN: 
                menu_driver(menu, REQ_DOWN_ITEM);
                wrefresh(menu_win);
                wattroff(menu_win, COLOR_PAIR(2));
                break;

            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                wrefresh(menu_win);
                wattroff(menu_win, COLOR_PAIR(2));
                break;

            case 10:
                current = current_item(menu);
                index = item_index(current);
                closeMenu(n_escolhas, menu, itens);
                wattroff(menu_win, COLOR_PAIR(2));
                return index;
        }
    }




    
}