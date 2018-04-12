
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#define ESC 27
#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3
#define IZQUIERDA 4
#define MAX_LENGTH 20
#define SNAKE_CHARACTER '*'
#define FOOD_CHARACTER '+'
#define WALL_CHAR '9'

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
        /*  while (snake[i].x != -1 && snake[i].y != -1) {
            move(snake[i].y, snake[i].x);
            addch(SNAKE_CHARACTER);
            i++;
            */
    }
    }

    void dibujar_comida(){
        mvprintw(foody.x, foody.y, "%c", FOOD_CHARACTER);

    }
   /* void dibujar_pared(){
        for(int ncol=0; ncol<col; ncol++){
            printw();
        }
        for(int nrow; nrow<row; nrow++){
            printw();
        }
    }*/
   /* void drawLevel() {
        for (int i=0; i<row; i++) {
            mvaddch(i, 0, WALL_CHAR);
            mvaddch(i, col-1, WALL_CHAR);
        }
        for (int i=1; i<col-1; i++) {
            mvaddch(0, i, WALL_CHAR);
            mvaddch(row-1, i, WALL_CHAR);
        }
        for (int i=25; i<55; i++) {
            mvaddch(row/4, i, WALL_CHAR);
            mvaddch((row/4)*3, i, WALL_CHAR);
        }
    }*/




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

    /* int tecla = NULL;*/

    /*getch();*/
    snakepart last = snake[0];
    switch(direccion/*tecla*/){
        case IZQUIERDA:/*(tecla == KEY_UP)*/
            snake[0].y--;
            break;
        case ABAJO:/*(tecla == KEY_RIGHT)*/
            snake[0].x++;
            break;
        case DERECHA:/*(tecla == KEY_DOWN)*/
            snake[0].y++;
            break;
        case ARRIBA:/*(tecla == KEY_LEFT)*/
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

void comprueba(){

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
}

void ganas(){
    clear();
    mvprintw(row/2.5, col/2, "Fin de la partida.\n");
    mvprintw(row/2, col/2, "Has ganado.");
    refresh();
}

int main(){

    initscr();
    inicio();
    foody.x = rand()%row;
    foody.y = rand()%col;
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
    ////dibujar_snake();
    // dibujar_comida();
    /*coges flecha
     * mueves
     *
     * */
    //pierdes();

    while(1){
        timeout(50);
        obtener_tecla();
        clear();
        cambiar_direccion();
        /*mover_snake();*/
        comer();
        dibujar_snake();
        dibujar_comida();

        refresh();
        usleep(90000);
    }
    endwin();

    return EXIT_SUCCESS;
}
