#include <stdexcept>
#include "parser.hpp"

void Parser::advance(){
    this->current = this->lexer.nextToken();
}

bool Parser::check(TokenType token){
    return this->current.type == token;
}

bool Parser::match(TokenType token){
    
    if(!this->check(token)) return false;

    this->advance();
    return true;
}


void Parser::consume(TokenType token){
    if(!check(token)){
        throw std::runtime_error("Unexpected token");
    }

    advance();
}

Node Parser::expression(){
    return this->primary();
}

Node Parser::primary(){

    if(this->match(TokenType::TOKEN_LPAREN)){
        Node node = expression();
        consume(TokenType::TOKEN_RPAREN);

        return node;
    }

    if(this->check(TokenType::TOKEN_BOOL)){
        auto boolean = std::get<bool>(this->current.value);
        advance();

        return Node{
            expr::Boolean{boolean}
        };
    }

    if(this->check(TokenType::TOKEN_NUMBER)){
        auto number = std::get<std::uint64_t>(this->current.value);
        advance();

        return Node{
            expr::Number{number}
        };
    }
    if(this->check(TokenType::TOKEN_STRING)){
        auto str = std::move(std::get<std::string>(this->current.value));
        advance();

        return Node{
            expr::String{std::move(str)}
        };
    }
    if(this->check(TokenType::TOKEN_IDENTIFIER)){
        auto str = std::move(std::get<std::string>(this->current.value));
        advance();

        return Node{
            expr::Identifier{std::move(str)}
        };
    }
    
    throw std::runtime_error("Expected Expression");
}
