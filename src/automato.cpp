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
#include "fecho.h"

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

struct State
{
    int origem;
    int destino;
};

int ultimoEstado(Automato aut)
{
    Automato automato;
    int totalEstados;
    vector<Transicao> ori, dest;
    ori = automato.transicoes;
    dest = automato.transicoes;

    sort(ori.begin(), ori.end(), [](const Transicao &a, const Transicao &b)
         { return (a.origem < b.origem); });
    sort(dest.begin(), dest.end(), [](const Transicao &a, const Transicao &b)
         { return (a.destino < b.destino); });
    if (ori.back().origem > dest.back().destino)
    {
        totalEstados = ori.back().origem;
        return totalEstados;
    }
    totalEstados = dest.back().destino;
    return totalEstados;
    // sort( s.begin(), s.end(), [](const staff &a, const staff &b){ return (a.id < b.id);});
}

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

Automato automatoConcatenacao(Automato aut1, Automato aut2)
{
    Automato automato;
    vector<Transicao> transicoes;
    Alfabeto alfabeto;
    Estado estados;

    for (auto v : aut1.transicoes)
    {
        transicoes.push_back(v);
    }
    for (auto v : aut2.transicoes)
    {
        transicoes.push_back(v);
    }
    for (auto v : aut1.alfabeto.simbolos)
    {
        alfabeto.simbolos.push_back(v);
    }
    for (auto v : aut2.alfabeto.simbolos)
    {
        alfabeto.simbolos.push_back(v);
    }
    for (auto v : aut1.estados.inicial)
    {
        for (auto x : aut2.estados.final)
        {
            Transicao transicao;
            transicao.origem = x;
            transicao.destino = v;
            transicao.simbolo = "lambda";
        }
    }
    automato.alfabeto = alfabeto;
    automato.transicoes = transicoes;
    for (auto v : aut2.estados.inicial)
    {
        estados.inicial.push_back(v);
    }
    for (auto v : aut1.estados.final)
    {
        estados.final.push_back(v);
    }
    automato.estados = estados;

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

void montaAutomato(Tag *tag)
{
    int totalEstados = 0;
    stack<Automato> pilha;

    // Tag *novaTag = tag;

    for (int i = 0; i < tag->descricao.length(); i++)
    {
        if (tag->descricao[i] == '+')
        {
            Automato aut1 = pilha.top();
            pilha.pop();
            Automato aut2 = pilha.top();
            pilha.pop();
            totalEstados = ultimoEstado(aut1);
            Automato automato = automatoUniao(aut1, aut2, totalEstados);

            pilha.push(automato);
        }
        else if (tag->descricao[i] == '*')
        {
            Automato aut1 = pilha.top();
            pilha.pop();
            Automato automato = criaFecho(aut1);
            pilha.push(automato);
        }
        else if (tag->descricao[i] == '.')
        {
            Automato aut1 = pilha.top();
            pilha.pop();
            Automato aut2 = pilha.top();
            pilha.pop();
            Automato automato;
            // automato = automatoConcatenacao(aut1, aut2);
            pilha.push(automato);
        }
        else
        {
            string simbolo(1, tag->descricao[i]);
            Automato automato = automatoSimples(simbolo, totalEstados);
            totalEstados = totalEstados + 2;
            pilha.push(automato);
        }
    }
    // Automato AF = pilha.pop()
    // AFlambda.push(AF);
    // fechoLambda(AF);
}

// testar com calma
/*
void fechoLambda(Automato aut)
{
    Fecho fecho;
    vector<State> states;
    vector<Transicao> auxiliarTransicao;
    vector<Transicao> transicoes;
    for (auto e : aut.transicoes)
    {
        State state;
        state.destino = e.destino;
        state.origem = e.origem;
        states.push_back(state);
    }

    vector<State>::iterator it;
    it = std::unique(states.begin(), states.end());   // Cria um vector somente com valores unicos presentes no alfabeto
    states.resize(std::distance(states.begin(), it)); // Da Resize no vector de simbolos de states somente com valores unicos

    sort(states.begin(), states.end(), [](const State &a, const State &b)
         { return (a.origem > b.origem); });

    auxiliarTransicao = aut.transicoes; // copia as transicoes
    remove_if(auxiliarTransicao.begin(), auxiliarTransicao.end(), [](const Transicao &t)
              { return (t.simbolo != "lambda"); }); // remove do vector todos elementos que o simbolo nao e lambda

    for (auto s : states)
    {
        vector<Transicao> aux = auxiliarTransicao;
        vector<Transicao> transicoes1;
        vector<Transicao> aux2;
        vector<State> transicoesFecho;
        remove_if(aux.begin(), aux.end(), [&](const Transicao &t)
                  { return (t.origem != s.origem); }); // remove todas as transicoes em que a origem da transicao nao e igual a do estado atual ??
        transicoes1 = aux;

        if (transicoes1.size() > 0)
        {
            //   transicoesFecho = s; //ARRUMAR

            for (auto t : transicoes1)
            {
                // transicoesFecho.push_back(t.destino); //ARRUMAR
                // aux2.push_back(t.destino); // ARRUMAR
            }
        }
        bool stop = true;
        while (stop)
        {
            for (auto a : aux2)
            {
                remove_if(aux.begin(), aux.end(), [&](const Transicao &t)
                          { return (t.origem != a.origem); }); // ajustar comment
                vector<Transicao> transicoes2 = aux;
            }
        }
    }
}
*/

