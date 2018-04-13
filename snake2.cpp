#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <curses.h>

#define ESC 27
#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3
#define IZQUIERDA 4
#define MAX_LENGTH 4
#define SNAKE_CHARACTER '*'
#define FOOD_CHARACTER '+'
#define ROW_CHAR '='
#define COL_CHAR '|'
bool finish=false;
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
food foody;


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
    mvprintw(foody.x, foody.y, "%c", FOOD_CHARACTER);

}

void drawLevel() {
    for (int i=0; i<row; i++) {
        mvaddch(i, 0, COL_CHAR);
        mvaddch(i, col-1, COL_CHAR);
    }
    for (int i=1; i<col-1; i++) {
        mvaddch(0, i,ROW_CHAR);
        mvaddch(row-1, i, ROW_CHAR);
    }
    for (int i=25; i<55; i++) {
        mvaddch(row/4, i, ROW_CHAR);
        mvaddch((row/4)*3, i, ROW_CHAR);
    }
}




void comer(){
    if((snake[0].x == foody.x)&&(snake[0].y == foody.y)){
        snakepart cola = snake[snake_length-1];
        snakepart nuevacola;
        //CAMBIAR
        nuevacola.x = cola.x+1;
        nuevacola.y = cola.y+1;

        snake[snake_length++] = nuevacola;

        foody.y = rand()%col;
        foody.x = rand()%row;
    }
}

void obtener_tecla(){
    int tecla = getch();
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

void cambiar_direccion(){

    snakepart last = snake[0];
    switch(direccion){
        case IZQUIERDA:
            snake[0].y--;
            break;
        case ABAJO:
            snake[0].x++;
            break;
        case DERECHA:
            snake[0].y++;
            break;
        case ARRIBA:
            snake[0].x--;
            break;

    }

    snakepart last2;
    for(int i=1;i<snake_length;i++){
        last2 = snake[i];
        snake[i] = last;
        last = last2;
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
    mvprintw(row/2.5, col/2,"Fin de la partida.\n");
    mvprintw(row/2, col/2, "Has perdido.");
    refresh();
    exit(0);
    clear();
}

void ganas(){
    clear();
    mvprintw(row/2.5, col/2, "Fin de la partida.\n");
    mvprintw(row/2, col/2, "Has ganado.");
    refresh();
    clear();
}

void comprueba(){
    if(snake_length==MAX_LENGTH){
        ganas();
        timeout(-1);
        finish=true;
    }
    else  if((((mvinch(snake[0].x, snake[0].y) & A_CHARTEXT) == COL_CHAR)) || (((mvinch(snake[0].x, snake[0].y) & A_CHARTEXT) == ROW_CHAR))){
        pierdes();
        timeout(-1);
        finish=true;
    }
}

int main(){

    int salir;

    initscr();
    inicio();
    foody.x = rand()%(row-1);
    foody.y = rand()%(col-1);
    noecho();
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_RED);
    bkgd(COLOR_PAIR(1));
    drawLevel();
    keypad(stdscr, TRUE);
    curs_set(0);
    bienvenida();
    getch();
    clear();
    inicio_snake();


    while(finish==false){
        timeout(50);
        obtener_tecla();
        clear();
        drawLevel();
        cambiar_direccion();
        comprueba();
        comer();
        if(!finish) {
          dibujar_snake();
          dibujar_comida();
          refresh();
        }
        usleep(70000);
    }

    salir = getch();
    if(salir == KEY_ENTER)
    endwin();

    return EXIT_SUCCESS;
}
