// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

export const AFN = [];
const AFlambda = [];

class Transicao {
  constructor(origem, destino, simbolo) {
    this.origem = origem;
    this.destino = destino;
    this.simbolo = simbolo;
  }
}
class Transicoes {
  constructor() {
    this.transicoes = [];
  }
  // cria uma nova transicao e salva na colecao
  newTransicao(origem, destino, simbolo) {
    let p = new Transicao(origem, destino, simbolo);
    this.transicoes.push({ origem, destino, simbolo });
    return p;
  }
}

/*
 * Funcao responsavel por tirar os automatos da pilha e executar o tipo de operacao (uniao, concat, simples, kleene)
 * Itera pela tag e de acordo com o simbolo adiciona um novo estado ou executa operacao
 * Atualiza o indice do numero de estados (indice é utilizado para criar o novo automato ou executar operacao)
 * Apos executar operacao adiciona o automato novo na pilha novamente
 * Falta completar o fecho lambda
 */
export function montarAutomato(tag) {
  var totalEstados = 0;
  const pilha = [];
  for (let i = 0; i < tag.length; i++) {
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
  const aut = pilha.pop();
  AFlambda.push(aut);
  fechoLambda(aut);
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
  const transicoes = new Transicoes();
  const alfabeto = [];
  aut1.transicoes.forEach((t) =>
    transicoes.newTransicao(t.origem, t.destino, t.simbolo)
  );
  aut2.transicoes.forEach((t) =>
    transicoes.newTransicao(t.origem, t.destino, t.simbolo)
  );
  aut1.alfabeto.forEach((a) => alfabeto.push(a));
  aut2.alfabeto.forEach((a) => alfabeto.push(a));
  aut1.estados.final.forEach((f) => {
    transicoes.newTransicao(f, fin, "lambda");
  });

  aut2.estados.final.forEach((f) => {
    transicoes.newTransicao(f, fin, "lambda");
  });
  aut1.estados.inicial.forEach((i) => {
    transicoes.newTransicao(ini, i, "lambda");
  });
  aut2.estados.inicial.forEach((i) => {
    transicoes.newTransicao(ini, i, "lambda");
  });
  alfabeto.push("lambda");
  const automato = {
    transicoes: transicoes.transicoes,
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
    transicoes: transicoes.transicoes,
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
  const transicoes = new Transicoes();
  
  const alfabeto = [];
  aut1.transicoes.forEach((t) =>
    transicoes.newTransicao(t.origem, t.destino, t.simbolo)
  );
  aut2.transicoes.forEach((t) =>
    transicoes.newTransicao(t.origem, t.destino, t.simbolo)
  );
  aut1.alfabeto.forEach((a) => alfabeto.push(a));
  aut2.alfabeto.forEach((a) => alfabeto.push(a));
  aut1.estados.inicial.forEach((i) => {
    aut2.estados.final.forEach((f) => {
      transicoes.newTransicao(f, i, "lambda");
    });
  });
  const automato = {
    alfabeto,
    transicoes: transicoes.transicoes,
    estados: {
      inicial: aut2.estados.inicial.map((i) => i),
      final: aut1.estados.final.map((f) => f),
    },
  };

  return automato;
}

/*
 * Objetivo da função: criar o fecho lambda apartir do automato passado como parametro
 * cria uma constante fecho para armazenar os fechos para.
 * remove os estados repetidos e ordena eles.
 * Filtra as transicoes do automato iguais a lambda em uma variavel aux
 * cria uma variavel transicao que recebe as transicoes da variavel auxiliar e filtra as possuem a origem igual ao estado
 * Para cada estado, verifica se o tamanho de transicoes é maior que 0. Para cada transição cujo a origem é igual ao estado é armazenado em aux2
 * enquanto for verdadeiro, percorre a aux2 e para cada valor faz um novo filtro na aux1 para pegar quando o valor for igual a origem.
 * Para cada valor, procura o index cujo valor é igual a -1 e se for o estadoFecho recebe o destino e aux2 tambem.
 * salva os estados e transicoes no array fecho e passa como parametro para funcao afnLambdaParaAfn.
 */
function fechoLambda(aut) {
  const fecho = [];
  var estados = Array.from(
    new Set(
      aut.transicoes
        .map((t) => {
          return [t.origem, t.destino];
        })
        .flat()
    )
  ).sort((a, b) => (a > b ? 1 : -1));
  const aux1 = aut.transicoes.filter((t) => t.simbolo === "lambda");
  estados.forEach((estado) => {
    var transicoes = aux1.filter((a) => a.origem === estado);
    if (transicoes.length > 0) {
      var estadosFecho = [estado];
      var aux2 = [];
      transicoes.forEach((t) => {
        estadosFecho.push(t.destino);
        aux2.push(t.destino);
      });
      var next = true;
      while (next === true) {
        aux2.forEach((aux) => {
          var transicoes = aux1.filter((a) => a.origem === aux);
          transicoes.forEach((t) => {
            if (estadosFecho.findIndex((e) => e === t) === -1) {
              estadosFecho.push(t.destino);
              aux2.push(t.destino);
            }
          });
          aux2.splice(0, 1);
        });
        if (aux2.length === 0) {
          next = false;
        }
      }
      fecho.push({
        estado,
        transicoes: estadosFecho,
      });
    } else {
      fecho.push({
        estado,
        transicoes: [estado],
      });
    }
  });
  afnLambdaParaAfn(aut, fecho);
}

/*
cria um array a partir dos estados iniciais do automato recebido como parametro e salva na variavel aux1.
após isso ataualiza para um novo array que possui os estados do fecho igual a cada valor do antigo array e
retorna um novo array com as transicoese remove os subarrays.
faz a mesma coisa com os estados finais

remove os valores repitidos das varieis auxiliares de inicio e fim.
cria um array de transicoes que vai receber as transicoes afn
verifica se as transicoes ja existes ao filtrar aquelas que possuem origem, destino e simbolo diferentes da proxima transicao
e para cada valor insere no array transicao sua origem, destino e simbolo

cria um objeto com os estados, transicoes e alfabeto e insere no afn

*/
function afnLambdaParaAfn(aut, fecho) {
  var aux1, aux2;
  aux1 = aut.estados.inicial.map((i) => i);
  aux1 = aux1
    .map((f) => {
      var _fecho = fecho.filter((v) => v.estado === f);
      return _fecho.map((r) => r.transicoes).flat();
    })
    .flat();
  aux2 = aut.estados.final.map((i) => i);
  aux2 = aux2
    .map((f) => {
      var _fecho = fecho.filter((v) => v.estado === f);
      return _fecho.map((r) => r.transicoes).flat();
    })
    .flat();
  const inicial = Array.from(new Set(aux1));
  const final = Array.from(new Set(aux2));

  const transicoes = new Transicoes();

  const semLambda = aut.transicoes.filter((t) => t.simbolo !== "lambda");
  const comLambda = aut.transicoes.filter((t) => t.simbolo === "lambda");

  fecho.map((f) => {
    const transicaoAfn = semLambda.filter((t) => t.origem === f.estado);
    if (transicaoAfn.length > 0) {
      transicaoAfn.map((t) => {
        transicoes.newTransicao(t.origem, t.destino, t.simbolo);
      });
      var next = true;
      const aux = [];
      transicaoAfn.forEach((t) => {
        aux.push({
          ...t,
          ref: t,
        });
      });
      while (next === true) {
        if (aux.length === 0) next = false;
        aux.forEach((t) => {
          const proxTransicao = comLambda.filter((l) => {
            return l.origem === t.destino;
          });
          if (proxTransicao.length > 0) {
            const validaTransicao = proxTransicao.filter((a) => {
              return transicoes.transicoes.filter((t) => {
                console.log("teste 3: ", transicoes);

                return (
                  t.origem !== a.origem &&
                  t.destino !== a.destino &&
                  t.simbolo !== a.simbolo
                );
              });
            });
            validaTransicao.forEach((v) => {
              transicoes.newTransicao(t.ref.origem, v.destino, t.ref.simbolo);
              aux.push({
                ...v,
                ref: t.ref,
              });
            });
          }
          aux.splice(0, 1);
        });
      }
    }
  });
  const alfabeto = criarAlfabeto(transicoes.transicoes.flat(2));
  // const afnProps =
  AFN.push({
    estados: {
      inicial,
      final,
    },
    transicoes: transicoes.transicoes,
    alfabeto,
  });
}

/*
cria um alfabeto apartir das transicoes passadas como parametro.
para cada transicao, insere no alfabeto os simbolos da transicao passada como parametro
e retorna um array sem nenhum simbolo repetido
*/
function criarAlfabeto(transicoes) {
  const alfabeto = [];
  transicoes.forEach((transicao) => {
    alfabeto.push(transicao.simbolo);
  });

  return Array.from(new Set(alfabeto));
}
