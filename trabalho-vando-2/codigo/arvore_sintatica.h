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

    AST_TIPO_NULL // A linguagem não aceita null.
} NoTipoAST;



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
  NoAST * no_comandos;
} NoRaizAST;


/************************************************************
 * Métodos
 ************************************************************/
extern NoAST * no_new_raiz(ListaEncadeada * declaracoes, NoAST * no_comandos);

#endif
