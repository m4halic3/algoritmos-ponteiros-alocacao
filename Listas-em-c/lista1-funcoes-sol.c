/*
 * Lista 1 - Revisão de Funções
 * Disciplina: Programação Estruturada
 *
 * Conteúdo:
 *  - Declaração e implementação de funções
 *  - Passagem de parâmetros por valor
 *  - Retorno de valores
 *  - Chamada correta das funções
 *
 * RESTRIÇÕES:
 *  - Não usar ponteiros
 *  - Não usar struct
 *
 * Arquivo: lista1-funcoes.c
 * Material de apoio - solução comentada.
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

    r = soma(a, b);
    printf("Soma: %d\n", r);

    if (eh_par(b))
        printf("Par: %d\n", b);
    else
        printf("Impar: %d\n", b);

    printf("Maior: %d\n", maior(a, b));

    printf("Potencia: %d\n", potencia(2, 10));

    printf("Fatorial: %d\n", fatorial(a));

    printf("Fatorial Recursivo: %d\n", fatorial_rec(a));

    return 0;
}

/* ============================================================
   EXERCICIO 1 - Soma de dois numeros
   ============================================================ */

int soma(int x, int y) {
    /* Soma simples de dois parametros recebidos por valor */
    return x + y;
}

/* ============================================================
   EXERCICIO 2 - Verificar numero par
   ============================================================ */

int eh_par(int n) {
    /* Um numero e par quando o resto da divisao por 2 e zero */
    if (n % 2 == 0)
        return 1;
    return 0;
}

/* ============================================================
   EXERCICIO 3 - Maior de dois numeros
   ============================================================ */

int maior(int a, int b) {
    if (a > b)
        return a;
    return b;
}

/* ============================================================
   EXERCICIO 4 - Potencia
   ============================================================ */

int potencia(int base, int expoente) {
    /* Multiplica "base" por si mesma "expoente" vezes, sem usar pow() */
    int i, result = 1;
    for (i = 0; i < expoente; i++)
        result *= base;
    return result;
}

/* ============================================================
   EXERCICIO 5 - Fatorial (versao iterativa)
   ============================================================ */

int fatorial(int n) {
    int i, result = 1;
    for (i = n; i > 0; i--)
        result *= i;
    return result;
}

/* ============================================================
   EXERCICIO 6 - Fatorial (versao recursiva)
   ============================================================ */

int fatorial_rec(int n) {
    /* Caso base: 0! e 1! valem 1 */
    if (n == 0 || n == 1)
        return 1;
    /* Caso recursivo: n! = n * (n-1)! */
    return n * fatorial_rec(n - 1);
}