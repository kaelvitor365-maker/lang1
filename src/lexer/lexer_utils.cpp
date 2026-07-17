#include "lexer_utils.hpp"

bool details::isDigit(char c){
    return c >= '0' && c <= '9';
}

bool details::isAlpha(char c){
    return (
        c >= 'a' && c <= 'z'
    ) || (
        c >= 'A' && c <= 'Z'
    ) || c == '_';
}

bool details::isAlphaNumeric(char c){
    return details::isAlpha(c) || details::isDigit(c);
}

bool details::isSpace(char c){
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}