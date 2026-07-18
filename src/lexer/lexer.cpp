#include "lexer.hpp"
#include "lexer_utils.hpp"

//
Token Lexer::peekToken(){
    return this->currentToken;
}
Token Lexer::nextToken(){
    Token tempToken = this->currentToken;
    this->currentToken = this->scanToken();
    return tempToken;
}

void Lexer::skipSpaces(){
    while(this->it != this->end && details::isSpace(*this->it)){
        if(*this->it == '\n')
            ++this->line;
        ++this->it;
    }
}

Token Lexer::scanToken(){

    std::string word;
    this->skipSpaces();
    
    Token token;
    token.line = this->line;

    // EOF
    if(this->it == this->end){
        token.type = TokenType::TOKEN_EOF;
        return token;
    }

    //STRING
    if(*this->it == '"'){

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
    // SPECIAL CHARACTERS
    for(
        int i = 0;
        i < 3 && this->it != end && (
            !details::isSpace(*this->it) &&
            !details::isAlphaNumeric(*this->it)
        );
        ++i
    ){
        word.push_back(*it);
        ++this->it;
    }
    if(!word.empty()){
        std::optional<TokenType> temp_ret = this->functions[word.size()-1](word);
        if(temp_ret != std::nullopt){
            token.type = *temp_ret;
            return token;
        }
        token.type = TokenType::TOKEN_INVALID;
        token.value = word;
        return token;
    }


    // NUMBERS
    if(details::isDigit(*this->it)){
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

    //ALPHA'S
    if(details::isAlpha(*this->it)){
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

    return token;
}