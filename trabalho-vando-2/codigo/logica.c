#include "logica.h"

#include "common.h"
#include "mensagem.h"

static void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo);

ListaEncadeada * logica_declarar_lista_variaveis(ListaEncadeada * lista, SimboloTipo tipo) {
  ListaElemento * elemento = lista->primeiro;

  while (elemento != NULL) {
    Simbolo * simbolo = (Simbolo *) elemento->valor;

    logica_declarar_variavel(simbolo, tipo);

    elemento = (ListaElemento *) elemento->proximo;
  }

  return lista;
}

static void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo) {
  if (!simbolo->declarado) {
    simbolo->declarado = TRUE;
    simbolo->valor.integer = 0;

    simbolo->tipo = tipo;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_verificar_variavel_declarada(Simbolo * simbolo) {
  if (!simbolo->declarado) {
    char * mensagem = mensagem_preparar("Variável %s‘%s’%s não declarado\n", "\033[1;97m", simbolo->nome, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
  }
}

NoAST * logica_atribuicao_variavel(Simbolo * simbolo, NoAST * no) {
  NoExpressaoAST * expressao = (NoExpressaoAST *) no->no;

  if (simbolo->tipo != expressao->tipo) {
    char * mensagem = mensagem_preparar(
        "Variável %s‘%s’%s é do tipo %s‘%s’%s, mas está sendo atribuído um valor do tipo %s‘%s’%s\n",
        "\033[1;97m", simbolo->nome, "\033[0m",
        "\033[1;97m", SimboloTipoDescricao[simbolo->tipo], "\033[0m",
        "\033[1;97m", SimboloTipoDescricao[expressao->tipo], "\033[0m"
    );
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
  }

  return no_new_atribuicao(simbolo, no);
}

void logica_verificar_expressao_booleana(NoExpressaoAST * expressao) {
  if (expressao->tipo == SIMBOLO_TIPO_BOOLEANO)
    return;

  char * mensagem = mensagem_preparar(
    "É esperado uma expressão %s‘%s’%s. Expressão utilizada: %s‘%s’%s\n",
    "\033[1;97m", SimboloTipoDescricao[SIMBOLO_TIPO_BOOLEANO], "\033[0m",
    "\033[1;97m", SimboloTipoDescricao[expressao->tipo], "\033[0m"
  );
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_verificar_expressao_inteira(NoExpressaoAST * expressao) {
  if (expressao->tipo == SIMBOLO_TIPO_INTEIRO)
    return;

  char * mensagem = mensagem_preparar(
    "É esperado uma expressão %s‘%s’%s. Expressão utilizada: %s‘%s’%s\n",
    "\033[1;97m", SimboloTipoDescricao[SIMBOLO_TIPO_INTEIRO], "\033[0m",
    "\033[1;97m", SimboloTipoDescricao[expressao->tipo], "\033[0m"
  );
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}
