// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#define BACKSLASH '\\'
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
#include "tag.h"

/**
 * Construtor para inicialização vazia da classe Tag
 * 
 *
*/
Tag::Tag()
{
    this->primeiraTag = nullptr;
    this->proximaTag = nullptr;
}

/**
 * Construtor da classe Tag para inicialização com elementos
 * 
 * 
*/
Tag::Tag(string nome, string descricao)
{
    this->setNome(nome);
    this->setDescricao(descricao);
    this->proximaTag = nullptr;
}

/**
 * Destrutor da class Tag
 * 
 * 
*/
Tag::~Tag()
{
    Tag *atual = this->primeiraTag;
    while (atual != nullptr)
    {
        Tag *proximo = atual->proximaTag;
        delete (atual);
        atual = proximo;
    }
}

/**
 * Função Responsável por incluir novas tags na lista.
 *
 * 
 * @param string line
 * @return void
*/
void Tag::adicionarTag(string line)
{
    bool start = false;
    string nome, descricao;
    for (int i = 0; i < line.length(); i++)
    {
        if (line.at(i) == ':' && !start)
        {
            start = true;
            i++;
        }
        else
        {
            if (start)
            {
                descricao += line.at(i);
            }
            else
            {
                nome += line.at(i);
            }
        }
    }
    if (this->validaTag(nome, descricao))
    {
        if (getPrimeiraTag() == nullptr)
        {
            Tag *tag = new Tag(nome, descricao);
            setPrimeiraTag(tag);
        }
        else
        {
            Tag *tag = this->getPrimeiraTag();

            while (tag->proximaTag != nullptr)
                tag = tag->proximaTag; // caminha até a ultima

            Tag *novaTag;
            novaTag = new Tag(nome, descricao);
            tag->proximaTag = novaTag; // adiciona depois da ultima
        }
        cout << "[ INFO ] TAG adicionada com sucesso!" << endl;
    }
    else
    {
        cout << "[ ERRO ] TAG inválida!" << endl;
    }
}

/**
 * Função responsável por validar a integridade da tag
 *
 * 
 * @param string nome
 * @param string descricao
 * @return boolean
*/
bool Tag::validaTag(string nome, string descricao)
{
    Tag *tag = this->getPrimeiraTag();
    while (tag != nullptr)
    {
        if (nome == tag->getNome())
        {
            return false;
        }
        tag = tag->proximaTag;
    }
    std::stack<string> stack;
    for (int i = 0; i < descricao.length(); i++)
    {
        if (descricao[i] == '*')
        {
            if (stack.size() == 0)
            {
                return false;
            }
            string aux = stack.top();
            stack.pop();
            stack.push(aux + '*');
        }
        else
        {
            if (descricao[i] == '+' || descricao[i] == '.')
            {
                if (stack.size() > 1)
                {
                    string firstElement = stack.top();
                    stack.pop();
                    string secondElement = stack.top();
                    stack.pop();
                    stack.push(firstElement + descricao[i] + secondElement);
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (descricao[i] == 92)
                {
                    i++;
                    stack.push("\\" + descricao[i]);
                }
                else
                {
                    string aux;
                    aux += descricao[i];
                    stack.push(aux);
                }
            }
        }
    }
    if (stack.size() == 1)
    {
        return true;
    }
    return false;
}

/**
 * Função responsável por listar todas as tags válidas armazenadas
 * 
 * 
 * @return void
*/
void Tag::listarTagsValidas()
{
    Tag *tag = this->getPrimeiraTag();
    while (tag != nullptr)
    {
        cout << tag->getNome() << ": " << tag->getDescricao() << endl;
        tag = tag->proximaTag;
    }
}

/**
 * Função responsável por salvar as tags em um arquivo externo
 * 
 * 
 * @param string file
 * @return void 
*/
void Tag::salvarTag(string file)
{
    Tag *tag = this->getPrimeiraTag();
    ofstream exit;
    exit.open(file);
    while (tag != nullptr)
    {
        exit << tag->getNome() << " " << tag->getDescricao() << endl;
        tag = tag->proximaTag;
    }
}

/**
 * Função responsável por retornar o nome da tag
 * 
 * 
 * @return string 
*/
string Tag::getNome()
{
    return this->nome;
}

/**
 * Função responsável por retornar a descrição da tag
 * 
 * 
 * @return string 
*/
string Tag::getDescricao()
{
    return this->descricao;
}

/**
 * Função responsável por retornar editar o nome da tag
 * 
 * 
 * @param string nome
 * @return void 
*/
void Tag::setNome(string nome)
{
    this->nome = nome;
}

/**
 * Função responsável por retornar editar a descrição da tag
 * 
 * 
 * @param string descricao
 * @return void 
*/
void Tag::setDescricao(string descricao)
{
    this->descricao = descricao;
}

/**
 * Função responsável por passar o valor da primeira tag
 * 
 * 
 * @param Tag *tag
 * @return void 
*/
void Tag::setPrimeiraTag(Tag *tag)
{
    this->primeiraTag = tag;
}

/**
 * Função responsável por retornar a primeira tag
 * 
 * 
 * @return Tag *tag
*/
Tag *Tag::getPrimeiraTag()
{
    return this->primeiraTag;
}