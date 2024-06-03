#include <ncurses.h>
#include <cstdlib>
#include "tetramino.h"
#include "gioco.h"
#include "menu.h"
#include <unistd.h>

void Gioco::disegna(){
    int Disegno;

    // Finestra principale
    tetramino.aggiornaTavola();         // Aggiorna lo stato del tetramino attivo
    WINDOW *campo = newwin(22, 22, 1, 50);         // Crea una nuova finestra per il campo di gioco
    start_color(); // Inizializza i colori
    wborder(campo, int('|'), int('|'), int('='), int('='), int('='), int('='), int('='), int('='));         // Disegna il bordo della finestra
    // Disegna i tetramini e lo sfondo
    for(int y=0; y<20; y++){
        for(int x = 0; x < 10; x++){
            Disegno = tavola[y][x] + tetramino.tavola[y+4][x];
                wattron(campo, COLOR_PAIR(Disegno));
                mvwprintw(campo, (y+1), (x*2+1), "  ");
                wattroff(campo, COLOR_PAIR(Disegno));
        }
    }
    wrefresh(campo);
    // Finestra punteggio
    mvprintw(5, 5, "punteggio: %d", punteggio);
}

void Gioco::cancellaRiga(int y){
    // Sposta tutte le righe sopra di una posizione verso il basso
    while (y > 0) {
        for (int x = 0; x < 10; x++) {
            tavola[y][x] = tavola[y - 1][x];
        }
        y--;
    }
    // Pulisce la prima riga
    for (int x = 0; x < 10; x++) {
        tavola[0][x] = 0;
    }
}

// Controlla se una riga è completa (senza zeri)
bool Gioco::rigaCompleta(int y){
    bool piena = true;
    int x = 0;
    while (x < 10 && piena) {
        if (tavola[y][x] == false) {
            piena = false;
        }
        x++;
    }
    return piena;
}

// Conta e rimuove le righe complete, aggiornando il punteggio
void Gioco::rimozioneRighePiene(){
    int righe_piene = 0;
    for (int y = 0; y < 20; y++){
        if(rigaCompleta(y)){
            righe_piene++;
            cancellaRiga(y);
        }
    }
    punteggio = punteggio + (righe_piene*100);
}

// Aggiorna lo stato del gioco in base alla posizione del tetramino
void Gioco::aggiornaStato(){
    bool collisione = !tetramino.giu();
    if(collisioniConTetramini()){
        tetramino.su();
        collisione=true;
    }

    if(collisione){
        tetramino.aggiornaTavola();     // Aggiunge il tetramino alla tavola
        for(int i=0; i<20; i++){
            for(int j=0; j<10;j++){
                if (tavola[i][j]==0){
                    tavola[i][j]=tetramino.tavola[i+4][j];
                }
            }
        }
        rimozioneRighePiene();     // Rimuove le righe complete
        tetramino = prossimoTetramino;     // Sostituisce il tetramino attuale con il prossimo
        prossimoTetramino = Tetramino();     // Genera un nuovo tetramino
    }
}

// Controlla se ci sono collisioni tra il tetramino attivo e quelli già presenti nella tavola
bool Gioco::collisioniConTetramini() {
    tetramino.aggiornaTavola();
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (tavola[i][j] != 0 && tetramino.tavola[i+4][j] != 0) {
                return true;
            }
        }
    }
    return false;
}

// Controlla se il gioco è terminato (sconfitta)
bool Gioco::sconfitta(){
    tetramino.aggiornaTavola();
    for (int j = 0; j < 10; ++j) {
        if (tavola[19][j] != 0 && tetramino.tavola[3][j] != 0) {
            return true; 
        }
    }
    return false;
}
void Gioco::gravita(){
    tetramino.giu();
    if (collisioniConTetramini()){
        tetramino.su();
    }
    refresh();
}

// Trasforma (ruota o muove) il tetramino in base all'input dell'utente
void Gioco::trasformaTetramino(int k){
    switch (k) {
        case KEY_UP:
            tetramino.ruota(false);
            if (collisioniConTetramini()) tetramino.ruota(true);
            break;
        case KEY_RIGHT:
            tetramino.destra();
            if (collisioniConTetramini()) tetramino.sinistra();
            break;
        case KEY_LEFT:
            tetramino.sinistra();
            if (collisioniConTetramini()) tetramino.destra();
            break;
        case KEY_DOWN:
            tetramino.ruota(true);
            if (collisioniConTetramini()) tetramino.ruota(false);
            break;
    }
}

