#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <optional>
#include <string>
#include <utility>
#include <functional>
#include <variant>

void Lexer::skipSpaces(){
    while(this->it != this->end && details::isSpace(*this->it)){
        if(*this->it == '\n')
            ++this->line;
        ++this->it;
    }
}


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

void Lexer::specialCharacters(std::string word_1){
    
    if(!word_1.empty()){
        auto result = this->functions[word_1.size() -1](word_1);
        if(result.has_value()){
            this->buffer.push(Token{
                .type = *result,
                .line = this->line,
                .value = std::monostate{}
            });
        }
        else {
            if(word_1.size() == 1){
                this->buffer.push(Token{
                    .type = TokenType::TOKEN_INVALID,
                    .line = this->line,
                    .value = word_1
                });
                return;
            }
            else{
                std::string word_2;
                word_2.push_back(*word_1.rbegin());
                word_1.pop_back();
                this->specialCharacters(word_1, word_2);
                return;
            }
        }
        return;
    }
}

void Lexer::specialCharacters(std::string word_1, std::string word_2){
    this->specialCharacters(word_1);
    if(word_2.size() == 1 && word_2[0] == '"'){
        this->buffer.push(this->string());
    }
    else {
        this->specialCharacters(word_2);
    }
}