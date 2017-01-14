#include "logica.h"

#include "common.h"
#include "mensagem.h"

void logica_declarar_variavel(Simbolo * simbolo) {
  if (!simbolo->atribuido) {
    simbolo->atribuido = 1;
    simbolo->valor.integer = 0;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}

void logica_atribuir_variavel(Simbolo * simbolo, void * sei_la) {
  if (!simbolo->atribuido) {
    char * mensagem = mensagem_preparar("Variável %s‘%s’%s não definida\n", "\033[1;97m", simbolo->nome, "\033[0m");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
    return;
  } 
}

/////////////////////////////////
// Erros
/////////////////////////////////
void erro_atribuicao_palavras_reservadas() {
    char * mensagem = mensagem_preparar("Palavras reservadas e números são nomes de variáveis inválidos\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
}
