#include <stdio.h>
#include <stdlib.h>

#include "arvore_sintatica.h"
#include "common.h"
#include "mensagem.h"

/***********************************
 * Operadores
 ***********************************/
void is_operacao_aritmetica(OperacaoExpressao operacao) {
   return operacao == ADICAO
       || operacao == SUBTRACAO
       || operacao == MULTIPLICACAO
       || operacao == DIVISAO;
}

void is_operacao_logica(OperacaoExpressao operacao) {
   return operacao == OR
       || operacao == AND
       || operacao == NOT;
}

void is_operacao_relacional(OperacaoExpressao operacao) {
   return operacao == IGUAL
       || operacao == DIFERENTE
       || operacao == MENOR_QUE
       || operacao == MENOR_IGUAL_QUE
       || operacao == MAIOR_QUE
       || operacao == MAIOR_IGUAL_QUE;
}

/***********************************
 * Nós
 ***********************************/
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

NoAST * no_new_repeticao_while(NoAST * expressao, ListaEncadeada * comandos) {
  NoAST * no = no_new();
  NoRepeticaoWhileAST * no_while = calloc(1, sizeof(NoRepeticaoWhileAST));

  no->no = no_while;
  no->tipo = AST_TIPO_REPETICAO_WHILE;

  no_while->expressao = expressao;
  no_while->comandos = comandos;

  return no;
}

NoAST * no_new_atribuicao(Simbolo * variavel, NoAST * expressao) {
  NoAST * no = no_new();
  NoAtribuicaoAST * no_variavel = calloc(1, sizeof(NoAtribuicaoAST));

  no->no = no_variavel;
  no->tipo = AST_TIPO_ATRIBUICAO;

  no_variavel->variavel = variavel;
  no_variavel->expressao = expressao;

  return no;
}

NoAST * no_new_print(NoAST * expressao) {
  NoAST * no = no_new();
  NoPrintAST * no_print = calloc(1, sizeof(NoPrintAST));

  no->no = no_print;
  no->tipo = AST_TIPO_PRINT;

  no_print->expressao = expressao;

  return no;
}

NoAST * no_new_input(Simbolo * variavel) {
  NoAST * no = no_new();
  NoInputAST * no_input = calloc(1, sizeof(NoInputAST));

  no->no = no_input;
  no->tipo = AST_TIPO_INPUT;

  no_input->variavel = variavel;

  return no;
}

NoAST * no_new_if_else(NoAST * expressao, ListaEncadeada * comandos_if, ListaEncadeada * comandos_else) {
  NoAST * no = no_new();
  NoIfElseAST * no_condicional = calloc(1, sizeof(NoIfElseAST));

  no->no = no_condicional;
  no->tipo = AST_TIPO_IF_ELSE;

  no_condicional->expressao = expressao;
  no_condicional->comandos_if = comandos_if;
  no_condicional->comandos_else = comandos_else;

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


NoAST * no_new_constante(void * valor, SimboloTipo tipo_constante) {
  NoAST * no = no_new();
  NoConstanteAST * no_constante = calloc(1, sizeof(NoConstanteAST));

  no->no = no_constante;
  no->tipo = AST_TIPO_CONSTANTE;

  no_constante->valor = valor;
  no_constante->tipo_constante = tipo_constante;

  return no;
}
