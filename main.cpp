#include <ncurses.h>
#include "gioco.h"
#include "menu.h"
#include <ctime>

int main(int argc, char const *argv[]) {
    int input;
    //Gioco gioco;
    initscr();        // Inizializza la libreria ncurses
    noecho();         // Impedisce la visualizzazione dei caratteri digitati dall'utente
    curs_set(0);      // Nasconde il cursore
    keypad(stdscr, TRUE); // Abilita l'uso dei tasti funzione (principalmente le frecce)
    mainMenu menu;
    menu.Menu();
    /*
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
    }*/
    endwin();  
}

///////////////////////////////////////////////////////////////////////////////////
/*
while (choice != 2){
    mainMenu();
    if (choice == 0) {
        Gioco gioco;
        //partita
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
    } else if (choice == 1) {
        classifica.finestra_classifica();
    }
}*/
