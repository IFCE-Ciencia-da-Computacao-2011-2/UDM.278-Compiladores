// AST = abstract syntax tree
// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

#include "tabela.h"
#include "lista_encadeada/lista_encadeada.h"


/************************************************************
 * Enumeração
 ************************************************************/
/**
 * Tipos de nós da árvore
 */
typedef enum {
    AST_TIPO_RAIZ,

    AST_TIPO_REPETICAO_FOR,
    AST_TIPO_REPETICAO_WHILE,

    AST_TIPO_EXPRESSAO,

    AST_TIPO_NULL // A linguagem não aceita null.
} NoTipoAST;


typedef enum {
    CONSTANTE = 'c',
    ADICAO = '+',
    SUBTRACAO = '-',
    MULTIPLICACAO = '*',
    DIVISAO = '/'
} OperacaoExpressao;


/************************************************************
 * Estruturas de dados
 ************************************************************/
/**
 * Funciona como interface.
 * NoAST encapsula nó `void * no` e informa o seu tipo
 * em `NoTipoAST tipo`
 */
typedef struct {
  // Nó que irá trabalhar
  void * no;

  // O tipo do nó encapsulado
  NoTipoAST tipo;
  // ?
  SimboloTipo simbolo_tipo;

  // ?
  char * identificador;
  // ?
  char * pai_identificador;
} NoAST;

/**
 * Nó raiz, que representa
 * var {declaracoes} begin {comandos} end
 */
typedef struct {
  ListaEncadeada * declaracoes;
  ListaEncadeada * comandos;
} NoRaizAST;

/**
 * No equivalente à estrutura de dados que se parece com um for crescente
 *
 * for (variavel = expressao_inicio; expressao_inicio < expressao_fim; expressao_inicio++) {
 *  lista_comandos
 * }
 */
typedef struct {
  Simbolo * variavel;
  NoAST * expressao_inicio;
  NoAST * expressao_fim;
  ListaEncadeada * comandos;
} NoRepeticaoForAST;

/**
 * No representando uma expressão
 *
 * Existem operações que não existe elemento da esquerda ou exclusivo da direita.
 * O que indentifica-as é OperacaoExpressao
 */
typedef struct {
  OperacaoExpressao operacao;
  NoAST * esquerda;
  NoAST * direita;
  ListaEncadeada * comandos;
} NoExpressaoAST;


/************************************************************
 * Métodos
 ************************************************************/
extern NoAST * no_new_raiz(ListaEncadeada * declaracoes, ListaEncadeada * comandos);

extern NoAST * no_new_repeticao_for(Simbolo * variavel, NoAST * expressao_inicio, NoAST * expressao_fim, ListaEncadeada * comandos);

extern NoAST * no_new_expressao(NoAST * no_esquerda, OperacaoExpressao operacao, NoAST * no_direita);

#endif
