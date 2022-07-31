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
#include "automato.h"
#include "tag.h"
#include "transicao.h"
#include "alfabeto.h"
#include "estado.h"

/**
 * Construtor para inicialização vazia da classe Automato
 *
 *
 */
Automato::Automato()
{

    // this-> = nullptr;
}
Automato::Automato(Transicao transi, Estado est, Alfabeto alf)
{
    this->transicao = transi;
    this->estado = est;
    this->alfabeto = alf;
    // this-> = nullptr;
}

/**
 * Destrutor da class Automato
 *
 */
Automato::~Automato()
{
}

Automato automatoSimples(string simbolo, int i)
{
    int ini = i + 1;
    int fin = i + 2;
    Transicao *transicao = new Transicao(ini, fin, simbolo);
    Estado *estado = new Estado(ini, fin);
    Alfabeto *alfabeto = new Alfabeto(simbolo);
    Automato *automato = new Automato(*transicao, *estado, *alfabeto);
    return *automato;
}