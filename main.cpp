#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "ASTprinter.hpp"
int main(int argc, char* args[]){
    if(argc < 2){
        std::cerr << "Error, need a arquive.lang to tokenize\n";
        return 1;
    }

    Lexer lexer(args[1]);
    Parser parser(lexer);
    Node node = parser.parse();
    std::cout << node << std::endl;


}