#include <stdio.h>
#include <stdlib.h>

#include "arvore_sintatica.h"
#include "common.h"
#include "mensagem.h"

/**
 * @return NoAST default, com todos os valores NULL
 */
NoAST * no_new() {
  NoAST * no = calloc(1, sizeof(NoAST));

  no->no = NULL;
  no->tipo = AST_TIPO_NULL;
  no->simbolo_tipo = SIMBOLO_TIPO_NULL;

  no->identificador = NULL;
  no->pai_identificador = NULL;

  return no;
}


NoAST * no_new_raiz(ListaEncadeada * declaracoes, ListaEncadeada * comandos) {
  NoAST * no = no_new();
  NoRaizAST * no_raiz = calloc(1, sizeof(NoRaizAST));

  no->no = no_raiz;
  no->tipo = AST_TIPO_RAIZ;

  no_raiz->declaracoes = declaracoes;
  no_raiz->comandos = comandos;

  return no;
}

NoAST * no_new_repeticao_for(Simbolo * variavel, NoAST * expressao_inicio, NoAST * expressao_fim, ListaEncadeada * comandos) {
  NoAST * no = no_new();
  NoRepeticaoForAST * no_for = calloc(1, sizeof(NoRepeticaoForAST));

  no->no = no_for;
  no->tipo = AST_TIPO_REPETICAO_FOR;

  no_for->variavel = variavel;
  no_for->expressao_inicio = expressao_inicio;
  no_for->expressao_fim = expressao_fim;
  no_for->comandos = comandos;

  return no;
}

NoAST * no_new_expressao(NoAST * no_esquerda, OperacaoExpressao operacao, NoAST * no_direita) {
  NoAST * no = no_new();
  NoExpressaoAST * no_expressao = calloc(1, sizeof(NoExpressaoAST));

  no->no = no_expressao;
  no->tipo = AST_TIPO_EXPRESSAO;

  no_expressao->esquerda = no_esquerda;
  no_expressao->operacao = operacao;
  no_expressao->direita = no_direita;

  return no;
}
