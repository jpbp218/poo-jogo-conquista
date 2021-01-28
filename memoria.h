#ifndef MEMORIA_H
#define MEMORIA_H


#include "jogo.h"

class Memoria{
    vector<Jogo*> mem;
public:
    Memoria();
    ~Memoria();
    void grava(Jogo *p); //Usado para guardar o jogo
    Jogo *ativa(string n); //Usado para ativar algum save do jogo
    bool apaga(string n); //Usado para apagar algum save do jogo
    bool verificaN(string nome);
    string obtemStringJogos(); // Obtem uma string com todos os jogos gravados disponiveis
};

#endif /* MEMORIA_H */

