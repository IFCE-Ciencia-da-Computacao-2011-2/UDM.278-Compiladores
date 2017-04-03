%{
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "logica.h"
#include "mensagem.h"
#include "lista_encadeada/lista_encadeada.h"

#include "regras.tab.h"
#include "conversor.h"

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
 // Identificador de variável na tabela de símbolos
 Simbolo * simbolo;

 // Declarar tipo de uma variável
 SimboloTipo tipo;

 // Lista de elementos
 ListaEncadeada * lista;

 // Nó da árvore sintática
 NoAST * no;

 int int_value;
}


// http://www.gnu.org/software/bison/manual/html_node/Token-Decl.html#Token-Decl
// Tipos
%token t_int
%token t_bool
%token t_string
%token <simbolo> t_variavel

%token t_constante_int
%token t_constante_bool_true
%token t_constante_bool_false
//%token t_constante_string


// Palavras reservadas
%token t_var // Bloco de definição de variáveis
%token t_begin // Bloco de código
%token t_end // Fim do código
%token t_do t_to // Laço "for"

// Análise léxica detecta e trata algum erro
%token t_noop
// Fim do arquivo
%token t_eof

// Prioridades
//%left t_bool_and t_bool_or
//%left t_comparacao_igual t_comparacao_diferente
//%left t_comparacao_menor t_comparacao_menor_igual t_operacao_maior t_operacao_maior_igual
%left '+' '-'
//%left t_multiplicacao t_divisao t_resto  // Verificar prioridade
//%left t_bool_not


// Tokens da gramática: Elementos não terminais
%type<tipo> tipo
%type<lista> lista_declaracoes
%type<lista> variavel_declaracao
%type<lista> lista_variaveis variavel

%type<lista> lista_comandos
%type<no> comando
%type<no> expressao
%type<no> constante constante_int constante_bool

/************************************************************/
%%
/************************************************************/

programa: t_var lista_declaracoes t_begin lista_comandos t_end fim_codigo {
//programa: t_var lista_declaracoes t_begin lista_comandos t_end fim_codigo {
  NoAST * no = no_new_raiz($2, $4);
  imprimir_codigo(no);
  //no_free(no);
  exit(0);
}
;


/******************************
 * Declarações
 ******************************/
lista_declaracoes: lista_declaracoes variavel_declaracao { $$ = lista_concatenar($1, new_lista_encadeada($2)); }
                 | variavel_declaracao { $$ = new_lista_encadeada($1); }
;

variavel_declaracao: tipo ':' lista_variaveis { $$ = logica_declarar_lista_variaveis($3, $1); }
;

tipo: t_int    {$$ = SIMBOLO_TIPO_INTEIRO;}
    | t_bool   {$$ = SIMBOLO_TIPO_BOOLEANO;}
    | t_string {$$ = SIMBOLO_TIPO_STRING;}
;

lista_variaveis: lista_variaveis ',' variavel { $$ = lista_concatenar($1, $3); }
               | variavel { $$ = $1; }
;

variavel: t_variavel { $$ = new_lista_encadeada($1); }
;

/******************************
 * Comandos
 ******************************/
lista_comandos: lista_comandos comando { $$ = lista_concatenar($1, new_lista_encadeada($2)); }
              | comando { $$ = new_lista_encadeada($1); }
;

comando: t_do t_variavel ':' '=' expressao t_to expressao t_begin
           expressao // lista_comandos
         t_end { $$ = no_new_repeticao_for($2, $5, $7, new_lista_encadeada($9)); }
;/*
         | palavra_reservada_if expressao lista_comandos t_end
         | palavra_reservada_if expressao lista_comandos
           palavra_reservada_else lista_comandos t_end
         | palavra_reservada_while expressao
           lista_comandos t_end
         | palavra_reservada_read t_variavel ';'
         | palavra_reservada_write expressao ';'
 ;
*/

expressao: expressao '+' expressao { $$ = no_new_expressao($1, ADICAO, $3); }
         | expressao '-' expressao { $$ = no_new_expressao($1, SUBTRACAO, $3); }
         /*| expressao '*' expressao
           | expressao '/' expressao
           | '-' expressao
           | expressao  boolean_or expressao
           | expressao boolean_and expressao
           | boolean_not expressao
           | expressao  boolean_igual expressao
           | expressao  boolean_diferente expressao
           | expressao  boolean_maior expressao
           | expressao  boolean_menor expressao
           | expressao  boolean_menor_igual expressao
           | expressao  boolean_maior_igual expressao
           | '(' expressao ')'*/
         | constante { $$ = no_new_expressao($1, CONSTANTE, NULL); }
         //| t_variavel
;

constante: constante_int { $$ = $1; }
         | constante_bool { $$ = $1; }
       //| t_constante_string
;

constante_int: t_constante_int { $$ = NULL; }

constante_bool: t_constante_bool_true  { $$ = NULL; }
              | t_constante_bool_false { $$ = NULL; }

/******************************
* Fim de arquivo
******************************/

fim_codigo: t_eof { /*ast_imprimir($$);*/ }
;

%%

int main() {
  printf("Vando 1.0.0 (64-bit)\n");
  printf("[GCC %d.%d.%d] on linux\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);

  return yyparse();
}
