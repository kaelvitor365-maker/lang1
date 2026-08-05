#include "ASTprinter.hpp"

void ast::details::printer::print(const Type<ast::type::NamedType>& type){

    this->str += std::format(
        "{0}namedType:\n{0}{1}",
        this->putSpace(),
        '{'
    ); ++this->spaces;

    this->str += std::format(
        "\n{0}line: {1}",
        this->putSpace(),
        type.line
    );
    this->str += std::format(
        "\n{0}name: {1}",
        this->putSpace(),
        type.name
    );
    this->str += std::format(
        "\n{0}arrayDepth: {1}",
        this->putSpace(),
        type.arrayDepth
    );

    --this->spaces;
    this->str += std::format(
        "\n{0}{1}",
        this->putSpace(),
        '}'
    );
}