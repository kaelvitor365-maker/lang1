#pragma once
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
    TOKEN_NUMBER,
    TOKEN_BOOL,
    TOKEN_STR,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_DIV,
    TOKEN_MUL,
    TOKEN_LSHIFT,
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
    TOKEN_INC,
    TOKEN_DEC,
    TOKEN_UNDEFINED,
    TOKEN_EOF
)

/**
 * @brief Representa um token gerado pelo lexer.
 * @param type  Tipo do token (TokenType)
 * @param line  Linha onde o token foi encontrado
 * @param word  Valor textual do token (máx 255 caracteres)
 */
CLASS(Token, {
    TokenType type;
    size_t line;
    char word[1 << 8];
})

/**
 * @brief Estado do lexer durante a tokenização.
 * @param file  Buffer com o conteúdo do arquivo fonte
 * @param pos   Ponteiro para o caractere atual
 * @param line  Linha atual
 */
CLASS(Lexer, {
    char* file;
    char* pos;
    size_t line;
})

/**
 * @brief Lê um arquivo fonte e inicializa o Lexer.
 * @param __arq Caminho para o arquivo
 * @return Ponteiro para o Lexer, ou NULL se falhar.
 */
Lexer* newLexer(const char* __arq);

/**
 * @brief Libera o Lexer e retorna NULL.
 * @param this Ponteiro para o Lexer
 * @return NULL
 */
void* freeLexer(Lexer* this);

/**
 * @brief Retorna o próximo token bruto do arquivo fonte (pass 1).
 * @param this Ponteiro para o Lexer
 * @return Ponteiro para o Token alocado, ou NULL se falhar.
 */
Token* Lexer__LexerNext(Lexer* this);

/// @brief Tokeniza o arquivo inteiro e retorna um Vector de tokens brutos.
/// @param this Ponteiro para o Lexer
/// @return Ponteiro para o Vector<Token*>, ou NULL se falhar.
_Vector* LexerVector(Lexer* this);