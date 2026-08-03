#pragma once

#include <cstddef>
#include <string>
#include <variant>
#include <utility>
#include <format>
#include <iostream>
#include "node.hpp"
namespace ast::details {
    struct printer final {
        printer() = default;

        std::string operator()(const Node& node){

            this->print(node);

            return str;
        }

    private:
        std::string putSpace();

        void print(std::monostate&) {}
        void print(const Node& expr);
        void print(const Expr<ast::Number>& expr);
        void print(const Expr<ast::String>& expr);
        void print(const Expr<ast::Identifier>& expr);
        void print(const Expr<ast::Boolean>& expr);
        void print(const Expr<ast::Unary>& expr);
        void print(const Expr<ast::Call>& expr);
        void print(const Expr<ast::Binary>& expr);
        void print(const Expr<ast::EndOfFile>& expr);
        void print(const Expr<ast::Assignment>& expr);

        void print(const Stmt<ast::VariableDeclaration>& stmt);
        void print(const Stmt<ast::Assignment>& stmt);
        void print(const Stmt<ast::Return>& stmt);
        void print(const Stmt<ast::Block>& stmt);
        void print(const Stmt<ast::If>& stmt);
        void print(const Stmt<ast::loop::While>& stmt);
        void print(const Stmt<ast::loop::For>& stmt);
        void print(const Stmt<ast::loop::doWhile>& stmt);
        void print(const Stmt<ast::loop::Break>& stmt);
        void print(const Stmt<ast::loop::Continue>& stmt);
        void print(const Stmt<ast::Nothing>& stmt);

        std::string str{""};
        std::size_t spaces = 0;
    };
}




namespace std {

    template <>
    struct formatter<Node>{
        constexpr auto parse(std::format_parse_context& ctx) const{
            return ctx.begin();
        }

        auto format(const Node& node, std::format_context& ctx) const{
            return std::format_to(
                ctx.out(),
                "{}",
                ast::details::printer{}(node)
            );
        }
    };

}

std::ostream& operator<<(std::ostream& os, Node& node);





