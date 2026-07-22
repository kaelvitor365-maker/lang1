#include "parser.hpp"

Node Parser::logical(){

    Node left = this->comparison();

    while(
        this->check(TokenType::TOKEN_ANDAND) ||
        this->check(TokenType::TOKEN_OROR)
    ){
        TokenType operation = this->current.type;
        std::size_t line = this->current.line;

        this->advance();

        Node right = this->comparison();

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