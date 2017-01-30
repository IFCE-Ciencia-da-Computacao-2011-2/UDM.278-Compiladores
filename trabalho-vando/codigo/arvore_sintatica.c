#include <stdio.h>
#include <stdlib.h>

#include "arvore_sintatica.h"
#include "common.h"
#include "mensagem.h"

NoAST * no_new_constante(int valor, SimboloTipo simbolo_tipo) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoConstanteAST * no_constante = malloc(sizeof(NoConstanteAST));
  
  no->no = no_constante;
  no->tipo = AST_TIPO_CONSTANTE;
  no->simbolo_tipo = simbolo_tipo;
  
  no_constante->valor = valor;
  
  return no;
}

NoAST * no_new_referencia(Simbolo * simbolo) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoReferenciaAST * no_referencia = malloc(sizeof(NoReferenciaAST));

  no->no = no_referencia;
  no->tipo = AST_TIPO_REFERENCIA;
  no->simbolo_tipo = simbolo->tipo;

  no_referencia->simbolo = simbolo;

  return no;
}

NoAST * no_new_delimitador(char valor) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoDelimitadorAST * no_delimitador = malloc(sizeof(NoDelimitadorAST));
  
  no->tipo = AST_TIPO_DELIMITADOR;
  no->no = no_delimitador;
  
  no_delimitador->valor = valor;
  
  return no;
}

NoAST * no_new_atribuicao(Simbolo * simbolo, NoAST * no_expressao) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoAtribuicaoAST * no_atribuicao = malloc(sizeof(NoAtribuicaoAST));
  
  no->tipo = AST_TIPO_ATRIBUICAO;
  no->no = no_atribuicao;

  no_atribuicao->simbolo = simbolo;
  no_atribuicao->no_expressao = no_expressao;
  
  return no;
}

static void erro_operacao_tipo(char * posicao, NoAST * no, char * operacao, SimboloTipo tipo_operacao);

NoAST * no_new_operacao_meio_inteiro(NoAST * no_esquerdo, NoAST * no_direito, char * operacao, SimboloTipo tipo_resultado) {
  SimboloTipo tipo = SIMBOLO_TIPO_INTEIRO;

  if (no_esquerdo->simbolo_tipo != tipo)
    erro_operacao_tipo("esquerda", no_esquerdo, operacao, tipo);
  if (no_direito->simbolo_tipo != tipo)
    erro_operacao_tipo("direito", no_direito, operacao, tipo);

  return no_new_operacao_meio(no_esquerdo, no_direito, operacao, tipo_resultado);
}

NoAST * no_new_operacao_meio_booleano(NoAST * no_esquerdo, NoAST * no_direito, char * operacao) {
  SimboloTipo tipo = SIMBOLO_TIPO_BOOLEANO;

  if (no_esquerdo->simbolo_tipo != tipo)
    erro_operacao_tipo("esquerda", no_esquerdo, operacao, tipo);
  if (no_direito->simbolo_tipo != tipo)
    erro_operacao_tipo("direito", no_direito, operacao, tipo);

  return no_new_operacao_meio(no_esquerdo, no_direito, operacao, tipo);
}

static void erro_operacao_tipo(char * posicao, NoAST * no, char * operacao, SimboloTipo tipo_operacao) {
  char * mensagem = mensagem_preparar(
    "Símbolo à %s da operação %s‘%s’%s é do tipo %s‘%s’%s, mas a operação aceita somente %s‘%s’%s\n",
    posicao,
    "\033[1;97m", operacao, "\033[0m",
    "\033[1;97m", SimboloTipoDescricao[no->simbolo_tipo], "\033[0m",
    "\033[1;97m", SimboloTipoDescricao[tipo_operacao], "\033[0m"
  );

  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

NoAST * no_new_operacao_meio(NoAST * no_esquerdo, NoAST * no_direito, char * operacao, SimboloTipo tipo_resultado) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoOperacaoMeioAST * no_operacao_meio = malloc(sizeof(NoOperacaoMeioAST));
  
  no->no = no_operacao_meio;
  no->tipo = AST_TIPO_OPERACAO_MEIO;
  no->simbolo_tipo = tipo_resultado;

  no_operacao_meio->no_esquerdo = no_esquerdo;
  no_operacao_meio->no_direito = no_direito;
  no_operacao_meio->operacao = operacao;

  return no;
}

NoAST * no_new_operacao_inicio(NoAST * no_direito, char * operacao) {
  SimboloTipo tipo = SIMBOLO_TIPO_BOOLEANO;

  if (no_direito->simbolo_tipo != tipo)
    erro_operacao_tipo("direito", no_direito, operacao, tipo);

  NoAST * no = calloc(1, sizeof(NoAST));
  NoOperacaoInicioAST * no_operacao_inicio = malloc(sizeof(NoOperacaoInicioAST));
  
  no->no = no_operacao_inicio;
  no->tipo = AST_TIPO_OPERACAO_INICIO;
  no->simbolo_tipo = tipo;

  no_operacao_inicio->operacao = operacao;
  no_operacao_inicio->no = no_direito;

  return no;
}

NoAST * no_new_parenteses(NoAST * no_expressao) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoParentesesAST * no_parenteses = malloc(sizeof(NoParentesesAST));
  
  no->no = no_parenteses;
  no->tipo = AST_TIPO_PARENTESES;
  no->simbolo_tipo = no_expressao->simbolo_tipo;

  no_parenteses->no = no_expressao;

  return no;
}


NoAST * no_new_elemento_lista_encadeada(Simbolo * simbolo) {
  NoAST * no = calloc(1, sizeof(NoAST));
  NoElementoListaEncadeadaAST * no_elemento = malloc(sizeof(NoElementoListaEncadeadaAST));
  
  no->no = no_elemento;
  no->tipo = AST_TIPO_ELEMENTO_LISTA_ENCADEADA;

  no_elemento->simbolo = simbolo;
  no_elemento->proximo_no = NULL;
  
  return no;
}

void no_vincula_elementos_lista_encadeada(NoAST * no, NoAST * proximo_no) {
   NoElementoListaEncadeadaAST * no_elemento = (NoElementoListaEncadeadaAST *) no->no;
   no_elemento->proximo_no = proximo_no;
}
