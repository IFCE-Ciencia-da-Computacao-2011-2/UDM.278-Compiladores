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

true   return t_constante_bool_true;
false  return t_constante_bool_false;


{ID} {
  yylval.simbolo = tabela_adicionar(yytext);
  return t_variavel;
}

{NUM} {
  yylval.int_value = atoi(yytext);
  return t_constante_int;
}

<<EOF>> { return t_eof; }

%%
