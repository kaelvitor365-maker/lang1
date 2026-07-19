#pragma once

/// @namespace details
/// @brief Funções auxiliares utilizadas internamente pelo lexer.
namespace details {

    /// @brief Verifica se um caractere representa espaço em branco.
    /// @param c Caractere a ser analisado.
    /// @return Retorna true caso o caractere seja um espaço em branco.
    bool isSpace(char c);


    /// @brief Verifica se um caractere pertence ao conjunto alfabético.
    /// @param c Caractere a ser analisado.
    /// @return Retorna true caso o caractere seja uma letra.
    bool isAlpha(char c);


    /// @brief Verifica se um caractere representa um número.
    /// @param c Caractere a ser analisado.
    /// @return Retorna true caso o caractere seja um dígito numérico.
    bool isDigit(char c);


    /// @brief Verifica se um caractere é alfanumérico.
    /// @param c Caractere a ser analisado.
    /// @return Retorna true caso o caractere seja uma letra ou um número.
    bool isAlphaNumeric(char c);

}