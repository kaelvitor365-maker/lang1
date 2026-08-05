#include "parser.hpp"

Node Parser::variableDeclaration(){

    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_VAR);

    Node target = this->primary();

    this->consume(TokenType::TOKEN_COLON);

    Node type = this->type();

    std::unique_ptr<Node> initializer = nullptr;

    if(this->match(TokenType::TOKEN_EQUAL)){
        initializer = std::make_unique<Node>(this->expression());
    }

    this->consume(TokenType::TOKEN_SEMICOLON);
    
    return Node{
        Stmt<ast::VariableDeclaration>{
            line,
            std::make_unique<Node>(std::move(target)),
            std::make_unique<Node>(std::move(type)),
            std::move(initializer)
        }
    };

}