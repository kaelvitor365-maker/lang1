#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <optional>

Token Lexer::number(){
    std::string word;

    while(
        this->it != this->end &&
        details::isDigit(*this->it)
    ){
        word.push_back(*this->it);
        ++it;
    }


    return Token{
        .type = TokenType::TOKEN_NUMBER,
        .line = this->line,
        .value = static_cast<std::uint64_t>(std::stoull(word))
    };
}