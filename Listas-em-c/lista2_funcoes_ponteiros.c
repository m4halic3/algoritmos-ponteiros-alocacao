/*
 * Lista de Exercícios – Chamada por referência
 * Tema: Chamada por valor, por referência (ponteiros) e vetores
 * Autora: Profa. Tiemi Christine Sakata (enunciado adaptado)
 * 
 * Instruções para estudantes:
 *  - Cada exercício possui uma função (ou mais) com corpo TODO.
 *  - Substitua os trechos TODO pelo seu código.
 *  - Mantenha as assinaturas (tipos e nomes dos parâmetros).
 *  - Faça a chamada das funções no main
 *  - O arquivo compila como está (retornos padrão), mas não resolve nada.
 *  - Use o bloco de testes no final (opcional) para validar suas soluções.
 */

#include <stdio.h>
#include <stdlib.h>

/* 1) Incrementa o valor de x */
void inc(int x);

/* 2) Troca o valor de x por y */
void troca_invalida(int x, int y);

/* 3) (Conceitual) — justificar por que não é possível trocar sem ponteiros. */

/* 4) Troca que FUNCIONA (swap por referência) */
void troca_ref(int *x, int *y);

// 24/08
/* 5) Incremento por referência */
void inc_ref(int *p);

// 24/08
/* 6) Troca condicional: troca apenas se *a > *b; retorna 1 se trocou, 0 caso contrário */
int troca_se_maior(int *a, int *b);

/* 7) Normalização de três valores: subtrai a média de cada um */
void normaliza_trio(float *x, float *y, float *z);

// 24/08
/* 8) Zera vetor */
void zera(int *v, int n);

/* 9) Soma e média (sem alterar o vetor) */
int soma(const int *v, int n);

float media_int(const int *v, int n);

/* 10) Escala in-place: v[i] *= k */
void escala(float *v, int n, float k);

// 24/08
/* 11) Troca de extremos: v[0] <-> v[n-1] */
void troca_extremos(int *v, int n);

/* 12) Filtragem por faixa em outro vetor; retorna quantidade copiada */
int filtra_faixa(const float *origem, int n, float *destino, float L, float U);

/* 13) Índice do mínimo (primeira ocorrência) */
int indice_min(const float *v, int n);
int indice_max(const float *v, int n);

/* 14) Remover a primeira ocorrência e deslocar; atualiza *n */
void remove_primeiro(int *v, int *n, int alvo);

/* 15) Inversão in-place */
void inverte(int *v, int n);

static void print_int(const int *v, int n){ for(int i=0;i<n;++i) printf("%d%s", v[i], (i==n-1)?"\n":" "); }
static void print_float(const float *v, int n){ for(int i=0;i<n;++i) printf("%.2f%s", v[i], (i==n-1)?"\n":" "); }

int main(void) {
    int a = 10, b = 7;
    int v1[5] = {1,2,3,4,5};
    float d1[5] = {1,-2,3,4.5,0};
    int v2[5] = {1,2,3,4,5};
    float o[5] = {1,10,5,20,7};
    float dest[5];
    float num1 = 8.0, num2 = 5.0, num3 = 5.0;

    // TODO 24/08
    // Altere a declaracao de vetores por ponteiros com alocacao dinamica


    // TODO: chamada da funcao inc passando a como parametro
    printf("[1] a=%d (esperado 10)\n", a);
   
    // TODO: chamada de troca_invalida
    printf("[2] a=%d b=%d (esperado 10,7)\n", a, b);

    // TODO: chamada de troca_ref
    printf("[4] swap ref: a=%d b=%d\n", a, b);

    // TODO: chamada de inc_ref
    printf("[5] inc_ref: a=%d\n", a);

    // TODO: chamada de troca_se_maior passando a e b nessa ordem
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    // TODO: chamada de troca_se_maior passando b e a nessa ordem
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    // TODO: chamada da funcao normaliza trio para num1, num2, num3
    printf("[7] apos normalizar: num1=%.2lf num2=%.2lf num3=%.2lf\n", num1, num2, num3);

    //TODO: chamada da funcao para zerar v1
    printf("[8] zerando um vetor\n"); 
    print_int(v1,5);

    // TODO: chamada das funcoes soma e media_int de v2
    print_int(v2,5);
    //printf("[9] Soma: %d, Media: %.2lf\n", /*chamar as funcoes aqui*/); 

    print_float(d1,5);
    // TODO: chamada a funcao escala fazendo com que triplique o valor de d1
    printf("[10]: triplica vetor: ");
    print_float(d1,5);

    printf("[11]: Troca primeiro pelo ultimo: ");
    // TODO: chamada da funcao troca_extremos para v2
    print_int(v2,5);

    // filtra todos os elementos entre 5 e 15 do vetor o
    int k = filtra_faixa(o,5,dest,5,15); 
    printf("[12] numero de 5 a 15: k=%d: ", k); 
    print_float(dest,k);
 
    print_float(o,5);
    // armazena em min e max o indice do menor e do maior elemento do vetor o
    int min, max;
    // TODO: chamada da funcao indice_min e indice_max
    printf("[13] ind_min=%d, ind_max=%d: \n", min, max); 

    print_int(v2,5);
    printf("[14]: apos remover valor 2 de v2: ");
    int n = 5;
    // TODO: chamada da funcao remove_primeiro de v2
    print_int(v2,n);

    printf("[15]: apos inverter v2: ");
    // TODO: chamada da funcao inverte de v2
    print_int(v2,4);

    return 0;
}

/* =============================================================
   PARTE A — Chamada por VALOR
   ============================================================= */

/* 1) Preveja a saída — cópia não altera o original */
void inc(int x) {
    /* TODO: incrementar x (a cópia). Explique depois por que não altera o original. */
}

/* 2) Troca que NÃO troca (por valor) */
void troca_invalida(int x, int y) {
    /* TODO: tente trocar x e y (cópias). Observe no main que não afeta a e b. */
}

/* 3) (Conceitual) — justificar por que não é possível trocar sem ponteiros. */
/* Sem código obrigatório. */

/* =============================================================
   PARTE B — Simulando chamada por REFERÊNCIA (ponteiros)
   ============================================================= */

/* 4) Troca que FUNCIONA (swap por referência) */
void troca_ref(int *x, int *y) {
    /* TODO: implemente swap usando um temporário e *x / *y */
}

/* 5) Incremento por referência */
void inc_ref(int *p) {
    /* TODO: incremente o conteúdo apontado por p */
    if (!p) return;
}

/* 6) Troca condicional: troca apenas se *a > *b; retorna 1 se trocou, 0 caso contrário */
int troca_se_maior(int *a, int *b) {
    /* TODO: implemente a lógica condicional com ponteiros */
    if (!a || !b) return 0;
    return 0;
}

/* 7) Normalização de três valores: subtrai a média de cada um */
void normaliza_trio(float *x, float *y, float *z) {
    /* TODO: calcule m=(x+y+z)/3 e subtraia de cada */
    if (!x || !y || !z) return;
}

/* =============================================================
   PARTE C — VETORES (passagem por referência automática)
   ============================================================= */

/* 8) Zera vetor */
void zera(int *v, int n) {
    /* TODO: colocar zero em todas as posições de v[0..n-1] */
}

/* 9) Soma e média (sem alterar o vetor) */
int soma(const int *v, int n) {
    /* TODO: acumular e retornar a soma */
    return 0;
}

float media_int(const int *v, int n) {
    /* TODO: retornar soma/(float)n; trate n<=0 conforme orientação do professor(a) */
    return 0;
}

/* 10) Escala in-place: v[i] *= k */
void escala(float *v, int n, float k) {
    /* TODO */
}

/* 11) Troca de extremos: v[0] <-> v[n-1] */
void troca_extremos(int *v, int n) {
    /* TODO */

}

/* 12) Filtragem por faixa em outro vetor; retorna quantidade copiada */
int filtra_faixa(const float *origem, int n, float *destino, float L, float U) {
    /* TODO: copiar mantendo a ordem se L <= origem[i] <= U */
    return 0;
}

/* 13) Índice do mínimo e do máximo (primeira ocorrência) */
int indice_min(const float *v, int n) {
    /* TODO */
    return 0;
}

int indice_max(const float *v, int n) {
    /* TODO */
    return 0;
}

/* 14) Remover a primeira ocorrência e deslocar; atualiza *n */
void remove_primeiro(int *v, int *n, int alvo) {
    /* TODO: encontrar índice, deslocar à esquerda, decrementar *n */
}

/* 15) Inversão in-place */
void inverte(int *v, int n) {
    /* TODO: use dois índices i (início) e j (fim) */
}


