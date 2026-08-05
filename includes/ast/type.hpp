#include "ast.hpp"
#include <string>

template<typename T>
struct Type final {};

template<>
struct Type<ast::type::NamedType> final {
    std::string name;
    std::size_t line;
    std::size_t arrayDepth;

    Type(std::size_t line, std::string name, std::size_t arrayDepth = 0) :
        name(std::move(name)), line(line), arrayDepth(arrayDepth)
    {}
};