#include "ASTprinter.hpp"


std::string ast::details::printer::putSpace(){
    std::string word;
    for(std::size_t i = 0; i < this->spaces; ++i)
        word.append(" |-");
    return word;
}

std::ostream& operator<<(std::ostream& os, Node& node){

    os << std::format("{}", node);
    return os;
}