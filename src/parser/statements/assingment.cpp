#include "parser.hpp"


Node Parser::assignment(){

    std::size_t line = this->current.line;

    Node target = this->expression();

    if(this->match(TokenType::TOKEN_EQUAL)){

        Node expression = this->expression();

        this->consume(TokenType::TOKEN_SEMICOLON);

        return Node{
            Stmt<ast::Assignment>{
                line,
                std::make_unique<Node>(std::move(target)),
                std::make_unique<Node>(std::move(expression))
            }
        };
    }

    return target;
}