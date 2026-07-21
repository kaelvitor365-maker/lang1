#pragma once

#include <utility>
#include <memory>
#include "token.hpp"

struct Node;

namespace ast {
    struct Number final {};
    struct String final {};
    struct Identifier final {};
    struct Boolean final {};
    struct Binary final {};
    struct Unary final {};
}
template <typename T>
struct Expr {};

template <>
struct Expr<ast::Number> {
    std::uint64_t number;
    std::size_t line;
    Expr(std::uint64_t number, std::size_t line) :
        number(number), line(line)
    {}
};

template <>
struct Expr<ast::String> {
    std::string str;
    std::size_t line;
    Expr(std::string str, std::size_t line) :
        str(std::move(str)), line(line)
    {}
};

template <>
struct Expr<ast::Identifier> {
    std::string name;
    std::size_t line;
    Expr(std::string name, std::size_t line) :
        name(std::move(name)), line(line)
    {}
};

template <>
struct Expr<ast::Boolean> {
    bool boolean;
    std::size_t line;
    Expr(bool boolean, std::size_t line) :
        boolean(boolean), line(line)
    {}
};

template <>
struct Expr<ast::Unary> {
    TokenType operation;
    std::size_t line;
    std::unique_ptr<Node> expression;
    Expr(TokenType operation, std::size_t line, std::unique_ptr<Node> expression) :
        operation(operation), line(line), expression(std::move(expression))
    {}
};

template<>
struct Expr<ast::Binary> {
    TokenType operation;
    std::size_t line;
    std::unique_ptr<Node> left, right;
    Expr(TokenType operation, std::size_t line, std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
        operation(operation), line(line), left(std::move(left)), right(std::move(right))
    {}
};

