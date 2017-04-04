#include "logica.h"

#include "common.h"
#include "mensagem.h"

static void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo);

ListaEncadeada * logica_declarar_lista_variaveis(ListaEncadeada * lista, SimboloTipo tipo) {
  ListaElemento * elemento = lista->primeiro;

  while (elemento != NULL) {
    Simbolo * simbolo = (Simbolo *) elemento->valor;

    logica_declarar_variavel(simbolo, tipo);

    elemento = (ListaElemento *) elemento->proximo;
  }

  return lista;
}

static void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo) {
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

void logica_expressao_valida(NoAST * no) {
  NoExpressaoAST * no_expressao = (NoExpressaoAST *) no->no;
  
  if (is_operacao_aritmetica(no_expressao->operacao)) {
    check_expressao_aritmetica(no_expressao);
  
  } else if (is_operacao_logica(no_expressao->operacao)) {
    check_expressao_logica(no_expressao);

  } else if (is_operacao_relacional(no_expressao->operacao)) {
    check_expressao_relacional(no_expressao);
  //} else if (no_expressao->operacao == "()") {
      
  } else {
    printf("Não sei tratar expressão \"%c\"", no_expressao->operacao);
    exit(1);
  }
}

void check_expressao_aritmetica(NoExpressaoAST * no_expressao) {
  if (no_expressao->operacao == ADICAO,
   || no_expressao->operacao == SUBTRACAO,
   || no_expressao->operacao == MULTIPLICACAO,
   || no_expressao->operacao == DIVISAO) {
    check_expressao_aritmetica(no_expressao->no_esquerda);
    check_expressao_aritmetica(no_expressao->no_direita);
  }/* else if (no_expressao->operacao == "- exp") {
    
  }*/ else {
    printf("??????");
    exit(1);
  }
}

void check_expressao_logica(NoExpressaoAST * no_expressao) {
    
}

void check_expressao_relacional(NoExpressaoAST * no_expressao) {
  
}
