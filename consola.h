
#ifndef CONSOLA_H
#define CONSOLA_H

#include <windows.h>
#define VERMELHO 4
#define AZUL 1
#define BRANCO 7
#define CIANO 3
#define AMARELO 6
#define VERDE 2

#include <string>
#include <iostream>
using namespace std;

void limpa();
void cCiano();
void cBranco();
void cVermelho();
void cAzul();
void cAmarelo();
void cVerde();
void espera();
void erro(string const &texto);
void aviso(string const &texto);
void titulo(string const &texto);

#endif /* CONSOLA_H */

