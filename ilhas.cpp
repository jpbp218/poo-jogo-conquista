#include "ilhas.h"

int Refugio::nRefugio = 1;
int Pescaria::nPescaria = 1;

Ilha::Ilha(const Ilha &outro):Territorio(outro){}
Ilha::Ilha(){}

Refugio::Refugio(const Refugio &outro):Ilha(outro){}
Refugio::Refugio(){
    nome = "refugio" + to_string(nRefugio++);
}
string Refugio::getNome() const{
    return nome;
}
int Refugio::getResistencia() const{
    return 9;
}
int Refugio::getProducaoOuro(int turno) const{
    return 1;
}
int Refugio::getProducaoP(int turno) const{
    return 0;
}
int Refugio::getPontos() const{
    return 2;
}
Territorio* Refugio::Clone(){
    return new Refugio(*this);
}


Pescaria::Pescaria(const Pescaria &outro):Ilha(outro){}
Pescaria::Pescaria(){
    nome = "pescaria" + to_string(nPescaria++);
}
string Pescaria::getNome() const{
    return nome;
}
int Pescaria::getResistencia() const{
    return 9;
}
int Pescaria::getProducaoOuro(int turno) const{
    return 1;
}
int Pescaria::getProducaoP(int turno) const{
    if(turno < 7)
        return 2;
    else
        return 4;
}
int Pescaria::getPontos() const{
    return 2;
}
Territorio* Pescaria::Clone(){
    return new Pescaria(*this);
}

