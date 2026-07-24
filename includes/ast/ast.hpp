#pragma once

namespace ast {
    struct Number final {};
    struct String final {};
    struct Identifier final {};
    struct Boolean final {};
    struct Binary final {};
    struct Unary final {};
    struct Call final {};
    struct EndOfFIle final {};
}

namespace ast {
    struct VariableDeclaration final {};
    struct Assignment final {};
    struct If final {};
    struct While final {};
    struct Return final {};
    struct Block final {};
    struct ExpressionAssignment final {}; 
}