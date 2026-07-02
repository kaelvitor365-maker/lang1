#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

Lexer* newLexer(const char* __arq){
    FILE* file = fopen(__arq, "r");
    Lexer* lexer;
    if(file == NULL) goto file_error;

    if(fseek(file, 0, SEEK_END) != 0) goto seek_error;
    size_t size = ftell(file);
    if(fseek(file, 0, SEEK_SET) != 0) goto seek_error;

    lexer = malloc(sizeof(Lexer));
    if(lexer == NULL) goto lexer_malloc_error;

    lexer->file = malloc(size+1);
    if(lexer->file == NULL) goto file_malloc_error;

    if(fread(lexer->file, 1, size, file) != size) goto file_malloc_error;

    fclose(file);

    lexer->line = 0;
    lexer->pos = 0;
    return lexer;


file_malloc_error:
    free(lexer->file);

lexer_malloc_error:
    free(lexer);

seek_error: 
    fclose(file);

file_error:
    return NULL;
}

void* freeLexer(Lexer* this){
    if(this == NULL) return this;
    free(this->file);
    free(this);
    return NULL;
}