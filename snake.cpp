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

void obtener_tecla(int tecla){


    getch();
    tecla = getch();

    switch(tecla){
        case KEY_UP:
            direccion = ARRIBA;
            break;
        case KEY_DOWN:
            direccion = ABAJO;
            break;
        case KEY_LEFT:
            direccion = IZQUIERDA;
            break;
        case KEY_RIGHT:
            direccion = DERECHA;
            break;

    }


}

void mover_snake(int direccion){

   /* int tecla = NULL;*/

    /*getch();*/

   switch(direccion/*tecla*/){
       case ARRIBA:/*(tecla == KEY_UP)*/
        snake[0].y--;
    break;
       case DERECHA:/*(tecla == KEY_RIGHT)*/
        snake[0].x++;
    break;
       case ABAJO:/*(tecla == KEY_DOWN)*/
        snake[0].y++;
    break;
       case IZQUIERDA:/*(tecla == KEY_LEFT)*/
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

    int tecla = 0;
    bool finish= false;

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

    while(finish == false){










        }




    endwin();

    return EXIT_SUCCESS;
}
