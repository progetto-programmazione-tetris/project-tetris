#include "tetramino.h"
#include "tetramini.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Tetramino::Tetramino() {
    srand(time(NULL));
    tipo=rand()%6;
    rotazione=rand()%3;
    aggiornaTavola();
}

void Tetramino::aggiornaTavola() {
    for (int i = 0; i < 20 + 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i - y < 4 && i - y >= 0 &&
                j - x < 4 && j - x >= 0) {
                tavola[i][j] = tetramini[tipo][rotazione][i - y][j - x];
            } else {
                tavola[i][j] = 0;
            }
        }
    }
}
bool Tetramino::collisioniBordo() {
    aggiornaTavola();
    int blocco=0;
    for (int i = 0; i < 20 + 4; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (tavola[i][j] != 0) blocco += 1;
        }
    }
    if (blocco < 4) return true;
    return false;
}
bool Tetramino::destra() {
    x=x+1;
    if (collisioniBordo()){
        x=x-1;
        return false;
    }
    return true;
}
bool Tetramino::sinistra() {
    x=x-1;
    if (collisioniBordo()){
        x=x+1;
        return false;
    }
    return true;
}
bool Tetramino::giu() {
    y=y-1;
    if (collisioniBordo()){
        y=y+1;
        return false;
    }
    return true;
}
bool Tetramino::su(){
    y=y-1;
    if(collisioniBordo()){
        y += 1;
        return false;
    }
    return true;
}
bool Tetramino::ruota(bool inverso){
    if(inverso) rotazione = rotazione + 2;
    rotazione=(rotazione+1) % 4;
    if (collisioniBordo()){
        rotazione=(rotazione+3) % 4;
        return false;
    }
    return true;
}