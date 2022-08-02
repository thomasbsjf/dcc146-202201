// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

import {salvarTags, adicionarTag, listarTagsValidas, validarTag} from './tags.js';

function main(restart) {
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
            printMessage("WARNING", "Comando ainda não implementado");
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
            printMessage("INFO", "Caminho de saída especificado com sucesso");
            main(true);
          } else if (validOption === ":p") {
            printMessage("WARNING", "Comando ainda não implementado");
            main(true);
          } else if (validOption === ":a") {
            printMessage(
              "INFO",
              "Listagem das definições formais dos autômatos."
            );
            main(true);
          } else if (validOption === ":l") {
            listarTagsValidas();
            printMessage("INFO", "Listagem das tags validas realizada");
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

main(true);
