#include "parser.hpp"

Node Parser::comparison(){
    
    Node left = this->bitwise();

    while(
        this->check(TokenType::TOKEN_EQEQ) ||
        this->check(TokenType::TOKEN_GT) ||
        this->check(TokenType::TOKEN_GTEQ) ||
        this->check(TokenType::TOKEN_LT) ||
        this->check(TokenType::TOKEN_LTEQ) ||
        this->check(TokenType::TOKEN_NOTEQ)
    ) {
        TokenType current = this->current.type;
        std::size_t line = this->current.line;

        this->advance();

        Node right = this->bitwise();

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