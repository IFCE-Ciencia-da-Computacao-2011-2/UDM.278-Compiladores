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
 char string_value[4095]; // C99 limit string
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
%token t_constante_string


// Palavras reservadas
%token t_var // Bloco de definição de variáveis
%token t_begin // Bloco de código
%token t_end // Fim do código
%token t_do t_to // Laço "for"
%token t_while // Laço "while"
%token t_read t_write // input e print
%token t_if t_else // condicional

// Análise léxica detecta e trata algum erro
%token t_noop
// Fim do arquivo
%token t_eof

// Prioridades
// Vertical: Último é mais prioritário que o primeiro
// Horizontal: Direita mais prioritário que esquerda
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
%type<no> expressao_booleana expressao_inteira
%type<no> constante constante_int constante_bool

%type<simbolo> variavel_declarada
%type<string_value> t_constante_string

/************************************************************/
%%
/************************************************************/

programa: t_var lista_declaracoes t_begin lista_comandos t_end fim_codigo {
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

comando: t_do variavel_declarada ':' '=' expressao_inteira t_to expressao_inteira t_begin
           lista_comandos
         t_end { $$ = no_new_repeticao_for($2, $5, $7, $9); }
       | t_if expressao_booleana t_begin
           lista_comandos
         t_end { $$ = no_new_if_else($2, $4, NULL); }
       | t_if expressao_booleana t_begin
           lista_comandos
         t_else
           lista_comandos
         t_end { $$ = no_new_if_else($2, $4, $6); }
       | t_while expressao_booleana t_begin
           lista_comandos
         t_end { $$ = no_new_repeticao_while($2, $4); }
       | t_read variavel_declarada ';' { $$ = no_new_input($2); }
       | t_write expressao ';' { $$ = no_new_print($2); }
       | variavel_declarada ':' '=' expressao ';' { $$ = logica_atribuicao_variavel($1, $4); }
;

variavel_declarada: t_variavel { $$ = $1; logica_verificar_variavel_declarada($1); }
;
/******************************
 * Expressões
 ******************************/
expressao_booleana: expressao { $$ = $1; logica_verificar_expressao_booleana((NoExpressaoAST *) $1->no); };
expressao_inteira:  expressao { $$ = $1; logica_verificar_expressao_inteira((NoExpressaoAST *) $1->no); };

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
         // FIXME VERIFICAR VARIÁVEIL JÁ DECLARADA
         | t_variavel { $$ = no_new_expressao(no_new_variavel($1), VARIAVEL, NULL); logica_verificar_variavel_declarada($1); }
;

constante: constante_int { $$ = $1; }
         | constante_bool { $$ = $1; }
         | t_constante_string { $$ = no_new_constante_referencia($1, SIMBOLO_TIPO_STRING); }
;

constante_int: t_constante_int { $$ = no_new_constante(0, SIMBOLO_TIPO_INTEIRO); }

constante_bool: t_constante_bool_true  { $$ = no_new_constante(TRUE, SIMBOLO_TIPO_BOOLEANO); }
              | t_constante_bool_false { $$ = no_new_constante(FALSE, SIMBOLO_TIPO_BOOLEANO); }

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
