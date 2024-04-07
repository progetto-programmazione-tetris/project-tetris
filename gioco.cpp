#include <ncurses.h>
#include <cstdlib>
#include "tetramino.h"
#include "gioco.h"
void Gioco::disegna(){
    int Disegno;

    tetramino.aggiornaTavola();
    WINDOW *campo = newwin(22, 22, 1, 50);
    start_color();
    wborder(campo, int('|'), int('|'), int('='), int('='),  int('='), int('='), int('='), int('='));
    for(int y=20-1; y>=0; y--){
        for(int x=0; x<10; x++){
            Disegno = tavola[y][x] + tetramino.tavola[i+4][j];
                wattron(campo, COLOR_PAIR(Disegno));
                mvwprintw(campo, (y+1), (x*2+1), "  ");
                wattroff(campo, COLOR_PAIR(Disegno));
        }
    }
    wrefresh(campo);

    mvprintw(5, 5, "punteggio: %d", punteggio);

    // finestra che mostra PROSSIMO tetramino

}
void Gioco::cancellaRiga(int y){
    while (y > 0) {
        for (int x = 0; x < 10; x++) {
            tavola[y][x] = tavola[y - 1][x];
        }
        y--;
    }
    for (int x = 0; x < 10; x++) {
        tavola[0][x] = 0;
    }
}
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
void Gioco::rimozioneRighePiene(){
    int righe_piene = 0;
    for (int y = 0; y < 20; y++){
        if(controlla_riga(y)){
            righe_piene++;
            togli_riga(y);
        }
    }
    punteggio = punteggio + righe_piene;
}
bool Gioco::sconfitta(){
    //
}
void Gioco::aggiornaStato(){
    bool collisione = !tetramino.giu();
    if(collisioniConTetramini()){
        tetramino.su();
        collisione=true;
    }

    if(collisione){
        tetramino.aggiornaTavola();
        for(int i=0; i<20; i++){
            for(int j=0; j<10;j++){
                if (tavola[i][j]==0){
                    tavola[i][j]==tetramino.tavola[i+4][j];
                }
            }
        }
        rimozioneRighePiene();
        tetramino = prossimoTetramino;
        prossimoTetramino = Tetramino();
    }
}

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
void Gioco::gravita(){
    tetramino.giu();
        if (collisioniConTetramini()){
            tetramino.su();
        }
}
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

