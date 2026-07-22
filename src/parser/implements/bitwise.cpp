#include "parser.hpp"

Node Parser::bitwise(){
    Node left = this->term();

    while(
        this->check(TokenType::TOKEN_AND) ||
        this->check(TokenType::TOKEN_OR) ||
        this->check(TokenType::TOKEN_LSHIFT) ||
        this->check(TokenType::TOKEN_RSHIFT)
    ){
        TokenType current = this->current.type;
        std::size_t line = this->current.line;
        this->advance();

        Node right = this->term();

        left = Node{
            Expr<ast::Binary>{
                current,
                line,
                std::make_unique<Node>(std::move(left)),
                std::make_unique<Node>(std::move(right))
            }
        };
    }

    return left;
}