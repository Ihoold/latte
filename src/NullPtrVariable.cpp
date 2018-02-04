//
// Created by ihoold on 29.01.18.
//

#include "NullPtrVariable.hpp"
#include "ConstBoolVariable.hpp"

#include <utility>

bool NullPtrVariable::isEqual(const Variable& b) const {
    auto nullPtrVar = dynamic_cast<const NullPtrVariable&>(b);
    return type == nullPtrVar.type;
}

NullPtrVariable::NullPtrVariable(TypePtr t) : type(std::move(t)) {}

TypePtr NullPtrVariable::getType() {
    return type;
}

VarPtr NullPtrVariable::copy() {
    return VarPtr(new NullPtrVariable(type));
}

VarPtr NullPtrVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    if (!(ptr->getType() == getType()))
        typeCheckFailure("==");

    if (ptr->isConst()) {
        return VarPtr(new ConstBoolVariable(true));
    } else {
        return ptr->eq(copy(), compiler);
    }
}

VarPtr NullPtrVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    if (!(ptr->getType() == getType()))
        typeCheckFailure("!=");

    if (ptr->isConst()) {
        return VarPtr(new ConstBoolVariable(false));;
    } else {
        return ptr->neq(copy(), compiler);
    }
}

std::string NullPtrVariable::getCode(Compiler *compiler) {
    return "null";
}
