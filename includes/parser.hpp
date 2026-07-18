#pragma once
#include "token.hpp"
#include "lexer.hpp"
#include "node.hpp"
#include <memory>


class Parser final {
    public:
        explicit Parser(Lexer& lexer) : lexer(lexer), current(lexer.nextToken()) {}


        Node parse();
    private:

    Node expression();
    Node primary();
    void advance();
    bool check(TokenType token);
    bool match(TokenType token);
    void consume(TokenType token);


    Lexer& lexer;
    Token current;
};