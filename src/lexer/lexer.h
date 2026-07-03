#include "def.h"
#include "vector.h"

ENUM(TokenType,
    TOKEN_IDENTIFIER,
    TOKEN_MAIN,
    TOKEN_FUNC,
    TOKEN_RET,
    TOKEN_COLON,

    TOKEN_VAR,

    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_INFWHILE,
    TOKEN_BREAK,
    TOKEN_CONTINUE,

    TOKEN_SEMICOLON,

    TOKEN_DOT,

    TOKEN_GT,
    TOKEN_LT,

    TOKEN_NOT,
    TOKEN_NOTB,
    TOKEN_EQUAL,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_XOR,

    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_LBRACE,
    TOKEN_RBRACE,

    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_BOOL,
    TOKEN_STR,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DIV,
    TOKEN_MUL,
    TOKEN_LSHITF,
    TOKEN_RSHIFT,

    TOKEN_EQEQ,
    TOKEN_GTEQ,
    TOKEN_LTEQ,
    TOKEN_NOTEQ,
    TOKEN_ANDAND,
    TOKEN_OROR,

    TOKEN_PLUSEQ,
    TOKEN_MINUSEQ,
    TOKEN_MULEQ,
    TOKEN_DIVEQ,
    TOKEN_LSHIFTEQ,
    TOKEN_RSHIFTEQ,


    TOKEN_UNDEFINED,
    TOKEN_EOF
)

CLASS(Token, {
    TokenType type;
    size_t line;
    char word[1 << 8];  
})

CLASS(Lexer, {
    char* file;
    char* pos;
    size_t line;
})

Lexer* newLexer(const char* __arq);

void* freeLexer(Lexer* this);

Token* Lexer__LexerNext(Lexer* this);