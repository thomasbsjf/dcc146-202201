// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "tag.h"

Tag::Tag()
{
    this->primeiraTag = nullptr;
    this->proximaTag = nullptr;
}

Tag::Tag(string nome, string descricao)
{
    this->setNome(nome);
    this->setDescricao(descricao);
    this->proximaTag = nullptr;
}

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

void Tag::adicionarTag(string line)
{
}

bool Tag::validaTag(string nome, string descricao)
{
    return 0;
}

void Tag::listarTagsValidas()
{
    Tag *tag = this->getPrimeiraTag();

    while (tag != nullptr)
    {
        cout << tag->getNome() << ": " << tag->getDescricao() << endl;
        tag = tag->proximaTag;
    }
}

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

string Tag::getNome()
{
    return this->nome;
}

string Tag::getDescricao()
{
    return this->descricao;
}

void Tag::setNome(string nome)
{
    this->nome = nome;
}

void Tag::setDescricao(string descricao)
{
    this->descricao = descricao;
}

void Tag::setPrimeiraTag(Tag *tag)
{
    this->primeiraTag = tag;
}

Tag *Tag::getPrimeiraTag()
{
    return this->primeiraTag;
}
