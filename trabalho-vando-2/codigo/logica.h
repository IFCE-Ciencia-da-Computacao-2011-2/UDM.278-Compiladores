#ifndef __LOGICA_H

#define __LOGICA_H

#include "arvore_sintatica.h"
#include "tabela.h"

extern ListaEncadeada * logica_declarar_lista_variaveis(ListaEncadeada * lista, SimboloTipo tipo);
extern void logica_verificar_variavel_declarada(Simbolo * simbolo);
extern NoAST * logica_atribuicao_variavel(Simbolo * simbolo, NoAST * no);

extern void logica_verificar_expressao_booleana(NoExpressaoAST * expressao);
extern void logica_verificar_expressao_inteira(NoExpressaoAST * expressao);

#endif
