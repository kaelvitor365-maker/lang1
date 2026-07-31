#include "parser.hpp"

Node Parser::factor(){
    
    Node left = this->unary();

    while(this->check(TokenType::TOKEN_MUL) || this->check(TokenType::TOKEN_DIV)){
        TokenType operation = this->current.type;
        std::size_t line = this->current.line;

        this->advance();

        Node right = this->unary();

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