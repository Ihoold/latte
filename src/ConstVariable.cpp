//
// Created by ihoold on 20.01.18.
//

#include "ConstVariable.hpp"
#include "ConstIntVariable.hpp"
#include "ConstBoolVariable.hpp"
#include "ConstStringVariable.hpp"

std::shared_ptr <Variable> ConstVariable::getConstDefault(TypeSpecifier t) {
    switch(t) {
        case TypeSpecifier::Int:
            return VarPtr(new ConstIntVariable());
        case TypeSpecifier::Bool:
            return VarPtr(new ConstBoolVariable());
        case TypeSpecifier::String:
            return VarPtr(new ConstStringVariable());
        default:
            throw std::logic_error("Not supported const generation.");
    }
}
