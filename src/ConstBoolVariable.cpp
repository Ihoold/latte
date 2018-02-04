//
// Created by ihoold on 20.01.18.
//

#include "ConstBoolVariable.hpp"
#include "Compiler.hpp"

ConstBoolVariable::ConstBoolVariable(bool b) : value(b) {}

bool ConstBoolVariable::getValue() const {
    return value;
}

std::string ConstBoolVariable::getCode(Compiler *compiler) {
    return (value) ? "true" : "false";
}

TypePtr ConstBoolVariable::getType() {
    return TypePtr(new Bool());
}

VarPtr ConstBoolVariable::copy() {
    return VarPtr(new ConstBoolVariable(value));
}

VarPtr ConstBoolVariable::band(Expr* expr2, Compiler *compiler) {
    if (!value) {
        return VarPtr(new ConstBoolVariable(false));
    } else {
        expr2->accept(compiler);
        if (compiler->getLastResult()->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
            typeCheckFailure("&&");
        return compiler->getLastResult();
    }
}

VarPtr ConstBoolVariable::bor(Expr* expr, Compiler *compiler) {

    if (value) {
        return VarPtr(new ConstBoolVariable(true));
    } else {
        expr->accept(compiler);
        if (compiler->getLastResult()->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
            typeCheckFailure("||");
        return compiler->getLastResult();
    }
}

VarPtr ConstBoolVariable::not_(Compiler *compiler) {
    return VarPtr(new ConstBoolVariable(not value));
}

VarPtr ConstBoolVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("==");

    if (ptr->isConst()) {
        auto boolVar1 = std::dynamic_pointer_cast<ConstBoolVariable>(ptr);
        return VarPtr(new ConstBoolVariable(boolVar1->value == value));
    } else {
        return ptr->eq(copy(), compiler);
    }
}

VarPtr ConstBoolVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("!=");

    if (ptr->isConst()) {
        auto boolVar1 = std::dynamic_pointer_cast<ConstBoolVariable>(ptr);
        return VarPtr(new ConstBoolVariable(boolVar1->value != value));
    } else {
        return ptr->neq(copy(), compiler);
    }
}

bool ConstBoolVariable::isEqual(const Variable& b) const {
    auto cbv = dynamic_cast<const ConstBoolVariable&>(b);
    return value == cbv.value;
}
