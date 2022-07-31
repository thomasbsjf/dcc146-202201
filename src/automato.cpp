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
 */
Automato::Automato()
{
}

/**
 * Destrutor da class Automato
 */
Automato::~Automato()
{
}

/*Funcao cria um automato simples que ira conter um vector de transicoes,
  um struct estado (que contem 1 vector de estados iniciais e 1 vector de estados finais) e
  um vector de simbolos do alfabeto
*/
Automato automatoSimples(string simb, int i)
{
    int ini = i + 1;
    int fin = i + 2;

    Transicao transicao;
    vector<Transicao> transicoes;
    Estado estados;
    Alfabeto alfabeto;
    Automato automato;

    transicao.origem = ini;
    transicao.destino = fin;
    transicao.simbolo = simb;
    transicoes.push_back(transicao);

    estados.inicial.push_back(ini);
    estados.final.push_back(fin);

    alfabeto.simbolos.push_back(simb);

    automato.transicoes = transicoes;
    automato.estados = estados;
    automato.alfabeto = alfabeto;

    return automato;
}

Automato automatoUniao(Automato aut1, Automato aut2, int i)
{
    int ini = i + 1;
    int fin = i + 2;
    Automato automato;
    vector<Transicao> transicoes;
    Alfabeto alfabeto;

    for (auto t = aut1.transicoes.begin(); t != aut1.transicoes.end(); ++t)
    {
        transicoes.push_back(*t);
    }

    for (auto t = aut2.transicoes.begin(); t != aut2.transicoes.end(); ++t)
    {
        transicoes.push_back(*t);
    }
    for (auto a = aut1.alfabeto.simbolos.begin(); a != aut1.alfabeto.simbolos.end(); ++a)
    {
        alfabeto.simbolos.push_back(*a);
    }
    for (auto a = aut2.alfabeto.simbolos.begin(); a != aut2.alfabeto.simbolos.end(); ++a)
    {
        alfabeto.simbolos.push_back(*a);
    }

    for (auto f = aut1.estados.final.begin(); f != aut1.estados.final.end(); ++f)
    {
        Transicao transicao;
        transicao.origem = *f;
        transicao.destino = fin;
        transicao.simbolo = "lambda";
        transicoes.push_back(transicao);
    }

    for (auto f = aut2.estados.final.begin(); f != aut2.estados.final.end(); ++f)
    {
        Transicao transicao;
        transicao.origem = *f;
        transicao.destino = fin;
        transicao.simbolo = "lambda";
        transicoes.push_back(transicao);
    }

    for (auto i = aut1.estados.inicial.begin(); i != aut1.estados.inicial.end(); ++i)
    {
        Transicao transicao;
        transicao.origem = ini;
        transicao.destino = *i;
        transicao.simbolo = "lambda";
        transicoes.push_back(transicao);
    }

    for (auto i = aut2.estados.inicial.begin(); i != aut2.estados.inicial.end(); ++i)
    {
        Transicao transicao;
        transicao.origem = ini;
        transicao.destino = *i;
        transicao.simbolo = "lambda";
        transicoes.push_back(transicao);
    }

    alfabeto.simbolos.push_back("lambda");

    Estado estados;
    estados.inicial.push_back(ini);
    estados.final.push_back(fin);
    automato.transicoes = transicoes;
    automato.estados = estados;

    vector<string>::iterator it;
    it = std::unique(alfabeto.simbolos.begin(), alfabeto.simbolos.end());   // Cria um vector somente com valores unicos presentes no alfabeto
    alfabeto.simbolos.resize(std::distance(alfabeto.simbolos.begin(), it)); // Da Resize no vector de simbolos de alfabetos somente com valores unicos

    return automato;
}

Automato criaFecho(Automato aut)
{
    Estado estados;
    Automato automato;
    vector<Transicao> transicoes = aut.transicoes;
    Alfabeto alfabeto = aut.alfabeto;

    for (auto i : aut.estados.inicial)
    {
        estados.inicial.push_back(i);
    }

    for (auto f : aut.estados.final)
    {
        for (auto i : aut.estados.inicial)
        {
            Transicao transicao;
            transicao.origem = f;
            transicao.destino = i;
            transicao.simbolo = "lambda";
            transicoes.push_back(transicao);
        }
    }
    alfabeto.simbolos.push_back("lambda");

    vector<string>::iterator it;
    it = std::unique(alfabeto.simbolos.begin(), alfabeto.simbolos.end());   // Cria um vector somente com valores unicos presentes no alfabeto
    alfabeto.simbolos.resize(std::distance(alfabeto.simbolos.begin(), it)); // Da Resize no vector de simbolos de alfabetos somente com valores unicos

    automato.estados.inicial = estados.inicial;
    automato.estados.final = estados.inicial;
    automato.transicoes = transicoes;
    automato.alfabeto = alfabeto;

    return automato;
}