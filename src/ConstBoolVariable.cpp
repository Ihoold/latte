//
// Created by ihoold on 20.01.18.
//

#include "ConstBoolVariable.hpp"

ConstBoolVariable::ConstBoolVariable(bool b) : value(b) {}

bool ConstBoolVariable::getValue() const {
    return value;
}

std::string ConstBoolVariable::getCode(Compiler *compiler) {
    return (value) ? "true" : "false";
}

TypeSpecifier ConstBoolVariable::getType() {
    return TypeSpecifier::Bool;
}

VarPtr ConstBoolVariable::copy() {
    return VarPtr(new ConstBoolVariable(value));
}

VarPtr ConstBoolVariable::band(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    if (!value) {
        return VarPtr(new ConstBoolVariable(false));
    } else {
        return ptr;
    }
}

VarPtr ConstBoolVariable::bor(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    if (value) {
        return VarPtr(new ConstBoolVariable(true));
    } else {
        return ptr;
    }
}

VarPtr ConstBoolVariable::not_(Compiler *compiler) {
    return VarPtr(new ConstBoolVariable(not value));
}

VarPtr ConstBoolVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    if (ptr->isConst()) {
        auto boolVar1 = dynamic_cast<ConstBoolVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(boolVar1->value == value));
    } else {
        return ptr->eq(VarPtr(new ConstBoolVariable(value)), compiler);
    }
}

VarPtr ConstBoolVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    if (ptr->isConst()) {
        auto boolVar1 = dynamic_cast<ConstBoolVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(boolVar1->value != value));
    } else {
        return ptr->neq(VarPtr(new ConstBoolVariable(value)), compiler);
    }
}

bool ConstBoolVariable::isEqual(const Variable& b) const {
    auto cbv = dynamic_cast<const ConstBoolVariable&>(b);
    return value == cbv.value;
}
