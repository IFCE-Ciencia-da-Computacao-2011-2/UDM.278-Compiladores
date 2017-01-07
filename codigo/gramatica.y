%{
#include <stdio.h>
#include <stdarg.h>

#include "tabela.h"
#include "common.h"
#include "mensagem.h"
#include "logica.h"

#include "regras.tab.h"

extern int yylex();
extern void yyerror(char *s, ...);

#define YY_USER_ACTION update_localization();
%}
%locations

// yylval
%union {
 int int_value;
 int bool_value;
 void * simbolo;
}

// http://www.gnu.org/software/bison/manual/html_node/Token-Decl.html#Token-Decl
%token t_integer
%token t_boolean
%token <simbolo> t_variavel

// Aparece quando a análise léxica detecta e trata algum erro
%token t_noop

%token <int_value> t_integer_value
%token <bool_value> t_boolean_value
%token t_bool_and t_bool_or t_bool_not
%token t_adicao t_subtracao t_multiplicacao t_divisao t_resto
%token t_comparacao_menor t_comparacao_menor_igual
%token t_operacao_maior t_operacao_maior_igual
%token t_comparacao_igual t_comparacao_diferente

%token t_atribuicao

%token t_abre_parecente t_fecha_parentese t_virgula t_ponto_virgula

%%
codigo:
| definicao_variaveis codigo
| erros codigo
;

definicao_variaveis: tipo definicao_variaveis_meio  {}
|                    tipo definicao_variavel_fim    {}
;

definicao_variaveis_meio: definicao_variavel_meio definicao_variaveis_meio   {}
                        | definicao_variavel_meio definicao_variavel_fim     {}

definicao_variavel_meio: t_variavel t_virgula      { logica_declarar_variavel($1); }
definicao_variavel_fim: t_variavel t_ponto_virgula { logica_declarar_variavel($1); }

tipo: t_integer | t_boolean {}

// Erros
erros: erro_atribuicao_palavras_reservadas {}
| t_noop
;

erro_atribuicao_palavras_reservadas: tipo valor t_ponto_virgula {
  char * mensagem = "Palavras reservadas e números são nomes de variáveis inválidos\n";
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
}

valor: t_integer_value | t_boolean_value
%%

int main() {
  printf("Vando 0.0.1 (64-bit)\n");
  printf("[GCC ?.?.?] on linux\n");

	return yyparse();
}
