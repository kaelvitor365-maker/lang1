#include "token.hpp"

std::ostream& operator<<(std::ostream& os, const Token& token){
    os << std::format("{}", token);
    return os;
}