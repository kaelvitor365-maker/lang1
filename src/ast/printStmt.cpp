#include "ASTprinter.hpp"

void ast::details::printer::print(const Stmt<ast::VariableDeclaration>& stmt){

    this->str += std::format("{0}Variable Declaration: \n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;

    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += std::format("{0}target:\n", this->putSpace());
    this->str += this->putSpace() + "{\n"; ++this->spaces;
    this->print(*stmt.target); --this->spaces;
    this->str += this->putSpace() + "}\n";


    this->str += this->putSpace() + "type:\n";
    this->str += this->putSpace() + "{\n"; ++this->spaces;
    this->print(*stmt.type); --this->spaces;
    this->str += this->putSpace() + "}\n";

    this->str += this->putSpace() + "initializer:\n";
    this->str += this->putSpace() + "{\n"; ++this->spaces;
    if(stmt.initializer != nullptr){
        this->print(*stmt.initializer); --this->spaces;
    }
    else{
        this->str += this->putSpace() + "null\n"; --this->spaces;
    }
    this->str += this->putSpace() + "}\n"; --this->spaces;

    this->str += std::format("{0}{1}\n", this->putSpace(), '}');

}

void ast::details::printer::print(const Stmt<ast::Assignment>& stmt){

    this->str += this->putSpace() + "Assignment:\n" + this->putSpace() + "{\n"; ++this->spaces;

    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += this->putSpace() + "target:\n";
    this->str += this->putSpace() + "{\n"; ++this->spaces;
    this->print(*stmt.target); --this->spaces;
    this->str += this->putSpace() + "}\n";

    this->str += this->putSpace() + "expression:\n";
    this->str += this->putSpace() + "{\n"; ++this->spaces;
    this->print(*stmt.expression); --this->spaces;
    this->str += this->putSpace() + "}\n"; --this->spaces;

    this->str += this->putSpace() + "}\n";

}

void ast::details::printer::print(const Stmt<ast::Block>& stmt){

    this->str += this->putSpace() + "Block:\n" + this->putSpace() + "{\n"; ++this->spaces;
    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += this->putSpace() + "statements:\n" + this->putSpace() + "{\n"; ++this->spaces;
    for(std::size_t i = 0; i < stmt.statements.size(); ++i)
        this->print(*stmt.statements[i]);
    --this->spaces; this->str += this->putSpace() + "}\n"; --this->spaces;

    this->str += this->putSpace() + "}\n";

}

void ast::details::printer::print(const Stmt<ast::If>& stmt){

    this->str += this->putSpace() + "If:\n" + this->putSpace() + "{\n"; ++this->spaces;
    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += std::format("{0}condition:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    this->print(*stmt.condition);
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}then branch:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    this->print(*stmt.thenBranch);
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}else branch:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    if(stmt.elseBranch != nullptr){
        this->print(*stmt.elseBranch);
    }
    else{
        this->str += this->putSpace() + "null\n";
    }
    --this->spaces; this->str += this->putSpace() + "}\n";

    --this->spaces; this->str += this->putSpace() + "}\n";
    
}

void ast::details::printer::print(const Stmt<ast::While>& stmt){

    this->str += this->putSpace() + "While:\n" + this->putSpace() + "{\n"; ++this->spaces;
    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += std::format("{0}condition:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    this->print(*stmt.condition);
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}block:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    this->print(*stmt.block);
    --this->spaces; this->str += this->putSpace() + "}\n";

    --this->spaces; this->str += this->putSpace() + "}\n";

}

void ast::details::printer::print(const Stmt<ast::For>& stmt){

    this->str += this->putSpace() + "For:\n" + this->putSpace() + "{\n"; ++this->spaces;
    this->str += std::format("{0}line: {1}\n", this->putSpace(), stmt.line);

    this->str += std::format("{0}initializer:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    if(stmt.initializer != nullptr){
        this->print(*stmt.initializer);
    }
    else{
        this->str += this->putSpace() + "null\n";
    }
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}condition:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    if(stmt.condition != nullptr){
        this->print(*stmt.condition);
    }
    else{
        this->str += this->putSpace() + "null\n";
    }
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}increment:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    if(stmt.increment != nullptr){
        this->print(*stmt.increment);
    }
    else{
        this->str += this->putSpace() + "null\n";
    }
    --this->spaces; this->str += this->putSpace() + "}\n";

    this->str += std::format("{0}block:\n{0}{1}\n", this->putSpace(), '{'); ++this->spaces;
    if(stmt.block != nullptr){
        this->print(*stmt.block);
    }
    else{
        this->str += this->putSpace() + "null\n";
    }
    --this->spaces; this->str += this->putSpace() + "}\n";

    --this->spaces; this->str += this->putSpace() + "}\n";

}

