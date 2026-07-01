# Vector

Array dinâmico genérico em C, inspirado no `vector<T>` do C++. Usa `void*` para ser compatível com qualquer tipo de dado.

---

## Estrutura

```c
CLASS(Vector, {
    void*  __data;        // buffer interno
    size_t __size;        // quantidade de elementos
    size_t __capacity;    // capacidade alocada
    size_t __size_value;  // tamanho de cada elemento (sizeof(T))
    void (*__init__)(struct Vector_t*, size_t);
    void (*__del__)(struct Vector_t*);
});
```

---

## Criando e destruindo

```c
// Aloca um novo Vector
Vector* vec = newVector();

// Inicializa com o tipo desejado (obrigatório antes de usar)
vec->__init__(vec, sizeof(int));

// Libera tudo (dados + struct)
freeVector(vec);
```

> ⚠️ Sempre chame `__init__` antes de qualquer outra operação.

---

## Funções

### `appendVector`
Adiciona um elemento no final. Cresce automaticamente quando necessário.
```c
int x = 42;
appendVector(vec, &x);
```

### `getVector`
Retorna um ponteiro para o elemento na posição `pos`.
```c
int* val = (int*)getVector(vec, 0);
```

### `setVector`
Sobrescreve o valor na posição `pos`.
```c
int x = 99;
vec = setVector(vec, 0, &x);
```

### `popVector`
Remove o último elemento (decrementa `__size`).
```c
popVector(vec);
```

### `extendVector`
Copia todos os elementos de `src` para o final de `this`. Os dois vetores precisam ter o mesmo `__size_value`.
```c
extendVector(vec_a, vec_b);
```

### `inVector`
Verifica se um valor existe no vetor usando `memcmp`.
```c
int x = 42;
if (inVector(vec, &x)) { ... }
```

### `Vector__resize` (interno)
Dobra a capacidade do vetor. Chamado automaticamente pelo `appendVector`.

---

## Macro utilitária

```c
// Itera sobre todos os elementos do vetor
VECTOR_FOR_EACH(vec, int, item, {
    printf("%d\n", *item);
});

// Tamanho atual
len(vec); // equivale a vec->__size
```

---

## Exemplo completo

```c
Vector* vec = newVector();
vec->__init__(vec, sizeof(int));

for (int i = 0; i < 10; i++) {
    appendVector(vec, &i);
}

VECTOR_FOR_EACH(vec, int, item, {
    printf("%d\n", *item);
});

freeVector(vec);
```

---

## Observações

- O vetor começa com capacidade para **8 elementos** e dobra quando necessário.
- Todas as funções validam `NULL` e imprimem mensagens de erro descritivas.
- Não há verificação de tipo em tempo de compilação — é responsabilidade do usuário passar o tipo correto.