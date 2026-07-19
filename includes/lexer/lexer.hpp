#pragma once
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <unordered_map>
#include <functional>
#include <array>
#include <optional>
#include <queue>
#include "token.hpp"



class Lexer final{
    public:
        Token nextToken();

        Token peekToken();

        explicit Lexer(const std::filesystem::path& path){

            std::ifstream file(path);
                if(!file.is_open()) throw std::runtime_error("Could not open file: " + path.string());
                this->data.assign(
                    std::istreambuf_iterator<char>{file},
                    std::istreambuf_iterator<char>{}
                );
                this->it = this->data.cbegin();
                this->end = this->data.cend();
            file.close();
            
            this->line = 0;
            this->scanToken();

        }


        ~Lexer() = default;



    private:
        void scanToken();
        void skipSpaces();
        Token string();
        Token number();
        Token alphaIdentfier();
        void specialCharacters(std::string word_1);
        void specialCharacters(std::string word_1, std::string word_2);


        std::unordered_map<char, TokenType> one_character{
                {'+', TokenType::TOKEN_PLUS},
                {'-', TokenType::TOKEN_MINUS},
                {'*', TokenType::TOKEN_MUL},
                {'/', TokenType::TOKEN_DIV},
                {'=', TokenType::TOKEN_EQUAL},
                {'!', TokenType::TOKEN_NOT},
                {'&', TokenType::TOKEN_AND},
                {'|', TokenType::TOKEN_OR},
                {'^', TokenType::TOKEN_XOR},
                {'~', TokenType::TOKEN_NOTB},
                {':', TokenType::TOKEN_COLON},
                {',', TokenType::TOKEN_COMMA},
                {'.', TokenType::TOKEN_DOT},
                {';', TokenType::TOKEN_SEMICOLON},
                {'>', TokenType::TOKEN_GT},
                {'<', TokenType::TOKEN_LT},
                {'(', TokenType::TOKEN_LPAREN},
                {')', TokenType::TOKEN_RPAREN},
                {'}', TokenType::TOKEN_RBRACE},
                {'{', TokenType::TOKEN_LBRACE},
                {'[', TokenType::TOKEN_LBRACKET},
                {']', TokenType::TOKEN_RBRACKET}
            };
        std::unordered_map<std::string, TokenType> two_characters{
            {"++", TokenType::TOKEN_INC},
            {"+=", TokenType::TOKEN_PLUSEQ},
            {"--", TokenType::TOKEN_DEC},
            {"-=", TokenType::TOKEN_MINUSEQ},
            {"*=", TokenType::TOKEN_MULEQ},
            {"/=", TokenType::TOKEN_DIVEQ},
            {"==", TokenType::TOKEN_EQEQ},
            {"!=", TokenType::TOKEN_NOTEQ},
            {"~=", TokenType::TOKEN_NOTBEQ},
            {"&&", TokenType::TOKEN_ANDAND},
            {"&=", TokenType::TOKEN_ANDEQ},
            {"||", TokenType::TOKEN_OROR},
            {"|=", TokenType::TOKEN_OREQ},
            {"^=", TokenType::TOKEN_XOREQ},
            {">>", TokenType::TOKEN_RSHIFT},
            {"<<", TokenType::TOKEN_LSHIFT}
        };
        std::unordered_map<std::string, TokenType> three_characters{
            {">>=", TokenType::TOKEN_RSHIFTEQ},
            {"<<=", TokenType::TOKEN_LSHIFTEQ}
        };
        std::unordered_map<std::string, TokenType> keywords{
            {"if", TokenType::TOKEN_IF},
            {"else", TokenType::TOKEN_ELSE},
            {"for", TokenType::TOKEN_FOR},
            {"do", TokenType::TOKEN_DO_WHILE},
            {"break", TokenType::TOKEN_BREAK},
            {"continue", TokenType::TOKEN_CONTINUE},
            {"func", TokenType::TOKEN_FUNC},
            {"return", TokenType::TOKEN_RETURN},
            {"main", TokenType::TOKEN_MAIN}
        };
        std::array<std::function<std::optional<TokenType>(const std::string&)>, 3> functions{
            [&](const std::string& str) -> std::optional<TokenType> {
                if(this->one_character.contains(str[0]))
                    return this->one_character.at(str[0]);
                return std::nullopt;
            },
            [&](const std::string& str) -> std::optional<TokenType>{
                if(this->two_characters.contains(str))
                    return this->two_characters.at(str);
                return std::nullopt;
            },
            [&](const std::string& str) -> std::optional<TokenType>{
                if(this->three_characters.contains(str))
                    return this->three_characters.at(str);
                return std::nullopt;
            }
            };
        std::string data;
        std::string::const_iterator it;
        std::string::const_iterator end;
        std::size_t line;
        std::queue<Token> buffer;
};