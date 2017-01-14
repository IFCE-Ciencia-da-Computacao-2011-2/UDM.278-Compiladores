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

%token t_bool_and t_bool_or t_bool_not
%token t_bool_true t_bool_false

%token t_adicao t_subtracao t_multiplicacao t_divisao t_resto
%token t_comparacao_menor t_comparacao_menor_igual
%token t_operacao_maior t_operacao_maior_igual
%token t_comparacao_igual t_comparacao_diferente

%token t_atribuicao

%token t_abre_parentese t_fecha_parentese t_virgula t_ponto_virgula

%%
codigo:
| definicao_variaveis codigo
| erros codigo
| atribuicoes
;

// Definições
definicao_variaveis: tipo definicao_variaveis_meio  {}
|                    tipo definicao_variavel_fim    {}
;

definicao_variaveis_meio: definicao_variavel_meio definicao_variaveis_meio   {}
                        | definicao_variavel_meio definicao_variavel_fim     {}

definicao_variavel_meio: t_variavel t_virgula        { logica_declarar_variavel($1); }
|                        palavra_reservada t_virgula { erro_atribuicao_palavras_reservadas(); }
|                        valor t_virgula             { erro_atribuicao_palavras_reservadas(); }
;

definicao_variavel_fim: t_variavel t_ponto_virgula { logica_declarar_variavel($1); }
|                       palavra_reservada t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
|                       valor t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
;

palavra_reservada: tipo
tipo: t_integer | t_boolean

valor: t_integer_value | boolean_valor
boolean_valor: t_bool_true | t_bool_false

// Erros
erros: t_noop
;

// Atribuições
atribuicoes: atribuicoes atribuicao t_ponto_virgula
|            atribuicao t_ponto_virgula

atribuicao: t_variavel t_atribuicao expressao       {logica_atribuir_variavel($1, NULL);}
;

expressao: t_abre_parentese expressao t_fecha_parentese
|          expressao operacao_meio expressao
|          operacao_inicio expressao
|          t_variavel
|          valor
;

operacao_meio: operacao_meio_inteiro
|              operacao_meio_booleano
;

operacao_meio_inteiro: t_adicao | t_subtracao | t_multiplicacao | t_divisao | t_resto
|                      t_comparacao_menor | t_comparacao_menor_igual | t_operacao_maior | t_operacao_maior_igual
|                      t_comparacao_igual | t_comparacao_diferente

operacao_meio_booleano: t_bool_and t_bool_or
operacao_inicio: t_bool_not
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
