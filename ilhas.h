#ifndef ILHAS_H
#define ILHAS_H

#include "territorio.h"

class Ilha: public Territorio{  
    public:
        Ilha();
        Ilha(const Ilha &d);
        
       
};

class Refugio: public Ilha{
    static int nRefugio;
    string nome;
    public:
        Refugio(const Refugio &d);
        Refugio();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const; 
        
        Territorio *Clone();
};

class Pescaria: public Ilha{
    static int nPescaria;
    string nome;
    public:
        Pescaria(const Pescaria &d);
        Pescaria();
        string getNome() const;
        int getResistencia() const;
        int getProducaoOuro(int turno) const;
        int getProducaoP(int turno) const;
        int getPontos() const; 
        
        Territorio *Clone();
};

#endif /* ILHAS_H */

