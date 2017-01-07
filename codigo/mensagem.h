#ifndef __MENSAGEM_H

#define __MENSAGEM_H

#include <stdio.h>
#include <stdlib.h>

extern char * mensagem_preparar(const char * fmt, ...);
extern void mensagem_erro(char * nome_arquivo, int linha, int coluna, char * mensagem, ...);
extern void mensagem_cabecalho(FILE * arquivo, char * nome_arquivo, int linha, int coluna);

extern void yyerror(char *s, ...);

#endif
