%{
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "logica.h"
#include "mensagem.h"

#include "regras.tab.h"

extern int yylex();
extern void yyerror(char *s, ...);

#define YY_USER_ACTION update_localization();
%}
%locations

%code requires {
    #include "tabela.h"
    #include "arvore_sintatica.h"
}

// yylval
%union {
 // Valor de constantes
 int int_value;

 // Identificador de variável na tabela de símbolos
 Simbolo * simbolo;
 
 // Definir tipo de uma variável
 SimboloTipo tipo;

 // Valor de expressão
 //   que não foi totalmente processada e enviada para a
 //   tabela de símbolos através de uma atribuição à uma variável
 NoAST * no;
}

// http://www.gnu.org/software/bison/manual/html_node/Token-Decl.html#Token-Decl
%token t_integer
%token t_boolean
%token <simbolo> t_variavel

// Aparece quando a análise léxica detecta e trata algum erro
%token t_noop
// Fim do arquivo
%token t_eof

%token <int_value> t_integer_value

%token t_bool_true t_bool_false

%token t_abre_parentese t_fecha_parentese t_virgula t_ponto_virgula

// Mais prioritário vem por último
%right t_atribuicao

%left t_bool_not
%left t_bool_and t_bool_or
%left t_comparacao_menor t_comparacao_menor_igual t_operacao_maior t_operacao_maior_igual
%left t_comparacao_igual t_comparacao_diferente
%left t_adicao t_subtracao               // Verificar prioridade
%left t_multiplicacao t_divisao t_resto  // Verificar prioridade

// Tokens da gramática: Elementos não terminais
%type<simbolo> definicao_variaveis_meio definicao_variavel_meio definicao_variavel_fim
%type<no> atomo atomo_boolean expressao atribuicao
%type<tipo> tipo

%%
codigo:
| definicao_variaveis codigo
| erros codigo
| atribuicoes fim_codigo
| fim_codigo
;

fim_codigo: t_eof { /*ast_imprimir($$);*/ exit(0); }

// Definições
definicao_variaveis
: tipo definicao_variaveis_meio  // A definição de tipos ocorre dentro de definicao_variaveis_meio
| tipo definicao_variavel_fim    { logica_definir_tipo($2, $1); }
;

definicao_variaveis_meio
: definicao_variavel_meio definicao_variaveis_meio { logica_declarar_variavel_mesmo_tipo($1, $2); $$ = $1; }
| definicao_variavel_meio definicao_variavel_fim { logica_declarar_variavel_mesmo_tipo($1, $2); $$ = $1; }
;

definicao_variavel_meio
: t_variavel t_virgula        { logica_declarar_variavel($1); $$ = $1;}
| palavra_reservada t_virgula { erro_atribuicao_palavras_reservadas(); }
| atomo t_virgula             { erro_atribuicao_palavras_reservadas(); }
;

definicao_variavel_fim
: t_variavel t_ponto_virgula { logica_declarar_variavel($1); $$ = $1; }
| palavra_reservada t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
| atomo t_ponto_virgula { erro_atribuicao_palavras_reservadas(); }
;

palavra_reservada: tipo
tipo
: t_integer {$$ = SIMBOLO_TIPO_INTEIRO;}
| t_boolean {$$ = SIMBOLO_TIPO_BOOLEANO;}

atomo
: t_integer_value {$$ = no_new_constante($1, SIMBOLO_TIPO_INTEIRO); }
| atomo_boolean   {$$ = $1; }
;
atomo_boolean
: t_bool_true  {$$ = no_new_constante(TRUE, SIMBOLO_TIPO_BOOLEANO); }
| t_bool_false {$$ = no_new_constante(FALSE, SIMBOLO_TIPO_BOOLEANO);}
;

// Erros
erros: t_noop
;

// Atribuições
atribuicoes
: atribuicoes atribuicao
| atribuicao 
;

atribuicao
: t_variavel t_atribuicao expressao t_ponto_virgula  {logica_atribuir_variavel($1, $3); $$ = no_new_atribuicao($1, $3); /*ast_imprimir($$);*/ }
;

// Mais prioritário vem por último ?
expressao
: atomo           { $$ = $1; }
| t_variavel      { $$ = no_new_referencia($1); }
// Inteiro
| expressao t_adicao expressao          { $$ = no_new_operacao_meio_inteiro($1, $3, "+", SIMBOLO_TIPO_INTEIRO); }
| expressao t_subtracao expressao       { $$ = no_new_operacao_meio_inteiro($1, $3, "-", SIMBOLO_TIPO_INTEIRO); }
| expressao t_multiplicacao expressao   { $$ = no_new_operacao_meio_inteiro($1, $3, "*", SIMBOLO_TIPO_INTEIRO); }
| expressao t_divisao expressao         { $$ = no_new_operacao_meio_inteiro($1, $3, "/", SIMBOLO_TIPO_INTEIRO); }
| expressao t_resto expressao           { $$ = no_new_operacao_meio_inteiro($1, $3, "%", SIMBOLO_TIPO_INTEIRO); }
// Booleano
| expressao t_operacao_maior_igual expressao     { $$ = no_new_operacao_meio_inteiro($1, $3, ">=", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_operacao_maior expressao           { $$ = no_new_operacao_meio_inteiro($1, $3, ">", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_comparacao_menor_igual expressao   { $$ = no_new_operacao_meio_inteiro($1, $3, "<=", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_comparacao_menor expressao         { $$ = no_new_operacao_meio_inteiro($1, $3, "<", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_comparacao_diferente expressao     { $$ = no_new_operacao_meio($1, $3, "!=", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_comparacao_igual expressao         { $$ = no_new_operacao_meio($1, $3, "==", SIMBOLO_TIPO_BOOLEANO); }
| expressao t_bool_or expressao                  { $$ = no_new_operacao_meio_booleano($1, $3, "or"); }
| expressao t_bool_and expressao                 { $$ = no_new_operacao_meio_booleano($1, $3, "and"); }
| t_bool_not expressao                           { $$ = no_new_operacao_inicio($2, "not"); }
| t_abre_parentese expressao t_fecha_parentese   { $$ = no_new_parenteses($2); }
;

%%

int main() {
  printf("Vando 0.0.1 (64-bit)\n");
  printf("[GCC ?.?.?] on linux\n");

  return yyparse();
}
