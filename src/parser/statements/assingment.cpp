#include "parser.hpp"

Node Parser::assignment(){

    std::size_t line = this->current.line;

    Node target = this->primary();


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


    if(this->compoundAssignmentOperators.contains(this->current.type)){

        TokenType op = this->compoundAssignmentOperators[this->current.type];

        this->advance();

        Node expression = this->expression();

        this->consume(TokenType::TOKEN_SEMICOLON);

        return Node{
            Stmt<ast::CompoundAssignment>{
                line,
                op,
                std::make_unique<Node>(std::move(target)),
                std::make_unique<Node>(std::move(expression))
            }
        };
    }

    this->consume(TokenType::TOKEN_SEMICOLON);
    return target;
}