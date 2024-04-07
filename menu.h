#ifndef MENU_H
#define MENU_H
#include <ncurses.h>
#include <cstring>
#include <fstream>
using namespace std;

class mainMenu{
    public:
        void initialize() {
            clear();
            refresh();
        }

        mainMenu(){
            initialize();
            // Get screen dimensions
            getmaxyx(stdscr, yMax, xMax);

            // Define menu options
            const char* options[] = {"New Game", "Scoreboard", "Quit"};
            int num_options = sizeof(options) / sizeof(options[0]);

            // Current highlighted option
            int choice = 0;
            // Is an option been selected
            bool isSelected = false;

            while (isSelected == false) {
                clear();
                // Print the menu title
                mvprintw(0, (xMax - strlen("TETRIS")) / 2, "TETRIS");

                // Print each option with highlighting
                for (int i = 0; i < num_options; ++i) {
                    attron(A_BOLD);
                    if (choice == i) {
                        mvprintw(i + 2, (xMax - strlen(options[i]))/2 - 2, "%s" ,">");
                        attron(A_REVERSE);// Highlight the current option
                        mvprintw(i + 2, (xMax - strlen(options[i]))/2, "%s", options[i]);
                        attroff(A_REVERSE);
                    } else {
                        mvprintw(i + 2, (xMax - strlen(options[i]))/2, "%s", options[i]);
                    }
                    attroff(A_BOLD);
                }

                refresh();

                // Get user input (arrow keys)
                int key = getch();
                switch (key) {
                    case KEY_UP:
                        choice = (choice - 1 + num_options) % num_options;
                        break;
                    case KEY_DOWN:
                        choice = (choice + 1) % num_options;
                        break;
                    case 10:  // Enter key
                        isSelected = true;
                        // Select highlighted option
                        clear();
                        if (choice == 0) {
                            printw("You selected Option 1\n");
                            getch();
                        } else if (choice == 1) {
                            printw("You selected Option 2\n");
                            scoreboardMenu();
                        } else if (choice == 2) {
                            break;
                        }
                        break;
                    default:
                        break;
                }

                // Exit on 'q' key
                if (key == 'q') {
                break;
                }
            }
        }
        // stampa il menu dei punteggi
        void scoreboardMenu() {
            initialize();
            char linea[64];
            char nome[32];
            char punti[10];
            getmaxyx(stdscr, yMax, xMax);
            WINDOW *win = newwin(yMax, xMax, 0, 0);
            refresh();
            box(win, 0, 0);
            curs_set(0);
            fstream file;
            file.open ("classifica.txt",ios::in);

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
            mainMenu();
        }

    protected:
    int yMax, xMax;

        // estrae il nome e il punteggio da una riga
    void ricava_nome_punti(char linea[], char punti[], char nome[]){
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

    // controlla il formato delle righe nel file classifica.txt
    bool controllo_file(){
        fstream file;
        file.open("classifica.txt", ios::in);

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
};

#endif
