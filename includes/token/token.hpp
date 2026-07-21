#pragma once

#include <variant>
#include <cstdint>
#include <string>
#include <cstddef>
#include <format>
#include "_token.hpp"




/// @brief Represents a lexical token produced by the lexer.
class Token {
public:

    /// @brief Token category.
    TokenType type = TokenType::TOKEN_INVALID;

    /// @brief Source code line where the token was recognized.
    std::size_t line = 0;

    /// @brief Token value, when applicable.
    ///
    /// Supported types:
    /// - std::monostate : token has no associated value.
    /// - std::uint64_t  : numeric literal.
    /// - std::string    : identifier or string literal.
    /// - bool           : boolean literal.
    std::variant<
        std::monostate,
        std::uint64_t,
        std::string,
        bool
    > value{};

    explicit operator bool(){
        return this->type != TokenType::TOKEN_EOF;
    }
};


namespace std{

    template <>
    struct formatter<Token> {

        constexpr auto parse(std::format_parse_context& ctx){
            return ctx.begin();
        }


        auto format(const Token& token, std::format_context& ctx) const{

            return std::visit(
                [&](auto&& value){

                    if constexpr(std::is_same_v<std::decay_t<decltype(value)>, std::monostate>){
                        return std::format_to(
                            ctx.out(),
                            "{} [line: {}]",
                            details::token_names[
                                static_cast<std::size_t>(token.type)
                            ],
                            token.line
                        );
                    }
                    else{
                        return std::format_to(
                            ctx.out(),
                            "{}({}) [line: {}]",
                            details::token_names[
                                static_cast<std::size_t>(token.type)
                            ],
                            value,
                            token.line
                        );
                    }

                },
                token.value
            );
        }
    };

}

/// @brief 
/// @param os 
/// @param token 
/// @return 
std::ostream& operator<<(std::ostream& os, const Token& token);
