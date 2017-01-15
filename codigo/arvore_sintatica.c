#include <stdio.h>
#include <stdlib.h>

#include "arvore_sintatica.h"
#include "common.h"
#include "mensagem.h"

NoAST * no_new_constante(int valor, SimboloTipo simbolo_tipo) {
  NoAST * no = malloc(sizeof(NoAST));
  NoConstanteAST * no_constante = malloc(sizeof(NoConstanteAST));
  
  no->no = no_constante;
    
  no->tipo = AST_TIPO_CONSTANTE;
  no->simbolo_tipo = simbolo_tipo;
  
  no_constante->valor = valor;
  
  return no;
}

NoAST * no_new_delimitador(char valor) {
  NoAST * no = malloc(sizeof(NoAST));
  NoDelimitadorAST * no_delimitador = malloc(sizeof(NoDelimitadorAST));
  
  no->tipo = AST_TIPO_DELIMITADOR;
  no->no = no_delimitador;
  
  no_delimitador->valor = valor;
  
  return no;
}

NoAST * no_new_operacao_meio(NoAST * no_esquerdo, NoAST * no_direito, char * operacao) {
  NoAST * no = malloc(sizeof(NoAST));
  NoOperacaoMeioAST * no_operacao_meio = malloc(sizeof(NoOperacaoMeioAST));
  
  if (no_operacao_meio->no_esquerdo->simbolo_tipo != no_operacao_meio->no_direito->simbolo_tipo) {
    char * mensagem = mensagem_preparar("Operação envolve dois valores de tipos distintos.\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
  }

  no->no = no_operacao_meio;
  no->simbolo_tipo = no_operacao_meio->no_esquerdo->simbolo_tipo;
  no->tipo = AST_TIPO_OPERACAO_MEIO;
    
  no_operacao_meio->no_esquerdo = no_esquerdo;
  no_operacao_meio->no_direito = no_direito;
  no_operacao_meio->operacao = operacao;
  
  no_operacao_meio->valor = 0; // FIXME

  return no;
}


void ast_imprimir() {
    printf("Insira o código a seguir em http://www.webgraphviz.com/\n");
    
    // a [label="node"]; b [label="node"]; a->b
    printf("\n");
    printf("digraph program {\n");
    printf("}\n");
}
