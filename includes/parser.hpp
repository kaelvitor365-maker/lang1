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
    Node postfix();
    Node unary();
    Node factor();
    Node term();
    Node bitwise();
    Node comparison();
    Node logical();
    
    void advance();
    bool check(TokenType token);
    bool match(TokenType token);
    void consume(TokenType token);
    Node finishCall(Node callee, std::size_t line);


    Lexer& lexer;
    Token current;
};