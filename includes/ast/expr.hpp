#pragma once

#include <utility>
#include <memory>
#include "token.hpp"

struct Node;

namespace expr {
    struct Number final{
        std::uint64_t number;
        Number(std::uint64_t number) : number(number) {}
    };
    struct String final{
        std::string str;
        String(std::string str) : str(std::move(str)) {}
    };
    struct Identifier final{
        std::string name;
        Identifier(std::string name) : name(std::move(name)) {}
    };

    struct Boolean final{
        bool boolean;
        Boolean(bool boolean) : boolean(boolean) {}
    };
    struct Binary final{
        TokenType operation;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Binary(TokenType operation, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
            operation(operation), left(std::move(left)), right(std::move(right)) {}
    };
    struct Unary final{
        TokenType operation;
        std::unique_ptr<Node> expression;
        Unary (TokenType operation, std::unique_ptr<Node> expression) :
            operation(operation), expression(std::move(expression)) {}
    };
};