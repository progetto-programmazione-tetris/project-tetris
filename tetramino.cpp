#include "tetramino.h"
#include "tetramini.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Tetramino::Tetramino() {
    // Selezione casuale del tipo e della rotazione del tetramino
    srand(time(NULL));
    tipo=rand()%7;
    rotazione=rand()%3;
    aggiornaTavola();
}

// Aggiorna la tavola di gioco con la posizione e la rotazione correnti del tetramino
void Tetramino::aggiornaTavola() {
    // Scorre la tavola
    for (int i = 0; i < 20 + 4; i++) {
        for (int j = 0; j < 10; j++) {
            if (((i - y < 4) && (i - y >= 0)) && ((j - x < 4) && (j - x >= 0))) {
                // Se il blocco è all'interno del tetramino, copia il valore dalla forma del tetramino
                 tavola[i][j] = tetramini[tipo][rotazione][i - y][j - x];
            } else {
                // Altrimenti, imposta il blocco a zero (vuoto)
                tavola[i][j] = 0;
            }
        }
    }
}

// Controlla se il tetramino ha collisioni con i bordi della tavola
bool Tetramino::collisioniBordo() {
    aggiornaTavola(); // Aggiorna la tavola con la posizione corrente del tetramino
    int blocco=0;
    // Scorre la tavola 
    for (int i = 0; i < 20 + 4; i++) {
        for (int j = 0; j < 10; j++) {
            if (tavola[i][j] != 0) blocco += 1;
        }
    }
    if (blocco < 4) return true; // Se ci sono meno di 4 blocchi, c'è una collisione
    return false; // Altrimenti, non c'è collisione
}

// Movimento del tetramino, altrimenti, in caso di collisione, viene annullato il movimento
bool Tetramino::destra() {
    x=x+1;
    if (collisioniBordo()) {
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
    y=y+1;
    if (collisioniBordo()){
        y=y-1;
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
    // Ruota il tetramino (in senso orario o antiorario)
    if(inverso) rotazione = rotazione + 2;         // Se inverso, calcola la rotazione inversa
    rotazione = (rotazione + 1) % 4;         // Ruota il tetramino
    if (collisioniBordo()){               // Se c'è una collisione, annulla la rotazione
        rotazione = (rotazione + 3) % 4;
        return false;
    }
    return true;
}
