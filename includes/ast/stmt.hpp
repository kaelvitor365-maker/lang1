#pragma once

#include <cstddef>
#include <utility>
#include <memory>
#include <vector>
#include "token.hpp"

#include "ast.hpp"

struct Node;

template <typename T>
struct Stmt final {};

template<>
struct Stmt<ast::VariableDeclaration> final {
    std::size_t line;
    std::unique_ptr<Node> target;
    std::unique_ptr<Node> type;
    std::unique_ptr<Node> initializer;
    Stmt(std::size_t line, std::unique_ptr<Node> target, std::unique_ptr<Node> type, std::unique_ptr<Node> initializer = nullptr) :
        line(line), target(std::move(target)), type(std::move(type)), initializer(std::move(initializer))
    {}
};

template<>
struct Stmt<ast::Assignment> final {
    std::size_t line;
    std::unique_ptr<Node> target;
    std::unique_ptr<Node> expression;
    Stmt(std::size_t line, std::unique_ptr<Node> target, std::unique_ptr<Node> expression = nullptr) :
        line(line), target(std::move(target)), expression(std::move(expression))
    {}
};

template<>
struct Stmt<ast::Block> {
    std::size_t line;
    std::vector<std::unique_ptr<Node>> statements;

    Stmt(std::size_t line, std::vector<std::unique_ptr<Node>> statements) :
        line(line), statements(std::move(statements))
    {}
};




template<>
struct Stmt<ast::If> {
    std::size_t line;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> thenBranch;
    std::unique_ptr<Node> elseBranch;

    Stmt(std::size_t line, std::unique_ptr<Node> condition, std::unique_ptr<Node> thenBranch, std::unique_ptr<Node> elseBranch = nullptr) :
        line(line), condition(std::move(condition)), thenBranch(std::move(thenBranch)), elseBranch(std::move(elseBranch))
    {}
};

template<>
struct Stmt<ast::loop::While> {
    std::size_t line;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> body;

    Stmt(std::size_t line, std::unique_ptr<Node> condition, std::unique_ptr<Node> body) :
        line(line), condition(std::move(condition)), body(std::move(body))
    {}
};

template<>
struct Stmt<ast::loop::doWhile> {
    std::size_t line;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> body;

    Stmt(std::size_t line, std::unique_ptr<Node> body, std::unique_ptr<Node> condition) :
        line(line), condition(std::move(condition)), body(std::move(body))
    {}
};
template<>
struct Stmt<ast::loop::For> {
    std::size_t line;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> increment;
    std::unique_ptr<Node> body;

    Stmt(std::size_t line, std::unique_ptr<Node> initializer = nullptr, std::unique_ptr<Node> condition = nullptr, std::unique_ptr<Node> increment = nullptr, std::unique_ptr<Node> body = nullptr) :
        line(line), initializer(std::move(initializer)), condition(std::move(condition)), increment(std::move(increment)), body(std::move(body))
    {}
};

template<>
struct Stmt<ast::loop::Break> {
    std::size_t line;

    Stmt(std::size_t line) : line(line) {}
};

template<>
struct Stmt<ast::loop::Continue> {
    std::size_t line;   

    Stmt(std::size_t line) : line(line) {}
};

template<>
struct Stmt<ast::Nothing> {
    std::size_t line;

    Stmt(std::size_t line) : line(line) {}
};





