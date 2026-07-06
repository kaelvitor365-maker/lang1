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
 * @param __is_ptr      Ajuda na hora de fazer get caso seja um ponteiro alocado
 */
CLASS(_Vector, {
    void* __data;
    size_t __size;
    size_t __capacity;
    size_t __size_value;
    bool __is_ptr;
    void FUNCTIONS(__init__, bool, INTERN_NAME(_Vector)*, size_t)
    void FUNCTIONS(__del__, INTERN_NAME(_Vector)*)
})

/**
 * @brief Iterador para _Vector.
 * @param __data        Ponteiro pro início do buffer
 * @param __pos         Posição atual do iterador
 * @param __size_value  Tamanho de cada elemento
 * @param __is_ptr      true se os elementos são ponteiros
 */
CLASS(__it__Vector, {
    void* __data;
    void* __pos;
    size_t __size_value;
    bool __is_ptr;
})

/**
 * @brief Namespace de funções do Vector.
 */
CLASS(_Vector_t, {
    _Vector* FUNCTIONS(new)
    void* FUNCTIONS(free, _Vector*)
    INTERN_NAME(_Vector)* FUNCTIONS(append, INTERN_NAME(_Vector)*, void*)
    INTERN_NAME(_Vector)* FUNCTIONS(extend, INTERN_NAME(_Vector)*, const INTERN_NAME(_Vector)*)
    INTERN_NAME(_Vector)* FUNCTIONS(pop, INTERN_NAME(_Vector)*)
    void* FUNCTIONS(get, INTERN_NAME(_Vector)*, const size_t)
    INTERN_NAME(_Vector)* FUNCTIONS(set, INTERN_NAME(_Vector)*, const size_t, void*)
    bool FUNCTIONS(in, INTERN_NAME(_Vector)*, const void*)
    __it__Vector* FUNCTIONS(begin, INTERN_NAME(_Vector)*)
    __it__Vector* FUNCTIONS(end, INTERN_NAME(_Vector)*)
    __it__Vector* FUNCTIONS(next, __it__Vector*)
    __it__Vector* FUNCTIONS(prev, __it__Vector*)
    void* FUNCTIONS(getIterator, __it__Vector*)
    void FUNCTIONS(setIterator, __it__Vector*, void*)
})

/**
 * @brief Aloca e retorna um novo Vector.
 * @note Chame __init__ antes de usar qualquer outra função.
 * @return Ponteiro para o novo Vector, ou NULL se falhar.
 */
_Vector* Vector__newVector();

/**
 * @brief Libera o buffer interno e a struct.
 * @param this Ponteiro para o Vector a ser liberado.
 */
void* Vector__freeVector(_Vector* this);

/**
 * @brief (Interno) Dobra a capacidade do vetor via realloc.
 * @param this Ponteiro para o Vector a ser redimensionado.
 * @return Ponteiro para o Vector, ou NULL se o realloc falhar.
 */
_Vector* Vector__resize(_Vector* this);

/**
 * @brief Adiciona um elemento no final. Cresce automaticamente se necessário.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
_Vector* Vector__appendVector(_Vector* this, void* value);

/**
 * @brief Copia todos os elementos de src para o final de this.
 * @param this Ponteiro para o Vector de destino.
 * @param src  Ponteiro para o Vector de origem.
 * @note Os dois vetores precisam ter o mesmo __size_value.
 * @return Ponteiro para o Vector de destino.
 */
_Vector* Vector__extendVector(_Vector* this, const _Vector* src);

/**
 * @brief Remove o último elemento (decrementa __size).
 * @param this Ponteiro para o Vector.
 * @return Ponteiro para o Vector.
 */
_Vector* Vector__popVector(_Vector* this);

/**
 * @brief Retorna ponteiro para o elemento na posição pos.
 * @param this Ponteiro para o Vector.
 * @param pos  Índice do elemento (0-based).
 * @return Ponteiro para o elemento, ou NULL se pos for inválido.
 */
void* Vector__getVector(_Vector* this, const size_t pos);

/**
 * @brief Sobrescreve o valor na posição pos.
 * @param this  Ponteiro para o Vector.
 * @param pos   Índice do elemento (0-based).
 * @param value Ponteiro para o novo valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
_Vector* Vector__setVector(_Vector* this, const size_t pos, void* value);

/**
 * @brief Verifica se value existe no vetor usando memcmp.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser buscado.
 * @return true se encontrado, false caso contrário.
 */
bool Vector__inVector(_Vector* this, const void* value);

/**
 * @brief Avança o iterador uma posição.
 * @param this Ponteiro para o iterador.
 * @return Ponteiro para o iterador atualizado.
 */
__it__Vector* Vector__itNext(__it__Vector* this);

/**
 * @brief Recua o iterador uma posição.
 * @param this Ponteiro para o iterador.
 * @return Ponteiro para o iterador atualizado.
 */
__it__Vector* Vector__itPrev(__it__Vector* this);

/**
 * @brief Cria iterador apontando pro primeiro elemento.
 * @param this Ponteiro para o Vector.
 * @return Ponteiro para o iterador, ou NULL se falhar.
 */
__it__Vector* Vector__itBegin(_Vector* this);

/**
 * @brief Cria iterador apontando após o último elemento.
 * @param this Ponteiro para o Vector.
 * @return Ponteiro para o iterador, ou NULL se falhar.
 */
__it__Vector* Vector__itEnd(_Vector* this);

/**
 * @brief Retorna ponteiro pro elemento atual do iterador.
 * @param this Ponteiro para o iterador.
 * @return Ponteiro para o elemento atual.
 */
void* Vector__itGet(__it__Vector* this);

/**
 * @brief Move o iterador para uma posição arbitrária.
 * @param this Ponteiro para o iterador.
 * @param pos  Nova posição.
 */
void Vector__itSet(__it__Vector* this, void* pos);

extern _Vector_t VectorF;
typedef _Vector VectorType;
typedef __it__Vector VectorIterator;