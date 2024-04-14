#include <ncurses.h>
#include "gioco.h"
#include "menu.h"

int main(int argc, char const *argv[]) {
    int input;
    initscr();
    Gioco gioco;
    
    for (int i = 1; i < 8; ++i) 
        init_pair(i, 0, i);
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    while (true){
        input = getch();
        gioco.trasformaTetramino(input);
        gioco.disegna();
        gioco.gravita();
        gioco.aggiornaStato();
    }
    endwin();  
}