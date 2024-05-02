#include <ncurses.h>
#include <chrono>
#include <thread>

#include "gioco.h"
#include "menu.h"
#include <ctime>

int main(int argc, char const *argv[]) {
    int input;
    Gioco gioco;
    initscr();
    start_color();
    cbreak(); // Enable cbreak mode (recommended with nodelay)
    nodelay(stdscr, TRUE); // Set nodelay mode for stdscr window

    for (int i = 1; i < 8; ++i) 
        init_pair(i, 0, i);

    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int prev = now->tm_sec;
    int curr = now->tm_sec;
    
    while (true){
        input = getch();
        if (input != ERR) { // Check if input is available
            gioco.trasformaTetramino(input);
            gioco.disegna();
            gioco.aggiornaStato();
            time_t t = time(nullptr);
    
            tm* now = localtime(&t);
            prev = now->tm_sec;
        }

        time_t t = time(nullptr);
    
        tm* now = localtime(&t);
        curr = now->tm_sec;
        if (curr != prev){
            gioco.gravita();
            gioco.disegna();
            gioco.aggiornaStato();
            prev = curr;
        }
    }
    endwin();  
}
