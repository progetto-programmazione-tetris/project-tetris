#include "tetramino.h"
#include "classifica.h"
#ifndef GAME_H
#define GAME_H

class Gioco{
    public:
        Gioco():tetramino(){};
        void disegna();
        void rimozioneRighePiene();
        void aggiornaStato();
        void trasformaTetramino(int);
        void gravita();
    private:
        bool collisioniConTetramini();
        bool sconfitta();
        bool rigaCompleta(int y);
        void cancellaRiga(int y);
        int tavola[20][10] = {};
        int righeComplete = 0;
        int punteggio = 0;
        Tetramino tetramino;
        Tetramino prossimoTetramino;
};
#endif
