#include "configuracao.h"
#include "continente.h"
#include "ilhas.h"
Configuracao::Configuracao(Mapa &t):vMont(false) {
    c = &t;
}

Configuracao::~Configuracao() {
}

void Configuracao::comandosP(string comando) {
    istringstream iss(comando);
    int i;
    string msg;
    string tipoT[8] = {"planicie", "montanha", "fortaleza", "mina", "duna", "castelo","refugio","pescaria"};
    string cmd[4] = {"carrega", "cria", "lista", "avancar"};
    iss >> msg;
    for (i = 0; cmd[i] != msg; ++i);

    switch (i) {
        case 0: // carrega <nomeFicheiro>
            if (iss >> msg) {
                carregaT(msg);
            } else {
                erro("[ERRO] carrega <nomeFicheiro> [ERRO]");
            }
            break;
        case 1: //Comando cria
            if (iss >> msg) { //Verifica o tipo de território a construir -> tipo

                for (i = 0; tipoT[i] != msg; ++i)
                    ;
                int quanT = 0; //Quantidade de territórios
                iss >> quanT;
                if (quanT > 0) { //Quantos vao ser construidos -> n
                    switch (i) {
                        case 0:
                            for (i = 1; i <= quanT; ++i) 
                                c->adicionaT(new Planicie());
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Planicies" << endl;
                            else
                                cout << "Criada 1 Planicie" << endl;
                            break;
                        case 1:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Montanha());
                            vMont = true;
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Montanhas" << endl;
                            else
                                cout << "Criada 1 Montanha" << endl;
                            break;
                        case 2:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Fortaleza());
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Fortalezas" << endl;
                            else
                                cout << "Criada 1 Fortaleza" << endl;
                            break;
                        case 3:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Mina());
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Minas" << endl;
                            else
                                cout << "Criada 1 Mina" << endl;
                            break;
                        case 4:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Duna());
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Dunas" << endl;
                            else
                                cout << "Criada 1 Duna" << endl;
                            break;
                        case 5:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Castelo());
                            if(quanT != 1)
                                cout << "Criados " << quanT << " Castelos" << endl;
                            else
                                cout << "Criado 1 Castelo" << endl;
                            break;
                        case 6:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Refugio());
                            if(quanT != 1)
                                cout << "Criados " << quanT << " Refugios" << endl;
                            else
                                cout << "Criado 1 Refugio" << endl;
                            break;
                        case 7:
                            for (i = 1; i <= quanT; ++i)
                                c->adicionaT(new Pescaria());
                            if(quanT != 1)
                                cout << "Criadas " << quanT << " Pescarias" << endl;
                            else
                                cout << "Criada 1 Pescaria" << endl;
                            break;
                        default:
                            erro("[ERRO] Tipo invalido [ERRO]");
                            cout << "Lista: 'planicie', 'montanha', 'fortaleza', 'mina', 'duna', 'castelo', 'refugio', 'pescaria'" << endl;
                            break;
                    }
                } else if (quanT <= 0)
                    erro("[ERRO] Valor invalido [ERRO]");
                else
                    erro("[ERRO] cria <tipo> <n> [ERRO]");

            } else {
                erro("[ERRO] cria <tipo> <n> [ERRO]");
            }
            break;
        case 2:
            if(c->verificaT())
                cout << lista();
            else
                erro("[ERRO] Nao existem territorios [erro]");
            break;
        case 3:
            if (!c->verificaT()) {
                erro("[ERRO] ADICIONE PELO MENOS 1 TERRITORIO [ERRO]");
            }
            break;
        default:
            if (msg != "sair") {
                erro("[ERRO] Comando inexistente [ERRO]");
                cout << "Lista: 'cria', 'carrega', 'avancar', 'sair'" << endl;
            }

            break;
    }
}

void Configuracao::carregaT(string nomeF) {
    ifstream fich(nomeF);
    string linha;

    if (fich.is_open()) {
        while (getline(fich, linha)) {
            comandosP(linha);
        }
        fich.close();
    } else {
        erro("[ERRO] Ficheiro inexistente [ERRO]");
    }
}


string Configuracao::lista() const{
    ostringstream oss;
    oss << "Territorios Criados: " << endl; //Territorios Criados
    oss << c->obtemStringMundo(1);
    return oss.str();
}

bool Configuracao::obtemMont(){
    return vMont;
}