#ifndef CLASSE_CLASSIFICA_CLASSIFICA_H
#define CLASSE_CLASSIFICA_CLASSIFICA_H
#include <fstream>
#include <cstring>
#include <ncurses.h>

using namespace std;

struct nodo {
    int punteggio;
    char nome[20];
    nodo *next;
};

class Classifica {
private:
    char file_classifica[32] = "classifica.txt";
    char alfabeto[53] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'l',
                         'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
                         'v', 'z', 'x', 'y', 'w', 'k', 'j', 'A', 'B',
                         'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M',
                         'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                         'Z', 'X', 'Y', 'W', 'K', 'J', ' '};

    bool controllo_file();
    void ricava_nome_punti(char linea[], char punti[], char nome[]);
    nodo* inserisci_coda(nodo* testa, int punti, char nome[]);
    nodo* crea_lista_punteggi();
    nodo* aggiungi_nodo(nodo *testa, char nome[], int punti);
    void dealloca_lista(nodo* testa);
    void riscrivi_classifica(nodo *testa);
    bool stampa_facciata(WINDOW* win, int indice_partenza, int yMax, nodo *testa);

public:
    //Classifica();
    void finestra_classifica();
    void aggiungi_punteggio(char nome[], int punteggio);
    void richiesta_nome(char input[]);
};

#endif
