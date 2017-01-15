// AST = abstract syntax tree
// https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/
#ifndef __ARVORE_SINTATICA_H

#define __ARVORE_SINTATICA_H

#include "tabela.h"

typedef enum {
    AST_TIPO_CONSTANTE, AST_TIPO_REFERENCIA,
    AST_TIPO_DELIMITADOR,
    AST_TIPO_OPERACAO_MEIO, AST_TIPO_OPERACAO_INICIO,
    AST_TIPO_PARENTESES
} NoTipoAST;

typedef struct {
  void * no;

  NoTipoAST tipo;
  SimboloTipo simbolo_tipo;
} NoAST;

typedef struct {
  int valor;
} NoConstanteAST;

typedef struct {
  Simbolo * simbolo;
} NoReferenciaAST;

typedef struct {
  char valor;
} NoDelimitadorAST;

typedef struct {
  NoAST * no_esquerdo;
  char * operacao;
  NoAST * no_direito;

} NoOperacaoMeioAST;

typedef struct {
  char * operacao;
  NoAST * no;

} NoOperacaoInicioAST;

typedef struct {
  NoAST * no;

} NoParentesesAST;

extern NoAST * no_new_constante(int valor, SimboloTipo simbolo_tipo);

/**
 * Utilizado uma variável em uma expressão
 */
extern NoAST * no_new_referencia(Simbolo * simbolo);

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

/**
 * Operação do início trabalha somente com expressões booleanas
 *
 * Exemplo: not
 */
extern NoAST * no_new_operacao_inicio(NoAST * no_direito, char * operacao);

/**
 * Expressão envolvida entre parênteses
 * 
 * Exemplo: ( 2 + 4 )
 */
extern NoAST * no_new_parenteses(NoAST * no_expressao);

extern void ast_imprimir(NoAST * raiz);

#endif
