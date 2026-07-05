#pragma once
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "def.h"

/**
 * @brief Array dinâmico genérico inspirado no vector<T> do C++.
 * 
 * @param __data        Buffer interno de dados (void* genérico)
 * @param __size        Quantidade atual de elementos
 * @param __capacity    Capacidade total alocada
 * @param __size_value  Tamanho em bytes de cada elemento (sizeof(T))
 * @param __init__      Inicializa o buffer interno com capacidade para 8 elementos
 * @param __del__       Libera o buffer interno e zera os campos
 * @param is_ptr        ajuda na hora de fazer get caso seja um ponteiro q sera alocado
 */
CLASS(_Vector, {
    void* __data;
    size_t __size;
    size_t __capacity;
    size_t __size_value;
    bool __is_ptr;
    void (*__init__)(PTR(INTERN_NAME(_Vector)));
    void (*__del__)(PTR(INTERN_NAME(_Vector)));
})


CLASS(Vector_t,{
    PTR(PTR(_Vector)) FUNCTIONS( new, PTR(_Vector))
    PTR(void) FUNCTIONS(free, PTR(_Vector))
    PTR(_Vector) FUNCTIONS(append, PTR(_Vector), const void*)
    PTR(_Vector) FUNCTIONS(extend, PTR(_Vector), const PTR(_Vector))
    PTR(_Vector) FUNCTIONS(pop, PTR(_Vector))
    void* FUNCTIONS(get, PTR(_Vector), const size_t)
    PTR(_Vector) FUNCTIONS(set, PTR(_Vector), const size_t, const void*)
    bool FUNCTIONS(in, PTR(_Vector), const PTR(void))

})
/**
 * @brief Aloca e retorna um novo Vector.
 * @note Chame __init__ antes de usar qualquer outra função.
 * @return Ponteiro para o novo Vector, ou NULL se falhar.
 */
PTR(_Vector) Vector__newVector();

/**
 * @brief Libera o buffer interno e a struct.
 * @param this Ponteiro para o Vector a ser liberado.
 */
PTR(void) Vector__freeVector(PTR(_Vector) this);

/**
 * @brief (Interno) Dobra a capacidade do vetor via realloc.
 * @param this Ponteiro para o Vector a ser redimensionado.
 * @return Ponteiro para o Vector, ou NULL se o realloc falhar.
 */
PTR(_Vector) Vector__resize(PTR(_Vector) this);

/**
 * @brief Adiciona um elemento no final. Cresce automaticamente se necessário.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
PTR(_Vector) Vector__appendVector(PTR(_Vector) this, const void* value);    

/**
 * @brief Copia todos os elementos de src para o final de this.
 * @param this Ponteiro para o Vector de destino.
 * @param src  Ponteiro para o Vector de origem.
 * @note Os dois vetores precisam ter o mesmo __size_value.
 * @return Ponteiro para o Vector de destino.
 */
PTR(_Vector) Vector__extendVector(PTR(_Vector) this, const PTR(_Vector) src);

/**
 * @brief Remove o último elemento (decrementa __size).
 * @param this Ponteiro para o Vector.
 * @return Ponteiro para o Vector.
 */
PTR(_Vector) Vector__popVector(PTR(_Vector) this);

/**
 * @brief Retorna ponteiro para o elemento na posição pos.
 * @param this Ponteiro para o Vector.
 * @param pos  Índice do elemento (0-based).
 * @return Ponteiro para o elemento, ou NULL se pos for inválido.
 */
void* Vector__getVector(PTR(_Vector) this, const size_t pos);

/**
 * @brief Sobrescreve o valor na posição pos.
 * @param this  Ponteiro para o Vector.
 * @param pos   Índice do elemento (0-based).
 * @param value Ponteiro para o novo valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
PTR(_Vector) Vector__setVector(PTR(_Vector) this, const size_t pos, const void* value);

/**
 * @brief Verifica se value existe no vetor usando memcmp.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser buscado.
 * @return true se encontrado, false caso contrário.
 */
bool Vector__inVector(PTR(_Vector) this, const PTR(void) value);

Vector_t Vector = {
    .new = &Vector__newVector,
    .free = &Vector__freeVector,
    .append = &Vector__appendVector,
    .extend = &Vector__extendVector,
    .pop = &Vector__popVector,
    .get = &Vector__getVector,
    .set = &Vector__setVector,
    .in = &Vector__inVector
};