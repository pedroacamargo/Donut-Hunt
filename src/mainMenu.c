#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <menu.h>
#include "main.h"

void closeMenu(int n_escolhas, MENU *menu, ITEM **itens) {

    unpost_menu(menu); //desativa/remove o menu da tela
    free_menu(menu); //libera a memória alocada para o menu

    for(int i = 0; i < n_escolhas; i++) {
        free_item(itens[i]); //liberar a memória alocada para cada item
    }

    endwin(); //encerra o modo janela do ncurses
}

int help() {

    raw();
	noecho();
    curs_set(FALSE);
	keypad(stdscr,true);
	refresh();
	clear();
    int x, y;
    getmaxyx(stdscr,y,x);

    start_color();
    init_pair(3, COLOR_WHITE, COLOR_BLACK);


    FILE *src;
    src = fopen ("data/instructions.txt", "r+");
    char text[28][26];
    



    int c;
    attron(COLOR_PAIR(3));

    for(int l = 0; l < 28; l++) {
        for(int i = 0; i < 26; i++) {
            char temp = (char) fgetc(src);
            text[l][i] = temp;

        }
      
    }

    fclose (src);

    for(int l = 0; l < 28; l++) {
        for(int i = 0; i < 26; i++) {
            mvprintw((y/2) - 12 + l, (x/2) - 12 +i, "%c", text[l][i]);
        
        }
    }
   
    while (( c = getch()) != 'q') {


    for(int l = 0; l < 28; l++) {
        for(int i = 0; i < 26; i++) {
            mvprintw((y/2) - 12 + l, (x/2) - 12 + i, "%c", text[l][i]);
        }
    }
    }
    attroff(COLOR_PAIR(3));


    return 0;
}



int inicio() {
    

    initscr(); //determina o tipo de terminal e inicializa todas as data structures do curses
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);

    int x,y;
    getmaxyx(stdscr, y,x);




    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    int c ;

    FILE *src;
    src = fopen("data/title.txt", "r+");
    char title[7][61];

    for(int l = 0; l < 7; l++) {
        for(int i = 0; i < 61; i++) {
            char temp = (char) fgetc(src);
            title[l][i] = temp;
        }
    }
    fclose(src);

    


    attron(COLOR_PAIR(1));
    
    for(int l = 0; l < 7; l++) {
        for(int i= 0; i < 61; i++) {
            mvprintw((y/2)-3+l, (x/2) - 30+i, "%c", title[l][i]);
        }
    }
    mvprintw((y/2)+10,(x/2)-8, "Press <ENTER>");


    while((c = getch()) != 10) {

        for(int l = 0; l < 7; l++) {
            for(int i= 0; i < 61; i++) {
                mvprintw((y/2)-3+l, (x/2) - 30+i, "%c", title[l][i]);
            }
        }
        mvprintw((y/2)+10,(x/2)-8, "Press <ENTER>");
    }
    attroff(COLOR_PAIR(1));
    clear();
    return 0;
}



int menu(int n_escolhas, char *escolhas[]) {
    ITEM **itens = malloc(sizeof(**itens) *n_escolhas); //criar um array de n_escolhas ponteiros para estruturas ITEM de tamanho variável, permite criar um menu com um número flexível de opções 
    WINDOW *menu_win; //criar a variável para a janela
    MENU *menu; //criar a variável para o menu
    ITEM *current; //criar uma variável para o item atual
    int index;
    int x,y;

    getmaxyx(stdscr, y, x);


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





    menu_win = newwin(y, x, 0, 0); // cria uma janela para exibir o menu ( altura, largura, y, x)
    keypad(menu_win, TRUE); //Habilita o processamento de teclas na janela do menu


    set_menu_win(menu, menu_win); // associa a janela menu_win ao menu
    set_menu_sub(menu, derwin(menu_win, 4, 15, (y/2)-1, (x/2)-5)); // define uma subjanela da janela do menu para exibir os itens
    // (janela, linhas, colunas, y, x)

    wattron(menu_win, COLOR_PAIR(2));



    set_menu_mark(menu, " >");


    refresh();


    //exibe o menu na tela
    post_menu(menu);
    wrefresh(menu_win);


    //MENU DRIVER


    while(TRUE) { //criar um ciclo infinito
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