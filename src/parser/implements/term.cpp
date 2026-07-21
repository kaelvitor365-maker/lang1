#include "parser.hpp"

Node Parser::term(){

    Node left = this->factor();

    while(
        this->check(TokenType::TOKEN_PLUS) ||
        this->check(TokenType::TOKEN_MINUS)
    ){
        TokenType operation = this->current.type;
        std::size_t line = this->current.line;

        this->advance();

        Node right = this->factor();

        left = Node{
            Expr<ast::Binary>{
                operation,
                line,
                std::make_unique<Node>(std::move(left)),
                std::make_unique<Node>(std::move(right))
            }
        };
    }


    return left;

}