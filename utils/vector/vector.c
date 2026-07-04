#include "vector.h"
#include <stdio.h>

Vector* Vector__resize(Vector* this){
    void* temp = realloc(this->__data, (this->__capacity << 1) * this->__size_value);
    if(temp == NULL){
        printf("MALLOC ERROR\n");
        return NULL;
    }
    this->__data = temp;
    this->__capacity <<= 1;
    
    return this;
}
// vector intern starter
void Vector__init__(Vector* this, const size_t size_value){
    if(this == NULL){ // test error
        printf("__INIT__(THE VECTOR IS NULL) this == NULL\n");
        return;
    }

    this->__data = malloc(size_value*8); // create the array
    if(this->__data == NULL){ // test error
        printf("MALLOC ERROR\n");
        return;
    }

    // finaly creating the array
    this->__size_value = size_value;
    this->__size = 0;
    this->__capacity = 8;
}

// clean the intern process of vector
void Vector__del__(Vector* this){
    if(this == NULL){ // test error
        printf("__DEL__(THE VECTOR IS NULL) this == NULL\n");
        return;
    }

    // cleaning
    free(this->__data);
    this->__size_value = 0;
    this->__capacity = 0;
    this->__size = 0;
}

// allocator of Vector
Vector* newVector(){
    Vector* this = malloc(sizeof(Vector));
    if(this == NULL) goto error;

    this->__init__ = &Vector__init__;
    this->__del__ = &Vector__del__;

    return this;

error:
    return NULL;
}


// unallocator of Vector
void freeVector(Vector* this){
    if(this == NULL){
        printf("THIS IS NULL IN THE FREE VECTOR\n");
        return;
    }
    if(this->__data == NULL) goto final_free;
    this->__del__(this);
final_free:
    free(this);
}

// append value in the vector
Vector* appendVector(Vector* this, const void* value){
    if(this == NULL){ // test error
        printf("appendVector(THIS IS NULL)\n");
        return this;
    }

    if(this->__data == NULL){ // test error
        printf("NEED START THE VECTOR WITH .__init__(Vector* this, size_t size_value)\n");
        return this;
    }

    if(this->__size == this->__capacity){ // test size of vector


        Vector* temp = Vector__resize(this);
        if(temp == NULL){
            printf("RESIZE ERROR\n");
            return this;
        }
    }

    // finaly update the vector
    void* pointer = CAST_TO(char*, this->__data) + (this->__size * this->__size_value);
    memcpy(pointer, value, this->__size_value);
    ++this->__size;
    
    return this;
}

Vector* extendVector(Vector* this, const Vector* src){
    if(this == NULL){
        printf("extendVector(THIS IS NULL)\n");
        return this;       
    }
    if(src == NULL){
        printf("extendVector(SRC IS NULL)\n");
        return this;       
    }
    if(this->__data == NULL){
        printf("THIS NEED START WITH .__init__(THIS)\n");
        return this;
    }
    if(src->__data == NULL){
        printf("SRC NEED START WITH .__init__(SRC)\n");
        return this;
    }
    if(this->__size_value != src->__size_value){
        printf("SRC DO NOT HAVE SAME SIZE_VALUE\n");
        return this;
    }

    if(this->__size + src->__size >= this->__capacity){
        void* temp = realloc(this->__data, ((this->__capacity + src->__size) << 1) * this->__size_value);
        if(temp == NULL){
            printf("MALLOC ERROR\n");
            return this;
        }
        this->__data = temp;
        this->__capacity += src->__size;
        this->__capacity <<= 1;
    }
    void* dest = CAST_TO(char*, this->__data) + (this->__size * this->__size_value);
    memcpy(dest, src->__data, src->__size*src->__size_value);
    this->__size += src->__size;

    return this;

}
// pop value in the vector
Vector* popVector(Vector* this){
    if(this == NULL){ // test error
        printf("popVector(THIS IS NULL)\n");
        return this;
    }
    if(this->__data == NULL){ // test error
        printf("NEED START THE VECTOR WITH .__init__(Vector* this, size_t size_value)\n");
        return this;
    }
    if(this->__size <= 0){ // test error
        printf("THIS VECTOR IS EMPTY\n");
        return this;
    }

    //popping
    --this->__size;
    return this;
}

//getting the value of one position
void* getVector(Vector* this, const size_t pos){
    if(this == NULL){ // test error
        printf("getVector(THIS IS NULL)\n");
        return NULL;
    }

    if(this->__data == NULL){ // test error
        printf("NEED START THE VECTOR WITH .__init__(Vector* this, size_t size_value)\n");
        return NULL;
    }

    if(pos >= this->__size){ // test error
        printf("THIS POS IS OUT OF THE RANGE\n");
        return NULL;
    }

    return CAST_TO(char*, this->__data) + (pos * this->__size_value); // the position
}

// setting the value in the vector
Vector* setVector(Vector* this, const size_t pos, const void* value){
    if(this == NULL){ // test error
        printf("getVector(THIS IS NULL)\n");
        return this;
    }

    if(this->__data == NULL){ // test error
        printf("NEED START THE VECTOR WITH .__init__(Vector* this, size_t size_value)\n");
        return this;
    }

    if(pos >= this->__size){ // test error
        printf("THIS POS IS OUT OF THE RANGE\n");
        return this;
    }

    void* pointer = CAST_TO(char*, this->__data) + (pos * this->__size_value); // getting the pos
    memcpy(pointer, value, this->__size_value); // setting the value

    return this;
}


bool inVector(Vector* this, const void* value){
    if(this == NULL){
        printf("inVector(THIS IS NULL)\n");
        return false;
    }
    if(this->__data == NULL){
        printf("NEED START THE VECTOR WITH .__init__(Vector* this, size_t size_value)\n");
        return false;
    }
    if(value == NULL){
        printf("inVector(VALUE IS NULL)\n");
        return false;
    }
    for(size_t i = 0; i < this->__size; ++i){
        if(memcmp(
            CAST_TO(char*, this->__data) + (i * this->__size_value),
            value,
            this->__size_value
        ) == 0)
            return true;
    }
    return false;
}




