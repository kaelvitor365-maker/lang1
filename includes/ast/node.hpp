#pragma once


#include <concepts>
#include <utility>
#include <variant>
#include "token.hpp"
#include "expr.hpp"
#include "stmt.hpp"

struct Node final{
    std::variant<
        std::monostate,
        Expr<ast::Number>,
        Expr<ast::String>,
        Expr<ast::Identifier>,
        Expr<ast::Boolean>,
        Expr<ast::Binary>,
        Expr<ast::Unary>,
        Expr<ast::Call>,
        Expr<ast::Assignment>,
        Expr<ast::EndOfFile>,
        Stmt<ast::VariableDeclaration>,
        Stmt<ast::Assignment>,
        Stmt<ast::Block>,
        Stmt<ast::If>,
        Stmt<ast::loop::While>,
        Stmt<ast::loop::For>,
        Stmt<ast::loop::doWhile>,
        Stmt<ast::loop::Break>,
        Stmt<ast::loop::Continue>,
        Stmt<ast::Nothing>
    >value;


    template <typename T>
    requires std::constructible_from<decltype(value), T>
    Node(T&& value) : value(std::forward<T>(value)) {}
};
