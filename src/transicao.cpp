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
#include "transicao.h"

/**
 * Construtor para inicialização vazia da classe Transicao
 * 
 *
*/
Transicao::Transicao()
{
    this->origem = 0;
    this->destino = 0;
    this->simbolo = nullptr;
}

/**
 * Construtor da classe Transicao para inicialização com elementos
 * 
 * 
*/
Transicao::Transicao(int ori, int dest, string simb)
{
    this->setOrigem(ori);
    this->setDestino(dest);
    this->setSimbolo(simb);
    //this->proximaTransicao = nullptr;
}

/**
 * Destrutor da class Transicao
 * 
*/
Transicao::~Transicao()
{
    //Transicao *atual = this->primeiraTransicao;
    //while (atual != nullptr)
    //{
    //    Transicao *proximo = atual->proximaTransicao;
    //    delete (atual);
   //     atual = proximo;
    //}
}
/**
 * Função responsável por colocar o valor da primeira Transicao
*/
void Transicao::setOrigem(int ori)
{
    this->origem = ori;
}

/**
 * Função responsável por retornar a primeira Transicao
*/
int Transicao::getOrigem()
{
    return this->origem;
}
/**
 * Função responsável por colocar o valor da primeira Transicao
*/
void Transicao::setDestino(int dest)
{
    this->destino = dest;
}

/**
 * Função responsável por retornar a primeira Transicao
*/
int Transicao::getDestino()
{
    return this->destino;
}
/**
 * Função responsável por colocar o valor da primeira Transicao
*/
void Transicao::setSimbolo(string simb)
{
    this->simbolo = simb;
}

/**
 * Função responsável por retornar a primeira Transicao
*/
string Transicao::getSimbolo()
{
    return this->simbolo;
}
//void Transicao::setTransicao(Transicao *Transicao)
//{
//    this->primeiraTransicao = Transicao;
//}

/**
 * Função responsável por retornar a primeira Transicao
*/
//Transicao *Transicao::getTransicao()
//{
//    return this->primeiraTransicao;
//}