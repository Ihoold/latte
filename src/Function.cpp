//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include <unordered_map>
#include "Function.hpp"
#include "RegisterVariable.hpp"
#include "Compiler.hpp"
#include "ExtraTypes.hpp"

VarPtr Function::getNewRegisterVar(TypePtr type) {
    return VarPtr(new RegisterVariable(getNewRegister(), type));
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

void Function::initVariables(Compiler* compiler, bool method) {
    variables.clear();
    variables.emplace_back();

    if (method) {
        auto this_var = arguments.front();
        auto type = this_var.second->getType();
        auto struct_type = std::dynamic_pointer_cast<Struct>(type);
        auto structure = compiler->getStructures().at(struct_type->getIdent_());

        for (const auto& attr : structure) {
            auto field = this_var.second->getField(attr.first, compiler);
            auto heapVar = PointerVarPtr(new PointerVariable(field->getType(), field->getCode(compiler)));
            variables.back()[attr.first] = heapVar;
        }
        variables.emplace_back();
    }

    for (auto& arg : arguments) {
        auto heapVar = PointerVarPtr(new PointerVariable(arg.second->getType(), compiler));
        heapVar->store(arg.second, compiler);

        variables.back()[arg.first] = heapVar;
    }
}

Function::Function(TypePtr type, std::vector<std::pair<Ident, VarPtr>> args)
        : returnType(type), arguments(std::move(args)) {}

std::vector<std::pair<Ident, VarPtr>> Function::getArguments() const {
    return arguments;
}

std::vector<std::unordered_map<Ident, PointerVarPtr>>& Function::getVariables() {
    return variables;
}

const TypePtr Function::getReturnType() const {
    return returnType;
}

void Function::clearBlockVariables(Compiler* compiler) {
    variables.pop_back();
}

PointerVarPtr Function::getVar(const Ident id) {
    for (auto it = variables.rbegin(); it != variables.rend(); it++) {
        if (it->find(id) != it->end())
            return it->find(id)->second;
    }

    throw std::logic_error("Variable undeclared.");
}

void Function::putVar(const Ident& id, PointerVarPtr& val) {
    auto& blockVariables = variables.back();
    if (blockVariables.find(id) != blockVariables.end()) {
        throw std::logic_error("Variable already exists.");
    }
    blockVariables[id] = val;
}

Function::Function() : returnType(TypePtr(new Void())) {}

std::string Function::getNewRegister() {
    std::stringstream ss;
    ss << "%" << counter++;
    return ss.str();
}
