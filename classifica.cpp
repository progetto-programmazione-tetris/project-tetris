#include "classifica.h"

bool Classifica::controllo_file(){
    fstream file;
    file.open(file_classifica, ios::in);

    char linea[32];
    while(!file.eof()) {
        file.getline(linea, 32);
        if (linea[0] != '\0') {
            int len = strlen(linea);
            if (len > 26) return false;
            //controlla che il punteggio non sia troppo lungo e che ci siano solo cifre
            int x = 0;
            while (linea[x] != ';' ){
                if (linea[x] == '\0') return false;
                if (x >= 9) return false;
                if (linea[x] < '0' || linea[x] > '9') return false;
                x++;
            }
            // controlla che il nome non sia troppo lungo
            int y = 1;
            while (linea[x + y] != ';'){
                if (linea[x + y] == '\0') return false;
                if (y > 15) return false;
                y++;
            }
        }
    }
    file.close();
    return true;
}

void Classifica::ricava_nome_punti(char linea[], char punti[], char nome[]){
    int x = 0;
    if(linea[0] != '\0') {
        while (linea[x] != ';') {
            punti[x] = linea[x];
            x++;
        }
        punti[x] = '\0';

        int y = 0;
        while (linea[x + y + 1] != ';' && y < 20) {
            nome[y] = linea[x + y + 1];
            y++;
        }
        nome[y] = '\0';
    }
    else {
        nome[0] = '\0';
        punti[0] = '\0';
    }
}

void Classifica::finestra_classifica(){
    clear();
    refresh();
    char linea[64];
    char nome[32];
    char punti[10];
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    refresh();
    box(win, 0, 0);
    curs_set(0);
    fstream file;
    file.open (file_classifica,ios::in);

    if (file.is_open()) {
        if(controllo_file()) {
            int ind = 0;
            // scorre il file riga per riga
            while (!file.eof() && ind < yMax-4) {
                file.getline(linea, 32);
                //stampa il nome e il punteggio salvati nella riga
                if (linea[0] != '\0') {
                    ricava_nome_punti(linea, punti, nome);

                    mvwprintw(win, ind + 2, 3, "%d >>", ind + 1);
                    mvwprintw(win, ind + 2, 10, "%s", nome);
                    mvwprintw(win, ind + 2, 28, "%s", punti);
                    ind++;
                }
            }
        }
        else {
            mvwprintw(win, 2, 2, "file classifica.txt manomesso");
        }
        file.close();
    }
    wrefresh(win);
    wgetch(win);
}

nodo* Classifica::inserisci_coda(nodo* testa, int punti, char nome[]){
    nodo *n = new nodo;
    n->next = nullptr;
    n->punteggio = punti;
    strcpy(n->nome, nome);
    if (testa == nullptr) return n;
    else {
        nodo *ptr = testa;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = n;
        return testa;
    }
}

nodo* Classifica::crea_lista_punteggi(){
    fstream file;
    file.open (file_classifica,ios::in);
    char linea[32];
    char punti[32];
    int int_punti;
    char nome[32];
    nodo *testa = nullptr;

    if (file.is_open()) {
        while (!file.eof()){
            file.getline(linea, 32);
            if(linea[0] != '\0'){
                ricava_nome_punti(linea, punti, nome);
                int_punti = std::stoi(punti);
                testa = inserisci_coda(testa, int_punti, nome);
            }
        }
    }
    file.close();
    return testa;
}

nodo* Classifica::aggiungi_nodo(nodo *testa, char nome[], int punti){
    nodo* n = new nodo;
    n->punteggio = punti;
    strcpy(n->nome, nome);

    if (testa == nullptr){
        n->next = nullptr;
        return n;
    }
    else if(testa->punteggio < punti){
        n->next = testa;
        return n;
    }
    else {
        nodo *ptr = testa;
        while(ptr->next != nullptr){
            if (ptr->next->punteggio < punti){
                n->next = ptr->next;
                ptr->next = n;
                return testa;
            }
            ptr = ptr->next;
        }
        ptr->next = n;
        n->next = nullptr;
    }
    return testa;
}

void Classifica::riscrivi_classifica(nodo *testa){
    fstream file;
    int max_punteggi = 50;
    int count = 0;

    file.open(file_classifica, ios::out);
    if(file.is_open()){
        while (testa != nullptr && count < max_punteggi){
            file <<testa->punteggio <<";" <<testa->nome <<";" <<endl;
            testa = testa->next;
            count++;
        }
    }
    file.close();
}

void Classifica::aggiungi_punteggio(char nome[], int punteggio) {
    if(strlen(nome) <= 16 && punteggio <= 999999999 && punteggio > 0) {
        fstream file;
        file.open(file_classifica);
        if (file.is_open()) {
            file.close();
            //se il file è manomesso la funzione non fa niente
            if (controllo_file()) {
                nodo *testa = crea_lista_punteggi();
                testa = aggiungi_nodo(testa, nome, punteggio);
                riscrivi_classifica(testa);
            }
        }
            //se il file non c'è viene creato
        else {
            file.open(file_classifica, ios::out);
            file << punteggio << ";" << nome << ";" << endl;
            file.close();
        }
    }
}

// stampa la finestra in cui viene richiesto il nome
void Classifica::richiesta_nome(char input[]) {
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    box(win, 0, 0);
    keypad(win, true);
    curs_set(1);
    input[0] = '\0';
    int input_getch = 0;
    int indice_Ar = 0;
    int inizio_riga_x = 6;
    int inizio_riga_y = 3;

    mvwprintw(win, inizio_riga_y-1, inizio_riga_x, "inserisci il tuo nome:");
    wmove(win, inizio_riga_y, inizio_riga_x);

    while(input_getch != 10) {
        input_getch = wgetch(win);
        wmove(win, inizio_riga_y, inizio_riga_x+indice_Ar);

        for(int x = 0; x < 53; x++) {

            if (input_getch == (int)alfabeto[x]) {
                if(indice_Ar < 15){
                    input[indice_Ar] = alfabeto[x];
                    input[indice_Ar+1] = '\0';
                    mvwprintw(win, inizio_riga_y, inizio_riga_x, "%s", input);
                    indice_Ar++;
                }
            }
        }

        if (input_getch == (KEY_BACKSPACE)){
            if (indice_Ar > 0) {
                indice_Ar--;
            }
            mvwprintw(win, inizio_riga_y, inizio_riga_x + indice_Ar, " ");
            wmove(win, inizio_riga_y, inizio_riga_x + indice_Ar);
            input[indice_Ar] = '\0';
        }
        wrefresh(win);
    }
    curs_set(0);
}
