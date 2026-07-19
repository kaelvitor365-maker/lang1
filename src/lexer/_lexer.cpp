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
    Token token;

    ++this->it;

    if(this->it == this->end){
        token.type = TokenType::TOKEN_INCOMPLETED_STRING;
        token.value = "";
        return token;
    }


    while(*this->it != '"'){
        if(this->it == this->end){
            token.type = TokenType::TOKEN_INCOMPLETED_STRING;
            token.value = word;
            return token;
        }
        word.push_back(*(this->it++));
    }

    ++this->it;

    token.type = TokenType::TOKEN_STRING;
    token.value = word;
    return token;
}

Token Lexer::number(){
    std::string word;
    Token token;

    while(
        this->it != this->end &&
        details::isDigit(*this->it)
    ){
        word.push_back(*this->it);
        ++it;
    }
    token.type = TokenType::TOKEN_NUMBER;
    token.value = static_cast<std::uint64_t>(std::stoull(word));

    return token;
}

Token Lexer::alphaIdentfier(){
    std::string word;
    Token token;

    while(
        this->it != this->end &&
        details::isAlphaNumeric(*this->it)
    ){
        word.push_back(*this->it);
        ++this->it;
    }
    if(!this->keywords.contains(word)){

        if(word == "true" || word == "false"){
            token.type = TokenType::TOKEN_BOOL;
            token.value = word == "true";
            return token;
        }

        token.type = TokenType::TOKEN_IDENTIFIER;
        token.value = word;
        return token;
    }
    token.type = this->keywords.at(word);
    return token;
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
    this->specialCharacters(word_2);
}