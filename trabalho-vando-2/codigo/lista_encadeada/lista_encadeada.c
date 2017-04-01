#include <stdlib.h>

#include "lista_encadeada.h"

ListaEncadeada * new_lista_encadeada(void * valor) {
  ListaEncadeada * lista = calloc(1, sizeof(ListaEncadeada));

  lista->valor = valor;
  lista->proximo = NULL;

  return lista;
}

/**
 * O próximo elemento da lista é a lista fim
 */
ListaEncadeada * lista_concatenar(ListaEncadeada * lista, ListaEncadeada * lista_fim) {
  lista->proximo = lista_fim;
  return lista;
}
