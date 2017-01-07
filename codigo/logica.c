#include "logica.h"

#include "common.h"
#include "mensagem.h"

void logica_declarar_variavel(Simbolo * simbolo) {
  if (!simbolo->atribuido) {
    simbolo->atribuido = 1;
    return;
  }

  char * mensagem = mensagem_preparar("Variável %s‘%s’%s já foi declarado previamente\n", "\033[1;97m", simbolo->nome, "\033[0m");
  mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
  free(mensagem);
}


/////////////////////////////////
// Erros
/////////////////////////////////
void erro_atribuicao_palavras_reservadas() {
    char * mensagem = mensagem_preparar("Palavras reservadas e números são nomes de variáveis inválidos\n");
    mensagem_erro(yy_nome_arquivo, yylineno, 0, mensagem);
    free(mensagem);
}
