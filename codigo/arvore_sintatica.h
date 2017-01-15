// AST = abstract syntax tree
// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

#include "tabela.h"

typedef enum {AST_TIPO_CONSTANTE, AST_TIPO_DELIMITADOR, AST_TIPO_OPERACAO_MEIO} NoTipoAST;

typedef struct {
  void * no;

  NoTipoAST tipo;
  SimboloTipo simbolo_tipo;
} NoAST;

typedef struct {
  int valor;
} NoConstanteAST;

typedef struct {
  char valor;
} NoDelimitadorAST;

typedef struct {
  NoAST * no_esquerdo;
  char * operacao;
  NoAST * no_direito;
    
  int valor;
} NoOperacaoMeioAST;

extern NoAST * no_new_constante(int valor, SimboloTipo simbolo_tipo);

extern NoAST * no_new_atribuicao(Simbolo * simbolo, NoAST * no_expressao);

/**
 * Operação do meio trabalha somente com expressões inteiras
 *
 * Exemplo: <, >, <=, >=, +, -, *, /, % 
 */ 
extern NoAST * no_new_operacao_meio_inteiro(NoAST * no_esquerdo, NoAST * no_direito, char * operacao, SimboloTipo tipo_resultado);

/**
 * Operação do meio trabalha somente com expressões booleanas
 *
 * Exemplo: or, and
 */ 
extern NoAST * no_new_operacao_meio_booleano(NoAST * no_esquerdo, NoAST * no_direito, char * operacao);

/**
 * Operação do meio genérica, não verifica tipagem dos nos envolvidos
 */ 
extern NoAST * no_new_operacao_meio(NoAST * no_esquerdo, NoAST * no_direito, char * operacao, SimboloTipo tipo_resultado);

extern void ast_imprimir();

#endif
