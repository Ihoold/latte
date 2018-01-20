//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_COMPILATIONEXCEPTION_HPP
#define INSTANT_COMPILATIONEXCEPTION_HPP

#include <stdexcept>

class CompilationException : public std::logic_error {
private:
    int line_num;
public:
    CompilationException(const std::string& what, int line) : std::logic_error(what), line_num(line) {};

    int getLine_num() const {
        return line_num;
    }
};


#endif //INSTANT_COMPILATIONEXCEPTION_HPP
