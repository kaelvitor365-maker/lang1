#pragma once

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "defines/def.h"



CLASS(Vector, {
    void* __data;
    size_t __size;
    size_t __capacity;
    size_t __size_value;

    void (*__init__)(struct Vector_t*, size_t);
    void (*__del__)(struct Vector_t*);
});


Vector* newVector();
void freeVector(Vector* this);

Vector* Vector__resize(Vector* this);

Vector* appendVector(Vector* this,const void* value);
Vector* extendVector(Vector* this, const Vector* src);
Vector* popVector(Vector* this);

void* getVector(Vector* this, const size_t pos);
Vector* setVector(Vector* this, const size_t pos, const void* value);

bool inVector(Vector* this, const void* value);