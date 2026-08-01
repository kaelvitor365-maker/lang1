#include "parser.hpp"


Node Parser::block(){
    std::size_t line = this->current.line;
    this->consume(TokenType::TOKEN_LBRACE);

    std::vector<std::unique_ptr<Node>> statements;

    while(!this->check(TokenType::TOKEN_RBRACE) &&
        !this->check(TokenType::TOKEN_EOF)
    ){
        statements.push_back(std::make_unique<Node>(this->statement()));
    }

    this->consume(TokenType::TOKEN_RBRACE);

    return Node{
        Stmt<ast::Block>{
            line,
            std::move(statements)
        }
    };

}