#include "lexer.hpp"
#include "lexer_utils.hpp"
#include <iterator>
void Lexer::scanToken(){

while(true){

        skipSpaces();

        if(it == end)
            break;


        if(
            *it == '/' &&
            std::next(it) != end &&
            *std::next(it) == '/'
        ){
            while(it != end && *it != '\n')
                ++it;

            continue;
        }



        if(
            *it == '/' &&
            std::next(it) != end &&
            *std::next(it) == '*'
        ){
            it += 2;

            while(it != end){

                if(
                    *it == '*' &&
                    std::next(it) != end &&
                    *std::next(it) == '/'
                ){
                    it += 2;
                    break;
                }

                if(*it == '\n')
                    ++line;

                ++it;
            }

            continue;
        }

        break;
    }

    // EOF
    if(this->it == this->end){

        this->buffer.push(Token{
            .type = TokenType::TOKEN_EOF,
            .line = this->line,
            .value = std::monostate{}
        });
        return;
    }

    //STRING
    if(*this->it == '"'){
        ++this->it;
        this->buffer.push(this->string());
        return;
    }

    // SPECIAL CHARACTERS
    if(!details::isAlphaNumeric(*this->it)){
        std::string word;
        for(int i = 0; i<3 &&
            this->it != this->end &&
            (
            !details::isSpace(*this->it) &&
            !details::isAlphaNumeric(*this->it)
            )
        ;++i){
            word.push_back(*this->it);
            ++it;
        }
        this->specialCharacters(word);
        return;
    }


    // NUMBERS
    if(details::isDigit(*this->it)){
        this->buffer.push(this->number());
        return;
    }

    //ALPHA'S
    if(details::isAlpha(*this->it)){
        this->buffer.push(this->alphaIdentfier());
        return;
    }

}

Token Lexer::peekToken(){
    return this->buffer.front();
}

Token Lexer::nextToken(){
    Token token = this->peekToken();
    this->buffer.pop();
    if(this->buffer.empty()){
        this->scanToken();
    }

    return token;
}