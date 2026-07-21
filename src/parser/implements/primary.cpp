#include "parser.hpp"

Node Parser::primary(){

    if(this->match(TokenType::TOKEN_LPAREN)){
        Node node = expression();
        consume(TokenType::TOKEN_RPAREN);

        return node;
    }

    if(this->check(TokenType::TOKEN_BOOL)){
        auto boolean = std::get<bool>(this->current.value);
        std::size_t line = this->current.line;
        advance();

        return Node{
            Expr<ast::Boolean>{
                boolean,
                line
            }
        };
    }

    if(this->check(TokenType::TOKEN_NUMBER)){
        auto number = std::get<std::uint64_t>(this->current.value);
        std::size_t line = this->current.line;
        advance();

        return Node{
            Expr<ast::Number>{
                number,
                line
            }
        };
    }
    if(this->check(TokenType::TOKEN_STRING)){
        auto str = std::move(std::get<std::string>(this->current.value));
        std::size_t line = this->current.line;
        advance();

        return Node{
            Expr<ast::String>{
                std::move(str),
                line
            }
        };
    }
    if(this->check(TokenType::TOKEN_IDENTIFIER)){
        auto str = std::move(std::get<std::string>(this->current.value));
        std::size_t line = this->current.line;
        advance();

        return Node{
            Expr<ast::Identifier>{
                std::move(str),
                line
            }
        };
    }
    
    throw std::runtime_error("Expected Expression");
}