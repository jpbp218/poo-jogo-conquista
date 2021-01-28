#ifndef JOGO_H
#define JOGO_H

#include "mapa.h"
class Memoria;
class Jogo {
    Mapa *d; 

    string nome,ultimo;
    int nTurnos, nFase, fatorSorte; //Informação do jogo
    int unidadeMilitar, armazem, cofre; //Recursos e força militar
    bool drones, misseis, defesa, bolsa, banco; //Tecnologias
    bool recolha,compraM,compraT; //Flags
public:
    Jogo(Mapa & t);
    Jogo();
    Jogo(const Jogo &outro);
    ~Jogo();
    
    Jogo *comandosJ(string comando,Memoria &c); //Escolher a fase
    bool fase1(string comando);
    void fase2(string comando);
    bool fase3(string comando);
    void fase4(); 
    
    int conquista(Territorio *p); //Indicar se conquistou
    bool verifica(); //No caso de ser uma pescaria ou refugio precisamos de saber as condições
    bool verificaConquista(string nome); //Aplicar a conquista
    
    void recolhe(); //Recolhe os recursos produzidos pelo império
    void troca(string comando); //Para fazer as trocas de recursos
    void maisOuro(); //Troca 2 produtos por 1 ouro
    void maisProdutos(); //Troca 2 ouros por 1 produto
        
    void adquireMilitar(); //Comando maismilitar
    void compraMilitar(); //Atualiza recursos e unidades militares
    bool compraTecnologias(string nome); //Verifica se pode ou nao comprar tecnologias e atualiza recursos
    
    void adicionaOuro(int total); //Modifica o total de ouro no cofre 
    void adicionaProd(int total); //Modifica o total de produtos no armazem
    
    void fevento(string evento); //Comando para ativar um evento
    void recurso(); //Evento de recursos
    void invasao(); //Evento de invasão inimiga
    void defesaI(int vAtaque,Territorio *p); //Regista se conseguiu defender
    void alianca(); //Evento de unidades militares
    
    void tomaTerr(string msg); //Toma um território
    void tomaTec(string msg); //Toma uma tecnologia
    
    int obtemLimiteUM() const; //Devolve o limite de unidades militares
    int obtemLimiteA() const; //Devolve o limite do armazém
    int obtemLimiteC() const; //Devolve o limite do cofre
    int obtemFase() const; //Devolve a fase
    int obtemTurnos() const; //Devolve o turno
    int obtemAno() const; //Devolve o ano
    
    string avisoInvalido(string msg); //Caso nenhum comando seja válido
    
    string lista() const; //Imprime os dados do jogo
    string lista(string nome) const; //Imprime os dados de um territorio
    string obtemExistentes() const;
    string devolveEstado(string nome) const;
    string ultimoEvento() const;
    int totalTec() ; //Verifica quantas tecnologias foram adquiridas e devolve o total
    bool contaTec(); //Verifica se todas as tecnologias foram adquiridas
    
    void carregaC(string nomeF,Memoria &m);
    string obtemNome() const;
    Mapa *obtemMapa() const;
    Jogo &operator=(const Jogo &outro);
};

#endif /* JOGO_H */

