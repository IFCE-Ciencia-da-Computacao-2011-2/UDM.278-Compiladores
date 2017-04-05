#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

char * read_string() {
  char buffer[4095];
  scanf("%[^\n]%*c", buffer);

  char * string = (char *) calloc(1, strlen(buffer) + 1);
  strcpy(string, buffer);
  return string;
}

int read_int() {
  int number;
  scanf("%d", &number);
  clear();

  return number;
}

int read_bool() {
  char * string = read_string();

  int result = strcmp(string, "true\0");
  free(string);

  return result == 0;
}

char * concatenate(char * a, char * b) {
  char * string = calloc(1, strlen(a) + strlen(b) + 1);

  strcpy(string, a);
  strcat(string, b);

  return string;
}

// gcc -o teste base.c && ./teste
/*
int main() {
  printf("Nome: ");
  char * nome = read_string();

  printf("Idade: ");
  int idade = read_int();

  printf("Curso: ");
  char * curso = read_string();

  printf("Maior de idade (true, false)? ");
  int maior_idade = read_bool();

  printf("\n");
  printf("Nome - Curso: \n");
  printf(" - %s \n", concatenate(nome, concatenate(" - ", curso)));
  printf("Idade: \n");
  printf(" - %d \n", idade);
  printf("Maior de idade: \n");
  printf(" - %s \n", maior_idade ? "Sim" : "Não");
}
*/
