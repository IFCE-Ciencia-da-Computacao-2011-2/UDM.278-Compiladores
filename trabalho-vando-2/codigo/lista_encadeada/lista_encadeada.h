#ifndef __LISTA_ENCADEADA_H

#define __LISTA_ENCADEADA_H


typedef struct {
  void * valor;
  void * proximo;

} ListaEncadeada;

/**
 * Cria uma lista encadeada com um elemento (valor dado)
 */
extern ListaEncadeada * new_lista_encadeada(void * valor);

/**
 * Concatena duas lista, apontando o fim da `lista` para `lista_fim`
 */
extern ListaEncadeada * lista_concatenar(ListaEncadeada * lista, ListaEncadeada * lista_fim);

#endif
