#ifndef MENU_H
#define MENU_H
#include <cstring>
#include <fstream>

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

        void scoreboardMenu() {
            initialize();
            //codice qui
            mainMenu();
        }
    protected:
    int yMax, xMax;
};

#endif
