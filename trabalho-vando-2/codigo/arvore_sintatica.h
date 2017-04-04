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

    AST_TIPO_ATRIBUICAO,

    AST_TIPO_PRINT,
    AST_TIPO_INPUT,

    AST_TIPO_IF_ELSE,

    AST_TIPO_EXPRESSAO,
    AST_TIPO_CONSTANTE,
    AST_TIPO_VARIAVEL
} NoTipoAST;


typedef enum {
    CONSTANTE,
    VARIAVEL,

    ADICAO,
    SUBTRACAO,
    MULTIPLICACAO,
    DIVISAO,

    MAIOR_QUE,
    MAIOR_IGUAL_QUE,
    MENOR_QUE,
    MENOR_IGUAL_QUE,
    IGUAL,
    DIFERENTE,

    OR,
    AND,
    NOT
} OperacaoExpressao;

extern const char * OperacaoExpressaoDescricao[];

extern int is_operacao_aritmetica(OperacaoExpressao operacao);

extern int is_operacao_logica(OperacaoExpressao operacao);

extern int is_operacao_relacional(OperacaoExpressao operacao);

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
 * No equivalente à estrutura de dados que se parece com um while
 *
 * while (expressao) {
 *  lista_comandos
 * }
 */
typedef struct {
  NoAST * expressao;
  ListaEncadeada * comandos;
} NoRepeticaoWhileAST;

/**
 * No atribuição
 *
 * variavel = expressao
 */
typedef struct {
  Simbolo * variavel;
  NoAST * expressao;
} NoAtribuicaoAST;

/**
 * No equivalente à print
 */
typedef struct {
  NoAST * expressao;
} NoPrintAST;

/**
 * No equivalente à input / gets
 */
typedef struct {
  Simbolo * variavel;
} NoInputAST;


/**
 * No condicional equivalente à if-else
 * Se comandos_else == NULL, então é só um IF mesmo
 */
typedef struct {
  NoAST * expressao;
  ListaEncadeada * comandos_if;
  ListaEncadeada * comandos_else;
} NoIfElseAST;

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

  // Tipo de expressão
  SimboloTipo tipo;
} NoExpressaoAST;


/**
 * No representando uma constante: valor booleano, inteiro ou uma string
 *
 * Existem operações que não existe elemento da esquerda ou exclusivo da direita.
 * O que indentifica-as é OperacaoExpressao
 */
typedef struct {
  void * valor;
  SimboloTipo tipo;
} NoConstanteAST;

typedef struct {
  Simbolo * valor;
} NoVariavelAST;

/************************************************************
 * Métodos
 ************************************************************/
extern NoAST * no_new_raiz(ListaEncadeada * declaracoes, ListaEncadeada * comandos);

extern NoAST * no_new_repeticao_for(Simbolo * variavel, NoAST * expressao_inicio, NoAST * expressao_fim, ListaEncadeada * comandos);
extern NoAST * no_new_repeticao_while(NoAST * expressao, ListaEncadeada * comandos);

extern NoAST * no_new_atribuicao(Simbolo * variavel, NoAST * expressao);
extern NoAST * no_new_if_else(NoAST * expressao, ListaEncadeada * comandos_if, ListaEncadeada * comandos_else);

extern NoAST * no_new_print(NoAST * expressao);
extern NoAST * no_new_input(Simbolo * variavel);

extern NoAST * no_new_expressao(NoAST * no_esquerda, OperacaoExpressao operacao, NoAST * no_direita);

extern NoAST * no_new_constante(void * valor, SimboloTipo tipo_constante);

#endif
