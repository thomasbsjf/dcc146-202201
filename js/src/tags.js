// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021
import { montarAutomato, AFN } from "./automato.js";
import { Transicoes } from "./transicao.js";
import fs from "fs";

export const tags = [];
export const divisao = [];

export function printMessage(type, text) {
  console.log(`[${type}] ${text}`)
}

/*
  Função responsável por validar se a Tag é válida.
  Faz uso de uma variavel auxiliar para checar se já existe uma tag com o nome
  Faz uso de uma pilha para armazenar os caracteres
  Diferencia os caracteres especiais e adiciona \\ se aparecerem
  

*/
function validarTag(nome, descricao) {
  var auxiliar = true;
  tags.forEach((tag) => {
    if (nome === tag.nome) {
      auxiliar = false;
    }
  });
  if (!auxiliar) {
    printMessage("ERROR", "Nome da TAG ja utilizado");
    return false;
  }
  var pilha = [];
  for (let i = 0; i < descricao.length; i++) {
    if (descricao[i] === "*") {
      if (pilha.length === 0) {
        printMessage("ERROR", "Pilha vazia");
        return false;
      }
      aux = pilha.pop();
      pilha.push(aux + "*");
    } else {
      if (descricao[i] === "+" || descricao[i] === ".") {
        if (pilha.length > 1) {
          var primeiroChar = pilha.pop();
          var segundoChar = pilha.pop();
          pilha.push(primeiroChar + descricao[i] + segundoChar);
        } else {
          printMessage(
            "ERROR",
            "São necessarios pelo menos dois elementos."
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
          var aux = "";
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

/*
  Função responsável por listar as tags validas criadas.
*/
export function listarTagsValidas() {
  tags.forEach((tag) => {
    console.log(`${tag.nome}: ${tag.descricao}`);
  });
}

/*
  Função responsável adicionar novas tags.
  Checa se existe algo antes do ":", se sim ao chegar no : pula 1 e começa a escrever a descrição da TAG
  por fim VALIDA a Tag, salva em um objeto "tags" e chama a função para montar o automato da TAG passada
*/
export function adicionarTag(line) {
  var start = false;
  var nome = "";
  var descricao = "";
  for (let i = 0; i < line.length; i++) {
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
    montarAutomato(descricao);
    printMessage("INFO", "A TAG foi adicionada com sucesso");
  } else {
    printMessage("ERROR", "TAG digitada é inválida");
  }
}

/*
  Função responsável por salvas as Tags Validas em um arquivo especificado.
*/
export function salvarTags(file) {
  const stream = fs.createWriteStream(`src/${file}`);
  stream.once("open", () => {
    tags.forEach((tag) => {
      stream.write(`${tag.nome}: ${tag.descricao}\n`);
    });
    stream.end();
  });
}


export function dividirTags(criterio) {
  var indice = [];
  tags.forEach((t) => {
    indice.push({
      index: 0,
      origem: 1,
    });
  });
  const criterioInicial = criterio;
  var divisaoParcial = "";
  var continua = true;
  while (continua) {
    const resultado = [];
    console.log("afn: ", AFN);

    AFN.forEach((automato, i) => {
      resultado.push({ pos: i, consome: validarSeConsome(automato, criterio) });
    });
    if (resultado.length === 0) {
      continua = false;
    } else {
      const ordenarResultado = resultado.sort((a, b) =>
        a.consome < b.consome ? 1 : -1
      );
      divisaoParcial =
        divisaoParcial + " " + tags[ordenarResultado[0].pos].nome;
      criterio = criterio.substr(ordenarResultado[0].consome);
      if (ordenarResultado[0].consome === -1) {
        continua = false;
        divisaoParcial = "";
      }
      if (criterio.length === 0) {
        continua = false;
      }
    }
  }
  if (divisaoParcial === "") {
    printMessage("ERROR", "Não foi possível dividir a TAG informada");
    return;
  } else {
    divisao.push({
      criterio: criterioInicial,
      divisao: divisaoParcial,
    });
  }
}

function validarSeConsome(automato, criterio) {
  const inicial = automato.estados.inicial;
  const final = automato.estados.final;
  var estadoAtual = [];
  var indice = -1;
  for (var i = 0; i < criterio.length; i++) {
    if (criterio[i] !== "*" && criterio[i] !== "." && criterio[i] !== "+") {
      if (criterio[i].charCodeAt(0) === 47) {
        i++;
      }
      if (i === 0) {
        var transicoes = automato.transicoes.filter(
          (transicao) => transicao.simbolo === criterio[0]
        );
        if (transicoes.length > 0) {
          const elementos = transicoes.filter((transicao) => {
            return inicial.includes(transicao.origem);
          });
          if (elementos.length === 0) {
            return -1;
          } else {
            indice = 1;
            elementos.forEach((e) => estadoAtual.push(e.destino));
          }
        } else {
          return -1;
        }
      } else {
        const validarFinal = estadoAtual.filter((e) => {
          return final.includes(e);
        });
        if (validarFinal.length > 0) {
          indice = indice < i ? i + 1 : indice;
        }
        var transicoes = automato.transicoes.filter((transicao) => {
          return (
            transicao.simbolo === criterio[i] &&
            estadoAtual.includes(transicao.origem)
          );
        });
        if (transicoes.length > 0) {
          transicoes.forEach((e) => estadoAtual.push(e.destino));
        } else {
          return indice;
        }
      }
    }
  }
  return indice;
}
