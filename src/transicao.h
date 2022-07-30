// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef TRANSICAO_H_INCLUDED
#define TRANSICAO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "estado.h"

using namespace std;

class Transicao
{
private:
    int origem, destino;
    string simbolo;
public:
    Transicao();
    Transicao(int origem, int destino, string simbolo);
    ~Transicao();

    void setOrigem(int ori);
    void setSimbolo(string simb);
    void setDestino(int dest);
    int getOrigem();
    string getSimbolo();
    int getDestino();

};

#endif // TRANSICAO_H_INCLUDED