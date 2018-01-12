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

    Program *parse_tree = pProgram(input);
    if (parse_tree) {
        ShowAbsyn *s = new ShowAbsyn();
        printf("%s\n\n", s->show(parse_tree));
        Compiler* compiler = new Compiler();
        const std::string& path = argv[1];
        try {
            parse_tree->accept(compiler);
        } catch(CompilationException exception) {
            std::cerr << "ERROR" <<  std::endl;
            std::cerr << "Line #" << exception.getLine_num() << ": " << exception.what() << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Unable to parse file" << std::endl;
    }

    return 1;
}