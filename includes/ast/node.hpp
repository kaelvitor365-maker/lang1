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
        Expr<ast::EndOfFIle>,
        Stmt<ast::VariableDeclaration>,
        Stmt<ast::Assignment>,
        Stmt<ast::Block>,
        Stmt<ast::Return>,
        Stmt<ast::If>,
        Stmt<ast::While>
    >value;


    template <typename T>
    requires std::constructible_from<decltype(value), T>
    Node(T&& value) : value(std::forward<T>(value)) {}
};
