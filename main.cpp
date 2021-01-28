#include <iostream>
#include <cstdlib>
#include "mapa.h"
#include "configuracao.h"
#include "jogo.h"
#include "menu.h"

using namespace std;


int main(int argc, char **argv)
{

 
    Mapa cont;
    Configuracao c(cont);
    Jogo j(cont);
    Menu t(cont,c,j);

    if(!t.configura())
        return 0;
    limpa();
    t.combate();
    return 0;
}
