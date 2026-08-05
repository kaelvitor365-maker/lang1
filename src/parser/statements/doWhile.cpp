#include "parser.hpp"

Node Parser::doWhileStatement(){

    std::size_t line = this->current.line;
    this->consume(TokenType::TOKEN_DO_WHILE);

    Node body = this->statement();

    this->consume(TokenType::TOKEN_WHILE);
    this->consume(TokenType::TOKEN_LPAREN);
    Node condition = this->expression();
    this->consume(TokenType::TOKEN_RPAREN);

    this->consume(TokenType::TOKEN_SEMICOLON);

    return Node{
        Stmt<ast::loop::doWhile>{
            line,
            std::make_unique<Node>(std::move(body)),
            std::make_unique<Node>(std::move(condition))
        }
    };
}