#ifndef __LOGICA_H

#define __LOGICA_H

#include "arvore_sintatica.h"
#include "tabela.h"

extern void logica_declarar_variavel(Simbolo * simbolo, SimboloTipo tipo);
extern void logica_declarar_lista_variaveis(NoAST * no, SimboloTipo tipo);

extern void logica_atribuir_variavel(Simbolo * simbolo, NoAST * expressao_noh);

extern void erro_atribuicao_palavras_reservadas();

#endif
