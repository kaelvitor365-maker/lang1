#pragma once

namespace ast {
    struct Number final {};
    struct String final {};
    struct Identifier final {};
    struct Boolean final {};
    struct Binary final {};
    struct Unary final {};
    struct Call final {};
    struct EndOfFile final {};
}

namespace ast {
    struct VariableDeclaration final {};
    struct Assignment final {};
    struct If final {};
    
    namespace loop {
        struct While final {};
        struct doWhile final {};
        struct For final {};
        struct Break final {};
        struct Continue final {};
    }


    struct Return final {};
    struct Block final {};

    struct Nothing final {};
}
