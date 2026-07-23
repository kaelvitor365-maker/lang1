#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "ASTprinter.hpp"
int main(int argc, char* args[]){
    if(argc < 2){
        std::cerr << "Error, need a arquive.lang to tokenize\n";
        return 1;
    }

    if(argc == 2){
        Lexer lexer(args[1]);
        Parser parser(lexer);
        Node node = parser.parse();
        std::cout << node << std::endl;

        return 0;
    }

    if(std::string{args[1]} == "--Tokenize"){
        Lexer lexer(args[2]);
        while(true){

            Token token = lexer.nextToken();
            std::cout << token << std::endl;
            if(!token) break;
        }
        return 0;
    }

    if(std::string{args[1]} == "--Parserize"){
        Lexer lexer(args[2]);
        Parser parser(lexer);
        Node node = parser.parse();
        std::cout << node << std::endl;
    }


}