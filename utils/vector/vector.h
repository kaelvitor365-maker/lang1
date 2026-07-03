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
 */
CLASS(Vector, {
    void* __data;
    size_t __size;
    size_t __capacity;
    size_t __size_value;
    void (*__init__)(struct Vector_t*, size_t);
    void (*__del__)(struct Vector_t*);
})

/**
 * @brief Aloca e retorna um novo Vector.
 * @note Chame __init__ antes de usar qualquer outra função.
 * @return Ponteiro para o novo Vector, ou NULL se falhar.
 */
Vector* newVector();

/**
 * @brief Libera o buffer interno e a struct.
 * @param this Ponteiro para o Vector a ser liberado.
 */
void freeVector(Vector* this);

/**
 * @brief (Interno) Dobra a capacidade do vetor via realloc.
 * @param this Ponteiro para o Vector a ser redimensionado.
 * @return Ponteiro para o Vector, ou NULL se o realloc falhar.
 */
Vector* Vector__resize(Vector* this);

/**
 * @brief Adiciona um elemento no final. Cresce automaticamente se necessário.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
Vector* appendVector(Vector* this, const void* value);

/**
 * @brief Copia todos os elementos de src para o final de this.
 * @param this Ponteiro para o Vector de destino.
 * @param src  Ponteiro para o Vector de origem.
 * @note Os dois vetores precisam ter o mesmo __size_value.
 * @return Ponteiro para o Vector de destino.
 */
Vector* extendVector(Vector* this, const Vector* src);

/**
 * @brief Remove o último elemento (decrementa __size).
 * @param this Ponteiro para o Vector.
 * @return Ponteiro para o Vector.
 */
Vector* popVector(Vector* this);

/**
 * @brief Retorna ponteiro para o elemento na posição pos.
 * @param this Ponteiro para o Vector.
 * @param pos  Índice do elemento (0-based).
 * @return Ponteiro para o elemento, ou NULL se pos for inválido.
 */
void* getVector(Vector* this, const size_t pos);

/**
 * @brief Sobrescreve o valor na posição pos.
 * @param this  Ponteiro para o Vector.
 * @param pos   Índice do elemento (0-based).
 * @param value Ponteiro para o novo valor a ser copiado.
 * @return Ponteiro para o Vector.
 */
Vector* setVector(Vector* this, const size_t pos, const void* value);

/**
 * @brief Verifica se value existe no vetor usando memcmp.
 * @param this  Ponteiro para o Vector.
 * @param value Ponteiro para o valor a ser buscado.
 * @return true se encontrado, false caso contrário.
 */
bool inVector(Vector* this, const void* value);