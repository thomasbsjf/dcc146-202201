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
} from "./tags.js";
import { afn as AFN } from "./automato.js";
const inquirer = require("inquirer");
const lineReader = require("line-reader");

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
            listarAutomatosValidos();
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

function listarAutomatosValidos() {
  for (var i = 0; i < tags.length; i++) {
    console.log(`------------------------------------------`);
    console.log(`Tag: ${tags[i].nome}: ${tags[i].descricao}`);
    console.log(`------------------------------------------`);
    console.log(`Automato:`);
    console.log(`Estados Iniciais: ${AFN[i].estados.inicial}`);
    console.log(`Estados Finais: ${AFN[i].estados.final}`);
    console.log(`Alfabeto: ${AFN[i].alfabeto}`);
    console.log(`Transições: `);
    AFN[i].transicoes.forEach((transicao) => {
      console.log(
        `origem: ${transicao.origem} - destino: ${transicao.destino} - simbolo: ${transicao.simbolo}`
      );
    });
  }
}

function imprimirArquivo(file) {
  const stream = fs.createWriteStream(`src/${file}`);
  stream.once("open", () => {
    divisao.forEach((resultado) => {
      stream.write(
        `Parâmetro: ${resultado.criterio} ==================  Resultado: ${resultado.divisao}\n`
      );
    });
    stream.end();
  });
}

main(true);
