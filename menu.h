#ifndef MENU_H
#define MENU_H
#include <cstring>
#include <fstream>
#include "gioco.h"
#include "classifica.h"
using namespace std;

class mainMenu{
    public:
    void Menu();
    
    protected:
        int yMax, xMax;
        Classifica classifica;
};

#endif