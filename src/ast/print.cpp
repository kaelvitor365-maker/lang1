#include "ASTprinter.hpp"


void ast::details::printer::print(const Node& expr){
    std::visit([&](auto&& value){
        this->print(value);
    }
    ,expr.value);
}
void ast::details::printer::print(const Expr<ast::Number>& expr){

    this->str += std::format("{}Number:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}number: {}\n", this->putSpace(), expr.number);
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');

}


void ast::details::printer::print(const Expr<ast::String>& expr){

    this->str += std::format("{}String:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}str: {}\n", this->putSpace(),expr.str);
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');

}


void ast::details::printer::print(const Expr<ast::Boolean>& expr){

    this->str += std::format("{}Boolean:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}boolean: {}\n", this->putSpace(), expr.boolean ? "true" : "false");
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');

}



void ast::details::printer::print(const Expr<ast::Identifier>& expr){

    this->str += std::format("{}Identifier:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}identifier: {}\n", this->putSpace(), expr.name);
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');

}


void ast::details::printer::print(const Expr<ast::Unary>& expr){
    
    this->str += std::format("{}Unary: {}\n{}{}", this->putSpace(), expr.operation, this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    this->str += std::format("{}expression:\n{}{}", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->print(*expr.expression); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}'); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
}


void ast::details::printer::print(const Expr<ast::Call>& expr){
    this->str += std::format("{}Call:\n{}{}\n", this->putSpace(), this->putSpace(), '{');++this->spaces;
    this->str += std::format("{}callee:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->print(*expr.callee); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
    this->str += std::format("{}arguments:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    for(std::size_t i = 0; i < expr.arguments.size(); ++i)
        this->print(*expr.arguments[i]);
    this->str += std::format("{}{}\n", this->putSpace(), '}'); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
}


void ast::details::printer::print(const Expr<ast::Binary>& expr){

    this->str += std::format("{}Binary: {}\n{}{}\n", this->putSpace(), expr.operation, this->putSpace(), '{'); ++this->spaces;
    this->str += std::format("{}line: {}\n", this->putSpace(), expr.line);
    this->str += std::format("{}left:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces; 
    this->print(*expr.left); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
    this->str += std::format("{}right:\n{}{}\n", this->putSpace(), this->putSpace(), '{'); ++this->spaces;
    this->print(*expr.right); --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
    --this->spaces;
    this->str += std::format("{}{}\n", this->putSpace(), '}');
}

void ast::details::printer::print(const Expr<ast::EndOfFIle>& expr){
    this->str += std::format("{}EOF:\n", this->putSpace()); ++this->spaces;
    this->str += std::format("{}line:\n", expr.line); --this->spaces;
}