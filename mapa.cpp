#include "mapa.h"
#include "configuracao.h"
#include "jogo.h"
#include "continente.h"
Mapa::Mapa(){
    adicionaI(new Inicial());
}

Mapa::Mapa(const Mapa& outro){
    *this = outro;
}

Mapa::~Mapa()
{
    vector<Territorio *>::iterator it = mundo.begin();
    while (it != mundo.end())
    {
        if(mundo.size() > 0){ 
            delete *it;           
            it++;
        }    
    }

    it = imperio.begin();
    while (it != imperio.end())
    {
        if(imperio.size() > 0){ 
            delete *it;           
            it++;
        }        
    }
}

void Mapa::adicionaI(Territorio *p)
{
    imperio.push_back(p);
}

void Mapa::adicionaT(Territorio *p)
{
    mundo.push_back(p);
}

void Mapa::removeT(string t)
{
    vector<Territorio *>::iterator it = mundo.begin();
    while (it != mundo.end())
    {
        if ((*it)->getNome().compare(t) == 0)
        {
            it = mundo.erase(it);
            return;
        }
        it++;
    }
}

void Mapa::removeI(){
    imperio.pop_back();
}

Territorio *Mapa::obtemUltimo(){
    return imperio.back();
}

Territorio *Mapa::encontra(string nome)
{
    vector<Territorio *>::const_iterator it = mundo.begin();

    while (it != mundo.end())
    {
        if ((*it)->getNome().compare(nome) == 0)
        {
            return (*it);
        }
        it++;
    }
    return nullptr;
}


string Mapa::obtemStringMundo(int turno) const
{
    ostringstream oss;

    vector<Territorio *>::const_iterator it = mundo.begin();

    while (it != mundo.end())
    {
        oss << "Nome: " << (*it)->getNome() << endl;
        oss << " - Resistencia: " << (*it)->getResistencia() << endl;
        oss << " - Ouro: " << (*it)->getProducaoOuro(turno) << endl;
        oss << " - Produtos: " << (*it)->getProducaoP(turno) << endl;
        oss << " - Pontos: " << (*it)->getPontos() << endl;
        it++;
    }
    return oss.str();
}

string Mapa::obtemStringImperio(int turno) const
{
    ostringstream oss;

    vector<Territorio *>::const_iterator it = imperio.begin();

    while (it != imperio.end())
    {
        oss << "Nome: " << (*it)->getNome() << endl;
        oss << " - Resistencia: " << (*it)->getResistencia() << endl;
        oss << " - Ouro: " << (*it)->getProducaoOuro(turno) << endl;
        oss << " - Produtos: " << (*it)->getProducaoP(turno) << endl;
        oss << " - Pontos: " << (*it)->getPontos() << endl;
        it++;
    }
    return oss.str();
}

string Mapa::obtemTerritorio(string nome,int turno) const
{
    ostringstream oss;
    vector<Territorio *>::const_iterator it = mundo.begin();
    while (it != mundo.end())
    {
        if ((*it)->getNome() == nome)
        {
            oss << "Nome: " << (*it)->getNome() << endl;
            oss << " - Resistencia: " << (*it)->getResistencia() << endl;
            oss << " - Ouro: " << (*it)->getProducaoOuro(turno) << endl;
            oss << " - Produtos: " << (*it)->getProducaoP(turno) << endl;
            oss << " - Pontos: " << (*it)->getPontos() << endl;
            return oss.str();
        }
        ++it;
    }
    
    it = imperio.begin();
    while (it != imperio.end())
    {
        if ((*it)->getNome() == nome)
        {
            oss << "Nome: " << (*it)->getNome() << endl;
            oss << " - Resistencia: " << (*it)->getResistencia() << endl;
            oss << " - Ouro: " << (*it)->getProducaoOuro(turno) << endl;
            oss << " - Produtos: " << (*it)->getProducaoP(turno) << endl;
            oss << " - Pontos: " << (*it)->getPontos() << endl;
            return oss.str();
        }
        ++it;
    }
    oss << "[AVISO] TERRITORIO INEXISTENTE [AVISO]" << endl;
    return oss.str();
}

bool Mapa::verificaT()
{
    if (mundo.size() > 0)
        return true;
    else
        return false;
}

int Mapa::obtemOuroGerado(int turno)
{
    int total = 0;
    vector<Territorio *>::iterator it = imperio.begin();
    while (it != imperio.end())
    {
        total += (*it)->getProducaoOuro(turno);
        ++it;
    }
    return total;
}

int Mapa::obtemProdutoGerado(int turno)
{
    int total = 0;
    vector<Territorio *>::iterator it = imperio.begin();
    while (it != imperio.end())
    {
        total += (*it)->getProducaoP(turno);
        ++it;
    }
    return total;
}

int Mapa::totalPontos()
{
    int total = 0;
    vector<Territorio *>::iterator it = imperio.begin();
    while (it != imperio.end())
    {
        total += (*it)->getPontos();
        ++it;
    }
    if (mundo.size() == 0){
        aviso("[AVISO] BONUS IMPERADOR SUPREMO [AVISO]");
        return total + 3;        
    }
    else
        return total;
}

int Mapa::totalI(){
    return imperio.size();
}

void Mapa::verificaMontanha(int turnos){
    int i;
    for(i = 0; i < mundo.size(); i++)
        mundo[i]->setFalse();
    for(i = 0; i < imperio.size(); i++)
        imperio[i]->setTrue(turnos);
}

Mapa &Mapa::operator=(const Mapa &outro) {

    for (vector<Territorio *>::iterator it = mundo.begin(); it != mundo.end(); ++it) //Limpa o vetor para onde serão copiados os territorios
        if (mundo.size() > 0)
            delete *it;
    mundo.clear();
    for (vector<Territorio *>::iterator it = imperio.begin(); it != imperio.end(); ++it) //Limpa o vetor para onde serão copiados os territorios
        if (imperio.size() > 0)
            delete *it;
    imperio.clear();

    for (vector<Territorio *>::const_iterator it = outro.mundo.begin(); it != outro.mundo.end(); ++it) //Copia do outro vetor para o vetor
        mundo.push_back((*it)->Clone());

    for (vector<Territorio *>::const_iterator it = outro.imperio.begin(); it != outro.imperio.end(); ++it) //Copia do outro vetor para o vetor
        imperio.push_back((*it)->Clone());

    return *this;
}