#include <stdio.h>
#include <stdlib.h>

#include "regras.tab.h"
#include "gramatica.tab.h"

#include "codigo.h"
#include "tabela.h"
#include "tokens.h"


////////////////////////////////////////
void print_titulo(char * string) {
  printf("\033[1;37m%s\033[0m\n", string);
}

void print_erro(char * string) {
  printf("\033[0;31m%s\033[0m", string);
}

////////////////////////////////////////

void inicializar_analise(char *nome_arquivo, FILE ** yyin);
Token *proximo_token();

void imprimir_token(Token *token);
char *palavra_chave_descricao(int operacao);
char *operador_descricao(int operacao);
char *pontuacao_descricao(int operacao);

void finalizar_analise(FILE * yyin);

extern FILE *yyin;


int main2(int argc, char **argv) {
  if (argc < 2) {
    printf("Uso: vando <arquivo>\n");
    return 0;
  }

  yy_nome_arquivo = argv[1];

  printf("\n");
  printf("*********************\n");
  printf(" Análise Léxica      \n");
  printf("*********************\n");
  printf("\n");
  printf(" * Processando %s\n", yy_nome_arquivo);
  printf("\n");
  printf(" * Análise\n");
  printf("\n");

  inicializar_analise(argv[1], &yyin);

  Token *token = proximo_token();

  while (token != NULL) {
    imprimir_token(token);
    token = proximo_token();
  }

  printf("\n");
  printf("*********************\n");
  printf(" Análise Sintática      \n");
  printf("*********************\n");
  printf("\n");
  printf(" * Processando %s\n", yy_nome_arquivo);
  printf("\n");
  printf(" * Análise\n");
  printf("\n");

  yyparse();

  finalizar_analise(yyin);

  return 0;
}

void inicializar_analise(char *nome_arquivo, FILE ** yyin) {
  FILE *f = fopen(nome_arquivo, "r");

  if (f == NULL) {
    fprintf(stderr, "Não foi possivel abrir o arquivo de entrada:%s\n", nome_arquivo);
    exit(1);
  }

  *yyin = f;
}

Token *proximo_token() {
    return NULL;//yylex();
}

void imprimir_token(Token *token) {
  switch (token->tipo) {
    case TOKEN_PALAVRA_CHAVE:
      print_titulo(" * Palavra chave");
      printf("   - Valor: %s\n", palavra_chave_descricao(token->valor));
      break;

    case TOKEN_ID:
      print_titulo(" * Identificador");
      printf("   - Valor: \033[0;94m%d\033[0m\n", token->valor);
      printf("   - Corresponde a: \033[0;94m%s\033[0m\n", yytext);
      break;

    case TOKEN_NUMERO:
      print_titulo(" * Inteiro");
      printf("   - Valor: %d\n", token->valor);
      break;

    case TOKEN_OPERACAO:
      print_titulo(" * Operador");
      printf("   - Valor: %s\n", operador_descricao(token->valor));
      break;

    case TOKEN_PONTUACAO:
      print_titulo(" * Pontuacao");
      printf("   - Valor: %s\n", pontuacao_descricao(token->valor));
      break;

    case TOKEN_ERRO:
      print_erro(" * Token não reconhecido: ");
      print_erro(yytext);
      print_erro("\n");
      break;

    default:
      print_erro("TIPO DE TOKEN DESCONHECIODO\n");
  }
}

char *palavra_chave_descricao(int operacao) {
  char *res;

  switch (operacao) {
    case TOKEN_INT:
      res = "INT";
      break;
    case TOKEN_BOOLEAN:
      res = "BOOLEAN";
      break;

    default:
      res = "NENHUM";
  }

  return res;
}

char *operador_descricao(int operacao) {
  char *res;

  switch(operacao) {
    case SOMA:
      res = "SOMA";
      break;
    case SUBTRACAO:
      res = "SUBTRAÇÃO";
      break;
    case MULTIPLICACAO:
      res = "MULTIPLICAÇÃO";
      break;
    case DIVISAO:
      res = "DIVISÃO";
      break;
    case RESTO:
      res = "RESTO";
      break;

    case MENOR:
      res = "MENOR";
      break;
    case MENOR_IGUAL:
      res = "MENOR OU IGUAL";
      break;

    case MAIOR:
      res = "MAIOR";
      break;
    case MAIOR_IGUAL:
      res = "MAIOR OU IGUAL";
      break;

    case COMPARACAO_IGUAL:
      res = "COMPARAÇÃO IGUAL";
      break;
    case COMPARACAO_DIFERENTE:
      res = "COMPARAÇÃO DIFERENTE";
      break;

    case BOOLEANO_AND:
      res = "AND (boolean)";
      break;
    case BOOLEANO_OR:
      res = "OR (boolean)";
      break;
    case BOOLEANO_NOT:
      res = "NOT (boolean)";
      break;

    case ATRIBUICAO:
      res = "ATRIBUIÇÃO";
      break;

    default:
      res = "NENHUM";
  }

  return res;
}


char *pontuacao_descricao(int operacao){
  char *res;

  switch (operacao){
    case PARENTESE_ESQUERDO:
      res = "PARENTESE_ESQUERDO";
      break;

    case PARENTESE_DIREITO:
      res = "PARENTESE_DIREITO";
      break;

    case VIRGULA:
      res = "VIRGULA";
      break;

    case PONTO_VIRGULA:
      res = "PONTO_VIRGULA";
      break;

    default:
      res = "NENHUM";
  }
  return res;
}

void finalizar_analise(FILE * yyin) {
  destruir_tabela_simbolos();
  fclose(yyin);
}
