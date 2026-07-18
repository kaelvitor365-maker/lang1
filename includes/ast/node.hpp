#pragma once


#include <concepts>
#include <utility>
#include <variant>
#include "token.hpp"
#include "expr.hpp"

struct Node final{
    std::variant<
        expr::Number,
        expr::String,
        expr::Identifier,
        expr::Boolean,
        expr::Binary,
        expr::Unary
    >value;

    template <typename T>
    requires std::constructible_from<decltype(value), T>
    Node(T&& value) : value(std::forward<T>(value)) {}
};