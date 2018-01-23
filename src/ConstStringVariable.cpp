//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include "ConstStringVariable.hpp"
#include "Compiler.hpp"

VarPtr ConstStringVariable::add(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType() != TypeSpecifier::String)
        typeCheckFailure("+");

    if (ptr->isConst()) {
        auto strVar = dynamic_cast<ConstStringVariable*>(ptr.get());
        return VarPtr(new ConstStringVariable(value + strVar->getValue()));
    } else {
        ptr->swap = true;
        return ptr->add(copy(), compiler);
    }
}

std::string ConstStringVariable::getCode(Compiler *compiler) {
    std::stringstream ss;
    ss << "getelementptr inbounds ([" << value.size() << " x i8], [" << value.size() << " x i8]* "
       << compiler->getGlobalStringName(value) << ", i64 0, i64 0)";
    return ss.str();
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

bool ConstStringVariable::isEqual(const Variable& b) const {
    auto csv = dynamic_cast<const ConstStringVariable&>(b);
    return value == csv.value;
}
