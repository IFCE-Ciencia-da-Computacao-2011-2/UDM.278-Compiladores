// Vando 1.0.0 (64-bit)
// [GCC 5.4.0] on linux
// Vando: Por Paulo Mateus e Leonardo Silva

#include <stdio.h>
#include <stdbool.h>

#include "base.h"

int main() {
    char * nome;
    int n1, n2;
    int media;
    int max_fibo;
    _Bool love;

    printf("%s", "Nome: ");
    nome = read_string();
    printf("%s", "Nota na N1: ");
    n1 = read_int();
    printf("%s", "Nota na N2: ");
    n2 = read_int();
    media = (n1 * 2 + n2 * 3) / 5;
    printf("%s", "\n");
    printf("%s", "Média: ");
    printf("%d", media);
    printf("%s", "\n");
    printf("%s", concatenate(nome, ",\n"));
    if (media >= 7) {
    printf("%s", "você passou de semestre!\n");
    } else {
    if (media >= 5) {
    printf("%s", "você passaria por conceito B\n");
    } else {
    printf("%s", "você está em uma situação delicada\n");
    }
    }
    printf("%s", "\n");
    printf("%s", "A média é um número ");
    if (media / 2 * 2 == media) {
    printf("%s", "par\n");
    } else {
    printf("%s", "ímpar\n");
    }
    printf("%s", "\n");
    printf("%s", "Fibo até: ");
    max_fibo = read_int();
    printf("%s", "\n");
    printf("%s", "Você gosta de mim (true/false)? ");
    love = read_bool();
    if (love) {
    printf("%s", "Cê tá confundindo as parada\n");
    } else {
    printf("%s", "Aié?! Eu vou te reprovar!\n");
    }
}
