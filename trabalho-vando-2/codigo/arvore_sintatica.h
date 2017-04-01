// AST = abstract syntax tree
// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

#include "tabela.h"

/************************************************************
 * Enumeração
 ************************************************************/
/**
 * Tipos de nós da árvore
 */
typedef enum {
    AST_TIPO_RAIZ,

    AST_TIPO_ELEMENTO_LISTA_ENCADEADA,

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
  NoAST * no_declaracoes;
  NoAST * no_comandos;
} NoRaizAST;

/**
 * Em alguns casos é necessário gerar uma lista de nós AST.
 * NoElementoListaEncadeadaAST permite gerar uma lista encadeada
 * de nós.
 *
 * Adicione um símbolo como valor do elemento da lista
 * e aponte o próximo nó
 */
typedef struct {
  // NoElementoListaEncadeadaAST
  Simbolo * simbolo;
  // Próximo elemento da lista encadeada
  NoAST * proximo_no;
} NoElementoListaEncadeadaAST;


/************************************************************
 * Métodos
 ************************************************************/
extern NoAST * no_new_raiz(NoAST * no_declaracoes, NoAST * no_comandos);

/**
 * Cria um nó de lista encadeada a partir de símbolo
 */
extern NoAST * no_new_elemento_lista_encadeada(Simbolo * simbolo);

/**
 * Vincula o no com o proximo_no
 */
extern NoAST * no_vincular_elementos_lista_encadeada(NoAST * no, NoAST * proximo_no);

#endif
