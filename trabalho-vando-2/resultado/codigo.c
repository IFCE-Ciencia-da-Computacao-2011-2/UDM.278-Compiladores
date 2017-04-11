// Vando 1.0.0 (64-bit)
// [GCC 5.4.0] on linux
// Vando: Por Paulo Mateus e Leonardo Silva

#include <stdio.h>
#include <stdbool.h>

#include "base.h"

int main() {
    char * nome, curso, campus;
    int idade, semestre, ira;
    _Bool cursando;

    cursando = (true >= false);
    nome = "Paulo";
    nome = concatenate(nome, (concatenate(" ", "Mateus")));
    printf("%s", concatenate(nome, "\n"));
}
