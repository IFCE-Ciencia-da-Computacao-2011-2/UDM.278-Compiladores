#ifndef __TABELA_H

#define __TABELA_H

#define MAX_SIMBOLOS  300

typedef enum {
  SIMBOLO_TIPO_INTEIRO,
  SIMBOLO_TIPO_BOOLEANO,

  SIMBOLO_TIPO_NULL // A linguagem não aceita null.
} SimboloTipo;

extern const char * SimboloTipoDescricao[];

typedef enum {FALSE, TRUE} Boolean;

typedef struct Simbolo {
  int id;
  char nome[32];
  SimboloTipo tipo;
  Boolean atribuido;

  union {
    int integer;
    Boolean boolean;
  } valor;
} Simbolo;


extern Simbolo * tabela_adicionar(char *id);
extern void destruir_tabela_simbolos();

#endif
