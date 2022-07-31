// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef FECHO_H_INCLUDED
#define FECHO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "estado.h"
#include "transicao.h"

using namespace std;

class Fecho
{
public:
    //int origem, destino;
    Estado estado;
    vector<Transicao> transicoes;
    Fecho();
    ~Fecho();
};

#endif // FECHO_H_INCLUDED