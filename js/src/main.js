// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

import {
  salvarTags,
  adicionarTag,
  listarTagsValidas,
  dividirTags,
  tags,
  printMessage
} from "./tags.js";
import { AFN } from "./automato.js";
import { divisao } from "./tags.js"
import lineReader from "line-reader";
import inquirer from "inquirer";
import fs from "fs";


/*
  Função principal do programa, responsável por coordenar os comandos executados.
  Checa se o primeiro char é : e chama as devidas funções que começam com esse caractere
  Se não for, adiciona uma nova TAG.

*/
function main(restart) {
  const caminho = "";
  if (restart) {
    inquirer
      .prompt([
        {
          type: "input",
          name: "option",
        },
      ])
      .then(({ option }) => {
        const validOption = option[0] + option[1];
        if (option[0] == ":") {
          if (validOption == ":d") {
            const arquivo = option.replace(":d ", "");
            imprimirArquivo(arquivo);
            printMessage(
              "INFO",
              "Divisão das Tags disponibilizadas no arquivo externo"
            );
            main(true);
          } else if (validOption === ":c") {
            const file = option.replace(":c ", "");
            lineReader.eachLine(
              `src/${file}`,
              function (line) {
                if (line != "") {
                  adicionarTag(line);
                }
              },
              function (err) {
                if (err) throw err;
                printMessage(
                  "INFO",
                  "Arquivo carregado com as definições das tags"
                );
              }
            );

            main(true);
          } else if (validOption === ":o") {
            const file = option.replace(":o ", "");
            caminho = file;
            printMessage("INFO", "Caminho de saída especificado com sucesso");
            main(true);
          } else if (validOption === ":p") {
            const linha = option.replace(":p ", "");
            dividirTags(linha);
            printMessage("INFO", "Divisão realizada com sucesso");
            main(true);
          } else if (validOption === ":a") {
            listarAutomatos();
            printMessage(
              "INFO",
              "Listagem das definições formais dos autômatos."
            );
            main(true);
          } else if (validOption === ":l") {
            listarTagsValidas();
            printMessage("INFO", "Listagem das tags válidas realizada");
            main(true);
          } else if (validOption === ":q") {
            printMessage("INFO", "Programa finalizado com sucesso");
            main(false);
          } else if (validOption === ":s") {
            const file = option.replace(":s ", "");
            salvarTags(file);
            printMessage("INFO", "Tags armazenadas com sucesso");
            main(true);
          }
        } else {
          adicionarTag(option);
          main(true);
        }
      });
  }
}


/*
  Função responsável por listar todos os Automatos criados informando suas devidas
  Tags, Estados Iniciais e Finais, Alfabeto e transições realizadas.
*/
function listarAutomatos() {
  for (var i = 0; i < tags.length; i++) {
    console.log(`------------------------------------------`);
    console.log(`Tag: ${tags[i].nome}: ${tags[i].descricao}`);
    console.log(`------------------------------------------`);
    console.log(`Informacoes sobre o Automato:`);
    console.log(`Estados Iniciais: ${AFN[i].estados.inicial}`);
    console.log(`Estados Finais: ${AFN[i].estados.final}`);
    console.log(`Alfabeto: ${AFN[i].alfabeto}`);
    console.log("teste AFN: ", AFN);
    console.log(`Transições: `);
    AFN[i].transicoes.forEach((transicao) => {
      console.log(
        `Origem: ${transicao.origem} - Destino: ${transicao.destino} - Simbolo: ${transicao.simbolo}`
      );
    });
  }
}

/*
  Função responsável por imprimir em um arquivo as Tags divididas
*/
function imprimirArquivo(file) {
  const stream = fs.createWriteStream(`src/${file}`);
  stream.once("open", () => {
    divisao.forEach((resultado) => {
      // console.log("passou");
      stream.write(
        `Parâmetro: ${resultado.criterio} <===>  Resultado: ${resultado.divisao}\n`
      );
    });
    stream.end();
  });
}

main(true);
