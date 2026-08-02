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
struct Stmt<ast::While> {
    std::size_t line;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> block;

    Stmt(std::size_t line, std::unique_ptr<Node> condition, std::unique_ptr<Node> block) :
        line(line), condition(std::move(condition)), block(std::move(block))
    {}
};

template<>
struct Stmt<ast::For> {
    std::size_t line;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> increment;
    std::unique_ptr<Node> block;

    Stmt(std::size_t line, std::unique_ptr<Node> initializer = nullptr, std::unique_ptr<Node> condition = nullptr, std::unique_ptr<Node> increment = nullptr, std::unique_ptr<Node> block = nullptr) :
        line(line), initializer(std::move(initializer)), condition(std::move(condition)), increment(std::move(increment)), block(std::move(block))
    {}
};



