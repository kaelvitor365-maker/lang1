#include <stdexcept>
#include <iostream>
#include "parser.hpp"

Node Parser::nothingStatement(){
    std::size_t line = this->current.line;
    this->consume(TokenType::TOKEN_NOTHING);
    this->consume(TokenType::TOKEN_SEMICOLON);
    return Node{
        Stmt<ast::Nothing>{
            line
        }
    };
}

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
            << "Expected: " << details::token_names[static_cast<std::size_t>(token)]
            << "\nGot: " << details::token_names[static_cast<std::size_t>(this->current.type)]
            << "\nLine: " << current.line
            << "\n";

        throw std::runtime_error("Unexpected token");
    }

    advance();
}

Node Parser::expression(){
    return this->logical();
}
Node Parser::statement(){

    if(this->check(TokenType::TOKEN_VAR)){
        return this->variableDeclaration();
    }

    if(this->check(TokenType::TOKEN_IF)){
        return this->ifStatement();
    }

    if(this->check(TokenType::TOKEN_WHILE)){
        return this->whileStatement();
    }

    if(this->check(TokenType::TOKEN_FOR)){
        return this->forStatement();
    }

    if(this->check(TokenType::TOKEN_NOTHING)){
        return this->nothingStatement();
    }

    if(this->check(TokenType::TOKEN_LBRACE)){
        return this->block();
    }

    if(this->check(TokenType::TOKEN_BREAK)){
        return this->breakStatement();
    }

    if(this->check(TokenType::TOKEN_CONTINUE)){
        return this->continueStatement();
    }

    return this->assignment();
}

std::vector<std::unique_ptr<Node>> Parser::parse(){
    std::vector<std::unique_ptr<Node>> statements;

    while(!this->check(TokenType::TOKEN_EOF)){
        statements.push_back(std::make_unique<Node>(this->statement()));
    }

    return statements;  
}






