#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <optional>

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