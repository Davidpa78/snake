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
#define MAX_LENGTH 20
#define SNAKE_CHARACTER '*'
#define FOOD_CHARACTER '+'
#define WALL_CHAR '='

bool finish=false;
int row, col;
int direccion;
int snake_length = 1;
int comida = 1;

struct Coordenadas{
    int x;
    int y;
} snake[MAX_LENGTH], cola, nuevacola, last, last2, food;



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
    if((food.y > 0) && (food.x > 0))
        mvprintw(food.x, food.y, "%c", FOOD_CHARACTER);

}

void drawLevel() {
    for (int i=0; i<row; i++) {
        mvaddch(i, 0, WALL_CHAR);
        mvaddch(i, col-1, WALL_CHAR);
    }
    for (int i=1; i<col-1; i++) {
        mvaddch(0, i,WALL_CHAR);
        mvaddch(row-1, i, WALL_CHAR);
    }
    /*    for (int i=25; i<55; i++) {
          mvaddch(row/4, i, ROW_CHAR);
          mvaddch((row/4)*3, i, ROW_CHAR);
          }*/
}

void comer(){
    if((snake[0].x == food.x)&&(snake[0].y == food.y)){
        cola = snake[snake_length-1];
        //CAMBIAR
        nuevacola.x = cola.x+1;
        nuevacola.y = cola.y+1;

        snake[snake_length++] = nuevacola;

        food.y = rand()%(col-1);
        food.x = rand()%(row-1);
        dibujar_comida();
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

    last = snake[0];
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
    else  if((snake[0].x == row) || (snake[0].y == col)){
        pierdes();
        timeout(-1);
        finish=true;
    }
}

int main(){

    int salir;

    initscr();
    inicio();
    food.x = rand()%(row-1);
    food.y = rand()%(col-1);
    noecho();
    start_color();
    init_pair(1,COLOR_YELLOW,COLOR_BLUE);
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
    if(salir == 10){
        curs_set(1);
        endwin();
    }

    return EXIT_SUCCESS;
}
