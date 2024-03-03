#include <ncurses.h>
#include "tetramino.h"
#include "gioco.h"
void Gioco::disegna(){
    int Disegno;
    // finsetra principale
    // finestra punteggio
    // finestra che mostra PROSSIMO tetramino

}
void Gioco::aggiornaPunteggio(){
    //
}
void Gioco::cancellaRiga(){
    //
}
bool rigaCompleta(){
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
        aggiornaPunteggio();
        tetramino = prossimoTetramino;
        prossimoTetramino = Tetramino();
    }
}

bool  Gioco::collisioniConTetramini(){
    tetramino.aggiornaTavola();
    for(int i = 0;i<20;i++){
        for(int j=0; j<10; j++){
            if(tavola[i][j] != 0 && tetramino.tavola[i+4]){
                tavola[i][j] = tetramino.tavola[i+4][j];
            }
        }
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
void trasformaTetramino(int k){
    switch (k) {
        case KEY_UP:
            tetramino.ruota();
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
            if (collisioniConTetramini()) tetramino.ruota();
            break;
    }
}

