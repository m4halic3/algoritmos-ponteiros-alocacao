* TOC
{:toc}
Guia didático e prático para quem trava tentando entender como uma função recebe e devolve valores, por que uma variável não muda dentro dela, qual a diferença entre `&x` e `*p`, ou como mexer em vetores sem usar colchetes.

O guia segue a ordem em que esses temas fazem mais sentido pra aprender: primeiro funções puras (parâmetro, retorno, recursão, sem ponteiro nenhum), depois ponteiros e tudo que se apoia neles. A partir da seção de ponteiros, o conteúdo segue **uma única analogia** do início ao fim: endereços e cartas. A ideia é que, uma vez que essa analogia fizer sentido, todo o resto (vetores, alocação dinâmica) vira só uma aplicação repetida da mesma ideia.

## Estrutura do repositório

```
lista1-funcoes.c       # exemplos de funções: parâmetro, retorno e recursão
lista2-referencia.c    # exemplos de ponteiros, chamada por referência e vetores
README.md              # este guia, explicando o raciocínio por trás de cada exemplo
```

Os trechos de código comentados ao longo deste README são extraídos e adaptados de `lista1-funcoes.c` e `lista2-referencia.c`. Os dois arquivos já vêm com a implementação completa e comentada linha a linha, servindo como material de apoio pronto para consulta. Eles servem também como **base de estudo ativo**: a leitura explica o porquê de cada linha, mas o aprendizado fica mais sólido rodando, alterando e testando os arquivos originais no seu compilador (GCC, VS Code, Dev-C++, o que preferir). Sempre que possível, compile o exemplo, quebre o código de propósito e observe o que muda, essa é a forma mais rápida de internalizar o conteúdo.

## Sumário

1. [Funções: a base antes dos ponteiros](#1-funções-a-base-antes-dos-ponteiros)
2. [O que é um ponteiro](#2-o-que-é-um-ponteiro)
3. [Declarando e usando ponteiros](#3-declarando-e-usando-ponteiros)
4. [Ponteiros e vetores](#4-ponteiros-e-vetores)
5. [Chamada por valor x chamada por referência](#5-chamada-por-valor-x-chamada-por-referência)
6. [Vetores como referência automática](#6-vetores-como-referência-automática)
7. [Alocação dinâmica de memória](#7-alocação-dinâmica-de-memória)
8. [Matrizes dinâmicas](#8-matrizes-dinâmicas)
9. [Checklist de erros comuns](#9-checklist-de-erros-comuns)
10. [Perguntas de fixação](#10-perguntas-de-fixação)

---

## 1. Funções: a base antes dos ponteiros

> Código-base para praticar: `lista1-funcoes.c`. O arquivo não usa ponteiro nem struct de propósito, o foco aqui é só entender função, parâmetro e retorno.

Antes de qualquer ponteiro, vale consolidar o que é uma função em C: um bloco de código que recebe valores de entrada (parâmetros), faz algo com eles, e devolve um resultado (`return`).

### Declaração, definição e chamada

```c
int soma(int x, int y); // declaração (protótipo): avisa ao compilador que essa função existe
```

A declaração no topo do arquivo permite que o `main()` chame a função mesmo ela sendo definida (implementada de verdade) só mais abaixo no arquivo.

```c
int soma(int x, int y) {
    return x + y; // definição: aqui está o corpo de verdade da função
}
```

```c
int r = soma(a, b); // chamada: executa a função com a e b como argumentos
```

Repare que os nomes dos parâmetros na declaração (`x`, `y`) não precisam ser os mesmos usados na chamada (`a`, `b`). Os valores de `a` e `b` são copiados para dentro de `x` e `y` no momento da chamada, e `x`/`y` só existem enquanto a função está rodando.

### Exemplo completo comentado

```c
int soma(int x, int y) {
    return x + y;
    // recebe x e y, devolve a soma direto no return, sem variável intermediária
}

int eh_par(int n) {
    if (n % 2 == 0)
        return 1;  // 1 representa "verdadeiro" em C
    return 0;      // 0 representa "falso"
    // o resto da divisão por 2 (%) é zero apenas quando o número é par
}

int maior(int a, int b) {
    if (a > b)
        return a;
    return b;
    // compara os dois parâmetros e devolve o maior deles
}

int potencia(int base, int expoente) {
    int i, result = 1;
    for (i = 0; i < expoente; i++)
        result *= base;
    return result;
    // result começa em 1 (elemento neutro da multiplicação)
    // e é multiplicado por "base" repetidamente, "expoente" vezes,
    // simulando base^expoente sem usar a função pow()
}

int fatorial(int n) {
    int i, result = 1;
    for (i = n; i > 0; i--)
        result *= i;
    return result;
    // i começa em n e desce até 1, multiplicando result a cada volta
    // fatorial(4) = 1 * 4 * 3 * 2 * 1 = 24
}
```

### Recursão: uma função que chama a si mesma

```c
int fatorial_rec(int n) {
    if (n == 0 || n == 1)
        return 1; // caso base: obrigatório, senão a função nunca para de se chamar
    return n * fatorial_rec(n - 1); // caso recursivo: quebra o problema em um menor
}
```

Rastreando `fatorial_rec(4)` chamada por chamada:

```
fatorial_rec(4) = 4 * fatorial_rec(3)
fatorial_rec(3) = 3 * fatorial_rec(2)
fatorial_rec(2) = 2 * fatorial_rec(1)
fatorial_rec(1) = 1                     <- caso base, para de chamar
```

E as multiplicações acontecem enquanto essas chamadas "voltam", na ordem inversa: `2 * 1 = 2`, depois `3 * 2 = 6`, depois `4 * 6 = 24`. O resultado final é o mesmo do `fatorial()` com laço, só que construído através da cadeia de chamadas em vez de um laço explícito.

### Chamando tudo no main

```c
int main(void) {
    int a = 4, b = 6, r;

    r = soma(a, b);
    printf("Soma: %d\n", r); // 10

    if (eh_par(b))
        printf("Par: %d\n", b); // executa, porque 6 é par

    printf("Maior: %d\n", maior(a, b)); // 6

    printf("Potencia: %d\n", potencia(2, 10)); // 1024

    printf("Fatorial: %d\n", fatorial(a)); // 24

    printf("Fatorial Recursivo: %d\n", fatorial_rec(a)); // 24

    return 0;
}
```

Esse exemplo, com as funções já implementadas, é a base pra tudo que vem a seguir: assim que ficar claro que `soma(a, b)` recebe cópias de `a` e `b` (e não os endereços deles), fica muito mais fácil entender por que às vezes isso é uma limitação, e é exatamente essa limitação que os ponteiros resolvem na próxima seção.

---

## 2. O que é um ponteiro

### A analogia: endereço e carta

Pensa na memória RAM como uma rua enorme, cheia de casas numeradas.

* Cada **casa** é um espaço de memória, com um **número** (o endereço).
* O que está **dentro da casa** é o valor guardado ali.
* Uma variável comum é a própria casa: você olha direto pra dentro dela e vê o valor.
* Um **ponteiro** não é uma casa. Ele é uma **carta com o endereço de uma casa escrito no envelope**. A carta não é a casa, ela só diz onde a casa fica.

```c
int x = 10;   // a casa "x" existe, com o valor 10 guardado dentro dela
int *p = &x;  // p é uma carta: no envelope está escrito "o endereço de x é tal"
```

A partir dessa ideia, os dois operadores centrais de ponteiros ganham nome e função:

| Operador | Nome | O que faz na analogia |
|---|---|---|
| `&` | operador de endereço | Escreve, no envelope, qual é o número da casa de uma variável |
| `*` | operador de indireção (desreferência) | Pega a carta, vai até o endereço escrito nela e mexe no que tem dentro da casa |

```c
printf("Valor: %d\n", x);            // acesso direto: olhar pra dentro da própria casa
printf("Endereco: %p\n", (void*)&x); // qual é o número da casa de x
```

### Declarando e usando

```c
int var = 10;
int *ptr = NULL;   // a carta ainda não tem nenhum endereço escrito nela
ptr = &var;         // agora a carta tem o endereço de var escrito nela
```

**Por que `= NULL` é obrigatório antes de apontar pra algo?**
Uma carta declarada e "largada" (`int *p;` sem inicializar) tem um endereço aleatório escrito nela, algo tipo "lixo" de memória. Se você seguir esse endereço com `*p`, pode acabar entrando numa casa que não é sua, e corromper dados de outra parte do programa, ou travar o programa inteiro. `NULL` é a forma de dizer "essa carta ainda não tem nenhum endereço válido escrito nela, com segurança".

### O operador de indireção na prática

```c
printf("%d", x);   // 10, acesso direto (olhando pra dentro da própria casa)
printf("%d", *p);  // 10, acesso indireto (seguindo a carta até a casa)

*p = 20; // não muda a carta em si, muda o CONTEÚDO da casa pra onde ela aponta
```

`*p = 20;` não troca o endereço escrito na carta, troca o que está dentro da casa apontada por ela. É a diferença entre reescrever o envelope com outro endereço e ir até a casa e reformar o que tem lá dentro.

### Um detalhe que costuma travar bastante

Um ponteiro também é uma variável. Logo, ele também mora em algum lugar da memória e também tem o seu próprio endereço:

```c
int x = 10;
int *p = &x;

printf("x = %d\n", x);
printf("*p = %d\n", *p);
printf("p = %p\n", (void*)p);    // endereço de x (o que está escrito na carta)
printf("&p = %p\n", (void*)&p);  // endereço da PRÓPRIA carta (ela também está guardada em algum lugar)

*p = 20;
printf("agora x = %d\n", x); // prova que x virou 20 através de p
```

É "carta que aponta pra um endereço, mas a carta em si também está guardada numa casa própria". Se esse ponto ficar confuso na primeira leitura, tudo bem, ele costuma clarear depois do próximo tópico.

---

## 3. Declarando e usando ponteiros

### Ponteiros nulos e endereços inválidos

```c
int *p;         // PERIGO: carta com um endereço aleatório escrito nela
int *p2 = NULL;  // seguro: carta explicitamente sem endereço nenhum ainda
```

Regra de ouro: todo ponteiro deveria nascer com `= NULL` até você ter certeza de qual endereço vai escrever nele.

### O tipo do ponteiro importa

O tipo do ponteiro (`int*`, `char*`, `float*`...) define o tamanho do "lote" de cada casa na rua. Isso importa porque, quando a carta "anda" pra frente (próximo tópico), ela precisa saber quantos metros pular pra chegar na próxima casa certa.

```c
int *pi;    // anda de 4 em 4 bytes (tamanho de int, na maioria dos sistemas)
char *pc;   // anda de 1 em 1 byte (tamanho de char)
```

---

## 4. Ponteiros e vetores

### A rua com casas numeradas em sequência

Um vetor é uma rua onde as casas são vizinhas e sequenciais. O nome do vetor já É o endereço da primeira casa, sem precisar escrever `&`:

```c
int lista[10];
// lista é equivalente a &lista[0]
```

Diferente de uma carta comum, o nome do vetor é uma espécie de "placa fixa da rua": ele aponta pra primeira casa, mas não pode ser movido (`lista++` não é permitido). Já um ponteiro separado que recebeu esse endereço pode navegar livremente:

```c
int *p_lista = lista; // agora p_lista é uma carta de verdade, pode andar
p_lista++;              // válido
// lista++;             // erro de compilação, lista não é uma carta, é a placa fixa da rua
```

### Por que `p++` não anda 1 byte

Se cada casa (elemento) ocupa um terreno de 4 metros (`sizeof(int) == 4`), andar "uma casa" significa andar 4 metros, não 1. O compilador sabe o tamanho do terreno pelo tipo declarado na carta:

```c
int i = 12;
int *p_i = &i;
p_i++; // pula 4 bytes (o tamanho de um int), não 1 byte
```

Essa é exatamente a lógica usada em `lista2-referencia.c` para preencher o vetor `v1` sem usar colchetes nenhuma vez:

```c
*v1 = 1;
for (p = v1 + 1; p < v1 + 5; p++)
    *p = *(p - 1) + 1;
// p começa na segunda casa da rua (v1 + 1) e anda até a quinta (v1 + 5),
// preenchendo cada casa com o valor da casa anterior mais 1
```

### A equivalência que costuma faltar

```c
int v[5];
int *pv = v;

for (int i = 0; i < 5; i++) scanf("%d", pv + i);        // sem usar v[i]!
for (int i = 0; i < 5; i++) printf("%d\n", *(pv + i));
```

`vetor[i]` é exatamente a mesma coisa que `*(vetor + i)`. Ler essa linha em voz alta ajuda: "vá na rua `vetor`, ande `i` casas, e abra a porta pra ver o que tem dentro".

---

## 5. Chamada por valor x chamada por referência

> Código-base para praticar: `lista2-referencia.c`. Os trechos abaixo são recortes desse arquivo.

Esse é o assunto mais cobrado em prova. A pergunta que resume tudo:

> Quando a função termina, a alteração que ela fez continua valendo lá fora, em quem chamou a função?

### Chamada por valor: entregar uma fotocópia

```c
void inc(int x) {
    x = x + 1; // só a CÓPIA local muda
}
```

Chamando `inc(a)` no `main`, o valor de `a` continua exatamente o mesmo depois. A função recebeu uma fotocópia da carta, rabiscou a cópia à vontade, mas o original nunca foi tocado.

```c
void troca_invalida(int x, int y) {
    int tmp = x;
    x = y;
    y = tmp; // troca as CÓPIAS de lugar, os originais continuam intactos
}
```

### Chamada por referência: entregar o endereço real

Pra função conseguir mexer no valor original, ela precisa receber o endereço da casa, não uma fotocópia do conteúdo:

```c
void troca_ref(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
```

Chamando no `main` com `troca_ref(&a, &b);`: `&a` é o endereço real da casa `a`, então a função vai até lá e troca o conteúdo de verdade.

```c
void inc_ref(int *p) {
    if (!p) return; // nunca siga uma carta sem endereço nenhum escrito nela
    *p = *p + 1;
}
```

```c
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
```

### Múltiplos retornos via referência

Em C, `return` só devolve um único valor. Passar por referência é a forma de abrir vários "canais de retorno" ao mesmo tempo:

```c
void normaliza_trio(float *x, float *y, float *z) {
    if (!x || !y || !z) return;
    float m = (*x + *y + *z) / 3.0f;
    *x -= m;
    *y -= m;
    *z -= m;
}
```

Nesse caso a função "retorna" três resultados de uma vez, um em cada casa apontada por `x`, `y` e `z`, coisa que um único `return` nunca conseguiria fazer sozinho.

---

## 6. Vetores como referência automática

> Continuação do mesmo arquivo (`lista2-referencia.c`), agora com funções que recebem vetores inteiros como parâmetro. Vale abrir o arquivo e testar cada função isoladamente antes de seguir pro próximo tópico.

Diferente de uma variável simples, um vetor já é passado por referência sem precisar de `&`, porque o nome do vetor já é um endereço:

```c
f(vetor) // é a mesma coisa que f(&vetor[0])
```

Pense nisso como "emprestar a rua inteira automaticamente": a função recebe o mapa da rua e pode alterar qualquer casa dela.

```c
/* Zera todas as posições do vetor */
void zera(int *v, int n) {
    int *fim = v + n;
    for (; v < fim; v++)
        *v = 0; // ou: v[i] = 0
}
```

```c
/* Soma sem alterar o vetor original */
int soma(const int *v, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s;
}

float media_int(const int *v, int n) {
    if (n <= 0) return 0.0f;
    return soma(v, n) / (float) n;
}
```

O `const int *v` é o "olhar, não tocar": a função pode ler a rua inteira, mas o compilador impede qualquer alteração nas casas.

```c
/* Multiplica cada posição por k, direto no vetor original */
void escala(float *v, int n, float k) {
    for (int i = 0; i < n; i++) v[i] *= k;
}

/* Troca o primeiro elemento com o último */
void troca_extremos(int *v, int n) {
    if (n < 2) return;
    int tmp = v[0];
    v[0] = v[n - 1];
    v[n - 1] = tmp;
}
```

```c
/* Copia pra outro vetor apenas os valores dentro de uma faixa [L, U] */
int filtra_faixa(const float *origem, int n, float *destino, float L, float U) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (origem[i] >= L && origem[i] <= U) {
            destino[k] = origem[i];
            k++;
        }
    }
    return k;
}

/* Índice da primeira ocorrência do menor valor */
int indice_min(const float *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++)
        if (v[i] < v[idx]) idx = i;
    return idx;
}
// indice_max segue a mesma lógica, trocando o sinal de comparação para >
```

```c
/* Remove a primeira ocorrência de um valor e desloca o restante */
void remove_primeiro(int *v, int *n, int alvo) {
    int idx = -1;
    for (int i = 0; i < *n; i++) {
        if (v[i] == alvo) { idx = i; break; }
    }
    if (idx == -1) return; // não encontrou o valor

    for (int i = idx; i < *n - 1; i++)
        v[i] = v[i + 1];

    (*n)--; // atualiza o tamanho lógico do vetor pra quem chamou a função
}
```

Aqui `n` também é passado como ponteiro (`int *n`), porque a função precisa alterar o tamanho lógico do vetor pra quem chamou, exatamente o mesmo raciocínio de "múltiplo retorno via referência" visto na seção anterior.

```c
/* Inverte o vetor no próprio lugar */
void inverte(int *v, int n) {
    int i = 0, j = n - 1;
    while (i < j) {
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        i++; j--;
    }
}
```

---

## 7. Alocação dinâmica de memória

> O trecho abaixo é o mesmo raciocínio usado em `lista2-referencia.c`, no ponto em que o vetor `v1` deixa de ser um vetor estático (`int v1[5]`) e passa a ser reservado em tempo de execução com `malloc`.

### Quando a rua ainda não existe

`int v1[5];` é uma rua já construída em tempo de compilação: o tamanho é decidido antes mesmo do programa rodar. O problema é quando esse tamanho só é conhecido durante a execução, por exemplo quando o usuário decide na hora quantos elementos quer.

Pra isso existe o Heap: uma área de memória que pode ser "encomendada" ao sistema operacional em tempo de execução, do tamanho exato que for preciso naquele momento.

```c
int *v1 = (int *) malloc(5 * sizeof(int));
if (v1 == NULL) return 1; // regra de ouro: sempre verifique se a encomenda deu certo

*v1 = 1;
for (int *p = v1 + 1; p < v1 + 5; p++)
    *p = *(p - 1) + 1;

/* ... uso normal do vetor ... */

free(v1);   // devolve o bloco pro sistema operacional
v1 = NULL;  // evita usar um endereço que já foi devolvido
```

Esse é o mesmo raciocínio de `int v1[5] = {1,2,3,4,5};`, só que construído em tempo de execução em vez de tempo de compilação.

### As quatro ferramentas

| Função | O que faz |
|---|---|
| `malloc(bytes)` | Reserva um bloco novo. O conteúdo inicial vem "sujo", com lixo de memória |
| `calloc(n, tam)` | Reserva um bloco novo e já zera todo o conteúdo |
| `realloc(ptr, novo_tam)` | Redimensiona (aumenta ou diminui) um bloco já existente |
| `free(ptr)` | Devolve o bloco pro sistema operacional |

```c
int n = 5;
int *v = (int*) malloc(n * sizeof(int));   // reserva espaço pra 5 ints
int *v2 = (int*) calloc(n, sizeof(int));    // reserva e já zera 5 ints
v = (int*) realloc(v, 10 * sizeof(int));   // redimensiona o bloco de v pra 10 ints
```

### Verificando falha na alocação

Às vezes não existe mais espaço disponível pra encomendar. Nesse caso, `malloc`/`calloc` retornam `NULL` em vez de um endereço válido:

```c
int *v = (int*) malloc(n * sizeof(int));

if (v == NULL) {
    printf("Erro: memoria insuficiente!\n");
    exit(1);
}
```

### A regra de ouro final

Tudo que nasceu com `malloc`/`calloc` precisa morrer com `free`. Esquecer isso é como continuar "alugando" um espaço que você não usa mais, gerando o que se chama de memory leak.

```c
free(v1);
v1 = NULL; // depois do free, o endereço continua escrito na carta,
           // mas a casa já foi demolida. usar *v1 aqui seria acessar
           // uma casa que não existe mais. NULL evita esse acidente.
```

---

## 8. Matrizes dinâmicas

Uma matriz é um vetor de vetores. Na mesma analogia, cada casa da rua principal não guarda um número, guarda o endereço de uma rua secundária inteira.

```c
int **matriz = (int**) malloc(linhas * sizeof(int*));
// matriz é o endereço de um vetor de ENDEREÇOS,
// cada posição vai guardar o endereço de uma linha da matriz

for (int i = 0; i < linhas; i++) {
    matriz[i] = (int*) malloc(colunas * sizeof(int));
    // pra cada linha, alocamos um vetor de verdade com "colunas" espaços
}
```

Depois disso, `matriz[i][j]` funciona normalmente, como se fosse uma matriz comum.

### Liberando a matriz: a ordem importa

Primeiro devolvem-se as ruas secundárias (cada linha), e só por último devolve-se a rua principal (o vetor de endereços). Se a ordem for invertida, a referência das linhas se perde antes de conseguir liberá-las:

```c
for (int i = 0; i < linhas; i++) {
    free(matriz[i]); // libera cada linha primeiro
}
free(matriz); // só depois libera o vetor de ponteiros
```

---

## 9. Checklist de erros comuns

* Esquecer o `free()` depois de um `malloc`/`calloc`/`realloc` (memory leak)
* Usar um ponteiro sem inicializar, sem `NULL` e sem apontar pra nada válido (comportamento indefinido, possível Segmentation Fault)
* Confundir o `*` da declaração com o `*` do uso:
  * `int *p;` aqui o `*` só indica que `p` é um ponteiro para int (declaração)
  * `*p = 20;` aqui o `*` significa "siga o endereço e mexa no valor" (desreferência)
* Errar a aritmética de ponteiros: `p + 1` anda `sizeof(tipo)` bytes, não 1 byte
* Trocar passagem por valor com passagem por referência: se a função precisa alterar o original, ela precisa receber um endereço (`&variavel`)
* Inverter a ordem ao liberar uma matriz dinâmica: sempre libera as linhas primeiro, a matriz de ponteiros por último
* Usar um ponteiro depois do `free` sem colocar `NULL`, o que equivale a tentar entrar numa casa que já foi demolida

---

## 10. Perguntas de fixação

Tente responder cada uma sem consultar o material, e só depois confira com o texto acima:

1. Por que `soma(a, b)` não altera `a` e `b` originais, mesmo usando `return`?
2. Por que `fatorial_rec` precisa de um caso base (`n == 0 || n == 1`)?
3. Qual a diferença entre `p`, `&p` e `*p`?
4. Por que `troca_invalida(a, b)` não troca `a` e `b`, mas `troca_ref(&a, &b)` troca?
5. Por que `zera(v1, 5)` funciona sem precisar de `&v1`?
6. O que `p++` faz de verdade quando `p` é `int*`?
7. Por que esquecer o `free()` é perigoso?
8. Numa matriz dinâmica, por que as linhas são liberadas antes da matriz principal?

---

Se esse material ajudar, fica à vontade pra abrir uma issue com dúvidas ou sugestões de melhoria. Contribuições que tragam mais exemplos comentados são bem-vindas.