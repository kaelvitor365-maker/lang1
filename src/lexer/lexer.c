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

    lexer->line = 1;
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

static inline void skipCommentLineLexer(Lexer* this){
    while(peekLexer(this) != '\0' && peekLexer(this) != '\n'){
        advanceLexer(this);
    }
}

static inline void skipCommentMultLineLexer(Lexer* this){
    while(peekLexer(this) != '\0'){
        if(peekLexer(this) == '*' && *(this->pos + 1) == '/'){
            advanceLexer(this);
            advanceLexer(this);
            return;
        }
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

#define MATCH_C(c, tok) if(matchChar(this, c, tok, token))
Token* Lexer__LexerNext(Lexer* this){
    for(;;){
        skipSpaceLexer(this);
        if(peekLexer(this) == '/' && *(this->pos + 1) == '/'){
            skipCommentLineLexer(this);
            continue;
        }
        if(peekLexer(this) == '/' && *(this->pos + 1) == '*'){
            skipCommentMultLineLexer(this);
            continue;
        }
        break;
    }
    
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

    MATCH_C('\0', TOKEN_EOF) goto return_token;
    MATCH_C('+',  TOKEN_PLUS){
        MATCH_C('+', TOKEN_INC) goto return_token;
        MATCH_C('=', TOKEN_PLUSEQ) goto return_token;
        goto return_token;
    }
    MATCH_C('-',  TOKEN_MINUS){
        MATCH_C('-', TOKEN_DEC) goto return_token;
        MATCH_C('=', TOKEN_MINUSEQ) goto return_token;
        goto return_token;
    }
    MATCH_C('*',  TOKEN_MUL){
        MATCH_C('=', TOKEN_MULEQ) goto return_token;
        goto return_token;
    }
    MATCH_C('/',  TOKEN_DIV){
        MATCH_C('=', TOKEN_DIVEQ) goto return_token;
        goto return_token;
    }
    MATCH_C(':',  TOKEN_COLON) goto return_token;
    
    MATCH_C(';',  TOKEN_SEMICOLON) goto return_token;

    MATCH_C('.',  TOKEN_DOT) goto return_token;

    MATCH_C('(',  TOKEN_LPAREN) goto return_token;

    MATCH_C(')',  TOKEN_RPAREN) goto return_token;

    MATCH_C('{',  TOKEN_LBRACE) goto return_token;

    MATCH_C('}',  TOKEN_RBRACE) goto return_token;

    MATCH_C('[',  TOKEN_LBRACKET) goto return_token;

    MATCH_C(']',  TOKEN_RBRACKET) goto return_token;

    MATCH_C('=',  TOKEN_EQUAL){
        MATCH_C('=', TOKEN_EQEQ) goto return_token;
        goto return_token;
    }
    MATCH_C('>',  TOKEN_GT){
        MATCH_C('=', TOKEN_GTEQ) goto return_token;
        MATCH_C('>', TOKEN_RSHIFT){
            MATCH_C('=', TOKEN_RSHIFTEQ) goto return_token;
            goto return_token;
        }
        goto return_token;
    }
    MATCH_C('<',  TOKEN_LT){
        MATCH_C('=', TOKEN_LTEQ) goto return_token;
        MATCH_C('<', TOKEN_LSHIFT){
            MATCH_C('=', TOKEN_LSHIFTEQ) goto return_token;
        }
        goto return_token;
    }
    MATCH_C('!',  TOKEN_NOT) goto return_token;

    MATCH_C('^',  TOKEN_XOR) goto return_token;

    MATCH_C('|',  TOKEN_OR){
        MATCH_C('|', TOKEN_OROR) goto return_token;
        goto return_token;
    }
    MATCH_C('~',  TOKEN_NOTB) goto return_token;

    MATCH_C('&',  TOKEN_AND){
        MATCH_C('&', TOKEN_ANDAND) goto return_token;
        goto return_token;
    }

    token->line = this->line;
    token->type = TOKEN_UNDEFINED;
    token->word[0] = advanceLexer(this);
    token->word[1] = '\0';

return_token:
    return token;
}

_Vector* LexerVector(Lexer* this){
    _Vector* vector = VectorF.new();
    if(vector == NULL) return NULL;
    vector->__init__(true, vector, sizeof(Token*));

    for(;;){
        Token* token = Lexer__LexerNext(this);
        vector = VectorF.append(vector, &token);
        if(token->type == TOKEN_EOF) break;
    }
    return vector;
}

#include "lexer.h"
#include <stdio.h>

void log_token(Token* token){
    if(token == NULL){
        printf("[NULL TOKEN]\n");
        return;
    }

    printf("Line: %zu | ", token->line);

    if(token->type == TOKEN_IDENTIFIER){
        printf("[IDENTIFIER] -> %s\n", token->word);
        return;
    }

    if(token->type == TOKEN_NUMBER){
        printf("[NUMBER] -> %s\n", token->word);
        return;
    }

    if(token->type == TOKEN_STR){
        printf("[STRING] -> \"%s\"\n", token->word);
        return;
    }

    if(token->type == TOKEN_BOOL){
        printf("[BOOL] -> %s\n", token->word);
        return;
    }

    if(token->type == TOKEN_EQEQ){
        printf("[EQUAL EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_GTEQ){
        printf("[GT EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_LTEQ){
        printf("[LT EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_NOTEQ){
        printf("[NOT EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_ANDAND){
        printf("[AND AND]\n");
        return;
    }

    if(token->type == TOKEN_OROR){
        printf("[OR OR]\n");
        return;
    }

    if(token->type == TOKEN_PLUSEQ){
        printf("[PLUS EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_MINUSEQ){
        printf("[MINUS EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_MULEQ){
        printf("[MUL EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_DIVEQ){
        printf("[DIV EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_LSHIFT){
        printf("[LT LT]\n");
        return;
    }

    if(token->type == TOKEN_RSHIFT){
        printf("[GT GT]\n");
        return;
    }

    if(token->type == TOKEN_LSHIFTEQ){
        printf("[LT LT EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_RSHIFTEQ){
        printf("[GT GT EQUAL]\n");
        return;
    }


    if(token->type == TOKEN_MAIN){
        printf("[MAIN]\n");
        return;
    }

    if(token->type == TOKEN_FUNC){
        printf("[FUNCTION]\n");
        return;
    }

    if(token->type == TOKEN_RET){
        printf("[RETURN]\n");
        return;
    }

    if(token->type == TOKEN_VAR){
        printf("[VAR]\n");
        return;
    }

    if(token->type == TOKEN_IF){
        printf("[IF]\n");
        return;
    }

    if(token->type == TOKEN_ELSE){
        printf("[ELSE]\n");
        return;
    }


    if(token->type == TOKEN_PLUS){
        printf("[PLUS]\n");
        return;
    }

    if(token->type == TOKEN_MINUS){
        printf("[MINUS]\n");
        return;
    }

    if(token->type == TOKEN_MUL){
        printf("[MUL]\n");
        return;
    }

    if(token->type == TOKEN_DIV){
        printf("[DIV]\n");
        return;
    }

    if(token->type == TOKEN_EQUAL){
        printf("[EQUAL]\n");
        return;
    }

    if(token->type == TOKEN_GT){
        printf("[GT]\n");
        return;
    }

    if(token->type == TOKEN_LT){
        printf("[LT]\n");
        return;
    }

    if(token->type == TOKEN_NOT){
        printf("[NOT]\n");
        return;
    }

    if(token->type == TOKEN_AND){
        printf("[AND]\n");
        return;
    }

    if(token->type == TOKEN_OR){
        printf("[OR]\n");
        return;
    }

    if(token->type == TOKEN_XOR){
        printf("[XOR]\n");
        return;
    }


    if(token->type == TOKEN_LPAREN){
        printf("[LPAREN]\n");
        return;
    }

    if(token->type == TOKEN_RPAREN){
        printf("[RPAREN]\n");
        return;
    }

    if(token->type == TOKEN_LBRACE){
        printf("[LBRACE]\n");
        return;
    }

    if(token->type == TOKEN_RBRACE){
        printf("[RBRACE]\n");
        return;
    }

    if(token->type == TOKEN_LBRACKET){
        printf("[LBRACKET]\n");
        return;
    }

    if(token->type == TOKEN_RBRACKET){
        printf("[RBRACKET]\n");
        return;
    }

    if(token->type == TOKEN_SEMICOLON){
        printf("[SEMICOLON]\n");
        return;
    }


    if(token->type == TOKEN_EOF){
        printf("[EOF]\n");
        return;
    }

    printf("[UNKNOWN TOKEN] -> %s\n", token->word);
}