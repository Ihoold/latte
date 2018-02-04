//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include "ConstStringVariable.hpp"
#include "Compiler.hpp"

VarPtr ConstStringVariable::add(const VarPtr& ptr, Compiler *compiler) {
    if (ptr->getType()->getTypeSpecifier() != TypeSpecifier::String)
        typeCheckFailure("+");

    if (ptr->isConst()) {
        VarPtr result(compiler->getCurrentFunction().getNewRegisterVar(ptr->getType()));
        std::stringstream ss;
        ss << "\t" << result->getCode(compiler) << " = call i8* @concat(i8* " << getCode(compiler)
           << ", i8* " << ptr->getCode(compiler) << ")";
        compiler->getCompiledCode().push_back(ss.str());
        return result;
    } else {
        ptr->swap = true;
        return ptr->add(copy(), compiler);
    }
}

std::string ConstStringVariable::getCode(Compiler *compiler) {
    std::stringstream ss;
    ss << "getelementptr inbounds ([" << value.size() + 1 << " x i8], [" << value.size() + 1 << " x i8]* "
       << compiler->getGlobalStringName(value) << ", i64 0, i64 0)";
    return ss.str();
}

TypePtr ConstStringVariable::getType() {
    return TypePtr(new Str());
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
