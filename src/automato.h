// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef AUTOMATO_H_INCLUDED
#define AUTOMATO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "automato.h"
#include "tag.h"
#include "estado.h"
#include "transicao.h"
#include "alfabeto.h"

using namespace std;

class Automato
{

public:
   vector<Transicao> transicoes;
   Estado estados;
   Alfabeto alfabeto;

    Automato();
    ~Automato();

    void montaAutomato(Tag *tag);
    void estadoFinal(Automato aut);
    Automato automatoSimples(string simbolo, int i);
    Automato automatoUniao(Automato aut1, Automato au2, int i);
    Automato automatoConcatenacao(Automato aut1, Automato aut2);
    Automato criaFecho(Automato aut);
    void fechoLambda(Automato aut);
};

#endif // AUTOMATO_H_INCLUDED