#ifndef MAPA_H
#define MAPA_H

#include "territorio.h"

class Mapa{

    vector<Territorio*> mundo; //Territórios a conquistar
    vector<Territorio*> imperio; //Territórios conquistados
public:
    Mapa();
    Mapa(const Mapa &outro);
    ~Mapa();
    void adicionaI(Territorio *p); //Adiciona ao império
    void adicionaT(Territorio *p); //Adiciona ao mundo   
    void removeT(string t); //Remove do mundo
    void removeI(); //Remove do império
       
    Territorio* obtemUltimo();
    Territorio* encontra(string nome); //Pesquisa um território pelo seu nome
    
    string obtemStringMundo(int turno) const; //Lista os territórios do mundo
    string obtemStringImperio(int turno) const; //Lista os territórios do império
    string obtemTerritorio(string nome,int turno) const; //Lista os dados de um território especifico
    
    bool verificaT(); //Verifica se existe pelo menos um território no vetor mundo
    
    int obtemOuroGerado(int turno); //Obtém o total de ouro produzido pelo império num determinado turno
    int obtemProdutoGerado(int turno); //Obtém o total de produtos produzidos pelo império num determinado turno
    int totalPontos(); // OBTEM PONTOS PRODUZIDOS NO TURNO
    
    int totalI();
    void verificaMontanha(int y);
   
    Mapa &operator=(const Mapa &outro);
    
};

#endif /* MAPA_H */

