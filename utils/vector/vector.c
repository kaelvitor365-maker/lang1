#include "vector.h"
#include <stdio.h>

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


        void* temp = realloc(this->__data, (this->__capacity << 1) * this->__size_value);
        if(temp == NULL){ // test error
            printf("MALLOC ERROR IN appendVector\n");
            return this;
        }

        // update the vector
        this->__data = temp;
        this->__capacity <<= 1;
    }

    // finaly update the vector
    void* pointer = (char*)this->__data + (this->__size * this->__size_value);
    memcpy(pointer, value, this->__size_value);
    ++this->__size;
    
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

    return (char*)this->__data + (pos * this->__size_value); // the position
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

    void* pointer = (char*)this->__data + (pos * this->__size_value); // getting the pos
    memcpy(pointer, value, this->__size_value); // setting the value

    return this;
}





