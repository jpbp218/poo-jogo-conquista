#ifndef MENU_H
#define MENU_H

#include "territorio.h"
class Mapa;
class Configuracao;
class Jogo;

class Menu{
    Mapa * map;
    Configuracao * conf;
    Jogo * game;

    
public:
    Menu(Mapa &m, Configuracao & c,Jogo & j);
    ~Menu();
    bool configura();
    void combate();
    bool fim(string comando);
    void trocaJogo(Jogo *c);
};

#endif /* MENU_H */

