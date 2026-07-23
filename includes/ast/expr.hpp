#pragma once

#include <utility>
#include <memory>
#include <vector>
#include "ast.hpp"
#include "token.hpp"

struct Node;


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

template<>
struct Expr<ast::Call> {
    std::size_t line;
    std::unique_ptr<Node> callee;
    std::vector<std::unique_ptr<Node>> arguments;

    Expr(std::size_t line, std::unique_ptr<Node> callee, std::vector<std::unique_ptr<Node>> arguments) :
        line(line), callee(std::move(callee)), arguments(std::move(arguments))
    {}
};

template<>
struct Expr<ast::EndOfFIle> {
    std::size_t line;
    TokenType token;

    Expr(std::size_t line, TokenType token = TokenType::TOKEN_EOF) :
        line(line), token(token)
    {}
};

