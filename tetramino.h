#ifndef TETRIS_TETRAMINO_H
#define TETRIS_TETRAMINO_H

class Tetramino{
    public:
        Tetramino();
        void aggiornaTavola();
        bool destra();
        bool sinistra();
        bool giu();
        bool su();
        bool ruota(bool=false);
        int tavola[24][10]={};
    private:
        int y=1;
        int x=3;
        int rotazione;
        int tipo;
        bool collisioniBordo();
};

#endif //TETRIS_TETRAMINO_H