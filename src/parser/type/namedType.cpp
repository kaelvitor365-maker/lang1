#include "parser.hpp"

Node Parser::namedType(){
    

    std::string name = std::get<std::string>(this->current.value);
    std::size_t line = this->current.line;

    this->consume(TokenType::TOKEN_IDENTIFIER);

    std::size_t arrayDepth = 0;

    while(this->check(TokenType::TOKEN_LBRACKET)){
        this->advance();
        this->consume(TokenType::TOKEN_RBRACKET);
        arrayDepth++;
    }

    return Node{
        Type<ast::type::NamedType>{
            line,
            name,
            arrayDepth
        }
    };

}