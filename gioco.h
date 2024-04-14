#include "tetramino.h"
#include "menu.h"

#ifndef GIOCO_H
#define GIOCO_H

class Gioco{
    public:
        Gioco():tetramino(){};
        void disegna();
        void aggiornaStato();
        void trasformaTetramino(int);
        void gravita();

    private:
        bool collisioniConTetramini();
        void rimozioneRighePiene();
        bool sconfitta();        
        bool rigaCompleta(int);
        void cancellaRiga(int);
        int tavola[20][10] = {};
        int righeComplete = 0;
        int punteggio = 0;
        Tetramino tetramino;
        Tetramino prossimoTetramino;
};
#endif