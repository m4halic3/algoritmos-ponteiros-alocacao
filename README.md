# Aula: Ponteiros e Chamada por Referência em C
Repositório de estudos focado em desmistificar **Ponteiros**, **Chamada por Referência** e **Alocação Dinâmica** na linguagem C. 

Se você já travou tentando entender por que uma variável não muda dentro de uma função, qual a diferença entre `&x` e `*p`, ou como mexer em vetores sem usar colchetes, este material foi feito para você.

---

## Fundamentos: o que é um ponteiro

### **casa e endereço**

Fixe essa analogia porque ela sustenta a aula inteira:

- Uma **variável** é uma **casa**: um espaço físico na "rua" (a memória RAM), com um número de porta (o endereço).
- O **valor** guardado é o que tem **dentro** da casa (o morador).
- Um **ponteiro** não é a casa — é um **papel com o endereço** dessa casa escrito nele. Ele "aponta" para onde a casa fica, mas não é a casa.
- `&` (E comercial) = "qual é o **endereço** dessa casa?"
- `*` (asterisco) = "vá até o endereço e mexa no que tem **dentro**"

```c
int x = 10;      // a casa "x" existe, com o número 10 dentro
int *p = &x;     // p é um papelzinho: "o endereço de x é tal"
```

Mostre no quadro/terminal:
```c
printf("Valor: %d\n", x);          // acesso direto: o que tem dentro da casa
printf("Endereco: %p\n", (void*)&x); // qual é o endereço da casa
```

### Declarando e usando

```c
int var = 10;
int *ptr = NULL;   // ainda não aponta pra lugar nenhum (regra de ouro: nunca deixe "solto")
ptr = &var;        // agora ptr guarda o endereço de var
```

**Por que `= NULL` é obrigatório antes de apontar?** Porque um ponteiro declarado e "largado" (`int *p;` sem inicializar) aponta para um endereço de memória aleatório ("lixo"). Se você usar `*p` nesse estado, pode corromper dados de outra parte do programa ou travar. `NULL` é a forma de dizer "esse ponteiro não aponta pra lugar nenhum ainda, com segurança".

### O operador de indireção (`*`)

```c
printf("%d", x);    // 100 — acesso direto
printf("%d", *p_x); // 100 — acesso indireto (mesma coisa, caminho diferente)
```

`*p = 10;` não muda o ponteiro — muda **o que está no endereço apontado**. É a diferença entre trocar o papel com o endereço na sua mão e ir até a casa e reformar ela por dentro.

### Exercício de exemplo
**antes** de rodar:
```c
int x = 10;
int *p = &x;
printf("x = %d\n", x);
printf("*p = %d\n", *p);
printf("p = %p\n", (void*)p);   // endereço de x
printf("&p = %p\n", (void*)&p); // endereço do PRÓPRIO ponteiro (ele também mora em algum lugar!)

*p = 20;
printf("agora x = %d\n", x); // prova que x virou 20
```

**Ponto-chave que trava muitos alunos:** um ponteiro *também* é uma variável, então ele também tem um endereço (`&p`). É "papel que aponta pra endereço, mas o papel em si também está guardado em algum lugar". Use o slide "A Inception dos Ponteiros" pra reforçar isso.

---

## Ponteiro + vetor e aritmética

### Analogia: **a rua com casas numeradas**

Um vetor é uma rua onde as casas são vizinhas e sequenciais. O nome do vetor (`lista`) é um "ponteiro constante" — é a placa fixa da rua, aponta pra primeira casa e **não pode ser movida**.

```c
int lista[10];
lista == &lista[0]; // o nome do vetor JÁ é o endereço do primeiro elemento
```

### Por que `p++` não anda "1 byte"

Analogia: se cada casa (elemento) ocupa um terreno de 4 metros (`sizeof(int) = 4`), andar "uma casa" significa andar 4 metros, não 1. O compilador sabe o tamanho do "terreno" pelo tipo declarado:

```c
int i = 12;
int *p_i = &i;
p_i++;   // pula 4 bytes (o tamanho de um int), não 1 byte
```

### Ponteiro constante x ponteiro variável

- `mat` (nome do vetor) = ponteiro **constante**: fixo, não pode fazer `mat++`.
- `int *p_mat = mat;` = ponteiro **variável**: pode navegar livremente (`p_mat++`, `p_mat += 3`, etc).

### Exercício ao vivo (slide "Exercício 3" e "Exercício 4")
```c
int v[5]; 
int *pv = v;
for (int i = 0; i < 5; i++) scanf("%d", pv + i);       // sem usar v[i]!
for (int i = 0; i < 5; i++) printf("%d\n", *(pv + i));
```
Mostre a equivalência: `vetor[i]` é **exatamente** `*(vetor + i)`. Isso é o "clique" que costuma faltar.

---

## Chamada por valor x chamada por referência

Esse é o coração da lista de exercícios (`lista2_funcoes_ponteiros.c`). Use a analogia do slide da profa: **cópia do RG x GPS da casa real**.

- **Chamada por valor** (`void inc(int x)`): você entrega uma **fotocópia** do documento. Quem recebe rabisca a cópia à vontade, o original nem percebe.
- **Chamada por referência** (`void inc_ref(int *p)`): você entrega o **endereço real da casa**. Quem recebe vai até lá e mexe direto no original.

### Demonstre com o próprio exercício 1 e 2 do arquivo do aluno

```c
/* 1) Preveja a saída — cópia não altera o original */
void inc(int x) {
    x = x + 1;   // só a cópia local muda
}
```
Chame `inc(a)` no `main` e mostre que `a` continua `10`. Pergunte pro aluno: "por que será que não mudou?" — deixe ele chegar na resposta usando a analogia da fotocópia.

```c
/* 2) Troca que NÃO troca (por valor) */
void troca_invalida(int x, int y) {
    int temp = x;
    x = y;
    y = temp;   // troca as cópias, não os originais
}
```

### Agora a solução — exercícios 4, 5 e 6 do arquivo

```c
/* 4) Troca que FUNCIONA (swap por referência) */
void troca_ref(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
```
No `main`: `troca_ref(&a, &b);` — reforce: `&a` é "o GPS da casa `a`", a função vai até lá e troca o morador de verdade.

```c
/* 5) Incremento por referência */
void inc_ref(int *p) {
    if (!p) return;      // proteção: nunca desreferencie um ponteiro nulo
    *p = *p + 1;
}
```

```c
/* 6) Troca condicional: troca apenas se *a > *b */
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
Peça pro aluno implementar esse sozinho — é o primeiro exercício "real" da lista, combina desreferência com lógica condicional.

### Exercício 7 — múltiplos retornos

```c
/* 7) Normalização de três valores: subtrai a média de cada um */
void normaliza_trio(float *x, float *y, float *z) {
    if (!x || !y || !z) return;
    float m = (*x + *y + *z) / 3;
    *x -= m;
    *y -= m;
    *z -= m;
}
```
Gancho importante: em C, `return` só devolve **um** valor. Passar por referência é como abrir três "canais de retorno" simultâneos — é assim que se "retorna" mais de uma coisa.

---

## Vetores: referência automática

### Analogia: vetor é "empresta a rua inteira automaticamente"

Diferente de uma variável simples, um vetor **já é passado por referência sem precisar de `&`**, porque o nome do vetor já É um endereço (ponteiro constante, visto no Bloco 2).

```c
f(vetor) == f(&vetor[0])   // são a mesma coisa
```

Percorra as funções do arquivo nessa ordem, sempre plugando na analogia "a função recebe o mapa da rua e pode alterar qualquer casa dela":

```c
/* 8) Zera vetor */
void zera(int *v, int n) {
    for (int i = 0; i < n; i++)
        v[i] = 0;   // ou: *(v + i) = 0;
}

/* 9) Soma e média (sem alterar o vetor) */
int soma(const int *v, int n) {
    int s = 0;
    for (int i = 0; i < n; i++) s += v[i];
    return s;
}
```
Chame atenção pro `const int *v` — é o "olhar, não tocar": a função pode ler a rua inteira, mas o compilador impede ela de alterar qualquer casa.

```c
float media_int(const int *v, int n) {
    if (n <= 0) return 0;
    return soma(v, n) / (float) n;
}

/* 10) Escala in-place: v[i] *= k */
void escala(float *v, int n, float k) {
    for (int i = 0; i < n; i++) v[i] *= k;
}

/* 11) Troca de extremos: v[0] <-> v[n-1] */
void troca_extremos(int *v, int n) {
    int tmp = v[0];
    v[0] = v[n-1];
    v[n-1] = tmp;
}
```

Depois os mais avançados o:

```c
/* 12) Filtragem por faixa em outro vetor; retorna quantidade copiada */
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

/* 13) Índice do mínimo e do máximo (primeira ocorrência) */
int indice_min(const float *v, int n) {
    int idx = 0;
    for (int i = 1; i < n; i++)
        if (v[i] < v[idx]) idx = i;
    return idx;
}
// indice_max é o espelho, com >

/* 14) Remover a primeira ocorrência e deslocar; atualiza *n */
void remove_primeiro(int *v, int *n, int alvo) {
    int i;
    for (i = 0; i < *n; i++)
        if (v[i] == alvo) break;
    if (i == *n) return; // não achou
    for (; i < *n - 1; i++)
        v[i] = v[i+1];
    (*n)--;   // atualiza o tamanho do vetor no CALLER também — por isso *n
}

/* 15) Inversão in-place */
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

**Destaque do exercício 14:** aqui `n` também é passado como ponteiro (`int *n`), porque a função precisa alterar o *tamanho lógico* do vetor pra quem chamou — outro exemplo de "múltiplo retorno via referência".

---

## Alocação dinâmica: quando a "rua" ainda não existe

### Analogia: **gaveta sob encomenda x prédio já construído**

`int v1[5];` é um prédio já construído em tempo de compilação: você sabe o tamanho antes de rodar o programa.
`malloc()` é pedir pra construir uma gaveta **na hora**, do tamanho exato que você precisa, usando o "terreno livre" chamado **heap**.

```c
int *v1;
v1 = (int *) malloc(5 * sizeof(int));
if (v1 == NULL) return 1;   // regra de ouro: sempre verifique se a construção deu certo

*v1 = 1;
for (int *p = v1 + 1; p < v1 + 5; p++)
    *p = *(p - 1) + 1;
```

Esse é exatamente o trecho que a solução (`lista2_funcoes_ponteiros-sol.c`) usa no lugar de `int v1[5] = {1,2,3,4,5};` — mostre lado a lado os dois arquivos pro aluno ver a transformação de estático pra dinâmico.

### As 4 ferramentas

| Função | O que faz |
|---|---|
| `malloc(bytes)` | Reserva um bloco cru (com "lixo" residual dentro) |
| `calloc(n, tam)` | Reserva e já zera tudo |
| `realloc(ptr, novo_tam)` | Redimensiona um bloco já existente |
| `free(ptr)` | Devolve o bloco pro sistema |

### A regra de ouro final

```c
free(v1);
v1 = NULL;   // "exorcismo do ponteiro fantasma"
```
Depois do `free`, o endereço continua guardado em `v1`, mas a "casa" foi demolida. Usar `*v1` depois disso é acessar uma casa que não existe mais — daí a importância de sempre zerar (`= NULL`) o ponteiro logo depois de liberar.

---

## Fechamento

Perguntas rápidas de verificação (peça respostas em voz alta, sem consultar nada):
1. Qual a diferença entre `p`, `&p` e `*p`?
2. Por que `troca_invalida(a, b)` não troca `a` e `b`, mas `troca_ref(&a, &b)` troca?
3. Por que `zera(v1, 5)` funciona sem precisar de `&v1`?
4. O que `p++` faz de verdade quando `p` é `int*`?
5. Por que esquecer o `free()` é perigoso?
