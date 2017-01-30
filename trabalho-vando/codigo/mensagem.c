#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

#include "mensagem.h"

#include "gramatica.tab.h"
    
// https://latedev.wordpress.com/2012/10/29/understanding-printf/
char * mensagem_preparar(const char * fmt, ...) {
    int size = 40, n;
    char * buffer = NULL;

    do {
        size *= 2;
        va_list valist;
        va_start(valist, fmt);
        buffer = realloc(buffer, size);
        n = vsnprintf(buffer, size, fmt, valist);
        va_end(valist);
    } while (n >= size);

    return buffer;
}

void mensagem_erro(char * nome_arquivo, int linha, int coluna, char * mensagem, ...) {
    if (nome_arquivo == NULL)
      nome_arquivo = "interpretador";

    mensagem_cabecalho(stderr, nome_arquivo, linha, coluna);
    fprintf(stderr, "\033[1;31merro:\033[0m ");
    fprintf(stderr, "%s", mensagem);
    //if (yy_line_buffer[0] != '\0')
    //  fprintf(stderr, " > %s\n", yy_line_buffer);
}

void mensagem_cabecalho(FILE * arquivo, char * nome_arquivo, int linha, int coluna) {
    fprintf(arquivo, "\033[1;97m%s:%d:%d\033[0m ", nome_arquivo, linha, coluna);
}

void yyerror(char *s, ...) {
  fprintf(stderr, "Algo de errado não está certo\n");

  /*
  va_list ap;
  va_start(ap, s);
  fprintf(stderr, "%d: error: ", yylineno);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
  */

  va_list ap;
  va_start(ap, s);
  if (yylloc.first_line)
    fprintf(stderr, "%d.%d-%d.%d: error: ", yylloc.first_line, yylloc.first_column,
  yylloc.last_line, yylloc.last_column);
  vfprintf(stderr, s, ap);
  fprintf(stderr, "\n");
}
