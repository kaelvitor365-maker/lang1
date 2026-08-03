#include "parser.hpp"

Node Parser::breakStatement(){

    std::size_t line = this->current.line;
    this->consume(TokenType::TOKEN_BREAK);
    this->consume(TokenType::TOKEN_SEMICOLON);

    return Node{
        Stmt<ast::loop::Break>{
            line
        }
    };
}

Node Parser::continueStatement(){

    std::size_t line = this->current.line;
    this->consume(TokenType::TOKEN_CONTINUE);
    this->consume(TokenType::TOKEN_SEMICOLON);

    return Node{
        Stmt<ast::loop::Continue>{
            line
        }
    };
}