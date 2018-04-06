#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

#define ESC 27
#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3
#define IZQUIERDA 4
#define MAX_LENGTH 20
#define SNAKE_CHARACTER '*'
#define FOOD_CHARACTER '+'

int row, col;
int direccion;
int snake_length = 1;
int comida = 1;

typedef struct{
    int x;
    int y;
} snakepart;

typedef struct{
    int x;
    int y;
} food;

snakepart snake[MAX_LENGTH];


void inicio(){
    getmaxyx(stdscr, row, col);
    srand(time(NULL));
}

void inicio_snake(){
    snake[0].x= row/2;
    snake[0].y= col/2;
}

void dibujar_snake(){
    for(int i=0 ; i<snake_length; i++){
        mvprintw(snake[i].x, snake[i].y,"%c", SNAKE_CHARACTER);
    }
}

void dibujar_comida(){
    int aleatory_row, aleatory_col;
    aleatory_col = rand()%col;
    aleatory_row = rand()%row;

    for(int i=0; i<comida; i++)
        move(row/2, col/2);
    mvprintw(aleatory_row, aleatory_col, "%c", FOOD_CHARACTER);
}
void mover_snake(){
        while(tecla == KEY_UP)
            snake[0].y--;
    while(DERECHA)
        snake[0].x++;
     ABAJO
        snake[0].y++;
    break;
    case IZQUIERDA
        snake[0].x--;
    break;
}
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
    inicio_snake();
    dibujar_snake();
    dibujar_comida();
    /*coges flecha
     * mueves
     *
     * */
    //pierdes();

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
        if (option == ESC){
            endwin();
            exit(0);

        }


    }

    endwin();

    return EXIT_SUCCESS;
}
