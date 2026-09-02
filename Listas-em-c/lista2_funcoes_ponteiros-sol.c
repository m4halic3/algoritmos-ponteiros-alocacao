/*
 * Lista 2 - Chamada por valor, por referencia (ponteiros) e vetores
 * Disciplina: Estrutura de Dados
 *
 * Arquivo: lista2-referencia.c
 * Material de apoio - solucao comentada.
 */

#include <stdio.h>
#include <stdlib.h>

/* --- Declaracoes --- */
void inc(int x);
void troca_invalida(int x, int y);
void troca_ref(int *x, int *y);
void inc_ref(int *p);
int troca_se_maior(int *a, int *b);
void normaliza_trio(float *x, float *y, float *z);
void zera(int *v, int n);
int soma(const int *v, int n);
float media_int(const int *v, int n);
void escala(float *v, int n, float k);
void troca_extremos(int *v, int n);
int filtra_faixa(const float *origem, int n, float *destino, float L, float U);
int indice_min(const float *v, int n);
int indice_max(const float *v, int n);
void remove_primeiro(int *v, int *n, int alvo);
void inverte(int *v, int n);

static void print_int(const int *v, int n){ for(int i=0;i<n;++i) printf("%d%s", v[i], (i==n-1)?"\n":" "); }
static void print_float(const float *v, int n){ for(int i=0;i<n;++i) printf("%.2f%s", v[i], (i==n-1)?"\n":" "); }

int main(void) {
    int *p;
    int a = 10, b = 7;
    float d1[5] = {1,-2,3,4.5,0};
    int v2[5] = {1,2,3,4,5};
    float o[5] = {1,10,5,20,7};
    float dest[5];
    float num1 = 8.0, num2 = 5.0, num3 = 5.0;

    /* v1 alocado dinamicamente e preenchido com 1,2,3,4,5 usando aritmetica de ponteiros */
    int *v1 = (int *) malloc(5 * sizeof(int));
    if (v1 == NULL)
        return 1;
    *v1 = 1;
    for (p = v1 + 1; p < v1 + 5; p++)
        *p = *(p - 1) + 1;

    /* [1] Chamada por valor: inc recebe uma copia de "a", entao o original nao muda */
    inc(a);
    printf("[1] a=%d (esperado 10)\n", a);

    /* [2] Mesma ideia: troca_invalida recebe copias de a e b */
    troca_invalida(a, b);
    printf("[2] a=%d b=%d (esperado 10,7)\n", a, b);

    /* [4] Passando os enderecos de a e b, a funcao altera os originais */
    troca_ref(&a, &b);
    printf("[4] swap ref: a=%d b=%d\n", a, b);

    /* [5] Incremento por referencia */
    inc_ref(&a);
    printf("[5] inc_ref: a=%d\n", a);

    /* [6] Troca condicional: so troca se *a > *b */
    troca_se_maior(&a, &b);
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    troca_se_maior(&b, &a);
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    /* [7] Normalizacao: subtrai a media dos tres valores */
    normaliza_trio(&num1, &num2, &num3);
    printf("[7] apos normalizar: num1=%.2f num2=%.2f num3=%.2f\n", num1, num2, num3);

    /* [8] Zerando o vetor v1 (alocado dinamicamente) */
    print_int(v1, 5);
    zera(v1, 5);
    printf("[8] zerando um vetor\n");
    print_int(v1, 5);

    /* [9] Soma e media de v2, sem alterar o vetor */
    print_int(v2, 5);
    printf("[9] Soma: %d, Media: %.2f\n", soma(v2, 5), media_int(v2, 5));

    /* [10] Escala d1 in-place multiplicando por 3 */
    print_float(d1, 5);
    escala(d1, 5, 3.0f);
    printf("[10]: triplica vetor: ");
    print_float(d1, 5);

    /* [11] Troca o primeiro elemento com o ultimo */
    printf("[11]: Troca primeiro pelo ultimo: ");
    troca_extremos(v2, 5);
    print_int(v2, 5);

    /* [12] Filtra elementos de "o" entre 5 e 15, copiando para dest */
    int k = filtra_faixa(o, 5, dest, 5, 15);
    printf("[12] numero de 5 a 15: k=%d: ", k);
    print_float(dest, k);

    print_float(o, 5);
    /* [13] Indices do menor e do maior elemento de "o" */
    int min, max;
    min = indice_min(o, 5);
    max = indice_max(o, 5);
    printf("[13] ind_min=%d, ind_max=%d: \n", min, max);

    print_int(v2, 5);
    printf("[14]: apos remover valor 2 de v2: ");
    int n = 5;
    remove_primeiro(v2, &n, 2);
    print_int(v2, n);

    printf("[15]: apos inverter v2: ");
    inverte(v2, n);
    print_int(v2, n);

    free(v1);
    v1 = NULL;
    return 0;
}

/* =============================================================
   PARTE A - Chamada por VALOR
   ============================================================= */

/* 1) A funcao recebe uma copia de x. Alterar essa copia nao afeta a
      variavel original passada no main (por isso "a" continua 10). */
void inc(int x) {
    x = x + 1;
}

/* 2) Mesmo raciocinio: x e y sao copias locais. A "troca" acontece
      apenas dentro da funcao e e perdida quando ela retorna. */
void troca_invalida(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp;
}

/* 3) Sem ponteiros, a funcao so tem acesso as copias dos valores
      (passagem por valor). Para alterar as variaveis do chamador e
      necessario passar o endereco delas (ponteiro), permitindo que a
      funcao acesse e modifique o conteudo original via *ponteiro. */

/* =============================================================
   PARTE B - Simulando chamada por REFERENCIA (ponteiros)
   ============================================================= */

/* 4) Troca por referencia: x e y sao enderecos, entao *x e *y acessam
      diretamente as variaveis originais do chamador. */
void troca_ref(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/* 5) Incrementa o conteudo apontado por p */
void inc_ref(int *p) {
    if (!p) return;
    *p = *p + 1;
}

/* 6) So troca se *a for maior que *b; informa se houve troca */
int troca_se_maior(int *a, int *b) {
    if (!a || !b) return 0;
    if (*a > *b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
        return 1;
    }
    return 0;
}

/* 7) Calcula a media dos tres valores e subtrai de cada um */
void normaliza_trio(float *x, float *y, float *z) {
    if (!x || !y || !z) return;
    float m = (*x + *y + *z) / 3.0f;
    *x -= m;
    *y -= m;
    *z -= m;
}

/* =============================================================
   PARTE C - VETORES (passagem por referencia automatica)
   ============================================================= */

/* 8) Zera todas as posicoes de v[0..n-1] usando aritmetica de ponteiros */
void zera(int *v, int n) {
    int *fim = v + n;
    for (; v < fim; v++)
        *v = 0;
}

/* 9) Soma dos elementos, sem alterar o vetor original (por isso "const") */
int soma(const int *v, int n) {
    int i, s = 0;
    for (i = 0; i < n; i++)
        s += v[i];
    return s;
}

float media_int(const int *v, int n) {
    if (n <= 0) return 0.0f;
    return soma(v, n) / (float) n;
}

/* 10) Multiplica cada elemento por k, alterando o vetor in-place */
void escala(float *v, int n, float k) {
    int i;
    for (i = 0; i < n; i++)
        v[i] *= k;
}

/* 11) Troca v[0] com v[n-1] */
void troca_extremos(int *v, int n) {
    if (n < 2) return;
    int tmp = v[0];
    v[0] = v[n - 1];
    v[n - 1] = tmp;
}

/* 12) Copia para "destino" os elementos de "origem" que estao entre L e U,
       mantendo a ordem original. Retorna quantos foram copiados. */
int filtra_faixa(const float *origem, int n, float *destino, float L, float U) {
    int i, k = 0;
    for (i = 0; i < n; i++) {
        if (origem[i] >= L && origem[i] <= U) {
            destino[k] = origem[i];
            k++;
        }
    }
    return k;
}

/* 13) Indice da primeira ocorrencia do menor e do maior valor */
int indice_min(const float *v, int n) {
    int i, idx = 0;
    for (i = 1; i < n; i++)
        if (v[i] < v[idx])
            idx = i;
    return idx;
}

int indice_max(const float *v, int n) {
    int i, idx = 0;
    for (i = 1; i < n; i++)
        if (v[i] > v[idx])
            idx = i;
    return idx;
}

/* 14) Remove a primeira ocorrencia de "alvo", deslocando os elementos
       seguintes uma posicao para a esquerda e diminuindo *n */
void remove_primeiro(int *v, int *n, int alvo) {
    int i, idx = -1;
    for (i = 0; i < *n; i++) {
        if (v[i] == alvo) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return; /* nao encontrado */

    for (i = idx; i < *n - 1; i++)
        v[i] = v[i + 1];

    (*n)--;
}

/* 15) Inverte o vetor in-place usando dois indices que se encontram no meio */
void inverte(int *v, int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        i++;
        j--;
    }
}