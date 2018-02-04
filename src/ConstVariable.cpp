//
// Created by ihoold on 20.01.18.
//

#include "ConstVariable.hpp"
#include "ConstIntVariable.hpp"
#include "ConstBoolVariable.hpp"
#include "ConstStringVariable.hpp"
#include "NullPtrVariable.hpp"

std::shared_ptr <Variable> ConstVariable::getConstDefault(TypePtr type) {
    auto t = type->getTypeSpecifier();
    switch(t) {
        case TypeSpecifier::Int:
            return VarPtr(new ConstIntVariable());
        case TypeSpecifier::Bool:
            return VarPtr(new ConstBoolVariable());
        case TypeSpecifier::String:
            return VarPtr(new ConstStringVariable());
        case TypeSpecifier::Struct:
            return VarPtr(new NullPtrVariable(type));
        default:
            throw std::logic_error("Not supported const generation.");
    }
}
