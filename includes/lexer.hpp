#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <stdexcept>


class Lexer {
    public:
        explicit Lexer(std::filesystem::path path) {
            std::ifstream file(path);
            if(!file.is_open()) throw std::runtime_error("Could not open file: " + path.string());

            this->data.assign(
                std::istreambuf_iterator<char>{file},
                std::istreambuf_iterator<char>{}
            );
            this->it = this->data.cbegin();
            this->end = this->data.cend();

            file.close();
        }


        ~Lexer() = default;

    private:
        std::string data;
        std::string::const_iterator it;
        std::string::const_iterator end;
};