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


NoAST * no_new_raiz(NoAST * no_declaracoes, NoAST * no_comandos) {
  NoAST * no = no_new();
  NoRaizAST * no_raiz = calloc(1, sizeof(NoRaizAST));

  no->no = no_raiz;
  no->tipo = AST_TIPO_RAIZ;

  no_raiz->no_declaracoes = no_declaracoes;
  no_raiz->no_comandos = no_comandos;

  return no;
}


NoAST * no_new_elemento_lista_encadeada(Simbolo * simbolo) {
  NoAST * no = no_new();
  NoElementoListaEncadeadaAST * no_elemento = malloc(sizeof(NoElementoListaEncadeadaAST));

  no->no = no_elemento;
  no->tipo = AST_TIPO_ELEMENTO_LISTA_ENCADEADA;

  no_elemento->simbolo = simbolo;
  no_elemento->proximo_no = NULL;

  return no;
}


NoAST * no_vincular_elementos_lista_encadeada(NoAST * no, NoAST * proximo_no) {
   NoElementoListaEncadeadaAST * no_elemento = (NoElementoListaEncadeadaAST *) no->no;
   no_elemento->proximo_no = proximo_no;

   return no;
}
