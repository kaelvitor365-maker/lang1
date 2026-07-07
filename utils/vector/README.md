# Vector

Array dinâmico genérico em C, inspirado no `vector<T>` do C++. Usa `void*` para ser compatível com qualquer tipo de dado. Inclui suporte a iteradores.

---

## Estruturas

### `_Vector` (interna)
```cgit a
CLASS(_Vector, {
    void*  __data;        // buffer interno
    size_t __size;        // quantidade atual de elementos
    size_t __capacity;    // capacidade total alocada
    size_t __size_value;  // tamanho de cada elemento (sizeof(T))
    bool   __is_ptr;      // true se os elementos são ponteiros
    void (*__init__)(bool, _Vector*, size_t);
    void (*__del__)(_Vector*);
});
typedef _Vector Vector; // alias público
```

### `VectorIterator` — iterador
```c
CLASS(__it__Vector, {
    void*  __data;        // início do buffer
    void*  __pos;         // posição atual
    size_t __size_value;  // tamanho de cada elemento
    bool   __is_ptr;      // true se os elementos são ponteiros
});
```

### `Vector_t` — namespace de funções
Objeto global que agrupa todas as funções como "métodos":
```c
extern _Vector_t VectorF;
```

---

## Uso básico

```c
// Criar (elementos por valor)
Vector* vec = VectorF.new();
vec->__init__(false, vec, sizeof(int));

// Criar (elementos por ponteiro)
Vector* vec = VectorF.new();
vec->__init__(true, vec, sizeof(void*));

// Adicionar
int x = 42;
vec = VectorF.append(vec, &x);

// Acessar
int* val = (int*)VectorF.get(vec, 0);

// Modificar
int y = 99;
vec = VectorF.set(vec, 0, &y);

// Remover último
vec = VectorF.pop(vec);

// Verificar existência
int z = 42;
if (VectorF.in(vec, &z)) { ... }

// Extender com outro vector
vec = VectorF.extend(vec_a, vec_b);

// Liberar
VectorF.free(vec);
```

---

## Funções

| Função | Descrição |
|--------|-----------|
| `VectorF.new()` | Aloca a struct. Chame `__init__` antes de usar. |
| `vec->__init__(is_ptr, vec, sizeof(T))` | Inicializa o buffer com capacidade para 8 elementos |
| `VectorF.free(vec)` | Libera buffer interno e a struct |
| `VectorF.append(vec, &val)` | Adiciona elemento no final, cresce automaticamente |
| `VectorF.extend(vec, src)` | Copia todos os elementos de `src` pro final de `vec` |
| `VectorF.pop(vec)` | Remove o último elemento |
| `VectorF.get(vec, pos)` | Retorna ponteiro pro elemento na posição `pos` |
| `VectorF.set(vec, pos, &val)` | Sobrescreve o valor na posição `pos` |
| `VectorF.in(vec, &val)` | Retorna `true` se o valor existir (usa `memcmp`) |

---

## Iterador

```c
// Criar iterador
VectorIterator* it = VectorF.begin(vec);

// Iterar
for(VectorIterator it = VectorF.begin(vec); it->__pos != VectorF.end(vec); it = VectorF.next(it));

// Liberar
free(it);
```

| Função | Descrição |
|--------|-----------|
| `VectorF.begin(vec)` | Cria iterador apontando pro primeiro elemento |
| `VectorF.end(vec)` | Cria iterador apontando após o último elemento |
| `VectorF.next(it)` | Avança o iterador uma posição |
| `VectorF.prev(it)` | Recua o iterador uma posição |
| `VectorF.getIterator(it)` | Retorna ponteiro pro elemento atual |
| `VectorF.setIterator(it, pos)` | Move o iterador para uma posição arbitrária |

---

## `__is_ptr` — modo ponteiro

Quando `__is_ptr = true`, `get` e `getIterator` desreferenciam automaticamente o ponteiro guardado:

```c
// sem is_ptr: recebe void* apontando pro buffer interno
// com is_ptr: recebe diretamente o ponteiro guardado
Token* t = (Token*)VectorF.get(vec, 0); // já desreferenciado!
```

---

## Macros utilitárias

```c
len(vec)          // vec->__size
capacity(vec)     // vec->__capacity
size_value(vec)   // vec->__size_value
```

---

## Observações

- O vector começa com capacidade para **8 elementos** e dobra quando necessário.
- Todas as funções validam `NULL` e imprimem mensagens de erro descritivas.
- `Vector_t Vector` é definido em `vector.c` — o header expõe apenas `extern Vector_t Vector`.
- Os dois vetores precisam ter o mesmo `__size_value` para usar `extend`.
- Não há verificação de tipo em tempo de compilação — responsabilidade do usuário passar o tipo correto.
- Iteradores alocam memória com `malloc` — lembre de dar `free` após o uso.
