# Vector

Array dinâmico genérico em C, inspirado no `vector<T>` do C++. Usa `void*` para ser compatível com qualquer tipo de dado. Inclui suporte a iteradores.

---

## Estruturas

### `_Vector` (interna)
```c
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
Vector* vec = Vector.new();
vec->__init__(false, vec, sizeof(int));

// Criar (elementos por ponteiro)
Vector* vec = Vector.new();
vec->__init__(true, vec, sizeof(void*));

// Adicionar
int x = 42;
vec = Vector.append(vec, &x);

// Acessar
int* val = (int*)Vector.get(vec, 0);

// Modificar
int y = 99;
vec = Vector.set(vec, 0, &y);

// Remover último
Vector.pop(vec);

// Verificar existência
int z = 42;
if (Vector.in(vec, &z)) { ... }

// Extender com outro vector
vec = Vector.extend(vec_a, vec_b);

// Liberar
Vector.free(vec);
```

---

## Funções

| Função | Descrição |
|--------|-----------|
| `Vector.new()` | Aloca a struct. Chame `__init__` antes de usar. |
| `vec->__init__(is_ptr, vec, sizeof(T))` | Inicializa o buffer com capacidade para 8 elementos |
| `Vector.free(vec)` | Libera buffer interno e a struct |
| `Vector.append(vec, &val)` | Adiciona elemento no final, cresce automaticamente |
| `Vector.extend(vec, src)` | Copia todos os elementos de `src` pro final de `vec` |
| `Vector.pop(vec)` | Remove o último elemento |
| `Vector.get(vec, pos)` | Retorna ponteiro pro elemento na posição `pos` |
| `Vector.set(vec, pos, &val)` | Sobrescreve o valor na posição `pos` |
| `Vector.in(vec, &val)` | Retorna `true` se o valor existir (usa `memcmp`) |

---

## Iterador

```c
// Criar iterador
VectorIterator* it = Vector.begin(vec);
VectorIterator* end = Vector.end(vec);

// Iterar
for(VectorIterator it = Vector.begin(vec); it->__pos != end->__pos; it = Vector.next(it));

// Liberar
free(it);
free(end);
```

| Função | Descrição |
|--------|-----------|
| `Vector.begin(vec)` | Cria iterador apontando pro primeiro elemento |
| `Vector.end(vec)` | Cria iterador apontando após o último elemento |
| `Vector.next(it)` | Avança o iterador uma posição |
| `Vector.prev(it)` | Recua o iterador uma posição |
| `Vector.getIterator(it)` | Retorna ponteiro pro elemento atual |
| `Vector.setIterator(it, pos)` | Move o iterador para uma posição arbitrária |

---

## `__is_ptr` — modo ponteiro

Quando `__is_ptr = true`, `get` e `getIterator` desreferenciam automaticamente o ponteiro guardado:

```c
// sem is_ptr: recebe void* apontando pro buffer interno
// com is_ptr: recebe diretamente o ponteiro guardado
Token* t = (Token*)Vector.get(vec, 0); // já desreferenciado!
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
