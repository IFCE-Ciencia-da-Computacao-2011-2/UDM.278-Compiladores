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
 void * simbolo;
}

// http://www.gnu.org/software/bison/manual/html_node/Token-Decl.html#Token-Decl
%token t_integer
%token t_boolean
%token <simbolo> t_variavel

// Aparece quando a análise léxica detecta e trata algum erro
%token t_noop

%token <int_value> t_integer_value

%token t_bool_true t_bool_false

%token t_abre_parentese t_fecha_parentese t_virgula t_ponto_virgula

// Mais prioritário vem primeiro
%right t_atribuicao

%left t_bool_not
%left t_bool_and t_bool_or
%left t_comparacao_igual t_comparacao_diferente
%left t_comparacao_menor t_comparacao_menor_igual t_operacao_maior t_operacao_maior_igual
%left t_adicao t_subtracao
%left t_multiplicacao t_divisao t_resto


%%
codigo:
| definicao_variaveis codigo
| erros codigo
| atribuicoes
;

// Definições
definicao_variaveis
: tipo definicao_variaveis_meio      
| tipo definicao_variavel_fim
;

definicao_variaveis_meio
: definicao_variavel_meio definicao_variaveis_meio
| definicao_variavel_meio definicao_variavel_fim
;

definicao_variavel_meio
: t_variavel t_virgula        { logica_declarar_variavel($1);}
| palavra_reservada t_virgula { erro_atribuicao_palavras_reservadas(); }
| atomo t_virgula             { erro_atribuicao_palavras_reservadas(); }
;

definicao_variavel_fim
: t_variavel t_ponto_virgula { logica_declarar_variavel($1); }
| palavra_reservada t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
| atomo t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
;

palavra_reservada: tipo
tipo: t_integer | t_boolean

atomo: t_integer_value | atomo_boolean
atomo_boolean: t_bool_true | t_bool_false

// Erros
erros: t_noop
;

// Atribuições
atribuicoes
: atribuicoes atribuicao t_ponto_virgula
| atribuicao t_ponto_virgula
;

atribuicoes: atribuicao

atribuicao
: t_variavel t_atribuicao expressao       {logica_atribuir_variavel($1, NULL);}
;

// Mais prioritário vem por último ?
expressao
: atomo
| t_variavel
// Inteiro
| expressao t_adicao expressao
| expressao t_subtracao expressao
| expressao t_multiplicacao expressao
| expressao t_divisao expressao
| expressao t_resto expressao
// Booleano
| expressao t_operacao_maior_igual expressao
| expressao t_operacao_maior expressao
| expressao t_comparacao_menor_igual expressao
| expressao t_comparacao_menor expressao
| expressao t_comparacao_diferente expressao
| expressao t_comparacao_igual expressao
| expressao t_bool_or expressao
| expressao t_bool_and expressao
| t_bool_not expressao
| t_abre_parentese expressao t_fecha_parentese
;

%%

int main() {
  printf("Vando 0.0.1 (64-bit)\n");
  printf("[GCC ?.?.?] on linux\n");

  // a [label="node"]; b [label="node"]; a->b
  printf("\n");
  printf("digraph program {\n");

  return yyparse();
  
  printf("}");
}
