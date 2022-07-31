// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef ALFABETO_H_INCLUDED
#define ALFABETO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "estado.h"
#include <vector>

using namespace std;

class Alfabeto
{   
public:
    vector<string> simbolos;
    Alfabeto();
    ~Alfabeto();
};

#endif // ALFABETO_H_INCLUDED