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

/**
 * Construtor para inicialização vazia da classe Alfabeto
 * 
 *
*/
Alfabeto::Alfabeto()
{

}

/**
 * Construtor da classe Alfabeto para inicialização com elementos
 * 
 * 
*/
Alfabeto::Alfabeto(string simbolo)
{
    this->alfabeto.push_back(simbolo);
    //this->proximaAlfabeto = nullptr;
}

/**
 * Destrutor da class Alfabeto
 * 
*/
Alfabeto::~Alfabeto()
{
    //Alfabeto *atual = this->primeiraAlfabeto;
    //while (atual != nullptr)
    //{
    //    Alfabeto *proximo = atual->proximaAlfabeto;
    //    delete (atual);
   //     atual = proximo;
    //}
}
/**
 * Função responsável por colocar o valor do estado inicial
*/
void Alfabeto::addSimbolo(string simb)
{
    this->alfabeto.push_back(simbolo);
}


//void Alfabeto::setAlfabeto(Alfabeto *Alfabeto)
//{
//    this->primeiraAlfabeto = Alfabeto;
//}

/**
 * Função responsável por retornar a primeira Alfabeto
*/
//Alfabeto *Alfabeto::getAlfabeto()
//{
//    return this->primeiraAlfabeto;
//}