// Alunos:
// Denner Efisio Emanuel Reis - 201735008
// Thomas Santos - 201776034
// Igor Westermann Lima - 201876021

/*
  Classe transicao: Representa uma nova transição
*/
export class Transicao {
  constructor(origem, destino, simbolo) {
    this.origem = origem;
    this.destino = destino;
    this.simbolo = simbolo;
  }
}

/*
  Classe transicoes: Contém uma lista de transições 
*/
export class Transicoes {
  constructor() {
    this.transicoes = [];
  }

  /* Função auxiliar responsável pela criação de uma nova transição
       e inserção na lista de transições existentes no automato 
    */
    newTransicao(origem, destino, simbolo) {
    let p = new Transicao(origem, destino, simbolo);
    this.transicoes.push({ origem, destino, simbolo });
    return p;
  }
}
