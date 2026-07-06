#include "vector.h"
#include <stdio.h>

_Vector* Vector__resize(_Vector* this){
    void* temp = realloc(this->__data, (this->__capacity << 1) * this->__size_value);
    if(temp == NULL){
        printf("MALLOC ERROR\n");
        return NULL;
    }
    this->__data = temp;
    this->__capacity <<= 1;
    return this;
}

void Vector__init__(bool is_ptr, _Vector* this, const size_t size_value){
    if(this == NULL){
        printf("__INIT__(THE VECTOR IS NULL) this == NULL\n");
        return;
    }
    this->__data = malloc(size_value * 8);
    if(this->__data == NULL){
        printf("MALLOC ERROR\n");
        return;
    }
    this->__size_value = size_value;
    this->__is_ptr = is_ptr;
    this->__size = 0;
    this->__capacity = 8;
}

void Vector__del__(_Vector* this){
    if(this == NULL){
        printf("__DEL__(THE VECTOR IS NULL) this == NULL\n");
        return;
    }
    free(this->__data);
    this->__size_value = 0;
    this->__capacity = 0;
    this->__size = 0;
}

_Vector* Vector__newVector(){
    _Vector* this = malloc(sizeof(_Vector));
    if(this == NULL) return NULL;
    this->__init__ = &Vector__init__;
    this->__del__ = &Vector__del__;
    return this;
}

void* Vector__freeVector(_Vector* this){
    if(this == NULL){
        printf("THIS IS NULL IN THE FREE VECTOR\n");
        return NULL;
    }
    if(this->__data != NULL) this->__del__(this);
    free(this);
    return NULL;
}

_Vector* Vector__appendVector(_Vector* this, void* value){
    if(this == NULL){ printf("appendVector(THIS IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return this; }
    if(this->__size == this->__capacity){
        _Vector* temp = Vector__resize(this);
        if(temp == NULL){ printf("RESIZE ERROR\n"); return this; }
    }
    void* pointer = CAST_TO(char*, this->__data) + (this->__size * this->__size_value);
    memcpy(pointer, value, this->__size_value);
    ++this->__size;
    return this;
}

_Vector* Vector__extendVector(_Vector* this, const _Vector* src){
    if(this == NULL){ printf("extendVector(THIS IS NULL)\n"); return this; }
    if(src == NULL){ printf("extendVector(SRC IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("THIS NEED START WITH .__init__()\n"); return this; }
    if(src->__data == NULL){ printf("SRC NEED START WITH .__init__()\n"); return this; }
    if(this->__size_value != src->__size_value){ printf("SRC DO NOT HAVE SAME SIZE_VALUE\n"); return this; }
    if(this->__size + src->__size >= this->__capacity){
        void* temp = realloc(this->__data, ((this->__capacity + src->__size) << 1) * this->__size_value);
        if(temp == NULL){ printf("MALLOC ERROR\n"); return this; }
        this->__data = temp;
        this->__capacity += src->__size;
        this->__capacity <<= 1;
    }
    void* dest = CAST_TO(char*, this->__data) + (this->__size * this->__size_value);
    memcpy(dest, src->__data, src->__size * src->__size_value);
    this->__size += src->__size;
    return this;
}

_Vector* Vector__popVector(_Vector* this){
    if(this == NULL){ printf("popVector(THIS IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return this; }
    if(this->__size <= 0){ printf("THIS VECTOR IS EMPTY\n"); return this; }
    --this->__size;
    return this;
}

void* Vector__getVector(_Vector* this, const size_t pos){
    if(this == NULL){ printf("getVector(THIS IS NULL)\n"); return NULL; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return NULL; }
    if(pos >= this->__size){ printf("THIS POS IS OUT OF THE RANGE\n"); return NULL; }
    if(this->__is_ptr) return CAST_TO(void*, *(CAST_TO(void**, this->__data) + pos));
    return CAST_TO(char*, this->__data) + (pos * this->__size_value);
}

_Vector* Vector__setVector(_Vector* this, const size_t pos, void* value){
    if(this == NULL){ printf("setVector(THIS IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return this; }
    if(pos >= this->__size){ printf("THIS POS IS OUT OF THE RANGE\n"); return this; }
    void* pointer = CAST_TO(char*, this->__data) + (pos * this->__size_value);
    memcpy(pointer, value, this->__size_value);
    return this;
}

bool Vector__inVector(_Vector* this, const void* value){
    if(this == NULL){ printf("inVector(THIS IS NULL)\n"); return false; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return false; }
    if(value == NULL){ printf("inVector(VALUE IS NULL)\n"); return false; }
    for(size_t i = 0; i < this->__size; ++i){
        if(memcmp(
            CAST_TO(char*, this->__data) + (i * this->__size_value),
            value,
            this->__size_value
        ) == 0) return true;
    }
    return false;
}

__it__Vector* Vector__itBegin(_Vector* this){
    if(this == NULL){ printf("begin(THIS IS NULL)\n"); return NULL; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return NULL; }
    __it__Vector* it = malloc(sizeof(__it__Vector));
    if(it == NULL){ printf("MALLOC ERROR\n"); return NULL; }
    it->__data = this->__data;
    it->__pos = it->__data;
    it->__size_value = this->__size_value;
    it->__is_ptr = this->__is_ptr;
    return it;
}

__it__Vector* Vector__itEnd(_Vector* this){
    if(this == NULL){ printf("end(THIS IS NULL)\n"); return NULL; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return NULL; }
    __it__Vector* it = malloc(sizeof(__it__Vector));
    if(it == NULL){ printf("MALLOC ERROR\n"); return NULL; }
    it->__data = this->__data;
    it->__pos = CAST_TO(char*, this->__data) + (this->__size * this->__size_value);
    it->__size_value = this->__size_value;
    it->__is_ptr = this->__is_ptr;
    return it;
}

__it__Vector* Vector__itNext(__it__Vector* this){
    if(this == NULL){ printf("next(THIS IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return this; }
    this->__pos = CAST_TO(char*, this->__pos) + this->__size_value;
    return this;
}

__it__Vector* Vector__itPrev(__it__Vector* this){
    if(this == NULL){ printf("prev(THIS IS NULL)\n"); return this; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return this; }
    this->__pos = CAST_TO(char*, this->__pos) - this->__size_value;
    return this;
}

void* Vector__itGet(__it__Vector* this){
    if(this == NULL){ printf("getIterator(THIS IS NULL)\n"); return NULL; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return NULL; }
    if(this->__is_ptr) return CAST_TO(void*, *(CAST_TO(void**, this->__pos)));
    return this->__pos;
}

void Vector__itSet(__it__Vector* this, void* pos){
    if(this == NULL){ printf("setIterator(THIS IS NULL)\n"); return; }
    if(this->__data == NULL){ printf("NEED START THE VECTOR WITH .__init__()\n"); return; }
    this->__pos = pos;
}

_Vector_t VectorF = {
    .new         = &Vector__newVector,
    .free        = &Vector__freeVector,
    .append      = &Vector__appendVector,
    .extend      = &Vector__extendVector,
    .pop         = &Vector__popVector,
    .get         = &Vector__getVector,
    .set         = &Vector__setVector,
    .in          = &Vector__inVector,
    .begin       = &Vector__itBegin,
    .end         = &Vector__itEnd,
    .next        = &Vector__itNext,
    .prev        = &Vector__itPrev,
    .getIterator = &Vector__itGet,
    .setIterator = &Vector__itSet
};