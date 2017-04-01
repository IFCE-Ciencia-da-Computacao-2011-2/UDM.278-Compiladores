#ifndef __LISTA_ENCADEADA_H

#define __LISTA_ENCADEADA_H

typedef struct {
  void * valor;
  void * proximo;

} ListaElemento;

typedef struct {
  ListaElemento * primeiro;
  ListaElemento * ultimo;

} ListaEncadeada;


/**
 * Cria uma lista encadeada com um elemento (valor dado)
 */
extern ListaEncadeada * new_lista_encadeada(void * valor);

/**
 * DESTROI AS DUAS LISTAS e gera uma nova lista concatenando
 * `lista` e `lista_fim`
 */
extern ListaEncadeada * lista_concatenar(ListaEncadeada * lista, ListaEncadeada * lista_fim);

#endif
