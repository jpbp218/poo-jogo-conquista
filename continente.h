#ifndef CONTINENTE_H
#define CONTINENTE_H

#include "territorio.h"
/*
 * Mandar os anos e turnos nas produçoes
 * Consertar a atualizaçao da montanha
 * 
 */
class Inicial: public Territorio{
    string nome;
    public:
        Inicial(const Inicial &d);
        Inicial();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const;
        
       Territorio *Clone();
};

class Continente:  public Territorio{
    public:
        Continente();
        Continente(const Continente &d);      
};

class Planicie: public Continente{
    static int nPlanicie;
    string nome;
    
    public:
        Planicie(const Planicie &d);
        Planicie();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const;
        
        Territorio *Clone();
};

class Montanha: public Continente{
    static int nMontanha;
    string nome;
    bool auxConquistado;
    int auxTurno;
    public:
        Montanha(const Montanha &d);
        Montanha();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const;
        
        virtual void setTrue(int y);
        virtual void setFalse();
        
        Territorio *Clone();
};

class Fortaleza: public Continente{
    static int nFortaleza;
    string nome;
    public:
        Fortaleza(const Fortaleza &d);
        Fortaleza();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const; 
        
        Territorio *Clone();
};

class Mina: public Continente{
    static int nMina;
    string nome;
    public:
        Mina(const Mina &d);
        Mina();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const; 
        
        Territorio *Clone();
};

class Duna: public Continente{
    static int nDuna;
    string nome;
    public:
        Duna(const Duna &d);
        Duna();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const;
        
       Territorio *Clone();
};

class Castelo: public Continente{
    static int nCastelo;
    string nome;
    public:
        Castelo(const Castelo &d);
        Castelo();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const;
        
        Territorio *Clone();
};

#endif /* CONTINENTE_H */

