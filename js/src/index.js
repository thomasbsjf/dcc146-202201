const inquirer = require("inquirer");
const lineReader = require("line-reader");
const fs = require("fs");
const tags = [];
function printMessage(type, text) {
  console.log(`[${type}] ${text}`);
}

function validarTag(nome, descricao) {
  var auxiliar = true;
  tags.forEach((tag) => {
    console.log(nome, tag.nome, nome == tag.nome);
    if (nome === tag.nome) {
      auxiliar = false;
    }
  });
  if (!auxiliar) {
    printMessage("Erro", "Este nome já está sendo utilizado");
    return false;
  }
  var pilha = [];
  for (i = 0; i < descricao.length; i++) {
    if (descricao[i] === "*") {
      if (pilha.length === 0) {
        printMessage("ERRO", "Pilha vazia");
        return false;
      }
      aux = pilha.pop();
      pilha.push(aux + "*");
    } else {
      if (descricao[i] === "+" || descricao[i] === ".") {
        if (pilha.length > 1) {
          primeiroElemento = pilha.pop();
          segundoElemento = pilha.pop();
          pilha.push(primeiroElemento + descricao[i] + segundoElemento);
        } else {
          printMessage(
            "ERRO",
            "É necessário que a pilha tenha pelo menos dois elementos"
          );
          return false;
        }
      } else {
        if (String.fromCharCode(descricao[i]) === 92) {
          i++;
          if (
            descricao[i] === "n" ||
            String.fromCharCode(descricao[i]) == 92 ||
            descricao[i] == "*" ||
            descricao[i] == "." ||
            descricao[i] == "+" ||
            descricao[i] == "l"
          ) {
            pilha.push("\\" + descricao[i]);
          } else {
            return false;
          }
        } else {
          aux = "";
          aux += descricao[i];
          pilha.push(aux);
        }
      }
    }
  }
  if (pilha.length === 1) {
    return true;
  }
  return false;
}

function listarTagsValidas() {
  tags.forEach((tag) => {
    console.log(`${tag.nome}: ${tag.descricao}`);
  });
}

function adicionarTag(line) {
  start = false;
  (nome = ""), (descricao = "");
  for (i = 0; i < line.length; i++) {
    if (line[i] == ":" && !start) {
      i++;
      start = true;
    } else {
      if (start) {
        descricao += line[i];
      } else {
        nome += line[i];
      }
    }
  }
  if (validarTag(nome, descricao)) {
    tags.push({
      nome,
      descricao,
    });
    printMessage("INFO", "A TAG foi adicionada com sucesso");
  } else {
    printMessage("ERRO", "TAG inválida");
  }
}

function salvarTags(file) {
  const stream = fs.createWriteStream(`src/${file}`);
  stream.once("open", () => {
    tags.forEach((tag) => {
      stream.write(`${tag.nome}: ${tag.descricao}\n`);
    });
    stream.end();
  });
}

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
            printMessage("INFO", "Listagem das tags válidas realizada");
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
