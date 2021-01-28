#include "menu.h"
#include "consola.h"
#include "configuracao.h"
#include "jogo.h"
#include "memoria.h"

Menu::Menu(Mapa &m, Configuracao & c,Jogo & j){
    map = &m;
    conf = &c;
    game = &j;

}

Menu::~Menu() {
}

bool Menu::configura() {
    string comando;
    
    titulo("FASE DE CONFIGURACAO\n");

    while ((comando != "avancar" || !map->verificaT())) {
        cout << "Digite um comando: ";
        getline(cin, comando);
        transform(comando.begin(), comando.end(), comando.begin(), ::tolower); // Converte todos os caracteres para minusculas
        if (comando == "sair"){
            limpa();
            cout << "SAIU DO JOGO" << endl;
            return false;
        }
        conf->comandosP(comando);
    }
    return true;
}

void Menu::combate() {
    string comando;
    Jogo *aux;
    Memoria c;
    titulo("FASE DE COMBATE");

    while (comando != "desisto" && game->obtemTurnos() <= 12) {
        cout << "Fase " << game->obtemFase() << endl;
        cout << "Digite um comando: ";
        getline(cin, comando);
        transform(comando.begin(), comando.end(), comando.begin(), ::tolower);
        if (conf->obtemMont())
            map->verificaMontanha(game->obtemTurnos());
        if ((aux = game->comandosJ(comando, c)) != nullptr) {
            trocaJogo(aux);
        }
    }
    
    limpa();
    
    aviso("[AVISO] ACABOU O JOGO [AVISO]");
    if(fim(comando))
        cout << "DESISTENCIA" << endl;
    else
        cout << "TOTAL DE PONTOS: " << (map->totalPontos() + game->totalTec()) << endl;
    
}

bool Menu::fim(string comando){
    if (comando == "desisto")
        return true;
    else  
        return false;  
}

void Menu::trocaJogo(Jogo *c){
    delete game;
    game = new Jogo(*c);
}