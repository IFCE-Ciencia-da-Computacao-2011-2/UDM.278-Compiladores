#include <stdio.h>
#include "arvore_sintatica.h"

static void imprimir_cabecalho();
static void imprimir_declaracao_variaveis(NoAST * no_declaracoes);
static void imprimir_comandos(NoAST * no_expressoes);

/****************************
 * Cabeçalho
 ****************************/
void imprimir_codigo(NoAST * no_raiz) {
  NoRaizAST * no = (NoRaizAST *) no_raiz->no;

  imprimir_cabecalho();
  printf("\n");

  printf("int main() {\n");

  imprimir_declaracao_variaveis(no->no_declaracoes);
  imprimir_comandos(no->no_comandos);

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
static void imprimir_linha_declaracao(NoAST * no_linha_declaracao);

static void imprimir_declaracao_variaveis(NoAST * no_declaracoes) {
  //lista de declarações
  imprimir_linha_declaracao(no_declaracoes);
}

/**
 * Uma linha declaração pode ter a declaração de mais de uma variável para
 * um mesmo tipo:
 *
 * ```
 * int : x, i, y
 * string : msg
 * ```
 */
static void imprimir_linha_declaracao(NoAST * no_linha_declaracao) {
  NoElementoListaEncadeadaAST * no = (NoElementoListaEncadeadaAST *) no_linha_declaracao->no;

  printf("%s ", SimboloTipoDescricao[no->simbolo->tipo]);

  printf("%s", no->simbolo->nome);

  while (no->proximo_no != NULL) {
    no = (NoElementoListaEncadeadaAST *) no->proximo_no->no;

    printf(", %s", no->simbolo->nome);
  }

  printf(";\n");
}

/****************************
 * Expressões
 ****************************/
static void imprimir_comandos(NoAST * no_comandos) {

}
