// AST = abstract syntax tree
// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

#include "tabela.h"

/**
 * Tipos de nós da árvore
 */
typedef enum {
    AST_TIPO_RAIZ,

    AST_TIPO_NULL // A linguagem não aceita null.
} NoTipoAST;

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
 * var {declaracoes} begin {expressões} end
 */
typedef struct {
  NoAST * no_declaracoes;
  NoAST * no_expressoes;
} NoRaizAST;

extern NoAST * no_new_raiz(NoAST * no_declaracoes, NoAST * no_expressoes);

#endif
