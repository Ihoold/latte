//
// Created by ihoold on 20.01.18.
//

#include "Variable.hpp"

void typeCheckFailure(const std::string& operation) {
    throw std::logic_error("Type check failed in operation " + operation + ".");
}