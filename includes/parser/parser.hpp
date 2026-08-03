#pragma once
#include "token.hpp"
#include "lexer.hpp"
#include "node.hpp"
#include <memory>


class Parser final {
    public:
        explicit Parser(Lexer& lexer) : lexer(lexer), current(lexer.nextToken()) {}


        std::vector<std::unique_ptr<Node>> parse();
    private:

    //** EXPRESSIONS **//
    Node expression();
    Node primary();
    Node postfix();
    Node unary();
    Node factor();
    Node term();
    Node bitwise();
    Node comparison();
    Node logical();

    //** STATEMENTS **//
    Node statement();
    Node variableDeclaration();
    Node assignment();
    Node block();
    Node ifStatement();
    Node whileStatement();
    Node forStatement();
    Node forInitializer();
    Node forAssignment();
    Node forVariableDeclaration();
    Node nothingStatement();
    Node breakStatement();
    Node continueStatement();

    //** UTILITYS **//
    void advance();
    bool check(TokenType token);
    bool match(TokenType token);
    void consume(TokenType token);
    Node finishCall(Node callee, std::size_t line);


    Lexer& lexer;
    Token current;
};

