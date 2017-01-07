%option noyywrap
%option yylineno
%option outfile="regras.tab.c" header-file="regras.tab.h"

%top {
#include "gramatica.tab.h"
#include "codigo.h"
#include "tabela.h"
#include "tokens.h"

#include "mensagem.h"
}

NUM [0-9]+
EXP ([Ee][-+]?[0-9]+)
FLOAT ([0-9]*\.{NUM}|{NUM}\.){EXP}?
ID  [[:alpha:]]([[:alnum:]]|\_)*{0,31}

ID_INVALIDO {NUM}{ID}|{ID}
%%

\n.* {
  strncpy(yy_line_buffer, yytext+1, sizeof(yy_line_buffer));
  yyless(1);
}

[[:space:]]

int  return t_integer;
bool return t_boolean;

and return TOKEN_BOOLEANO_AND;
or  return TOKEN_BOOLEANO_OR;
not return TOKEN_BOOLEANO_NOT;

{NUM} {
  yylval.int_value = atoi(yytext);
  return t_integer_value;
};
{ID}  {
  yylval.simbolo = tabela_adicionar(yytext);
  return t_variavel;
}
\+ return TOKEN_OPERACAO_SOMA;
-  return TOKEN_OPERACAO_SUBTRACAO;
\* return TOKEN_OPERACAO_MULTIPLICACAO;
\/ return TOKEN_OPERACAO_DIVISAO;
\% return TOKEN_OPERACAO_RESTO;

\<  return TOKEN_OPERACAO_MENOR;
\<= return TOKEN_OPERACAO_MENOR_IGUAL;
\>  return TOKEN_OPERACAO_MAIOR;
\>= return TOKEN_OPERACAO_MAIOR_IGUAL;

==  return TOKEN_OPERACAO_COMPARACAO_IGUAL;
!=  return TOKEN_OPERACAO_COMPARACAO_DIFERENTE;

=   return TOKEN_OPERACAO_ATRIBUICAO;

\(  return TOKEN_PONTUACAO_PARENTESE_ESQUERDO;
\)  return TOKEN_PONTUACAO_PARENTESE_DIREITO;
,   return t_virgula;
;   return t_ponto_virgula;

{ID_INVALIDO} {
    char * mensagem = mensagem_preparar("%s‘%s’%s é um nome de variável inválido\n", "\033[1;97m", yytext, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return t_noop;
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

%%
