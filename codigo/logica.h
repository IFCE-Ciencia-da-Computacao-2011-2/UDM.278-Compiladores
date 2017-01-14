#ifndef __LOGICA_H

#define __LOGICA_H

#include "tabela.h"

extern void logica_declarar_variavel(Simbolo * simbolo);
extern void logica_atribuir_variavel(Simbolo * simbolo, void * sei_la);

extern void erro_atribuicao_palavras_reservadas();

#endif
