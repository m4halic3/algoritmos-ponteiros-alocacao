/*
 * Exemplos de Implementação - Funções em C
 * Disciplina: Estrutura de Dados
 *
 * Objetivo:
 *  Servir como material de apoio com exemplos comentados de funções
 *  simples, mostrando declaração, implementação, passagem de
 *  parâmetros por valor e retorno de valores.
 *
 * Arquivo: lista1-funcoes.c
 */

#include <stdio.h>
/* Inclui a biblioteca de entrada/saida padrao do C, necessaria para usar printf */

/* --- Prototipos das funcoes ---
   Um prototipo avisa o compilador que a funcao existe, quantos parametros
   recebe e o tipo de cada um, e qual tipo ela retorna. Isso permite chamar
   a funcao no main() mesmo que o corpo dela so seja definido mais abaixo. */
int soma(int x, int y);          /* recebe dois int e retorna um int (a soma) */
int eh_par(int n);                /* recebe um int e retorna 1 (par) ou 0 (impar) */
int maior(int a, int b);          /* recebe dois int e retorna o maior deles */
int potencia(int base, int expoente); /* retorna base elevado a expoente */
int fatorial(int n);              /* retorna n! calculado de forma iterativa */
int fatorial_rec(int n);          /* retorna n! calculado de forma recursiva */

/* ============================================================
   PROGRAMA PRINCIPAL
   ============================================================ */

int main(void) {
    /* main() e o ponto de entrada do programa: a execucao sempre comeca aqui.
       "void" entre parenteses indica que main nao recebe argumentos. */

    int a = 4, b = 6, r;
    /* Declara tres variaveis inteiras: a e b ja iniciam com valores fixos
       (4 e 6), e r fica sem valor inicial, sera usada para guardar
       resultados calculados pelas funcoes. */

    r = soma(a, b);
    /* Chama a funcao soma passando a (4) e b (6) por VALOR, ou seja,
       a funcao recebe copias de a e b. O resultado retornado (10)
       e armazenado em r. */
    printf("Soma: %d\n", r);
    /* Imprime o texto "Soma: " seguido do valor inteiro de r e uma quebra
       de linha (\n). %d e o especificador de formato para inteiros. */

    if (eh_par(b))
        /* Chama eh_par passando b (6). A funcao retorna 1 (verdadeiro) ou
           0 (falso). O if avalia esse retorno: qualquer valor diferente
           de 0 e tratado como verdadeiro em C. */
        printf("Par: %d\n", b);
        /* Executado somente se eh_par(b) retornar 1 (b e par) */
    else
        printf("Impar: %d\n", b);
        /* Executado se eh_par(b) retornar 0 (b e impar) */

    printf("Maior: %d\n", maior(a, b));
    /* Chama maior(a, b) diretamente dentro do printf; o valor retornado
       e passado no lugar de %d sem precisar de uma variavel intermediaria */

    printf("Potencia: %d\n", potencia(2, 10));
    /* Calcula 2 elevado a 10 (2^10 = 1024) e imprime o resultado */

    printf("Fatorial: %d\n", fatorial(a));
    /* Calcula o fatorial de a (4! = 24) usando a versao iterativa */

    printf("Fatorial Recursivo: %d\n", fatorial_rec(a));
    /* Calcula o fatorial de a (4! = 24) usando a versao recursiva,
       para comparar as duas abordagens */

    return 0;
    /* Retorna 0 ao sistema operacional, convencao que indica que o
       programa terminou sem erros */
}

/* ============================================================
   EXEMPLO 1 - Soma de dois numeros
   ============================================================ */

int soma(int x, int y) {
    /* x e y sao PARAMETROS: copias locais dos valores passados na chamada.
       Alterar x ou y aqui dentro nao afeta as variaveis originais do main. */
    return x + y;
    /* Retorna o resultado da soma; a funcao termina assim que "return"
       e executado */
}

/* ============================================================
   EXEMPLO 2 - Verificar numero par
   ============================================================ */

int eh_par(int n) {
    /* Um numero e par quando o resto da divisao por 2 e zero */
    if (n % 2 == 0)
        /* O operador % (modulo) retorna o resto da divisao inteira.
           Se n dividido por 2 nao deixa resto, n e par. */
        return 1;
        /* 1 representa "verdadeiro" (par) */
    return 0;
    /* Se o if acima nao retornou, o numero e impar; retorna 0 (falso) */
}

/* ============================================================
   EXEMPLO 3 - Maior de dois numeros
   ============================================================ */

int maior(int a, int b) {
    if (a > b)
        /* Compara os dois parametros recebidos */
        return a;
        /* Se a for estritamente maior, retorna a */
    return b;
    /* Caso contrario (a <= b), retorna b. Cobre tanto o caso "b maior"
       quanto o caso "a e b iguais". */
}

/* ============================================================
   EXEMPLO 4 - Potencia
   ============================================================ */

int potencia(int base, int expoente) {
    /* Multiplica "base" por si mesma "expoente" vezes, sem usar pow() */
    int i, result = 1;
    /* i sera o contador do laco; result acumula o produto e comeca em 1,
       que e o elemento neutro da multiplicacao (base^0 = 1) */
    for (i = 0; i < expoente; i++)
        /* Repete "expoente" vezes: i comeca em 0, o laco continua
           enquanto i for menor que expoente, e i aumenta 1 a cada volta */
        result *= base;
        /* Equivale a "result = result * base": multiplica o acumulado
           pela base a cada iteracao */
    return result;
    /* Depois do laco, result contem base elevado a expoente */
}

/* ============================================================
   EXEMPLO 5 - Fatorial (versao iterativa)
   ============================================================ */

int fatorial(int n) {
    int i, result = 1;
    /* result comeca em 1 (0! e 1! valem 1) */
    for (i = n; i > 0; i--)
        /* i comeca em n e diminui a cada volta (i--), ate chegar a 0 */
        result *= i;
        /* Multiplica result por i em cada iteracao: acumula n * (n-1) * ... * 1 */
    return result;
    /* Retorna o fatorial acumulado */
}

/* ============================================================
   EXEMPLO 6 - Fatorial (versao recursiva)
   ============================================================ */

int fatorial_rec(int n) {
    /* Caso base: 0! e 1! valem 1.
       Toda funcao recursiva precisa de um caso base para nao chamar
       a si mesma infinitamente. */
    if (n == 0 || n == 1)
        return 1;
    /* Caso recursivo: n! = n * (n-1)!
       A funcao chama a si mesma com n-1, ate atingir o caso base. */
    return n * fatorial_rec(n - 1);
    /* Exemplo com n=4: 4 * fatorial_rec(3) -> 4 * (3 * fatorial_rec(2))
       -> 4 * (3 * (2 * fatorial_rec(1))) -> 4 * 3 * 2 * 1 = 24 */
}