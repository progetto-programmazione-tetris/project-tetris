#include "classifica.h"
#include "menu.h"

// Funzione per controllare la validità del contenuto del file

bool Classifica::controllo_file(){
    fstream file;
    file.open(file_classifica, ios::in);

    char linea[32];
    while(!file.eof()) {
        file.getline(linea, 32);
        if (linea[0] != '\0') {
            int len = strlen(linea);
            if (len > 26) return false;
            // Controlla che il punteggio non sia troppo lungo e che ci siano solo cifre
            int x = 0;
            while (linea[x] != ';' ){
                if (linea[x] == '\0') return false;    // Controlla per il delimitatore corretto
                if (x >= 9) return false;               // Controlla se il punteggio è troppo lungo
                if (linea[x] < '0' || linea[x] > '9') return false;    // Assicura che il punteggio contenga solo cifre
                x++;
            }
            // controlla che il nome non sia troppo lungo
            int y = 1;
            while (linea[x + y] != ';'){
                if (linea[x + y] == '\0') return false;    // Controlla per il delimitatore corretto
                if (y > 15)     return false;        // Controlla se il nome è troppo lungo
                y++;
            }
        }
    }
    file.close();
    return true;
}

// Funzione per estrarre nome e punteggio da una linea
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

// Funzione per visualizzare la finestra della classifica
void Classifica::finestra_classifica() {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    refresh();
    curs_set(0);
    keypad(win, TRUE);

    nodo *testa = crea_lista_punteggi();

    int indice_inizio = 0;
    int input;

    bool fine_classifica;
    bool tmp = true;

    while (tmp) {
        box(win, 0, 0);

        fine_classifica = stampa_facciata(win, indice_inizio, yMax, testa);
        if (xMax > 55) {
            mvwprintw(win, 2, xMax - 22, "Press b to go back");
            mvwprintw(win, 4, xMax - 22, "Arrow keys to scroll");
        }
        wrefresh(win);

        input = wgetch(win);
        if (input == 'b') {
            tmp = false;
        }
        if (input == KEY_UP) {
            if (indice_inizio > 0) {
                indice_inizio--;
            }
        }
        if (input == KEY_DOWN) {
            if (!fine_classifica){
                indice_inizio++;
            }
        }
        wclear(win);
    }
    wclear(win);
    wrefresh(win);
    mainMenu menu;
    menu.Menu();
}

// Funzione per stampare il contenuto della classifica nella finestra
bool Classifica::stampa_facciata(WINDOW* win, int indice_partenza, int yMax, nodo *testa) {
    clear();
    refresh();

    bool fine_classifica = false;
    int ind = 0;
    int punteggio_y = 0;
    int posizione = 1;
    nodo *ptr = testa;

    while (ptr != nullptr && punteggio_y < yMax -4) {
        if (ind >= indice_partenza) {
            mvwprintw(win, punteggio_y + 2, 3, "%d >>", posizione);
            mvwprintw(win, punteggio_y + 2, 10, "%s", ptr->nome);
            mvwprintw(win, punteggio_y + 2, 28, "%d", ptr->punteggio);
            punteggio_y++;
        }
        posizione++;
        ind++;
        ptr = ptr->next;
    }
    if (ptr == nullptr) fine_classifica = true;
    wrefresh(win);
    return fine_classifica; // Ritorna true se la fine della classifica è stata raggiunta
}

// Funzione per inserire un nodo in coda alla lista
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

// Funzione per creare una lista di punteggi a partire dal file
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

// Funzione per inserire un nuovo punteggio nella posizione giusta della lista
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

// Funzione per riscrivere la classifica nel file
void Classifica::riscrivi_classifica(nodo *testa){
    fstream file;
    int max_punteggi = 50;
    int count = 0;

    file.open(file_classifica, ios::out);
    if(file.is_open()){
        // Scrive i punteggi dalla lista al file, fino al massimo consentito
        while (testa != nullptr && count < max_punteggi){
            file <<testa->punteggio <<";" <<testa->nome <<";" <<endl;
            testa = testa->next;
            count++;
        }
    }
    file.close();       // Chiusura file
}

// Funzione per aggiungere un punteggio nella classifica
void Classifica::aggiungi_punteggio(char nome[], int punteggio) {
    if(strlen(nome) <= 16 && punteggio <= 999999999 && punteggio >= 0) {
        if (nome[0] == '\0') {
            nome[0] = '?';
            nome[1] = '\0';
        }
        fstream file;
        file.open(file_classifica);
        if (file.is_open()) {
            file.close();
            // Se il file è manomesso, la funzione non fa niente
            if (controllo_file()) {
                nodo *testa = crea_lista_punteggi();         // Crea una lista di punteggi esistenti
                testa = aggiungi_nodo(testa, nome, punteggio);         // Aggiunge il nuovo punteggio alla lista
                riscrivi_classifica(testa);         // Riscrive il file della classifica con la lista aggiornata
                dealloca_lista(testa);
            }
        }
        // Se il file non c'è, viene creato
        else {
            file.open(file_classifica, ios::out);
            file << punteggio << ";" << nome << ";" << endl;
            file.close();
        }
    }
}

// Funzione per deallocare la memoria utilizzata dalla lista
void Classifica::dealloca_lista(nodo* testa){
    while (testa != nullptr) {
        nodo *ptr = testa;
        testa = testa->next;
        delete ptr;
    }
}

// Funzione per richiedere il nome dell'utente tramite una finestra di input
void Classifica::richiesta_nome(char input[]) {
    noecho();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *win = newwin(yMax, xMax, 0, 0);
    box(win, 0, 0);
    keypad(win, true);
    curs_set(1);
    input[0] = '\0';         // Inizializza l'input con una stringa vuota
    int input_getch = 0;
    int indice_Ar = 0;
    int inizio_riga_x = 6;
    int inizio_riga_y = 3;

   // Stampa il messaggio di richiesta del nome
    mvwprintw(win, inizio_riga_y - 1, inizio_riga_x, "Inserisci il tuo nome:");
    wmove(win, inizio_riga_y, inizio_riga_x);       // Muove il cursore alla posizione iniziale dell'input

    while (input_getch != 10){      // Continua a leggere input finché non viene premuto 'Enter' (codice ASCII 10)
        input_getch = wgetch(win);      // Legge un carattere dalla finestra
        wmove(win, inizio_riga_y, inizio_riga_x+indice_Ar);

        // Controlla se l'input corrisponde a un carattere valido dell'alfabeto
        for(int x = 0; x < 53; x++) {
            if (input_getch == (int)alfabeto[x]) {
                if(indice_Ar < 15){
                    input[indice_Ar] = alfabeto[x];         // Aggiunge il carattere all'input
                    input[indice_Ar + 1] = '\0';         // Termina la stringa
                    mvwprintw(win, inizio_riga_y, inizio_riga_x, "%s", input);
                    indice_Ar++;
                }
            }
        }
        
        // Gestisce il tasto 'Backspace'
        if (input_getch == (KEY_BACKSPACE)){
            if (indice_Ar > 0) {
                indice_Ar--;
            }
           mvwprintw(win, inizio_riga_y, inizio_riga_x + indice_Ar, " "); // Cancella l'ultimo carattere inserito
            wmove(win, inizio_riga_y, inizio_riga_x + indice_Ar); // Muove il cursore alla nuova posizione dell'input
            input[indice_Ar] = '\0'; // Termina la stringa
        }
        wrefresh(win); // Aggiorna la finestra per riflettere i cambiamenti
    }
    curs_set(0);
}
