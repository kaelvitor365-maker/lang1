#include <iostream>
#include "lexer.hpp"
int main(void){
    Lexer lexer("lang_arqs/test.lang");
    while(true){
        Token token = lexer.nextToken();
        std::cout << token << std::endl;
        if(token.type == TokenType::TOKEN_EOF) break;
    }
}