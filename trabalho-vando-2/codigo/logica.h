#ifndef __LOGICA_H

#define __LOGICA_H

#include "arvore_sintatica.h"
#include "tabela.h"

extern ListaEncadeada * logica_declarar_lista_variaveis(ListaEncadeada * lista, SimboloTipo tipo);

extern void logica_check_expressao_valida(NoAST * no);
extern void logica_check_expressao_booleana(NoAST * no);

extern void logica_check_expressao_aritmetica(NoExpressaoAST * no_expressao);
extern void logica_check_expressao_logica(NoExpressaoAST * no_expressao);
extern void logica_check_expressao_relacional(NoExpressaoAST * no_expressao);

#endif
