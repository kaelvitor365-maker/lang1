#include "parser.hpp"

Node Parser::ifStatement(){

    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_IF);
    
    this->consume(TokenType::TOKEN_LPAREN);
    Node expr = this->expression();
    this->consume(TokenType::TOKEN_RPAREN);

    Node thenBranch = this->block();

    std::unique_ptr<Node> elseBranch = nullptr;

    if(this->match(TokenType::TOKEN_ELSE)) {

        elseBranch = (this->check(TokenType::TOKEN_IF)) ?
            std::make_unique<Node>(this->ifStatement()) :
            std::make_unique<Node>(this->block());
    }

    return Node{
        Stmt<ast::If>{
            line,
            std::make_unique<Node>(std::move(expr)),
            std::make_unique<Node>(std::move(thenBranch)),
            std::move(elseBranch)
        }
    };
}