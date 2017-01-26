#ifndef __LOGICA_H

#define __LOGICA_H

#include "arvore_sintatica.h"
#include "tabela.h"

extern void logica_declarar_variavel(Simbolo * simbolo);
/**
 * Declara o símbolo a_ser_declarado com o mesmo tipo do simbolo ja_declarado
 * 
 * São verificadas as mesmas coisas que foram em 
 * - logica_declarar_variavel
 * - logica_definir_tipo
 */
extern void logica_declarar_variavel_mesmo_tipo(Simbolo * a_ser_declarado, Simbolo * ja_declarado);

extern void logica_definir_tipo(Simbolo * simbolo, SimboloTipo tipo);
extern void logica_atribuir_variavel(Simbolo * simbolo, NoAST * expressao_noh);

extern void erro_atribuicao_palavras_reservadas();

#endif
