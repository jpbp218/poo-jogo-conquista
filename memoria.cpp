#include "memoria.h"

Memoria::Memoria(){
}

Memoria::~Memoria() {
    vector<Jogo *>::iterator it = mem.begin();
    while (it != mem.end()) {
        if (mem.size() > 0) {
            delete *it;
            it++;
        }
    }
}

void Memoria::grava(Jogo *p){
    mem.push_back(p);
}

Jogo *Memoria::ativa(string nome) {
    vector<Jogo *>::iterator it = mem.begin();
    
    while (it != mem.end()) {
        if((*it)->obtemNome().compare(nome) == 0)
        {
            return *it; 
        }
        ++it;
    }
    return nullptr;
}

bool Memoria::apaga(string nome){
    vector<Jogo *>::iterator it = mem.begin();
    while (it != mem.end())
    {
        if ((*it)->obtemNome().compare(nome) == 0)
        {
            it = mem.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool Memoria::verificaN(string nome){
    vector<Jogo *>::iterator it = mem.begin();
    while (it != mem.end())
    {
        if ((*it)->obtemNome().compare(nome) == 0)
        {
            return true;
        }
        it++;
    }
    return false;
}

string Memoria::obtemStringJogos(){
    vector<Jogo *>::iterator it = mem.begin();
    ostringstream oss;
    while (it != mem.end())
    {
        oss << (*it)->obtemNome() << "\t";
        it++;
    }
    return oss.str();
}