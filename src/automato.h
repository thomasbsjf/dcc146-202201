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

using namespace std;

class Automato
{
private:
    Transicao transicao;
    Estado estado;
    Alfabeto alfabeto;

public:
    void montaAutomato(Tag *tag);
    void estadoFinal(Automato aut);
    Automato automatoSimples(String simbolo, int i);
    Automato automatoUniao(Automato aut1, Automato au2, int i);
    Automato automatoConcatenacao(Automato aut1, aut2);
    Automato criaFecho(Automato aut);

};

#endif // AUTOMATO_H_INCLUDED