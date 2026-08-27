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

int soma(int x, int y);
int eh_par(int n);
int maior(int a, int b);
int potencia(int base, int expoente);
int fatorial(int n);
int fatorial_rec(int n);

/* ============================================================
   PROGRAMA PRINCIPAL
   ============================================================ */

int main(void) {

    int a = 4, b = 6, r;

    /* TODO: chamar a função soma e armazenar o resultado em r */
    r = soma(a, b);
    printf("Soma: %d\n", r);

    /* TODO: chamar a função eh_par */
    if (eh_par(b))
        printf("Par: %d\n", b);

    /* TODO: chamar a função maior */
    printf("Maior: %d\n", maior(a,b));

    /* TODO: chamar a função potencia */
    printf("Potencia: %d\n", potencia(2, 10));

    /* TODO: chamar a função fatorial */
    printf("Fatorial: %d\n", fatorial(a));

    /* TODO: chamar a função fatorial_rec */
    printf("Fatorial Recursivo: %d\n", fatorial_rec(a));

    return 0;
}

/* ============================================================
   EXERCÍCIO 1 — Soma de dois números
   ============================================================ */

int soma(int x, int y) {
    /* TODO: retornar a soma de a e b */
    return x + y;
}

/* ============================================================
   EXERCÍCIO 2 — Verificar número par
   ============================================================ */

int eh_par(int n) {
    /* TODO: retornar 1 se n for par, 0 caso contrário */
    if (n % 2 == 0)
        return 1;
    return 0;
}

/* ============================================================
   EXERCÍCIO 3 — Maior de dois números
   ============================================================ */

int maior(int a, int b) {
    /* TODO: retornar o maior valor entre a e b */
    if (a > b)
        return a;
    return b;
}

/* ============================================================
   EXERCÍCIO 4 — Potência
   ============================================================ */

int potencia(int base, int expoente) {
    /* TODO: calcular base^expoente sem usar pow */
    int i, result = 1;
    for(i = 0; i < expoente; i++)
        result *= base;
    return result;
}

/* ============================================================
   EXERCÍCIO 5 — Fatorial
   ============================================================ */

int fatorial(int n) {
    /* TODO: calcular e retornar o fatorial de n */
    int i, result;

    result = 1;
    for (i = n; i > 0; i--)
        result *= i;

    return result;
}

/* ============================================================
   EXERCÍCIO 6 — Fatorial Recursico
   ============================================================ */

int fatorial_rec(int n) {

    // Caso base
    if (n == 1 || n == 0)
        return 1;

    return n * fatorial_rec(n-1);

}
