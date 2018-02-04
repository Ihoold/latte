//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include "ConstIntVariable.hpp"
#include "ConstBoolVariable.hpp"

std::string ConstIntVariable::getCode(Compiler *compiler) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

TypePtr ConstIntVariable::getType() {
    return TypePtr(new Int());
}

VarPtr ConstIntVariable::copy() {
    return VarPtr(new ConstIntVariable(value));
}

VarPtr ConstIntVariable::add(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("+");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstIntVariable(value + intVar1->value));
    } else {
        return ptr->add(copy(), compiler);
    }
}

VarPtr ConstIntVariable::sub(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("-");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstIntVariable(value - intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->sub(copy(), compiler);
    }
}

VarPtr ConstIntVariable::neg(Compiler *compiler) {
    return VarPtr(new ConstIntVariable(-1 * value));
}

VarPtr ConstIntVariable::mul(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("*");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstIntVariable(value * intVar1->value));
    } else {
        return ptr->mul(copy(), compiler);
    }
}

VarPtr ConstIntVariable::div(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("/");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstIntVariable(value / intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->div(copy(), compiler);
    }
}

VarPtr ConstIntVariable::rem(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("%");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstIntVariable(value % intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->rem(copy(), compiler);
    }
}

VarPtr ConstIntVariable::lt(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("<");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value < intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->lt(copy(), compiler);
    }
}

VarPtr ConstIntVariable::lte(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("<=");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value <= intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->lte(copy(), compiler);
    }
}

VarPtr ConstIntVariable::gt(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure(">");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value > intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->gt(copy(), compiler);
    }
}

VarPtr ConstIntVariable::gte(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure(">=");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value >= intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->gte(copy(), compiler);
    }
}

VarPtr ConstIntVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("==");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value == intVar1->value));
    } else {
        return ptr->eq(copy(), compiler);
    }
}

VarPtr ConstIntVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        typeCheckFailure("!=");

    if (ptr->isConst()) {
        auto intVar1 = std::dynamic_pointer_cast<ConstIntVariable>(ptr);
        return VarPtr(new ConstBoolVariable(value != intVar1->value));
    } else {
        return ptr->neq(copy(), compiler);
    }
}

ConstIntVariable::ConstIntVariable(int i) : value(i) {}

bool ConstIntVariable::isEqual(const Variable& b) const {
    auto civ = dynamic_cast<const ConstIntVariable&>(b);
    return value == civ.value;
}
