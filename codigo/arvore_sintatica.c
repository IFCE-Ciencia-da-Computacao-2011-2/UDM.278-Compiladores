#include <stdio.h>
#include <stdlib.h>

#include "arvore_sintatica.h"

NohAST * noh_new_constante(int valor) {
  NohAST * no = malloc(sizeof(NohAST));
  NohConstanteAST * no_constante = malloc(sizeof(NohConstanteAST));
  
  no->tipo = TIPO_CONSTANTE;
  no->noh = no_constante;
  
  no_constante->valor = valor;
  
  return no;
}

NohAST * noh_new_delimitador(char valor) {
  NohAST * no = malloc(sizeof(NohAST));
  NohDelimitadorAST * no_delimitador = malloc(sizeof(NohDelimitadorAST));
  
  no->tipo = TIPO_DELIMITADOR;
  no->noh = no_delimitador;
  
  no_delimitador->valor = valor;
  
  return no;
}

void ast_imprimir() {
    printf("Insira o código a seguir em http://www.webgraphviz.com/\n");
    
    // a [label="node"]; b [label="node"]; a->b
    printf("\n");
    printf("digraph program {\n");
    printf("}\n");
}
