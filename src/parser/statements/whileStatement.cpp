#include "parser.hpp"
#include <iostream>

Node Parser::whileStatement(){

    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_WHILE);

    this->consume(TokenType::TOKEN_LPAREN);
    Node expr = this->expression();

    this->consume(TokenType::TOKEN_RPAREN);

    return Node{
        Stmt<ast::loop::While>{
            line,
            std::make_unique<Node>(std::move(expr)),
            std::make_unique<Node>(this->statement())
        }
    };
    
}