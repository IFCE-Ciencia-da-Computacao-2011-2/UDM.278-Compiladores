%option noyywrap
%option yylineno
%option outfile="regras.tab.c" header-file="regras.tab.h"

%top {
#include "gramatica.tab.h"
#include "common.h"
#include "tabela.h"
#include "mensagem.h"
}

NUM [0-9]+
EXP ([Ee][-+]?[0-9]+)
FLOAT ([0-9]*\.{NUM}|{NUM}\.){EXP}?

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

int  return t_integer;
bool return t_boolean;

and return t_bool_and;
or  return t_bool_or;
not return t_bool_not;

true   return t_bool_true;
false  return t_bool_false;

{NUM} {
  yylval.int_value = atoi(yytext);
  return t_integer_value;
}

\+ return t_adicao;
-  return t_subtracao;
\* return t_multiplicacao;
\/ return t_divisao;
\% return t_resto;

\<  return t_comparacao_menor;
\<= return t_comparacao_menor_igual;
\>  return t_operacao_maior;
\>= return t_operacao_maior_igual;

==  return t_comparacao_igual;
!=  return t_comparacao_diferente;

=   return t_atribuicao;

\(  return t_abre_parentese;
\)  return t_fecha_parentese;
,   return t_virgula;
;   return t_ponto_virgula;

{ID_INVALIDO} {
    char * mensagem = mensagem_preparar("%s‘%s’%s é um nome de variável inválido\n", "\033[1;97m", yytext, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return t_noop;
}

{ID}  {
  yylval.simbolo = tabela_adicionar(yytext);
  return t_variavel;
}

{FLOAT} {
    char * mensagem = mensagem_preparar("%s‘%s’%s - Pontos flutuantes não são aceitos pela linguagem\n", "\033[1;97m", yytext, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return t_noop;
}
.   {
    char * mensagem = mensagem_preparar("%s‘%s’%s  é um elemento não previsto na análise léxica\n", "\033[1;97m", yytext, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return t_noop;
}

<<EOF>> { return t_eof; }

%%
