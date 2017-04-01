#include <stdlib.h>

#include "lista_encadeada.h"

static ListaElemento * new_lista_elemento(void * valor);
static void destroy_lista_encadeada(ListaEncadeada * lista);

ListaEncadeada * new_lista_encadeada(void * valor) {
  ListaEncadeada * lista = calloc(1, sizeof(ListaEncadeada));
  ListaElemento * elemento = new_lista_elemento(valor);

  lista->primeiro = elemento;
  lista->ultimo = elemento;

  return lista;
}

static ListaElemento * new_lista_elemento(void * valor) {
  ListaElemento * elemento = calloc(1, sizeof(ListaElemento));

  elemento->valor = valor;
  elemento->proximo = NULL;

  return elemento;
}

ListaEncadeada * lista_concatenar(ListaEncadeada * lista, ListaEncadeada * lista_fim) {
  ListaEncadeada * nova_lista = calloc(1, sizeof(ListaEncadeada));

  lista->ultimo->proximo = lista_fim->primeiro;

  nova_lista->primeiro = lista->primeiro;
  nova_lista->ultimo = lista_fim->ultimo;

  destroy_lista_encadeada(lista);
  destroy_lista_encadeada(lista_fim);

  return nova_lista;
}

static void destroy_lista_encadeada(ListaEncadeada * lista) {
  free(lista);
}
