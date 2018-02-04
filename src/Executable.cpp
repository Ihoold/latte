//
// Created by ihoold on 12.01.18.
//

#include <sstream>
#include <iterator>
#include <fstream>
#include <iostream>
#include "Parser.hpp"
#include "Printer.hpp"
#include "Compiler.hpp"
#include "CompilationException.hpp"
#include "RegisterVariable.hpp"

std::string getFilename(const std::string& path) {
    auto filenameEnd = path.find_last_of('.');
    auto filenameBegin = path.find_last_of('/');
    if (filenameBegin == std::string::npos) {
        return path.substr(0, filenameEnd);
    }
    return path.substr(filenameBegin + 1, filenameEnd - filenameBegin - 1);
}

std::string getDirName(const std::string& path) {
    auto filenameBegin = path.find_last_of('/');
    if (filenameBegin == std::string::npos) {
        return "./";
    }
    return path.substr(0, filenameBegin+1);
}

int main(int argc, char **argv) {
    FILE *input;
    if (argc > 1) {
        input = fopen(argv[1], "r");
        if (!input) {
            std::cerr << "Error opening input file." << std::endl;
            exit(1);
        }
    } else {
        std::cerr << "Usage: exec file" << std::endl;
        exit(2);
    }

    Program *parse_tree = nullptr;
    try {
        parse_tree = pProgram(input);
    } catch (const std::invalid_argument& ex) {
        std::cerr << "ERROR" << std::endl;
        std::cerr << ex.what();
        return -2;
    }

    auto compiler = new Compiler();
    try {
        parse_tree->accept(compiler);
    } catch(const CompilationException& exception) {
        std::cerr << "ERROR" <<  std::endl;
        std::cerr << "Line #" << exception.getLine_num() << ": " << exception.what() << std::endl;
        delete(compiler);
        return -1;
    }

    const std::string& path = argv[1];
    auto outPath = getDirName(path) + getFilename(path) + ".ll";
    std::cerr << "OK" <<  std::endl;
    {
        std::ofstream codeStream(outPath, std::ofstream::out);
        std::copy(compiler->getCompiledCode().begin(), compiler->getCompiledCode().end(),
                  std::ostream_iterator<std::string>(codeStream, "\n"));
    }

    delete(compiler);
    return 0;
}