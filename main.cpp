// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
//  Igor Westermann Lima - 201876021

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tag.h"

using namespace std;

/**
 * Função responsável por informar as opções disponíveis no programa
 * Informa como executar o comando desejado
*/
void mensagemInicial()
{
    cout << "-------------------------------"
         << "Instrucoes de uso"
         << "---------------------------------------------" << endl;
    cout << "---------------------------------------------------------------------------------------------" << endl;
    cout << ":c file_name  -> "
         << "Carrega um arquivo com definicoes de tags " << endl;
    cout << ":l            -> "
         << "Lista as definicoes de tag validas" << endl;
    cout << ":q            -> "
         << "Sai do programa" << endl;
    cout << ":s file_name  -> "
         << "Salvar as tags" << endl;
    cout << ":a            -> "
         << "Lista as definicoes formais dos automatos em memoria "
         << "(Nao implementado)" << endl;
    cout << ":p            -> "
         << "Realiza a divisao em tags da entrada informada "
         << "(Nao implementado)" << endl;
    cout << ":o file_name  -> "
         << "Especifica o caminho do arquivo de saida para a divisao em tags "
         << "(Nao implementado)" << endl;
    cout << ":d file_name  -> "
         << "Realiza a divisao em tags da string do arquivo informado "
         << "(Nao implementado)" << endl;
}

/**
 * Função responsável por imprimir as mensagens do arquivo main para o usuário
 *
 * 
 * @param string type
 * @param string message
 * @return void
*/
void printMessage(string type, string message)
{
    cout << "[" << type << "]" << message << endl;
}


/**
 * Função responsável por separar o texto digitado(split) após cada espaço digitado
 * Recebe uma string (digitada ou pegada pelo arquivo)
 * E recebe a posição que será avaliada 
*/
string split(string s, int pos)
{
    int i = 0;
    stringstream ss(s);
    string word;
    while (ss >> word)
    {
        if (pos == i)
        {
            return word;
        }
        i++;
    }
    return "";
}

/**
 * Função principal, responsável pela execução do programa
 *
 * 
 * @return int
*/
int main()
{
    mensagemInicial();

    bool stop = false;
    Tag *tag = new Tag();
    while (!stop)
    {
        string input;
        getline(cin, input);
        string option = split(input, 0);
        if (option.at(0) == ':')
        {
            if (option == ":d")
            {
                printMessage("WARNING", "Comando ainda nao implementado");
            }
            else
            {
                if (option == ":c")
                {
                    ifstream entrada(split(input, 1));
                    while (!entrada.eof())
                    {
                        string aux;
                        getline(entrada, aux, '\n');
                        cout << aux << endl;
                        if (aux != "")
                        {
                            tag->adicionarTag(aux);
                        }
                        else
                        {
                            break;
                        }
                    }
                    entrada.close();
                    printMessage("INFO", "Arquivo carregado com as definicoes das tags");
                }
                else
                {
                    if (option == ":o")
                    {
                        printMessage("INFO", "Caminho de saida especificado com sucesso");
                    }
                    else
                    {
                        if (option == ":p")
                        {
                            printMessage("WARNING", "Comando ainda nao implementado");
                        }
                        else
                        {
                            if (option == ":a")
                            {
                                printMessage("INFO", "Listagem das definicoes formais dos automatos.");
                            }
                            else
                            {
                                if (option == ":l")
                                {
                                    tag->listarTagsValidas();
                                    printMessage("INFO", "Listagem das tags validas realizada");
                                }
                                else
                                {
                                    if (option == ":q")
                                    {
                                        printMessage("INFO", "Programa finalizado com sucesso");
                                        stop = true;
                                    }
                                    else
                                    {
                                        if (option == ":s")
                                        {
                                            tag->salvarTag(split(input, 1));
                                            printMessage("INFO", "Tags armazenadas com sucesso");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            tag->adicionarTag(input);
        }
    }
}