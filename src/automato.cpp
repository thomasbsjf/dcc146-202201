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


/*
//Estrutura de transicao do Automato
struct Transicao
{
    int origem;
    int destino;
    string simbolo;
};
//Struct com vectors de estados iniciais e finais
struct Estado
{
    vector<int> inicial;
    vector<int> final;
};
//Struct que contem um vector com os simbolos do alfabeto do automato
struct Alfabeto
{
    vector<string> simbolos;
};

//Automato que contem um vector de transicoes, estados iniciais e finais
struct Automa
{
    vector<Transicao> transicoes;
    struct Estado estados;
    struct Alfabeto alfabeto;
};

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
    //struct Transicao transicao;
    //vector<Transicao> transicoes;
    //struct Estado estados;
    //struct Alfabeto alfabeto;


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
    vector<Alfabeto> alfabeto;
    
   // for_each(aut1.transicoes.begin(), aut1.transicoes.end(),transicoes);{
    //    transicoes.a;
   // }
    //aut1.transicoes.transicoes
    return automato;
}