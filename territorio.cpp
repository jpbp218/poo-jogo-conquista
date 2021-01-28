#include "territorio.h"
#include "mapa.h"

Territorio::Territorio(){
}

Territorio::Territorio(Territorio *p){
    *this = *p;
}

Territorio & Territorio::operator=(const Territorio & outro){
    if (this == &outro)
            return *this;
    
    return *this;
}

