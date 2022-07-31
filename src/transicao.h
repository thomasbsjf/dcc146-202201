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
public:
    int origem, destino;
    string simbolo;
    Transicao();
    ~Transicao();
};

#endif // TRANSICAO_H_INCLUDED