// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

#ifndef TAG_H_INCLUDED
#define TAG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include "tag.h"

using namespace std;

class Tag
{
private:
    string nome, descricao;
    Tag *primeiraTag, *proximaTag;

public:
    Tag();
    Tag(string nome, string descricao);
    ~Tag();

    void adicionarTag(string line);
    void listarTagsValidas();
    void salvarTag(string file);
    void setNome(string nome);
    void setDescricao(string descricao);
    void setPrimeiraTag(Tag *tag);
    bool validaTag(string nome, string descricao);
    string getNome();
    string getDescricao();
    Tag *getPrimeiraTag();
};

#endif // TAG_H_INCLUDED