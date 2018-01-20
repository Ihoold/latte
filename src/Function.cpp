//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include <unordered_map>
#include <utility>
#include "Function.hpp"
#include "Variable.hpp"
#include "Label.hpp"
#include "RegisterVariable.hpp"

std::shared_ptr<Variable> Function::getNewRegisterVar(TypeSpecifier type) {
    std::stringstream ss;
    ss << "%" << counter++;
    return std::shared_ptr<Variable>(new RegisterVariable(ss.str(), type));
}

Label Function::getNewLabel(std::vector<int> preds) {
    return Label(counter++, std::move(preds));}

int Function::getReturnStatements() const {
    return returnStatements;
}

void Function::setReturnStatements(int returnStatements) {
    Function::returnStatements = returnStatements;
}

void Function::setLastLabel(int lastLabel) {
    Function::lastLabel = lastLabel;
}

int Function::getLastLabel() const {
    return lastLabel;
}

void Function::initVariables() {
    variables.clear();
    variables.emplace_back();

    for (auto& arg : arguments) {
        variables.back()[arg.first] = arg.second->copy();
    }
}

Function::Function(TypeSpecifier type, std::vector<std::pair<Ident, VarPtr>> args)
        : returnType(type), arguments(std::move(args)) {}

std::vector<std::pair<Ident, VarPtr>> Function::getArguments() const {
    return arguments;
}

std::vector<std::unordered_map<Ident, VarPtr>>& Function::getVariables() {
    return variables;
}

const TypeSpecifier Function::getReturnType() const {
    return returnType;
}

void Function::clearBlockVariables() {
    variables.pop_back();
}

VarPtr Function::getVar(const Ident& id) {
    for (auto it = variables.rbegin(); it != variables.rend(); it++) {
        if (it->find(id) != it->end())
            return it->find(id)->second;
    }

    throw std::logic_error("Variable undeclared.");
}

void Function::putVar(const Ident& id, const VarPtr& val) {
    auto& blockVariables = variables.back();
    if (blockVariables.find(id) != blockVariables.end()) {
        throw std::logic_error("Variable already exists.");
    }
    blockVariables[id] = val;
}

void Function::changeVar(const Ident& id, VarPtr val) {
    for (auto it = variables.rbegin(); it != variables.rend(); it++) {
        if (it->find(id) != it->end()) {
            it->erase(id);
            it->insert({id, val});
            return;
        }
    }

    throw std::logic_error("Variable undeclared.");
}
