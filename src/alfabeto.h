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
private:
    vector<string> alfabeto;

public:
    Alfabeto();
    Alfabeto(string string);
    ~Alfabeto();

    void elementoAlfabeto(string string);
    void addSimbolo(string simbolo);
    // vec getDestino();
};

#endif // ALFABETO_H_INCLUDED