// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

typedef enum {TIPO_CONSTANTE, TIPO_DELIMITADOR} NohTipoAST;

typedef struct {
  NohTipoAST tipo;
  void * noh;
} NohAST;

typedef struct {
  int valor;
} NohConstanteAST;

typedef struct {
  char valor;
} NohDelimitadorAST;

extern NohAST * noh_new_constante(int valor);
extern void ast_imprimir();

#endif
