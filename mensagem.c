#include <stdio.h>
#include <stdlib.h>

#include <stdarg.h>

#include "codigo.h"
#include "mensagem.h"
#include "gramatica.tab.h"

/*
void update_localization() {
    static int curr_line = 1;
    static int curr_col  = 1;

    printf("aaa");
    yylloc.first_line   = curr_line;
    yylloc.first_column = curr_col;

    {
        char * s;
        for (s = yytext; *s != '\0'; s++) {
            if (*s == '\n') {
                curr_line++;
                curr_col = 1;
            } else {
                curr_col++;
            }
        }
    }

    yylloc.last_line   = curr_line;
    yylloc.last_column = curr_col-1;
}
*/

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
