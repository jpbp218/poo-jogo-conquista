#ifndef CONFIGURACAO_H
#define CONFIGURACAO_H

#include "mapa.h"
#include <algorithm>  

class Configuracao{
    Mapa *c;
    bool vMont;
public:
    Configuracao(Mapa & t);
    ~Configuracao();
    void comandosP(string comando);
    void carregaT(string nomeF);
    
    string lista() const;
    bool obtemMont();
};


#endif /* CONFIGURACAO_H */

