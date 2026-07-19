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


/// @brief Realiza a análise léxica do código-fonte.
///
/// O Lexer transforma caracteres do código-fonte em uma sequência de tokens.
/// Ele reconhece palavras reservadas, identificadores, literais, operadores
/// e delimitadores.
class Lexer final{
    public:

        /// @brief Consome e retorna o próximo token disponível.
        /// @return Próximo token produzido pelo lexer.
        Token nextToken();


        /// @brief Obtém o próximo token sem removê-lo do buffer.
        /// @return Próximo token disponível.
        Token peekToken();


        /// @brief Cria um lexer a partir de um arquivo.
        ///
        /// O arquivo é carregado para memória e utilizado como fonte
        /// de leitura dos tokens.
        ///
        /// @param path Caminho do arquivo que será analisado.
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


        /// @brief Destrutor padrão do lexer.
        ~Lexer() = default;



    private:

        /// @brief Analisa o próximo elemento léxico e adiciona o token ao buffer.
        void scanToken();


        /// @brief Ignora espaços em branco e atualiza o contador de linhas.
        void skipSpaces();


        /// @brief Lê um literal de string.
        ///
        /// @return Token contendo o valor da string.
        Token string();


        /// @brief Lê um literal numérico.
        ///
        /// @return Token contendo o valor numérico.
        Token number();


        /// @brief Lê identificadores e palavras reservadas.
        ///
        /// @return Token identificado como identificador ou keyword.
        Token alphaIdentfier();


        /// @brief Reconhece caracteres especiais e operadores.
        ///
        /// Tenta identificar operadores compostos antes de operadores simples.
        ///
        /// @param word_1 Sequência de caracteres especiais analisada.
        void specialCharacters(std::string word_1);


        /// @brief Divide uma sequência de caracteres especiais em partes menores.
        ///
        /// Utilizado quando uma sequência não corresponde a um operador válido.
        ///
        /// @param word_1 Primeira sequência de caracteres.
        /// @param word_2 Segunda sequência de caracteres.
        void specialCharacters(std::string word_1, std::string word_2);



        /// @brief Operadores compostos por um caractere.
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


        /// @brief Operadores compostos por dois caracteres.
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


        /// @brief Operadores compostos por três caracteres.
        std::unordered_map<std::string, TokenType> three_characters{
            {">>=", TokenType::TOKEN_RSHIFTEQ},
            {"<<=", TokenType::TOKEN_LSHIFTEQ}
        };


        /// @brief Palavras reservadas da linguagem.
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


        /// @brief Funções responsáveis por reconhecer operadores dependendo do tamanho.
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


        /// @brief Código-fonte carregado em memória.
        std::string data;


        /// @brief Iterador apontando para a posição atual da leitura.
        std::string::const_iterator it;


        /// @brief Iterador apontando para o final do código-fonte.
        std::string::const_iterator end;


        /// @brief Linha atual do código-fonte.
        std::size_t line;


        /// @brief Fila de tokens produzidos pelo lexer.
        std::queue<Token> buffer;
};