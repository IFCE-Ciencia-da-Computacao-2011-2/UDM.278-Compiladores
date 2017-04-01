#include <stdio.h>
#include "arvore_sintatica.h"

static void imprimir_cabecalho();
static void imprimir_declaracao_variaveis(NoAST * no_declaracoes);
static void imprimir_expressoes(NoAST * no_expressoes);

/****************************
 * Cabeçalho
 ****************************/
void imprimir_codigo(NoAST * no_raiz) {
  NoRaizAST * no = (NoRaizAST *) no_raiz->no;

  imprimir_cabecalho();
  printf("\n");

  printf("int main() {\n");

  imprimir_declaracao_variaveis(no->no_declaracoes);
  imprimir_expressoes(no->no_expressoes);

  printf("}\n");
}

static void imprimir_cabecalho() {
  printf("// Vando: Por Paulo Mateus e Leonardo Silva\n");
  printf("\n");

  printf("#include <stdio.h>\n");
}


/****************************
 * Declaração de variáveis
 ****************************/
static void imprimir_declaracao_variaveis(NoAST * no_declaracoes) {

}


/****************************
 * Expressões
 ****************************/
static void imprimir_expressoes(NoAST * no_expressoes) {

}
