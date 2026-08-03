#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <optional>

Token Lexer::alphaIdentfier(){
    std::string word;

    while(
        this->it != this->end &&
        details::isAlphaNumeric(*this->it)
    ){
        word.push_back(*this->it);
        ++this->it;
    }
    if(!this->keywords.contains(word)){

        if(word == "true" || word == "false"){
            return Token{
                .type = TokenType::TOKEN_BOOL,
                .line = this->line,
                .value = word == "true"
            };
        }

        return Token{
            .type = TokenType::TOKEN_IDENTIFIER,
            .line = this->line,
            .value = std::move(word)
        };
    }
    return Token{
        .type = this->keywords.at(word),
        .line = this->line,
        .value = std::monostate{}
    };
}