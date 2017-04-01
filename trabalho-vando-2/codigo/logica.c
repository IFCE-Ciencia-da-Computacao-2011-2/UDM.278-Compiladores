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
  if (!simbolo->atribuido) {
    simbolo->atribuido = TRUE;
    simbolo->valor.integer = 0;

    simbolo->tipo = tipo;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}
