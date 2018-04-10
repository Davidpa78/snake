
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
        foody.y = rand()%col;
        foody.x = rand()%row;
        mvprintw(foody.x, foody.y, "%c", FOOD_CHARACTER);

    }

    void comer(){
        if((snake[0].x == foody.x)&&(snake[0].y == foody.y))
        dibujar_comida();
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
        snakepart cabeza = snake[0];
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
        snake[0] = cabeza;
    }

void comprueba(){

}

void mover_snake(){
    cambiar_direccion();
    comprueba();



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

        initscr();
        inicio();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0);
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
            timeout(50);
            obtener_tecla();
            clear();
            mover_snake();
            dibujar_snake();
            dibujar_comida();

            refresh();
            usleep(100000);
        }
        endwin();

        return EXIT_SUCCESS;
    }
