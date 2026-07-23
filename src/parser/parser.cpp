#include <stdexcept>
#include <iostream>
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

        std::cerr 
            << "Expected: " << static_cast<int>(token)
            << "\nGot: " << details::token_names[static_cast<std::size_t>(this->current.type)]
            << "\nLine: " << current.line
            << "\n";

        throw std::runtime_error("Unexpected token");
    }

    advance();
}

Node Parser::expression(){
    return this->comparison();
}

Node Parser::parse(){
    return this->expression();
}






