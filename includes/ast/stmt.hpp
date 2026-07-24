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
    std::string name;
    std::string type;
    std::unique_ptr<Node> initializer;
    Stmt(std::size_t line, std::string name, std::string type, std::unique_ptr<Node> initializer = nullptr) :
        line(line), name(std::move(name)), type(std::move(type)), initializer(std::move(initializer))
    {}
};

template<>
struct Stmt<ast::Assignment> final {
    std::size_t line;
    std::string name;
    std::unique_ptr<Node> expression;
    Stmt(std::size_t line, std::string name, std::unique_ptr<Node> expression = nullptr) :
        line(line), name(std::move(name)), expression(std::move(expression))
    {}
};

template<>
struct Stmt<ast::Block> {
    std::size_t line;
    std::vector<Node> statements;

    Stmt(std::size_t line, std::vector<Node> statements) :
        line(line), statements(std::move(statements))
    {}
};


template<>
struct Stmt<ast::Return> {
    std::size_t line;
    std::unique_ptr<Node> expression;

    Stmt(std::size_t line, std::unique_ptr<Node> expression = nullptr) :
        line(line), expression(std::move(expression))
    {}
};

template<>
struct Stmt<ast::If> {
    std::size_t line;
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> block;

    Stmt(std::size_t line, std::unique_ptr<Node> condition, std::unique_ptr<Node> block) :
        line(line), condition(std::move(condition)), block(std::move(block))
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


