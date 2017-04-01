#include <stdio.h>
#include "arvore_sintatica.h"

static void imprimir_cabecalho();
static void imprimir_declaracao_variaveis(ListaEncadeada * declaracoes);
static void imprimir_comandos(NoAST * no_expressoes);

/****************************
 * Cabeçalho
 ****************************/
void imprimir_codigo(NoAST * no_raiz) {
  NoRaizAST * no = (NoRaizAST *) no_raiz->no;

  imprimir_cabecalho();
  printf("\n");

  printf("int main() {\n");

  imprimir_declaracao_variaveis(no->declaracoes);
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
static void imprimir_linha_declaracao(ListaEncadeada * linha_declaracao);

static void imprimir_declaracao_variaveis(ListaEncadeada * declaracoes) {
  //for elemento in declarações {
    imprimir_linha_declaracao(declaracoes);
  //}
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
static void imprimir_linha_declaracao(ListaEncadeada * linha_declaracao) {
  ListaEncadeada * elemento = linha_declaracao;

  Simbolo * simbolo = (Simbolo *) elemento->valor;
  printf("%s %s ", SimboloTipoDescricao[simbolo->tipo], simbolo->nome);

  while (elemento->proximo != NULL) {
    elemento = (ListaEncadeada *) elemento->proximo;
    simbolo = (Simbolo *) elemento->valor;

    printf(", %s", simbolo->nome);
  }

  printf(";\n");
}

/****************************
 * Expressões
 ****************************/
static void imprimir_comandos(NoAST * no_comandos) {

}
