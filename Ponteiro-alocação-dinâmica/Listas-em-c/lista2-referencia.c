/*
 * Exemplos de Implementação - Ponteiros e Vetores em C
 * Disciplina: Estrutura de Dados
 *
 * Objetivo:
 *  Servir como material de apoio com exemplos comentados sobre a
 *  diferenca entre passagem de parametros por valor e por referencia
 *  (ponteiros), alem de manipulacao de vetores.
 *
 * Arquivo: lista2-referencia.c
 */

#include <stdio.h>
/* Biblioteca padrao de entrada/saida: fornece printf */
#include <stdlib.h>
/* Biblioteca padrao geral: fornece malloc() e free(), usadas para
   alocacao dinamica de memoria */

/* --- Prototipos das funcoes --- */
void inc(int x);
/* recebe um int por valor; nao retorna nada (void) */
void troca_invalida(int x, int y);
/* recebe dois int por valor; tenta trocar mas nao consegue */
void troca_ref(int *x, int *y);
/* recebe dois ENDERECOS de int (ponteiros); consegue trocar de verdade */
void inc_ref(int *p);
/* recebe o endereco de um int; consegue incrementar o valor original */
int troca_se_maior(int *a, int *b);
/* recebe dois ponteiros; retorna 1 se trocou, 0 se nao */
void normaliza_trio(float *x, float *y, float *z);
/* recebe tres ponteiros para float; subtrai a media de cada valor */
void zera(int *v, int n);
/* recebe um vetor (ponteiro para o primeiro elemento) e seu tamanho */
int soma(const int *v, int n);
/* "const" indica que a funcao promete nao alterar o vetor recebido */
float media_int(const int *v, int n);
void escala(float *v, int n, float k);
void troca_extremos(int *v, int n);
int filtra_faixa(const float *origem, int n, float *destino, float L, float U);
int indice_min(const float *v, int n);
int indice_max(const float *v, int n);
void remove_primeiro(int *v, int *n, int alvo);
/* "n" aqui e um ponteiro para int, pois a funcao precisa ALTERAR o
   tamanho logico do vetor no chamador (nao so ler) */
void inverte(int *v, int n);

/* Funcoes auxiliares para imprimir vetores, evitando repetir o
   mesmo laco de impressao em varios lugares do codigo */
static void print_int(const int *v, int n){
    /* "static" limita a visibilidade da funcao a este arquivo */
    for(int i=0;i<n;++i)
        /* percorre cada indice de 0 ate n-1 */
        printf("%d%s", v[i], (i==n-1)?"\n":" ");
        /* imprime o valor; se for o ultimo elemento imprime quebra de
           linha, senao imprime um espaco (operador ternario condicao?a:b) */
}
static void print_float(const float *v, int n){
    for(int i=0;i<n;++i)
        printf("%.2f%s", v[i], (i==n-1)?"\n":" ");
        /* %.2f formata o float com 2 casas decimais */
}

int main(void) {
    int *p;
    /* ponteiro auxiliar, usado para percorrer o vetor v1 abaixo */
    int a = 10, b = 7;
    /* variaveis simples que vao demonstrar valor x referencia */
    float d1[5] = {1,-2,3,4.5,0};
    /* vetor de float com 5 posicoes ja inicializadas */
    int v2[5] = {1,2,3,4,5};
    /* vetor de int usado nos exemplos de manipulacao */
    float o[5] = {1,10,5,20,7};
    /* vetor "origem" usado no exemplo de filtragem */
    float dest[5];
    /* vetor "destino" que vai receber os valores filtrados de "o" */
    float num1 = 8.0, num2 = 5.0, num3 = 5.0;
    /* tres valores que serao normalizados (media subtraida de cada um) */

    /* Alocacao dinamica: v1 nao e um vetor fixo declarado como int v1[5],
       e sim um bloco de memoria reservado em tempo de execucao. */
    int *v1 = (int *) malloc(5 * sizeof(int));
    /* malloc reserva espaco para 5 inteiros e retorna o endereco do
       primeiro byte livre; o cast (int *) converte o retorno generico
       de malloc para ponteiro de int */
    if (v1 == NULL)
        /* malloc retorna NULL se nao conseguir alocar memoria */
        return 1;
        /* encerra o programa com codigo de erro se a alocacao falhar */

    *v1 = 1;
    /* *v1 acessa o valor apontado por v1 (primeiro elemento do vetor);
       equivale a v1[0] = 1 */
    for (p = v1 + 1; p < v1 + 5; p++)
        /* p comeca apontando para o segundo elemento (v1 + 1);
           o laco continua enquanto p nao ultrapassar o quinto
           elemento (v1 + 5); a cada volta p avanca uma posicao (p++) */
        *p = *(p - 1) + 1;
        /* preenche cada posicao com o valor da posicao anterior + 1,
           gerando a sequencia 1, 2, 3, 4, 5 */

    /* --- Demonstracao 1: chamada por VALOR --- */
    inc(a);
    /* passa uma copia de a; a funcao altera so a copia local */
    printf("[1] a=%d (esperado 10)\n", a);
    /* a continua 10 no main, provando que a copia interna nao afeta o original */

    /* --- Demonstracao 2: troca por VALOR (nao funciona) --- */
    troca_invalida(a, b);
    /* passa copias de a e b; a "troca" so acontece dentro da funcao */
    printf("[2] a=%d b=%d (esperado 10,7)\n", a, b);
    /* a e b continuam com os valores originais */

    /* --- Demonstracao 3: troca por REFERENCIA (funciona) --- */
    troca_ref(&a, &b);
    /* &a e &b sao os ENDERECOS de a e b; a funcao recebe ponteiros e
       consegue alterar as variaveis originais */
    printf("[4] swap ref: a=%d b=%d\n", a, b);
    /* agora a e b realmente trocaram de valor */

    inc_ref(&a);
    /* mesma ideia: passa o endereco de a para que a funcao possa
       incrementar o valor original */
    printf("[5] inc_ref: a=%d\n", a);

    troca_se_maior(&a, &b);
    /* passa os enderecos; a funcao so troca se *a for maior que *b */
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    troca_se_maior(&b, &a);
    /* chama de novo invertendo a ordem dos argumentos, para testar a
       condicao no outro sentido */
    printf("[6] a > b?: a=%d b=%d\n", a, b);

    normaliza_trio(&num1, &num2, &num3);
    /* passa os enderecos dos tres floats para que a funcao subtraia a
       media de cada um diretamente nas variaveis originais */
    printf("[7] apos normalizar: num1=%.2f num2=%.2f num3=%.2f\n", num1, num2, num3);

    /* --- Demonstracao com VETORES: em C, o nome do vetor ja e um
       ponteiro para seu primeiro elemento, entao vetores sao passados
       por referencia automaticamente, sem precisar do operador & --- */
    print_int(v1, 5);
    /* mostra v1 antes de zerar */
    zera(v1, 5);
    /* zera todas as posicoes de v1 */
    printf("[8] zerando um vetor\n");
    print_int(v1, 5);
    /* mostra v1 depois, todos os valores agora sao 0 */

    print_int(v2, 5);
    printf("[9] Soma: %d, Media: %.2f\n", soma(v2, 5), media_int(v2, 5));
    /* soma e media_int recebem "const int *", ou seja, apenas leem v2
       sem modifica-lo */

    print_float(d1, 5);
    escala(d1, 5, 3.0f);
    /* multiplica cada elemento de d1 por 3, alterando o vetor original */
    printf("[10]: triplica vetor: ");
    print_float(d1, 5);

    printf("[11]: Troca primeiro pelo ultimo: ");
    troca_extremos(v2, 5);
    /* troca v2[0] com v2[4] */
    print_int(v2, 5);

    int k = filtra_faixa(o, 5, dest, 5, 15);
    /* copia para "dest" os valores de "o" que estao entre 5 e 15;
       k recebe a quantidade de valores copiados */
    printf("[12] numero de 5 a 15: k=%d: ", k);
    print_float(dest, k);
    /* imprime apenas as k posicoes que foram de fato preenchidas */

    print_float(o, 5);
    int min, max;
    /* variaveis que vao guardar os INDICES do menor e do maior valor */
    min = indice_min(o, 5);
    max = indice_max(o, 5);
    printf("[13] ind_min=%d, ind_max=%d: \n", min, max);

    print_int(v2, 5);
    printf("[14]: apos remover valor 2 de v2: ");
    int n = 5;
    /* n guarda o tamanho logico atual de v2; sera atualizado pela funcao */
    remove_primeiro(v2, &n, 2);
    /* passa &n (endereco de n) porque a funcao precisa DIMINUIR esse
       valor apos remover um elemento */
    print_int(v2, n);
    /* imprime usando o novo tamanho (n agora vale 4) */

    printf("[15]: apos inverter v2: ");
    inverte(v2, n);
    /* inverte a ordem dos elementos validos de v2 */
    print_int(v2, n);

    free(v1);
    /* libera a memoria alocada com malloc; obrigatorio para evitar
       vazamento de memoria (memory leak) */
    v1 = NULL;
    /* boa pratica: zera o ponteiro apos liberar, evitando uso acidental
       de memoria ja liberada (ponteiro "pendurado") */
    return 0;
}

/* =============================================================
   PARTE A - Chamada por VALOR
   ============================================================= */

/* A funcao recebe uma copia de x. Alterar essa copia nao afeta a
   variavel original passada no main (por isso "a" continua 10). */
void inc(int x) {
    x = x + 1;
    /* incrementa apenas a copia local x; quando a funcao termina,
       essa copia e descartada e o valor original no main nao muda */
}

/* Mesmo raciocinio: x e y sao copias locais. A "troca" acontece
   apenas dentro da funcao e e perdida quando ela retorna. */
void troca_invalida(int x, int y) {
    int tmp = x;
    /* guarda temporariamente o valor de x */
    x = y;
    /* x recebe o valor de y */
    y = tmp;
    /* y recebe o valor original de x, guardado em tmp */
    /* a troca aconteceu, mas so entre as copias locais x e y */
}

/* =============================================================
   PARTE B - Simulando chamada por REFERENCIA (ponteiros)
   ============================================================= */

/* x e y aqui sao ENDERECOS (ponteiros), entao *x e *y acessam
   diretamente as variaveis originais do chamador. */
void troca_ref(int *x, int *y) {
    int tmp = *x;
    /* *x le o valor guardado no endereco apontado por x */
    *x = *y;
    /* escreve no endereco de x o valor que estava no endereco de y */
    *y = tmp;
    /* escreve no endereco de y o valor original de x, guardado em tmp */
}

/* Incrementa o conteudo apontado por p */
void inc_ref(int *p) {
    if (!p) return;
    /* verifica se p e um ponteiro nulo antes de usa-lo, evitando
       um erro grave (acessar memoria invalida) */
    *p = *p + 1;
    /* le o valor apontado, soma 1 e grava de volta no mesmo endereco */
}

/* So troca se *a for maior que *b; informa se houve troca */
int troca_se_maior(int *a, int *b) {
    if (!a || !b) return 0;
    /* se qualquer um dos ponteiros for nulo, nao ha o que fazer */
    if (*a > *b) {
        /* compara os valores apontados, nao os enderecos em si */
        int tmp = *a;
        *a = *b;
        *b = tmp;
        /* mesmo padrao de troca visto em troca_ref */
        return 1;
        /* informa ao chamador que a troca aconteceu */
    }
    return 0;
    /* nenhuma troca foi necessaria */
}

/* Calcula a media dos tres valores e subtrai de cada um */
void normaliza_trio(float *x, float *y, float *z) {
    if (!x || !y || !z) return;
    /* protege contra ponteiros nulos */
    float m = (*x + *y + *z) / 3.0f;
    /* soma os tres valores apontados e divide por 3 para obter a media */
    *x -= m;
    /* subtrai a media do valor apontado por x (equivale a *x = *x - m) */
    *y -= m;
    *z -= m;
}

/* =============================================================
   PARTE C - VETORES (passagem por referencia automatica)
   ============================================================= */

/* Zera todas as posicoes de v[0..n-1] usando aritmetica de ponteiros */
void zera(int *v, int n) {
    int *fim = v + n;
    /* calcula o endereco logo apos o ultimo elemento valido do vetor */
    for (; v < fim; v++)
        /* percorre do inicio ate "fim", avancando v uma posicao por vez */
        *v = 0;
        /* zera o valor apontado pela posicao atual */
}

/* Soma dos elementos, sem alterar o vetor original (por isso "const") */
int soma(const int *v, int n) {
    int i, s = 0;
    /* s acumula o total, comecando em 0 */
    for (i = 0; i < n; i++)
        /* percorre todos os indices validos do vetor */
        s += v[i];
        /* soma o valor atual ao acumulador */
    return s;
}

float media_int(const int *v, int n) {
    if (n <= 0) return 0.0f;
    /* evita divisao por zero (ou por numero negativo, que nao faz sentido) */
    return soma(v, n) / (float) n;
    /* reaproveita a funcao soma() ja implementada; o cast (float)
       garante uma divisao com casas decimais, e nao divisao inteira */
}

/* Multiplica cada elemento por k, alterando o vetor in-place */
void escala(float *v, int n, float k) {
    int i;
    for (i = 0; i < n; i++)
        v[i] *= k;
        /* equivale a v[i] = v[i] * k; altera o vetor original,
           por isso o parametro nao e "const" */
}

/* Troca v[0] com v[n-1] */
void troca_extremos(int *v, int n) {
    if (n < 2) return;
    /* com menos de 2 elementos nao ha o que trocar */
    int tmp = v[0];
    v[0] = v[n - 1];
    v[n - 1] = tmp;
    /* mesmo padrao de swap ja usado antes, agora aplicado a posicoes
       do vetor em vez de variaveis soltas */
}

/* Copia para "destino" os elementos de "origem" que estao entre L e U,
   mantendo a ordem original. Retorna quantos foram copiados. */
int filtra_faixa(const float *origem, int n, float *destino, float L, float U) {
    int i, k = 0;
    /* k conta e tambem serve de indice para preencher "destino" */
    for (i = 0; i < n; i++) {
        if (origem[i] >= L && origem[i] <= U) {
            /* testa se o elemento atual esta dentro do intervalo [L, U] */
            destino[k] = origem[i];
            /* copia o valor para a proxima posicao livre de destino */
            k++;
            /* avanca o indice/contador */
        }
    }
    return k;
    /* informa quantos elementos foram efetivamente copiados */
}

/* Indice da primeira ocorrencia do menor valor */
int indice_min(const float *v, int n) {
    int i, idx = 0;
    /* assume inicialmente que o menor esta na posicao 0 */
    for (i = 1; i < n; i++)
        /* comeca em 1 porque a posicao 0 ja foi considerada */
        if (v[i] < v[idx])
            /* se o elemento atual for menor que o menor ja encontrado */
            idx = i;
            /* atualiza o indice do menor valor */
    return idx;
}

/* Indice da primeira ocorrencia do maior valor */
int indice_max(const float *v, int n) {
    int i, idx = 0;
    for (i = 1; i < n; i++)
        if (v[i] > v[idx])
            /* mesma logica do indice_min, invertendo a comparacao */
            idx = i;
    return idx;
}

/* Remove a primeira ocorrencia de "alvo", deslocando os elementos
   seguintes uma posicao para a esquerda e diminuindo *n */
void remove_primeiro(int *v, int *n, int alvo) {
    int i, idx = -1;
    /* idx = -1 sera usado como sinal de "nao encontrado ainda" */
    for (i = 0; i < *n; i++) {
        /* *n le o valor apontado por n, ou seja, o tamanho atual do vetor */
        if (v[i] == alvo) {
            idx = i;
            /* guarda a posicao onde o alvo foi encontrado */
            break;
            /* interrompe o laco assim que encontra a primeira ocorrencia */
        }
    }
    if (idx == -1) return;
    /* se o alvo nao existe no vetor, nao ha nada a fazer */

    for (i = idx; i < *n - 1; i++)
        /* a partir da posicao encontrada, desloca cada elemento uma
           posicao para a esquerda, sobrescrevendo o valor removido */
        v[i] = v[i + 1];

    (*n)--;
    /* diminui em 1 o valor apontado por n, atualizando o tamanho
       logico do vetor no main (por isso n precisou ser um ponteiro) */
}

/* Inverte o vetor in-place usando dois indices que se encontram no meio */
void inverte(int *v, int n) {
    int i = 0, j = n - 1;
    /* i comeca no inicio do vetor, j comeca no fim */
    while (i < j) {
        /* continua enquanto os dois indices nao se cruzarem */
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        /* troca os elementos das posicoes i e j */
        i++;
        /* i avanca em direcao ao centro */
        j--;
        /* j retrocede em direcao ao centro */
    }
}