#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tabela.h"

const char * SimboloTipoDescricao[] = {"int", "bool", "string"};
const char * SimboloTipoDescricaoC[] = {"int", "int", "char[]"};

static Simbolo * tabela_simbolos[MAX_SIMBOLOS];
static unsigned int total_simbolos = 0;

static Simbolo * tabela_malloc(char * nome_variavel);
static Simbolo * tabela_new(Simbolo * simbolo, unsigned int id, char * nome_variavel);


Simbolo * tabela_buscar(char * nome_variavel) {
  int i;

  for (i=0; i < total_simbolos; ++i) {
    Simbolo * simbolo = tabela_simbolos[i];

    if (strcmp(nome_variavel, simbolo->nome) == 0)
      return simbolo;
  }

  return NULL;
}

/**
 * Adiciona um identificador na tabela de símbolos, se ainda
 * não estiver na tabela. Se o identificador já estiver na
 * tabela, retorna seu numero
 */
Simbolo * tabela_adicionar(char * nome_variavel) {
  Simbolo * simbolo = tabela_buscar(nome_variavel);
  if (simbolo != NULL)
    return simbolo;

  if (total_simbolos >= MAX_SIMBOLOS) {
    fprintf(stderr, "%sERRO: Limite máximo de símbolos armazenáveis na tabela de símbolos foi ultrapassado.\n", "\033[0;31m");
    fprintf(stderr, "      Para estabelecer um novo limite, verifique o arquivo %s‘%s’%s.\n", "\033[0;91m", "tabela.h", "\033[0;31m");
    fprintf(stderr, "      Limite do compilador: %s%d%s\n", "\033[0;91m", MAX_SIMBOLOS, "\033[0;31m");
    exit(1);
  }

  simbolo = tabela_malloc(nome_variavel);
  simbolo = tabela_new(simbolo, total_simbolos, nome_variavel);

  tabela_simbolos[total_simbolos] = simbolo;
  total_simbolos += 1;

  return simbolo;
}

static Simbolo * tabela_malloc(char * nome_variavel) {
  Simbolo * simbolo = (Simbolo *) malloc(sizeof(Simbolo));

  if (simbolo == NULL) {
    fprintf(stderr, "Não foi possivel alocar espaço para símbolo no. %d\n", total_simbolos);
    fprintf(stderr, "Símbolo: %s%s%s\n", "\033[0;91m", nome_variavel, "\033[0;31m");
    exit(1);
  }

  return simbolo;
}

static Simbolo * tabela_new(Simbolo * simbolo, unsigned int id, char * nome_variavel) {
  simbolo->id = total_simbolos;
  strcpy(simbolo->nome, nome_variavel);
  simbolo->declarado = FALSE;
  simbolo->tipo = 0;

  return simbolo;
}

void destruir_tabela_simbolos() {
  int i;

  for (i = 0; i < total_simbolos; ++i)
    free(tabela_simbolos[i]);
}
