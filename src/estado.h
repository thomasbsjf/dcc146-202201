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
#include <vector>

using namespace std;

class Estado
{
public:
    vector<int> inicial;
    vector<int> final;
    Estado();
    ~Estado();
};

#endif // ESTADO_H_INCLUDED