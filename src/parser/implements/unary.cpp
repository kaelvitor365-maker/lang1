#include "parser.hpp"

Node Parser::unary(){
    if(
        this->check(TokenType::TOKEN_MINUS) ||
        this->check(TokenType::TOKEN_NOT) ||
        this->check(TokenType::TOKEN_NOTB)
    ){
        Token operation  = this->current;
        this->advance();

        Node expression = this->unary();

        return Node{
            Expr<ast::Unary>{
                operation.type,
                operation.line,
                std::make_unique<Node>(std::move(expression))
            }
        };
    }

    return this->postfix();
}