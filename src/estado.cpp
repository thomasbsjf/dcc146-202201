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
#include "estado.h"

/**
 * Construtor para inicialização vazia da classe Estado
 * 
 *
*/
Estado::Estado()
{
    this->inicial = 0;
    this->final = 0;
}

/**
 * Construtor da classe Estado para inicialização com elementos
 * 
 * 
*/
Estado::Estado(int ini, int fin)
{
    this->setInicial(ini);
    this->setFinal(fin);
    //this->proximaEstado = nullptr;
}

/**
 * Destrutor da class Estado
 * 
*/
Estado::~Estado()
{
    //Estado *atual = this->primeiraEstado;
    //while (atual != nullptr)
    //{
    //    Estado *proximo = atual->proximaEstado;
    //    delete (atual);
   //     atual = proximo;
    //}
}
/**
 * Função responsável por colocar o valor do estado inicial
*/
void Estado::setInicial(int ini)
{
    this->inicial = ini;
}

/**
 * Função responsável por retornar o estado inicial
*/
int Estado::getInicial()
{
    return this->inicial;
}
/**
 * Função responsável por colocar o valor do estado final
*/
void Estado::setFinal(int fin)
{
    this->final = fin;
}

/**
 * Função responsável por retornar o estado final
*/
int Estado::getFinal()
{
    return this->final;
}

//void Estado::setEstado(Estado *Estado)
//{
//    this->primeiraEstado = Estado;
//}

/**
 * Função responsável por retornar a primeira Estado
*/
//Estado *Estado::getEstado()
//{
//    return this->primeiraEstado;
//}