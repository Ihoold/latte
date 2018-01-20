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

TypeSpecifier ConstIntVariable::getType() {
    return TypeSpecifier::Int;
}

VarPtr ConstIntVariable::copy() {
    return VarPtr(new ConstIntVariable(value));
}

VarPtr ConstIntVariable::add(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("+");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstIntVariable(value + intVar1->value));
    } else {
        return ptr->add(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::sub(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("-");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstIntVariable(value - intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->sub(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

void ConstIntVariable::incr(Compiler *compiler) {
    value++;
}

void ConstIntVariable::decr(Compiler *compiler) {
    value--;
}

VarPtr ConstIntVariable::neg(Compiler *compiler) {
    return VarPtr(new ConstIntVariable(-1 * value));
}

VarPtr ConstIntVariable::mul(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("*");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return {VarPtr(new ConstIntVariable(value * intVar1->value)), {}};
    } else {
        return ptr->mul(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::div(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("/");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstIntVariable(value / intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->div(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::rem(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("%");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstIntVariable(value % intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->rem(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::lt(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("<");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value < intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->lt(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::lte(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("<=");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value <= intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->lte(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::gt(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure(">");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value > intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->gt(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::gte(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure(">=");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value >= intVar1->value));
    } else {
        ptr->swap = true;
        return ptr->gte(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("==");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value == intVar1->value));
    } else {
        return ptr->eq(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

VarPtr ConstIntVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::Int)
        typeCheckFailure("!=");

    if (ptr->isConst()) {
        auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
        return VarPtr(new ConstBoolVariable(value != intVar1->value));
    } else {
        return ptr->neq(VarPtr(new ConstIntVariable(value)), compiler);
    }
}

ConstIntVariable::ConstIntVariable(int i) : value(i) {}
