#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <optional>

Token Lexer::string(){
    std::string word;


    if(this->it == this->end){
        return Token{
            .type = TokenType::TOKEN_INCOMPLETED_STRING,
            .line = this->line,
            .value = std::monostate{}
        };
    }


    while(*this->it != '"'){
        if(this->it == this->end){
            return Token{
                .type = TokenType::TOKEN_INCOMPLETED_STRING,
                .line = this->line,
                .value = std::monostate{}
            };
        }
        word.push_back(*(this->it++));
    }

    ++this->it;

    return Token{
        .type = TokenType::TOKEN_STRING,
        .line = this->line,
        .value = std::move(word)
    };
}