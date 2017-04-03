%option noyywrap
%option yylineno
%option outfile="regras.tab.c" header-file="regras.tab.h"

%top {
#include "gramatica.tab.h"
#include "common.h"
#include "tabela.h"
}

NUM [0-9]+
EXP ([Ee][-+]?[0-9]+)

ID_CARACTERES_VALIDOS  ([[:alnum:]]|\_)
ID_CARACTERES_INVALIDOS  (\.)

ID  [[:alpha:]]({ID_CARACTERES_VALIDOS})*{0,31}
ID_INVALIDO {NUM}{ID}|({ID}{ID_CARACTERES_INVALIDOS}{ID})+
STRING      L?\"(\\.|[^\\"])*\"
%%

\n.* {
  strncpy(yy_line_buffer, yytext+1, sizeof(yy_line_buffer));
  yyless(1);
}

[[:space:]]

[,:;=+\-*/()]	return *yytext;

int    return t_int;
bool   return t_bool;
string return t_string;


var    return t_var;
begin  return t_begin;
end    return t_end;

do     return t_do;
to     return t_to;

while  return t_while;

true   return t_constante_bool_true;
false  return t_constante_bool_false;

read   return t_read;
write  return t_write;

if     return t_if;
else   return t_else;

{ID} {
  yylval.simbolo = tabela_adicionar(yytext);
  return t_variavel;
}

{NUM} {
  yylval.int_value = atoi(yytext);
  return t_constante_int;
}

{STRING} {
  int size = strlen(yytext);

  // Remover aspas
  int string_vazia = size == 2;

  if (string_vazia)
    yytext[1] = '\0';
  else
    for (int i=0; i<(size-1); i++)
      yytext[i] = yytext[i+1];

  yytext[size-2] = '\0';

	strncpy(yylval.string_value, yytext, size);

	return t_constante_string;
}

<<EOF>> { return t_eof; }

%%
