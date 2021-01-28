#include "continente.h"

int Planicie::nPlanicie = 1;
int Montanha::nMontanha = 1;
int Fortaleza::nFortaleza = 1;
int Mina::nMina = 1;
int Duna::nDuna = 1;
int Castelo::nCastelo = 1;

Inicial::Inicial(const Inicial &outro):Territorio(outro){
    *this = outro;
}
Inicial::Inicial(){
    nome = "Territorio Inicial";
}
string Inicial::getNome() const{
    return nome;
}
int Inicial::getResistencia() const{
    return 9;
}
int Inicial::getProducaoOuro(int turno) const{
    return 1;
}
int Inicial::getProducaoP(int turno) const{
    return 1;
}
int Inicial::getPontos() const{
    return 0;
}
Territorio* Inicial::Clone(){
    return new Inicial(*this);
}


Continente::Continente(const Continente &outro):Territorio(outro){}
Continente::Continente(){}


Planicie::Planicie(const Planicie &outro):Continente(outro){
    *this = outro;
}
Planicie::Planicie(){
    nome = "planicie" + to_string(nPlanicie++);
}
string Planicie::getNome() const{
    return nome;
}
int Planicie::getResistencia() const{
    return 5;
}
int Planicie::getProducaoOuro(int turno) const{
    return 1;
}
int Planicie::getProducaoP(int turno) const{
    if(turno < 7)
        return 1;
    else 
        return 2;
}
int Planicie::getPontos() const{
    return 1;
}
Territorio* Planicie::Clone(){
    return new Planicie(*this);
}



Montanha::Montanha(const Montanha &outro):Continente(outro){
    *this = outro;
}
Montanha::Montanha(){
    nome = "montanha" + to_string(nMontanha++);
}
string Montanha::getNome() const{
    return nome;
}
int Montanha::getResistencia() const{
    return 6;
}
int Montanha::getProducaoOuro(int turno) const{
    return 0;
}
int Montanha::getProducaoP(int turno) const{
    if((turno - auxTurno) >= 2)
        return 1;
    else 
        return 0;
}
int Montanha::getPontos() const{
    return 1;
}
void Montanha::setTrue(int turno){
    if(auxConquistado == false)
        auxTurno = turno;
    auxConquistado = true;
}
void Montanha::setFalse(){
    if(auxConquistado == true)
        auxTurno = 0;
    auxConquistado = false;
}
Territorio* Montanha::Clone(){
    return new Montanha(*this);
}


Fortaleza::Fortaleza(const Fortaleza &outro):Continente(outro){
    *this = outro;
}
Fortaleza::Fortaleza(){
    nome = "fortaleza" + to_string(nFortaleza++);
}
string Fortaleza::getNome() const{
    return nome;
}
int Fortaleza::getResistencia() const{
    return 8;
}
int Fortaleza::getProducaoOuro(int turno) const{
    return 0;
}
int Fortaleza::getProducaoP(int turno) const{
    return 0;
}
int Fortaleza::getPontos() const{
    return 1;
}
Territorio* Fortaleza::Clone(){
    return new Fortaleza(*this);
}


Mina::Mina(const Mina &outro):Continente(outro){
    *this = outro;
}
Mina::Mina(){
    nome = "mina" + to_string(nMina++);
}
string Mina::getNome() const{
    return nome;
}
int Mina::getResistencia() const{
    return 5;
}
int Mina::getProducaoOuro(int turno) const{
    if(turno == 1 || turno == 2 || turno == 3 || turno == 7 || turno == 8 || turno == 9)
        return 1;
    else
        return 0;
}
int Mina::getProducaoP(int turno) const{
    return 0;
}
int Mina::getPontos() const{
    return 1;
}
Territorio* Mina::Clone(){
    return new Mina(*this);
}


Duna::Duna(const Duna &outro):Continente(outro){
    *this = outro;
}
Duna::Duna(){
    nome = "duna" + to_string(nDuna++);
}
string Duna::getNome() const{
    return nome;
}
int Duna::getResistencia() const{
    return 4;
}
int Duna::getProducaoOuro(int turno) const{
    return 0;
}
int Duna::getProducaoP(int turno) const{
    return 1;
}
int Duna::getPontos() const{
    return 1;
}
Territorio* Duna::Clone(){
    return new Duna(*this);
}


Castelo::Castelo(const Castelo &outro):Continente(outro){
    *this = outro;
}
Castelo::Castelo(){
    nome = "castelo" + to_string(nCastelo++);
}
string Castelo::getNome() const{
    return nome;
}
int Castelo::getResistencia() const{
    return 7;
}
int Castelo::getProducaoOuro(int turno) const{
    return 1;
}
int Castelo::getProducaoP(int turno) const{
    if(turno == 1 || turno == 2 || turno == 7 || turno == 8)
        return 3;
    else
        return 0;
}
int Castelo::getPontos() const{
    return 1;
}
Territorio* Castelo::Clone(){
    return new Castelo(*this);
}

