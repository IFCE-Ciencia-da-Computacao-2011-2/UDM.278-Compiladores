/**
 * tabela.h - Tabela de símbolos
 *
 * Adaptado de Andrei de A. Formiga, 2014-09-19
 * http://producao.virtual.ufpb.br/books/tautologico/compiladores-livro/livro/capitulos/code/cap2/minic/
 */

#ifndef __TOKENS_H
#define __TOKENS_H

// Tipos de token
#define TOKEN_PALAVRA_CHAVE 1
#define TOKEN_ID            2
#define TOKEN_NUMERO        3
#define TOKEN_OPERACAO      4
#define TOKEN_PONTUACAO     5
#define TOKEN_ERRO          100

// Tipos
#define TOKEN_INT            0
#define TOKEN_BOOLEAN        1

// Valores booleanos
#define FALSE 0
#define TRUE  1

// Constantes para valores de operadores
#define SOMA                 0
#define SUBTRACAO            1
#define MULTIPLICACAO        2
#define DIVISAO              3
#define RESTO                4

#define MENOR                5
#define MENOR_IGUAL          6
#define MAIOR                7
#define MAIOR_IGUAL          8

#define COMPARACAO_IGUAL     9
#define COMPARACAO_DIFERENTE 10

#define BOOLEANO_AND         11
#define BOOLEANO_OR          12
#define BOOLEANO_NOT         13

#define ATRIBUICAO           14

// Valores das pontuações
#define PARENTESE_ESQUERDO   0
#define PARENTESE_DIREITO    1
#define VIRGULA 	         2
#define PONTO_VIRGULA	     3

typedef struct {
    int tipo;
    int valor;
} Token;

// funcao para criar um token
extern Token *token(); // #define YY_DECL Token * yylex()

// funcao principal do analisador lexico
//extern Token *yylex();

#endif
