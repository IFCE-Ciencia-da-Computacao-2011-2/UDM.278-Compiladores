#ifndef __TABELA_H

#define __TABELA_H

#define MAX_SIMBOLOS  300

typedef struct Simbolo {
  int id;
  char nome[32];
  int tipo;
  int atribuido;

  union {
    int integer;
    int boolean;
  } valor;
} Simbolo;


extern Simbolo * tabela_adicionar(char *id);
extern void destruir_tabela_simbolos();

#endif
