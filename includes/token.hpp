#pragma once

#include <variant>
#include <cstdint>
#include <string>
#include <cstddef>

enum class TokenType {
    // Keywords
    TOKEN_MAIN,
    TOKEN_FUNC,
    TOKEN_RETURN,

    TOKEN_VAR,

    TOKEN_IF,
    TOKEN_ELSE,

    TOKEN_WHILE,
    TOKEN_DO_WHILE,
    TOKEN_FOR,

    TOKEN_BREAK,
    TOKEN_CONTINUE,

    // Literals
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_BOOL,

    // Boolean
    TOKEN_TRUE,
    TOKEN_FALSE,
    
    // Arithmetic
    TOKEN_PLUS,
    TOKEN_INC,
    TOKEN_DEC,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,

    // Assignment
    TOKEN_EQUAL,
    TOKEN_PLUSEQ,
    TOKEN_MINUSEQ,
    TOKEN_MULEQ,
    TOKEN_DIVEQ,

    // Comparison
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_GTEQ,
    TOKEN_LTEQ,
    TOKEN_EQEQ,
    TOKEN_NOTEQ,

    // Logical
    TOKEN_AND,
    TOKEN_ANDAND,
    TOKEN_OR,
    TOKEN_OROR,
    TOKEN_NOT,

    // Bitwise
    TOKEN_XOR,
    TOKEN_NOTB,
    TOKEN_LSHIFT,
    TOKEN_RSHIFT,
    TOKEN_ANDEQ,
    TOKEN_OREQ,
    TOKEN_XOREQ,
    TOKEN_NOTBEQ,
    TOKEN_RSHIFTEQ,
    TOKEN_LSHIFTEQ,

    // Delimiters
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_SEMICOLON,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_DOT,

    // Special
    TOKEN_EOF,
    TOKEN_INCOMPLETED_STRING,
    TOKEN_INVALID
};

class Token {
    public:
        TokenType type = TokenType::TOKEN_INVALID;
        std::size_t line = 0;
        std::variant<
            std::monostate,
            std::uint64_t,
            std::string,
            bool
        > value{};
};