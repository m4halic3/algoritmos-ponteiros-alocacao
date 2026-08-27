/*
 * Lista 1 – Revisão de Funções
 * Disciplina: Programação Estruturada
 *
 * Conteúdo:
 *  - Declaração e implementação de funções
 *  - Passagem de parâmetros por valor
 *  - Retorno de valores
 *  - Chamada correta das funções
 *
 * RESTRIÇÕES:
 *  - NÃO usar ponteiros
 *  - NÃO usar struct
 *
 * Arquivo: lista1-funcoes.c
 */

#include <stdio.h>

int soma(int a, int b);
int eh_par(int n);
int maior(int a, int b);
int potencia(int base, int expoente);
int fatorial(int n);

/* ============================================================
   PROGRAMA PRINCIPAL
   ============================================================ */

int main(void) {

    int a = 4, b = 6, r;

    /* TODO: chamar a função soma e armazenar o resultado em r */
    printf("Soma: %d\n", 0);

    /* TODO: chamar a função eh_par */
    printf("Par: %d\n", 0);

    /* TODO: chamar a função maior */
    printf("Maior: %d\n", 0);

    /* TODO: chamar a função potencia */
    printf("Potencia: %d\n", 0);

    /* TODO: chamar a função fatorial */
    printf("Fatorial: %d\n", 0);

    return 0;
}

/* ============================================================
   EXERCÍCIO 1 — Soma de dois números
   ============================================================ */

int soma(int a, int b) {
    /* TODO: retornar a soma de a e b */
    return 0;
}

/* ============================================================
   EXERCÍCIO 2 — Verificar número par
   ============================================================ */

int eh_par(int n) {
    /* TODO: retornar 1 se n for par, 0 caso contrário */
    return 0;
}

/* ============================================================
   EXERCÍCIO 3 — Maior de dois números
   ============================================================ */

int maior(int a, int b) {
    /* TODO: retornar o maior valor entre a e b */
    return 0;
}

/* ============================================================
   EXERCÍCIO 4 — Potência
   ============================================================ */

int potencia(int base, int expoente) {
    /* TODO: calcular base^expoente sem usar pow */
    return 0;
}

/* ============================================================
   EXERCÍCIO 5 — Fatorial
   ============================================================ */

int fatorial(int n) {
    /* TODO: calcular e retornar o fatorial de n */
    return 0;
}

