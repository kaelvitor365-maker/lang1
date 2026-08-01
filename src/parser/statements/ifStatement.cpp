#include "parser.hpp"

Node Parser::ifStatement(){

    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_IF);
    
    this->consume(TokenType::TOKEN_LPAREN);
    Node expr = this->expression();
    this->consume(TokenType::TOKEN_RPAREN);

    return Node{
        Stmt<ast::If>{
            line,
            std::make_unique<Node>(std::move(expr)),
            std::make_unique<Node>(std::move(this->block()))
        }
    };
}