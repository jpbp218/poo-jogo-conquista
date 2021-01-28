#ifndef TERRITORIO_H
#define TERRITORIO_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h> 
#include <time.h>
#include "consola.h"

using namespace std;

class Territorio{
      
public:
    Territorio();
    Territorio(Territorio *p);
    virtual ~Territorio(){}
    
    virtual string getNome() const = 0;
    virtual int getResistencia() const = 0;
    virtual int getProducaoOuro(int turno) const = 0;
    virtual int getProducaoP(int turno) const = 0;
    virtual int getPontos() const = 0;
    
    virtual void setTrue(int turno){}
    virtual void setFalse(){}
       
    Territorio & operator=(const Territorio & outro);
    virtual Territorio *Clone() = 0;
};


#endif /* TERRITORIO_H */

