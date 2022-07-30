// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef ESTADO_H_INCLUDED
#define ESTADO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "estado.h"

using namespace std;

class Estado
{
private:
    int inicial, final;

public:
    Estado();
    Estado(int inicial, int final);
    ~Estado();

    void setInicial(int inicial);
    void setFinal(int final);
    int getInicial();
    int getFinal();

};

#endif // ESTADO_H_INCLUDED