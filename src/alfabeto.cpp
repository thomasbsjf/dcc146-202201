// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <stack>
#include <regex>
#include "alfabeto.h"
#include "transicao.h"

/**
 * Construtor para inicialização vazia da classe Alfabeto
 *
 *
 */
Alfabeto::Alfabeto()
{
}

/**
 * Destrutor da class Alfabeto
 *
 */
Alfabeto::~Alfabeto()
{
}

Alfabeto geraAlfabetoTransicoes(vector<Transicao> transicoes)
{
    Alfabeto alfabeto;
    
    for (auto t : transicoes)
    {        
        alfabeto.simbolos.push_back(t.simbolo);
    }

    return alfabeto;
}