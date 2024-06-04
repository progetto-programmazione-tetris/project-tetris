#include <cstring>
#include <ncurses.h>
#include <fstream>
#include "gioco.h"
#include "menu.h"
#include <ctime>
using namespace std;

void mainMenu::Menu() {
    nodelay(stdscr, false); // Imposta la modalità nodelay su false per consentire l'attesa di input dall'utente
    clear(); // Pulisce lo schermo
    refresh(); // Aggiorna lo schermo
    // Ottiene le dimensioni dello schermo
    getmaxyx(stdscr, yMax, xMax);

    // Definisce le opzioni del menu
    const char* opzioni[] = {"New Game", "Scoreboard", "Quit"};
    int num_opzioni = sizeof(opzioni) / sizeof(opzioni[0]);

    // Opzione corrente evidenziata
    int scelta = 0;
    // È stata selezionata un'opzione
    bool isSelected = false;

    while (isSelected == false) {
        clear();
        // Stampa il titolo del menu
        mvprintw(0, (xMax - strlen("TETRIS")) / 2, "TETRIS");

        // Stampa ogni opzione con evidenziazione
        for (int i = 0; i < num_opzioni; ++i) {
            attron(A_BOLD); // Attiva il grassetto per il testo
            if (scelta == i) {
                mvprintw(i + 2, (xMax - strlen(opzioni[i]))/2 - 2, "%s" ,">");
                attron(A_REVERSE); // Evidenzia l'opzione corrente
                mvprintw(i + 2, (xMax - strlen(opzioni[i]))/2, "%s", opzioni[i]);
                attroff(A_REVERSE); // Disattiva l'evidenziazione
            } else {
                mvprintw(i + 2, (xMax - strlen(opzioni[i]))/2, "%s", opzioni[i]);
            }
            attroff(A_BOLD); // Disattiva il grassetto
        }

        refresh();

        // Ottiene l'input dell'utente (tasti freccia)
        int key = getch();
        switch (key) {
            case KEY_UP:
                scelta = (scelta - 1 + num_opzioni) % num_opzioni;        // Seleziona l'opzione sopra
                break;
            case KEY_DOWN:
                scelta = (scelta + 1) % num_opzioni;        // Seleziona l'opzione sotto
                break;
            case 10:  // Tasto Invio
                isSelected = true;
                // Seleziona l'opzione evidenziata
                clear();
                if (scelta == 0) {
                    // Inizia un nuovo gioco
                    Gioco gioco;
                    int input;
                    start_color();
                    cbreak(); 
                    nodelay(stdscr, TRUE); 

                    for (int i = 1; i < 8; ++i){
                        init_pair(i, 0, i);
                    }
                    time_t t = time(nullptr);
                    tm* now = localtime(&t);
                    int prev = now->tm_sec;
                    int curr = now->tm_sec;
                    
                    while (!gioco.sconfitta()){
                        input = getch();
                        if (input != ERR) { // Check if input is available
                            gioco.trasformaTetramino(input);
                            gioco.disegna();
                            gioco.aggiornaStato();
                        }
                        time_t t = time(nullptr);
                        tm* now = localtime(&t);
                        curr = now->tm_sec;
                        
                        if (curr != prev){
                            gioco.gravita();
                            gioco.disegna();
                            gioco.aggiornaStato();
                            prev = curr;
                        }
                    }
                    nodelay(stdscr, false);
                    gioco.gameOver();
                    char nome[32];
                    classifica.richiesta_nome(nome);
                    classifica.aggiungi_punteggio(nome, gioco.punteggio);
                    Menu();
                } else if (scelta == 1) {
                    // Visualizza la classifica
                    classifica.finestra_classifica();
                } else if (scelta == 2) {
                    // Esce dal programma
                    break;
                }
                break;
            default:
                break;
        }
    }
}
