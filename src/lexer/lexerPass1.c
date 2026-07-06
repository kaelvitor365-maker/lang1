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
    lexer->pos = lexer->file;
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
    if(this == NULL) return NULL;
    if(this->file != NULL) free(this->file);
    free(this);
    return NULL;
}

static inline char peekLexer(Lexer* this){
    return *this->pos;
}

static inline char advanceLexer(Lexer* this){
    if(*this->pos == '\n') ++this->line;
    return *this->pos++;
}

static inline void skipSpaceLexer(Lexer* this){
    while(
        peekLexer(this) != '\0' &&
        (
            peekLexer(this) == ' ' ||
            peekLexer(this) == '\t' ||
            peekLexer(this) == '\n'
        )
    ){
        advanceLexer(this);
    }
}

static inline bool isNumber(char c){
    return c >= '0' && c <= '9';
}

static inline bool isAlpha(char c){
    return (
        c >= 'A' && c <= 'Z'
    ) || (
        c >= 'a' && c <= 'z'
    ) || c == '_';
}

static inline bool isAlphaNumeric(char c){
    return isAlpha(c) || isNumber(c);
}

static inline bool matchChar(Lexer* this, char c, TokenType type, Token* token){
    if(*this->pos == c){
        token->line = this->line;
        token->type = type;
        token->word[0] = c;
        token->word[1] = '\0';
        advanceLexer(this);
        return true;
    }
    return false;
}

Token* tokenNumber(Lexer* this, Token* token){
    token->line = this->line;
    token->type = TOKEN_NUMBER;

    char* ptr = token->word;
    while(isNumber(peekLexer(this))){
        *ptr = advanceLexer(this);
        ++ptr;
    }
    *ptr = '\0';

    return token;
}

Token* tokenString(Lexer* this, Token* token){
    char* ptr = token->word;
    token->line = this->line;
    token->type = TOKEN_STR;

    while(peekLexer(this) != '"' && peekLexer(this) != '\0'){
        *ptr = advanceLexer(this);
        ++ptr;
    }
    if(peekLexer(this) == '\0'){
        token->type = TOKEN_UNDEFINED;
        *ptr = '"';
        ++ptr;
    } else {
        advanceLexer(this); // consome o '"' de fechamento
    }
    *ptr = '\0';

    return token;
}

Token* tokenIdentifier(Lexer* this, Token* token){
    char* ptr = token->word;
    token->line = this->line;

    while(isAlphaNumeric(peekLexer(this))){
        *ptr = advanceLexer(this);
        ++ptr;
    }
    *ptr = '\0';

    if(strcmp(token->word, "main") == 0)         { token->type = TOKEN_MAIN;       return token; }
    if(strcmp(token->word, "function") == 0)     { token->type = TOKEN_FUNC;       return token; }
    if(strcmp(token->word, "return") == 0)       { token->type = TOKEN_RET;        return token; }
    if(strcmp(token->word, "if") == 0)           { token->type = TOKEN_IF;         return token; }
    if(strcmp(token->word, "else") == 0)         { token->type = TOKEN_ELSE;       return token; }
    if(strcmp(token->word, "for") == 0)          { token->type = TOKEN_FOR;        return token; }
    if(strcmp(token->word, "while") == 0)        { token->type = TOKEN_WHILE;      return token; }
    if(strcmp(token->word, "infinitWhile") == 0) { token->type = TOKEN_INFWHILE;   return token; }
    if(strcmp(token->word, "break") == 0)        { token->type = TOKEN_BREAK;      return token; }
    if(strcmp(token->word, "continue") == 0)     { token->type = TOKEN_CONTINUE;   return token; }
    if(strcmp(token->word, "var") == 0)          { token->type = TOKEN_VAR;        return token; }
    if(strcmp(token->word, "true") == 0)         { token->type = TOKEN_BOOL;       return token; }
    if(strcmp(token->word, "false") == 0)        { token->type = TOKEN_BOOL;       return token; }

    token->type = TOKEN_IDENTIFIER;
    return token;
}

#define MATCH_C(c, tok) if(matchChar(this, c, tok, token)) goto return_token;

Token* Lexer__LexerNext(Lexer* this){
    skipSpaceLexer(this);

    Token* token = malloc(sizeof(Token));
    if(token == NULL) return NULL;

    if(peekLexer(this) == '"'){
        advanceLexer(this);
        token = tokenString(this, token);
        goto return_token;
    }

    if(isNumber(*this->pos)){
        token = tokenNumber(this, token);
        goto return_token;
    }

    if(isAlpha(*this->pos)){
        token = tokenIdentifier(this, token);
        goto return_token;
    }

    MATCH_C('\0', TOKEN_EOF)
    MATCH_C('+',  TOKEN_PLUS)
    MATCH_C('-',  TOKEN_MINUS)
    MATCH_C('*',  TOKEN_MUL)
    MATCH_C('/',  TOKEN_DIV)
    MATCH_C(':',  TOKEN_COLON)
    MATCH_C(';',  TOKEN_SEMICOLON)
    MATCH_C('.',  TOKEN_DOT)
    MATCH_C('(',  TOKEN_LPAREN)
    MATCH_C(')',  TOKEN_RPAREN)
    MATCH_C('{',  TOKEN_LBRACE)
    MATCH_C('}',  TOKEN_RBRACE)
    MATCH_C('[',  TOKEN_LBRACKET)
    MATCH_C(']',  TOKEN_RBRACKET)
    MATCH_C('=',  TOKEN_EQUAL)
    MATCH_C('>',  TOKEN_GT)
    MATCH_C('<',  TOKEN_LT)
    MATCH_C('!',  TOKEN_NOT)
    MATCH_C('^',  TOKEN_XOR)
    MATCH_C('|',  TOKEN_OR)
    MATCH_C('~',  TOKEN_NOTB)
    MATCH_C('&',  TOKEN_AND)

    token->line = this->line;
    token->type = TOKEN_UNDEFINED;
    token->word[0] = advanceLexer(this);
    token->word[1] = '\0';

return_token:
    return token;
}