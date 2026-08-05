#pragma once
#include "token.hpp"
#include "lexer.hpp"
#include "node.hpp"
#include <memory>
#include <unordered_map>


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
    Node compoundAssignment();
    Node block();
    Node ifStatement();
    Node whileStatement();
    Node doWhileStatement();
    Node forStatement();
    Node forInitializer();
    Node forAssignment();
    Node forVariableDeclaration();
    Node nothingStatement();
    Node breakStatement();
    Node continueStatement();

    //** TYPE **/
    Node type();
    Node namedType();

    //** UTILITYS **//
    void advance();
    bool check(TokenType token);
    bool match(TokenType token);
    void consume(TokenType token);
    Node finishCall(Node callee, std::size_t line);


    std::unordered_map<TokenType, TokenType> compoundAssignmentOperators{
        {TokenType::TOKEN_PLUSEQ, TokenType::TOKEN_PLUS},
        {TokenType::TOKEN_MINUSEQ, TokenType::TOKEN_MINUS},
        {TokenType::TOKEN_MULEQ, TokenType::TOKEN_MUL},
        {TokenType::TOKEN_DIVEQ, TokenType::TOKEN_DIV},
        {TokenType::TOKEN_MODEQ, TokenType::TOKEN_MOD}
    };

    Lexer& lexer;
    Token current;
};

