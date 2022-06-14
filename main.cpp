//Alunos: 
//Denner Efisio Emanuel Reis - 201735008
//Thomas Santos - 201776034

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void mensagemInicial()
{
    cout << "-------------------------------" << "Instrucoes de uso" << "---------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << ":c file_name  -> " << "Carrega um arquivo com definicoes de tags " << endl;
    cout << ":l            -> " << "Lista as definicoes de tag validas" << endl;
    cout << ":q            -> " << "Sai do programa" << endl;
    cout << ":s file_name  -> " << "Salvar as tags" << endl;
    cout << ":a            -> " << "Lista as definicoes formais dos automatos em memoria " << "(Nao implementado)" << endl;
    cout << ":p            -> " << "Realiza a divisao em tags da entrada informada " << "(Nao implementado)" << endl;
    cout << ":o file_name  -> " << "Especifica o caminho do arquivo de saida para a divisao em tags " << "(Nao implementado)" << endl;
    cout << ":d file_name  -> " << "Realiza a divisao em tags da string do arquivo informado " << "(Nao implementado)" << endl;
}

int main()
{
    mensagemInicial();
}