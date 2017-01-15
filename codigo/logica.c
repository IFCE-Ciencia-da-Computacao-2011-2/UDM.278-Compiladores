#include "logica.h"

#include "common.h"
#include "mensagem.h"

static int logica_resolver_expressao(NoAST * expressao_no);

void logica_declarar_variavel(Simbolo * simbolo) {
  if (!simbolo->atribuido) {
    simbolo->atribuido = TRUE;
    simbolo->valor.integer = 0;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_definir_tipo(Simbolo * simbolo, SimboloTipo tipo) {
  simbolo->tipo = tipo;
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
        "\033[1;97m", SimboloTipoDecricao[simbolo->tipo], "\033[0m",
        "\033[1;97m", SimboloTipoDecricao[expressao_no->simbolo_tipo], "\033[0m"
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

static int logica_resolver_expressao(NoAST * expressao_no) {
  if (expressao_no->tipo == AST_TIPO_CONSTANTE)
    return ((NoConstanteAST *) expressao_no->no)->valor;

  else if (expressao_no->tipo == AST_TIPO_DELIMITADOR) {
    char * mensagem = mensagem_preparar("Tentando pegar um valor de um delimitador. Caso não esperado\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    exit(1);
  }

  else if (expressao_no->tipo == AST_TIPO_OPERACAO_MEIO)
    return ((NoOperacaoMeioAST *) expressao_no->no)->valor;
}

/////////////////////////////////
// Erros
/////////////////////////////////
void erro_atribuicao_palavras_reservadas() {
    char * mensagem = mensagem_preparar("Palavras reservadas e números são nomes de variáveis inválidos\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
}
