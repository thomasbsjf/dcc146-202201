/*
 * Funcao responsavel por tirar os automatos da pilha e executar o tipo de operacao (uniao, concat, simples, kleene)
 * Itera pela tag e de acordo com o simbolo adiciona um novo estado ou executa operacao
 * Atualiza o indice do numero de estados (indice é utilizado para criar o novo automato ou executar operacao)
 * Apos executar operacao adiciona o automato novo na pilha novamente
 * Falta completar o fecho lambda
 */

function montaAutomato(tag) {
  var totalEstados = 0;
  const pilha = [];
  for (i = 0; i < tag.length; i++) {
    if (tag[i] === "+") {
      const aut1 = pilha.pop();
      const aut2 = pilha.pop();
      totalEstados = ultimoEstado(aut1);
      const automato = automatoUniao(aut1, aut2, totalEstados);
      totalEstados = ultimoEstado(automato);

      pilha.push(automato);
    } else if (tag[i] === "*") {
      const aut1 = pilha.pop();
      const automato = criaFechoKleene(aut1);
      pilha.push(automato);
    } else if (tag[i] === ".") {
      const aut1 = pilha.pop();
      const aut2 = pilha.pop();
      const automato = automatoConcatenacao(aut1, aut2);
      pilha.push(automato);
    } else {
      const automato = automatoSimples(tag[i], totalEstados);
      totalEstados = totalEstados + 2;
      pilha.push(automato);
    }
  }
}

/*
 * Funcao responsavel por tirar calcular o ultimo estado do automato, valor é utilizado para criacao do proximo automato ou operacao
 * Ordena de forma crescente as origens e destinos e retorna o maior valor entre elas
 * O maior valor seria entao o ultimo estado do automato, que sera passado como parametro para criacao do proximo/operacao (uniao,concat)
 */
function ultimoEstado(aut) {
  const total1 = aut.transicoes.sort((a, b) =>
    a.origem < b.origem ? 1 : -1
  )[0].origem;
  const total2 = aut.transicoes.sort((a, b) =>
    a.destino < b.destino ? 1 : -1
  )[0].destino;
  if (total1 > total2) {
    return total1;
  } else {
    return total2;
  }
}

/*
 * Monta um automato simples atraves de um simbolo da transicao e indice que é utilizado como base para calculo do estado inicial
 */
function automatoSimples(simbolo, i) {
  const ini = i + 1;
  const fin = i + 2;
  const automato = {
    transicoes: [
      {
        origem: ini,
        destino: fin,
        simbolo,
      },
    ],
    estados: {
      inicial: [ini],
      final: [fin],
    },
    alfabeto: [simbolo],
  };

  return automato;
}

/*
 * Faz a uniao entre dois automatos que sao passados por parametro.
 * Adiciona as transicoes dos dois automatos em uma lista de transicoes
 * Adiciona todos os simbolos do alfabeto de ambos automatos em num novo alfabeto
 * Para todos os estados finais de ambos automatos cria uma transicao lambda partindo dele para um novo estado do automato
 * Para todos os estados inicias de ambos automatos cria uma transicao lambda para um novo estado do automato
 * Cria um novo alfabeto com os simbolos nao repetidos de ambos automatos
 */
function automatoUniao(aut1, aut2, i) {
  const ini = i + 1;
  const fin = i + 2;
  const transicoes = [];
  const alfabeto = [];
  aut1.transicoes.forEach((t) => transicoes.push(t));
  aut2.transicoes.forEach((t) => transicoes.push(t));
  aut1.alfabeto.forEach((a) => alfabeto.push(a));
  aut2.alfabeto.forEach((a) => alfabeto.push(a));
  aut1.estados.final.forEach((f) => {
    transicoes.push({
      origem: f,
      destino: fin,
      simbolo: "lambda",
    });
  });

  aut2.estados.final.forEach((f) => {
    transicoes.push({
      origem: f,
      destino: fin,
      simbolo: "lambda",
    });
  });
  aut1.estados.inicial.forEach((i) => {
    transicoes.push({
      origem: ini,
      destino: i,
      simbolo: "lambda",
    });
  });
  aut2.estados.inicial.forEach((i) => {
    transicoes.push({
      origem: ini,
      destino: i,
      simbolo: "lambda",
    });
  });
  alfabeto.push("lambda");
  const automato = {
    transicoes: transicoes,
    estados: {
      inicial: [ini],
      final: [fin],
    },
    alfabeto: Array.from(new Set(alfabeto)),
  };

  return automato;
}

/*
 * Objetivo da Funcao: cria o fecho de kleene em um automato.
 * O estado final se torna o estado inicial e para cada estado final do automato,
 * é criado uma transicao lambda para ele mesmo
 * É criado um novo automato cujo os estados finais e inicias sao iguais
 * É adicionado ao alfabeto o simbolo lambda
 */
function criaFechoKleene(aut1) {
  const estados = aut1.estados.inicial.map((i) => i);
  const transicoes = aut1.transicoes;
  aut1.estados.final.forEach((f) => {
    aut1.estados.inicial.forEach((i) => {
      transicoes.push({
        origem: f,
        destino: i,
        simbolo: "lambda",
      });
    });
  });
  const automato = {
    estados: {
      inicial: estados,
      final: estados,
    },
    transicoes: transicoes,
    alfabeto: Array.from(new Set(aut1.alfabeto, "lambda")),
  };
  return automato;
}

/*
 * Objetivo da Funcao: Fazer a concatenacao entre dois automatos que sao passados por parametro.
 * Adiciona as transicoes dos dois automatos em uma lista de transicoes
 * Adiciona todos os simbolos do alfabeto de ambos automatos em num novo alfabeto
 * Cria uma transicao lambda dos estados finais do aut2 para os inicias do aut1 fazendo assim a
 * concatenacao dos dois automatos
 * Cria um novo automato onde os estados iniciais sao do aut2 e os finais os do aut1
 */
function automatoConcatenacao(aut1, aut2) {
  const transicoes = [];
  const alfabeto = [];
  aut1.transicoes.forEach((t) => transicoes.push(t));
  aut2.transicoes.forEach((t) => transicoes.push(t));
  aut1.alfabeto.forEach((a) => alfabeto.push(a));
  aut2.alfabeto.forEach((a) => alfabeto.push(a));
  aut1.estados.inicial.forEach((i) => {
    aut2.estados.final.forEach((f) => {
      transicoes.push({
        origem: f,
        destino: i,
        simbolo: "lambda",
      });
    });
  });
  const automato = {
    alfabeto,
    transicoes,
    estados: {
      inicial: aut2.estados.inicial.map((i) => i),
      final: aut1.estados.final.map((f) => f),
    },
  };

  return automato;
}
