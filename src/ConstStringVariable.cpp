//
// Created by ihoold on 20.01.18.
//

#include "ConstStringVariable.hpp"

VarPtr ConstStringVariable::add(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::String)
        typeCheckFailure("+");

    if (ptr->isConst()) {
        auto strVar = dynamic_cast<ConstStringVariable*>(ptr.get());
        return VarPtr(new ConstStringVariable(value + strVar->getValue()));
    } else {
        // TODO
    }
}

std::string ConstStringVariable::getCode(Compiler *compiler) {
    return value;
    // TODO
}

TypeSpecifier ConstStringVariable::getType() {
    return TypeSpecifier::String;
}

VarPtr ConstStringVariable::copy() {
    return VarPtr(new ConstStringVariable(value));
}

const std::string& ConstStringVariable::getValue() const {
    return value;
}

ConstStringVariable::ConstStringVariable(std::string v) : value(std::move(v)) {}
