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
  printf("#include <stdbool.h>\n");

  printf("\n");
  printf("#include \"base.h\"\n");
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

  printf("    %s %s", SimboloTipoDescricaoC[simbolo->tipo], simbolo->nome);

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

static void imprimir_print(NoPrintAST * no_print);
static void imprimir_input(NoInputAST * no_input);

static void imprimir_if_else(NoIfElseAST * no_condicional);

static void imprimir_expressao(NoExpressaoAST * no_expressao);
static void imprimir_variavel(NoVariavelAST * no_variavel);
static void imprimir_constante(NoConstanteAST * no_constante);

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

  else if (no->tipo == AST_TIPO_CONSTANTE)
    imprimir_constante((NoConstanteAST *) no->no);

  else if (no->tipo == AST_TIPO_VARIAVEL)
    imprimir_variavel((NoVariavelAST *) no->no);
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
  SimboloTipo tipo = tipo_simbolo(no_print->expressao);
  printf("    printf(");

  if (tipo == SIMBOLO_TIPO_INTEIRO
   || tipo == SIMBOLO_TIPO_BOOLEANO)
    printf("\"%%d\"");
  else
    printf("\"%%s\"");

  printf(", ");
  imprimir_no_ast(no_print->expressao);
  printf(");\n");
}

static void imprimir_input(NoInputAST * no_input) {
  Simbolo * variavel = no_input->variavel;

  if (variavel->tipo == SIMBOLO_TIPO_INTEIRO)
    printf("    %s = read_int();\n", variavel->nome);
  else if (variavel->tipo == SIMBOLO_TIPO_BOOLEANO)
    printf("    %s = read_bool();\n", variavel->nome);
  else
    printf("    %s = read_string();\n", variavel->nome);
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
  if (no_expressao->operacao == ENTRE_PARENTESES) {
    printf("(");
    imprimir_no_ast(no_expressao->esquerda);
    printf(")");

  } else if (no_expressao->operacao == ADICAO && tipo_simbolo(no_expressao->esquerda) == SIMBOLO_TIPO_STRING) {
    printf("concatenate(");
    imprimir_no_ast(no_expressao->esquerda);
    printf(", ");
    imprimir_no_ast(no_expressao->direita);
    printf(")");

  } else {
    if (no_expressao->esquerda != NULL)
      imprimir_no_ast(no_expressao->esquerda);

    if (!is_operacao_folha(no_expressao->operacao))
      printf(" %s ", OperacaoExpressaoDescricao[no_expressao->operacao]);

    if (no_expressao->direita != NULL)
      imprimir_no_ast(no_expressao->direita);
  }
}

static void imprimir_constante(NoConstanteAST * no_constante){
  if (no_constante->tipo == SIMBOLO_TIPO_INTEIRO)
    printf("%d", no_constante->valor.inteiro);

  else if (no_constante->tipo == SIMBOLO_TIPO_BOOLEANO)
    printf(no_constante->valor.inteiro ? "true" : "false");

  else if (no_constante->tipo == SIMBOLO_TIPO_STRING)
    printf("\"%s\"", (char *) no_constante->valor.referencia);
}

static void imprimir_variavel(NoVariavelAST * no_variavel){
  printf("%s", no_variavel->valor->nome);
  // fprintf(stderr, "balablallba");
}
//
// if(is_atomo(no_expressao->esquerda)){
//   if(no_expressao->esquerda->tipo == AST_TIPO_CONSTANTE){
//     if(no_expressao->esquerda->tipo->tipo)
//       printf(" %s ", no_expressao->esquerda-> );
//   }
// }


// if ((NoAST *)  no_expressao->tipo != NULL){
//   if(no_expressao->direita->tipo == AST_TIPO_CONSTANTE){
//     imprimir_constante((NoAST *) no_expressao->direita->tipo);
//   }
//   if(no_expressao->esquerda->tipo == AST_TIPO_CONSTANTE){
//     imprimir_constante((NoAST *) no_expressao->esquerda->tipo);
//   }
// }
// //
// //  imprimir_no_ast(no_expressao->esquerda)
// //
// // if (is_operacao_aritmetica(no_expressao->operacao))
// //   printf(" %s ", OperacaoExpressaoDescricao[no_expressao->operacao]);
//
// //if (no_expressao->direita != NULL)
// //  imprimir_no_ast(no_expressao->direita)


// imprimir_constante(NoAST * no_constante){
//   NoConstanteAST * constante = (NoConstanteAST *) no_constante->no;
//   printf("%d\n", no_constante->tipo);
// }
