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


NoAST * no_new_raiz(ListaEncadeada * declaracoes, NoAST * no_comandos) {
  NoAST * no = no_new();
  NoRaizAST * no_raiz = calloc(1, sizeof(NoRaizAST));

  no->no = no_raiz;
  no->tipo = AST_TIPO_RAIZ;

  no_raiz->declaracoes = declaracoes;
  no_raiz->no_comandos = no_comandos;

  return no;
}
