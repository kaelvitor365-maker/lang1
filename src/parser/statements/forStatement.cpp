#include "parser.hpp"

#include <iostream>
#include <format>


Node Parser::forStatement(){

    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_FOR);

    this->consume(TokenType::TOKEN_LPAREN);


    Node initializer = this->forInitializer();

    this->consume(TokenType::TOKEN_SEMICOLON);


    Node condition = this->expression();

    this->consume(TokenType::TOKEN_SEMICOLON);


    Node increment = this->forAssignment();

    this->consume(TokenType::TOKEN_RPAREN);


    Node body = this->statement();


    return Node{
        Stmt<ast::loop::For>{
            line,
            std::make_unique<Node>(std::move(initializer)),
            std::make_unique<Node>(std::move(condition)),
            std::make_unique<Node>(std::move(increment)),
            std::make_unique<Node>(std::move(body))
        }
    };
}



Node Parser::forInitializer(){

    if(this->check(TokenType::TOKEN_VAR)){
        return this->forVariableDeclaration();
    }


    return this->forAssignment();
}



Node Parser::forAssignment(){

    std::size_t line = this->current.line;


    Node target = this->primary();


    if(this->match(TokenType::TOKEN_EQUAL)){

        Node expression = this->expression();


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



Node Parser::forVariableDeclaration(){

    std::size_t line = this->current.line;


    this->consume(TokenType::TOKEN_VAR);


    Node target = this->primary();



    this->consume(TokenType::TOKEN_COLON);


    Node type = this->primary();


    std::unique_ptr<Node> initializer = nullptr;


    if(this->match(TokenType::TOKEN_EQUAL)){

        initializer = std::make_unique<Node>(
            this->expression()
        );
    }


    return Node{
        Stmt<ast::VariableDeclaration>{
            line,
            std::make_unique<Node>(std::move(target)),
            std::make_unique<Node>(std::move(type)),
            std::move(initializer)
        }
    };
}