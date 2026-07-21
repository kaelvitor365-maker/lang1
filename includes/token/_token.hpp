#pragma once

#include <array>
#include <string>
#include <string_view>
/// @brief Represents all token categories recognized by the lexer.
enum class TokenType {
    /// @name Keywords
    /// @{
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
    /// @}

    /// @name Literals
    /// @{
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_BOOL,
    /// @}


    /// @name Arithmetic operators
    /// @{
    TOKEN_PLUS,
    TOKEN_INC,
    TOKEN_DEC,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    /// @}

    /// @name Assignment operators
    /// @{
    TOKEN_EQUAL,
    TOKEN_INFERED_TYPE,
    TOKEN_PLUSEQ,
    TOKEN_MINUSEQ,
    TOKEN_MULEQ,
    TOKEN_DIVEQ,
    /// @}

    /// @name Comparison operators
    /// @{
    TOKEN_GT,
    TOKEN_LT,
    TOKEN_GTEQ,
    TOKEN_LTEQ,
    TOKEN_EQEQ,
    TOKEN_NOTEQ,
    /// @}

    /// @name Logical operators
    /// @{
    TOKEN_AND,
    TOKEN_ANDAND,
    TOKEN_OR,
    TOKEN_OROR,
    TOKEN_NOT,
    /// @}

    /// @name Bitwise operators
    /// @{
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
    /// @}

    /// @name Delimiters
    /// @{
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
    /// @}

    /// @name Special tokens
    /// @{
    TOKEN_EOF,
    TOKEN_INCOMPLETED_STRING,
    TOKEN_INVALID,
    /// @}

    TOKEN_COUNT
};

namespace details {

    constexpr std::array<std::string_view, static_cast<std::size_t>(TokenType::TOKEN_COUNT)> token_names{

        // Keywords
        "TOKEN_MAIN",
        "TOKEN_FUNC",
        "TOKEN_RETURN",

        "TOKEN_VAR",

        "TOKEN_IF",
        "TOKEN_ELSE",

        "TOKEN_WHILE",
        "TOKEN_DO_WHILE",
        "TOKEN_FOR",

        "TOKEN_BREAK",
        "TOKEN_CONTINUE",

        // Literals
        "TOKEN_NUMBER",
        "TOKEN_STRING",
        "TOKEN_IDENTIFIER",
        "TOKEN_BOOL",

        // Arithmetic
        "TOKEN_PLUS",
        "TOKEN_INC",
        "TOKEN_DEC",
        "TOKEN_MINUS",
        "TOKEN_MUL",
        "TOKEN_DIV",

        // Assignment
        "TOKEN_EQUAL",
        "TOKEN_INFERED_TYPE",
        "TOKEN_PLUSEQ",
        "TOKEN_MINUSEQ",
        "TOKEN_MULEQ",
        "TOKEN_DIVEQ",

        // Comparison
        "TOKEN_GT",
        "TOKEN_LT",
        "TOKEN_GTEQ",
        "TOKEN_LTEQ",
        "TOKEN_EQEQ",
        "TOKEN_NOTEQ",

        // Logical
        "TOKEN_AND",
        "TOKEN_ANDAND",
        "TOKEN_OR",
        "TOKEN_OROR",
        "TOKEN_NOT",

        // Bitwise
        "TOKEN_XOR",
        "TOKEN_NOTB",
        "TOKEN_LSHIFT",
        "TOKEN_RSHIFT",
        "TOKEN_ANDEQ",
        "TOKEN_OREQ",
        "TOKEN_XOREQ",
        "TOKEN_NOTBEQ",
        "TOKEN_RSHIFTEQ",
        "TOKEN_LSHIFTEQ",

        // Delimiters
        "TOKEN_LPAREN",
        "TOKEN_RPAREN",
        "TOKEN_LBRACE",
        "TOKEN_RBRACE",
        "TOKEN_LBRACKET",
        "TOKEN_RBRACKET",

        "TOKEN_SEMICOLON",
        "TOKEN_COLON",
        "TOKEN_COMMA",
        "TOKEN_DOT",

        // Special
        "TOKEN_EOF",
        "TOKEN_INCOMPLETED_STRING",
        "TOKEN_INVALID"
    };

};