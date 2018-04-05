#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#define ESC 27

int row, col;

void inicio(){
    getmaxyx(stdscr, row, col);
}

void bienvenida(){
    clear();
    mvprintw(row/2.5, col/2, "Welcome to the Classic Snake Game.\n");
    mvprintw(row/2, col/2, "Press any key to continue.");
    refresh();
}

void pierdes(){
    clear();
    mvprintw(row/2.5, col/2, "Fin de la partida.\n");
    mvprintw(row/2, col/2, "Has perdido.");
    refresh();
}

void ganas(){
    clear();
    mvprintw(row/2.5, col/2, "Fin de la partida.\n");
    mvprintw(row/2, col/2, "Has ganado.");
    refresh();
}

int main(){

    int option;

    initscr();
    inicio();
    noecho();
    bienvenida();
    getch();
    clear();
    pierdes();

    while(1){

        option = getch();
        if (option == KEY_UP){

        }
        if (option == KEY_DOWN){

        }
        if (option == KEY_LEFT){

        }
        if (option == KEY_RIGHT){

        }
        if (option == KEY_ENTER){

        }
        if (option == ESC){
            endwin();
            exit(0);

        }


    }

    endwin();

    return EXIT_SUCCESS;
}
