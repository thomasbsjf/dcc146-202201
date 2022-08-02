import {salvarTags, adicionarTag, listarTagsValidas, validarTag} from './tags.js';

function index(restart) {
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
            index(true);
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

            index(true);
          } else if (validOption === ":o") {
            printMessage("INFO", "Caminho de saída especificado com sucesso");
            index(true);
          } else if (validOption === ":p") {
            printMessage("WARNING", "Comando ainda não implementado");
            index(true);
          } else if (validOption === ":a") {
            printMessage(
              "INFO",
              "Listagem das definições formais dos autômatos."
            );
            index(true);
          } else if (validOption === ":l") {
            listarTagsValidas();
            printMessage("INFO", "Listagem das tags validas realizada");
            index(true);
          } else if (validOption === ":q") {
            printMessage("INFO", "Programa finalizado com sucesso");
            index(false);
          } else if (validOption === ":s") {
            const file = option.replace(":s ", "");
            salvarTags(file);
            printMessage("INFO", "Tags armazenadas com sucesso");
            index(true);
          }
        } else {
          adicionarTag(option);
          index(true);
        }
      });
  }
}

index(true);
