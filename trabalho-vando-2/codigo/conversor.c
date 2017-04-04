#include <stdio.h>
#include "arvore_sintatica.h"

static void imprimir_cabecalho();
static void imprimir_declaracao_variaveis(ListaEncadeada * declaracoes);
static void imprimir_comandos(ListaEncadeada * comandos);

/****************************
 * Cabeçalho
 ****************************/
void imprimir_codigo(NoAST * no_raiz) {
  NoRaizAST * no = (NoRaizAST *) no_raiz->no;

  imprimir_cabecalho();
  printf("\n");

  printf("int main() {\n");

  imprimir_declaracao_variaveis(no->declaracoes);
  printf("\n");
  imprimir_comandos(no->comandos);

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
  ListaElemento * elemento = declaracoes->primeiro;

  while (elemento != NULL) {
    imprimir_linha_declaracao((ListaEncadeada *) elemento->valor);
    elemento = elemento->proximo;
  }
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
  ListaElemento * elemento = linha_declaracao->primeiro;

  Simbolo * simbolo = (Simbolo *) elemento->valor;

  printf("    %s %s", SimboloTipoDescricao[simbolo->tipo], simbolo->nome);

  while (elemento->proximo != NULL) {
    elemento = (ListaElemento *) elemento->proximo;
    simbolo = (Simbolo *) elemento->valor;

    printf(", %s", simbolo->nome);
  }

  printf(";\n");
}

/****************************
 * Comandos e expressoes
 ****************************/
static void imprimir_no_ast(NoAST * no);

static void imprimir_for(NoRepeticaoForAST * no_for);
static void imprimir_while(NoRepeticaoWhileAST * no_while);

static void imprimir_atribuicao(NoAtribuicaoAST * no_atribuicao);

static void imprimir_expressao(NoExpressaoAST * no_expressao);

static void imprimir_print(NoPrintAST * no_print);
static void imprimir_input(NoInputAST * no_input);

static void imprimir_if_else(NoIfElseAST * no_condicional);

static void imprimir_comandos(ListaEncadeada * comandos) {
  ListaElemento * elemento = comandos->primeiro;

  NoAST * no = NULL;

  while (elemento != NULL) {
    imprimir_no_ast((NoAST *) elemento->valor);

    elemento = (ListaElemento *) elemento->proximo;
  }
}

static void imprimir_no_ast(NoAST * no) {
  if (no->tipo == AST_TIPO_REPETICAO_FOR)
    imprimir_for((NoRepeticaoForAST *) no->no);

  else if (no->tipo == AST_TIPO_REPETICAO_WHILE)
    imprimir_while((NoRepeticaoWhileAST *) no->no);

  else if (no->tipo == AST_TIPO_ATRIBUICAO)
    imprimir_atribuicao((NoAtribuicaoAST *) no->no);

  else if (no->tipo == AST_TIPO_PRINT)
    imprimir_print((NoPrintAST *) no->no);

  else if (no->tipo == AST_TIPO_INPUT)
    imprimir_input((NoInputAST *) no->no);

  else if (no->tipo == AST_TIPO_IF_ELSE)
    imprimir_if_else((NoIfElseAST *) no->no);

  else if (no->tipo == AST_TIPO_EXPRESSAO)
    imprimir_expressao((NoExpressaoAST *) no->no);
}

static void imprimir_for(NoRepeticaoForAST * no_for) {
  char * variavel = no_for->variavel->nome;
  NoAST * inicio = no_for->expressao_inicio;
  NoAST * fim = no_for->expressao_fim;

  printf("\n");
  printf("    for (%s = ", variavel);
    imprimir_no_ast(inicio);
    printf("; %s < (", variavel);
    imprimir_no_ast(fim);
    printf("); %s++) {\n", variavel);

  imprimir_comandos(no_for->comandos);
  printf("\n");

  printf("    }\n");
}

static void imprimir_while(NoRepeticaoWhileAST * no_while) {
  printf("\n");
  printf("    while (");
    imprimir_no_ast(no_while->expressao);
    printf(") {\n");

  imprimir_comandos(no_while->comandos);
  printf("\n");

  printf("    }\n");
}

static void imprimir_atribuicao(NoAtribuicaoAST * no_atribuicao) {
  char * variavel = no_atribuicao->variavel->nome;

  printf("    %s = ", variavel);
  imprimir_no_ast(no_atribuicao->expressao);
  printf(";\n");
}

static void imprimir_print(NoPrintAST * no_print) {
  printf("    printf();\n");
}

static void imprimir_input(NoInputAST * no_input) {
  printf("    [INPUT];\n");
}

static void imprimir_if_else(NoIfElseAST * no_condicional) {
  printf("    if (");
    imprimir_no_ast(no_condicional->expressao);
  printf(") {\n");
    imprimir_comandos(no_condicional->comandos_if);

  if (no_condicional->comandos_else != NULL) {
  printf("    } else {\n");
    imprimir_comandos(no_condicional->comandos_else);
  }
  printf("    }\n");
}

static void imprimir_expressao(NoExpressaoAST * no_expressao) {
  printf("Vou imprimir uma expressão");
  //if (no_expressao->esquerda != NULL)
  //  imprimir_no_ast(no_expressao->esquerda)

  if (is_operacao_aritmetica(no_expressao->operacao))
    printf(" %c ", no_expressao->operacao);

  //if (no_expressao->direita != NULL)
  //  imprimir_no_ast(no_expressao->direita)
}
