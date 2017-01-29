#include "logica.h"

#include "common.h"
#include "mensagem.h"

static int logica_resolver_expressao(NoAST * expressao_no);

void logica_verificar_variavel_declarada_anteriormente(Simbolo * simbolo) {
  if (simbolo->atribuido)
    return;
  
  char * mensagem = mensagem_preparar("Variável %s‘%s’%s não foi declarada previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_declarar_lista_variaveis(NoAST * no, SimboloTipo tipo) {
  NoAST * proximo_no = no;
  NoElementoListaEncadeadaAST * ponteiro = NULL;
  
  while (proximo_no != NULL) {
    ponteiro = (NoElementoListaEncadeadaAST *) proximo_no->no;

    Simbolo * simbolo = (Simbolo *) ponteiro->simbolo;
    
    logica_declarar_variavel(simbolo, tipo);

    proximo_no = ponteiro->proximo_no;
  }
}

void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo) {
  if (!simbolo->atribuido) {
    simbolo->atribuido = TRUE;
    simbolo->valor.integer = 0;

    simbolo->tipo = tipo;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_atribuir_variavel(Simbolo * simbolo, NoAST * expressao_no) {
  if (!simbolo->atribuido) {
    char * mensagem = mensagem_preparar("Variável %s‘%s’%s não definida\n", "\033[1;97m", simbolo->nome, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return;
  }

  if (simbolo->tipo != expressao_no->simbolo_tipo) {
    char * mensagem = mensagem_preparar(
        "Variável %s‘%s’%s é do tipo %s‘%s’%s, mas está sendo atribuído um valor do tipo %s‘%s’%s\n",
        "\033[1;97m", simbolo->nome, "\033[0m",
        "\033[1;97m", SimboloTipoDescricao[simbolo->tipo], "\033[0m",
        "\033[1;97m", SimboloTipoDescricao[expressao_no->simbolo_tipo], "\033[0m"
    );
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return;
  }  

  if (simbolo->tipo == SIMBOLO_TIPO_INTEIRO)
    simbolo->valor.integer = logica_resolver_expressao(expressao_no);
  else if (simbolo->tipo == SIMBOLO_TIPO_BOOLEANO)
    simbolo->valor.boolean = logica_resolver_expressao(expressao_no);
}

// Aqui que deve implementar o resolvedor de expressões
static int logica_resolver_expressao(NoAST * expressao_no) {
  return 0;
}

/////////////////////////////////
// Erros
/////////////////////////////////
void erro_atribuicao_palavras_reservadas() {
    char * mensagem = mensagem_preparar("Palavras reservadas e números são nomes de variáveis inválidos\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
}
