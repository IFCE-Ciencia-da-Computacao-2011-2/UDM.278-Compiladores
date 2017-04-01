%{
#include <stdio.h>
#include <stdarg.h>

#include "common.h"
#include "mensagem.h"

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
}


// http://www.gnu.org/software/bison/manual/html_node/Token-Decl.html#Token-Decl
// Tipos
%token t_int
%token t_bool
%token t_string
%token <simbolo> t_variavel

// Palavras reservadas
%token t_var // Bloco de definição de variáveis
%token t_begin // Bloco de código
%token t_end // Fim do código

// Análise léxica detecta e trata algum erro
%token t_noop
// Fim do arquivo
%token t_eof

// Pontuação
%token t_virgula t_ponto_virgula t_dois_pontos

// Tokens da gramática: Elementos não terminais

%%
//programa: t_var lista_declaracoes t_begin lista_comandos t_end fim_codigo {
programa: t_var t_begin t_end fim_codigo {
  //no_new_raiz($2, $4);
  NoAST * no = no_new_raiz(NULL, NULL);
  imprimir_codigo(no);
  //no_free(no);
  exit(0);
}
;



/******************************
 * Declarações
 ******************************/
lista_declaracoes: lista_declaracoes t_ponto_virgula variavel_declaracao
                 | variavel_declaracao
;

variavel_declaracao: tipo t_dois_pontos lista_variaveis
;

tipo: t_int
    | t_bool
    | t_string
;

lista_variaveis: lista_variaveis t_virgula variavel
               | variavel
;

variavel: t_variavel
;

/******************************
 * Comandos
 ******************************/

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
