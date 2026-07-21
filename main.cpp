#include <iostream>
#include "lexer.hpp"
int main(int argc, char* args[]){
    if(argc < 2){
        std::cerr << "Error, need a arquive.lang to tokenize\n";
        return 1;
    }

    Lexer lexer(args[1]);
    while(true){
        Token token = lexer.nextToken();

        std::cout << token << std::endl;

        if(!token) break;
    }
}