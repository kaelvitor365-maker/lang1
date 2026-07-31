#include "parser.hpp"

Node Parser::postfix(){

    Node expr = this->primary();

    while(this->check(TokenType::TOKEN_LPAREN)){

        std::size_t line = this->current.line;
        this->advance();

        expr = this->finishCall(std::move(expr), line);

    }

    return expr;

}

Node Parser::finishCall(Node callee, std::size_t line){

    std::vector<std::unique_ptr<Node>> arguments{};

    if(!this->check(TokenType::TOKEN_RPAREN)){

        do{

            Node argument = this->expression();

            arguments.push_back(
                std::make_unique<Node>(std::move(argument))
            );

        }while(this->match(TokenType::TOKEN_COMMA));
        
    }
    this->consume(TokenType::TOKEN_RPAREN);

    return Node{
        Expr<ast::Call>{
            line,
            std::make_unique<Node>(std::move(callee)),
            std::move(arguments)
        }
    };
}