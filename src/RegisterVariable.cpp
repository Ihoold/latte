//
// Created by ihoold on 20.01.18.
//

#include <sstream>
#include "RegisterVariable.hpp"
#include "ConstIntVariable.hpp"
#include "Compiler.hpp"

void RegisterVariable::throwIfTypesDiffer(const VarPtr& ptr, const std::string& operation) {
    if (ptr->getType() != type)
        typeCheckFailure(operation);
}

void
RegisterVariable::typeControl(const VarPtr& ptr, std::vector<TypeSpecifier> expectedTypes, const std::string& operation) {
    if (!typeIn(type, std::move(expectedTypes)))
        typeCheckFailure(operation);
    throwIfTypesDiffer(ptr, operation);
}

bool RegisterVariable::isConst() {
    return false;
}

TypeSpecifier RegisterVariable::getType() {
    return type;
}

RegisterVariable::RegisterVariable(std::string reg_, TypeSpecifier _type) : reg(std::move(reg_)), type(_type) {}

std::string RegisterVariable::getCode(Compiler *compiler) {
    return reg;
}

VarPtr RegisterVariable::copy() {
    return VarPtr(new RegisterVariable(reg, type));
}

VarPtr RegisterVariable::twoOp(const VarPtr& ptr, Compiler *compiler, const std::string& operation) {
    throwIfTypesDiffer(ptr, operation);

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Int);

    if(swap) {
        ss << "\t" << result->getCode(compiler) << " = " << operation << " i32 " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
    } else {
        ss << "\t" << result->getCode(compiler) << " = " << operation << " i32 " << ptr->getCode(compiler) << ", " << this->getCode(compiler);
    }
    swap = false;
    compiler->getCompiledCode().push_back(ss.str());
    return result;
}

VarPtr RegisterVariable::add(const VarPtr& ptr, Compiler *compiler) {
    switch (ptr->getType()) {
        case TypeSpecifier::Int:
            return twoOp(ptr, compiler, "add");
        case TypeSpecifier::String: {
            VarPtr result(compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::String));
            std::stringstream ss;
            ss << "\t" << result->getCode(compiler) << " = call i8* @strcat(" << translateTypeSpecifier(type)
               << " " << getCode(compiler) << ", " << translateTypeSpecifier(ptr->getType()) << " " << ptr->getCode(compiler) << ")";
            compiler->getCompiledCode().push_back(ss.str());
            return result;
        }
        default:
            typeCheckFailure("!=");
    }
}

VarPtr RegisterVariable::sub(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "-");
    return twoOp(ptr, compiler, "sub");
}

void RegisterVariable::incr(Compiler *compiler) {
    if(type != TypeSpecifier::Int)
        typeCheckFailure("++");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Int);

    ss << "\t" << result->getCode(compiler) << " = add i32 " << this->getCode(compiler) << ", " << "1";
    compiler->getCompiledCode().push_back(ss.str());
}

void RegisterVariable::decr(Compiler *compiler) {
    if(type != TypeSpecifier::Int)
        typeCheckFailure("--");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Int);

    ss << "\t" << result->getCode(compiler) << " = sub i32 " << this->getCode(compiler) << ", " << "1";
    compiler->getCompiledCode().push_back(ss.str());

}

VarPtr RegisterVariable::neg(Compiler *compiler) {
    VarPtr e2(new ConstIntVariable(0));
    return sub(e2, compiler);
}

VarPtr RegisterVariable::mul(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "*");
    return twoOp(ptr, compiler, "mul");
}

VarPtr RegisterVariable::div(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "/");
    return twoOp(ptr, compiler, "sdiv");
}

VarPtr RegisterVariable::rem(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "%");
    return twoOp(ptr, compiler, "srem");
}

VarPtr RegisterVariable::band(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Bool}, "&&");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Bool);

    ss << "\t" << result->getCode(compiler) << " = " << "and i1 " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
    compiler->getCompiledCode().push_back(ss.str());

    return result;
}

VarPtr RegisterVariable::bor(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Bool}, "||");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Bool);

    ss << "\t" << result->getCode(compiler) << " = " << "or i1 " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
    compiler->getCompiledCode().push_back(ss.str());

    return result;
}

VarPtr RegisterVariable::not_(Compiler *compiler) {
    if (type != TypeSpecifier::Bool)
        typeCheckFailure("!");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Bool);

    ss << "\t" << result->getCode(compiler) << " = " << "add i1 " << this->getCode(compiler) << ", 1";
    compiler->getCompiledCode().push_back(ss.str());

    return result;
}

VarPtr
RegisterVariable::cmp(const VarPtr& ptr, Compiler *compiler, const std::string& operation, const std::string& type) {
    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Bool);

    if(swap) {
        ss << "\t" << result->getCode(compiler) << " = " << "icmp " << operation << " "
           << type << " " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
    } else {
        ss << "\t" << result->getCode(compiler) << " = " << "icmp " << operation << " "
           << type << " " << ptr->getCode(compiler) << ", " << this->getCode(compiler);
    }
    swap = false;
    compiler->getCompiledCode().push_back(ss.str());
    return result;
}

VarPtr RegisterVariable::lt(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "<");
    return cmp(ptr, compiler, "slt", "i32");
}

VarPtr RegisterVariable::lte(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, "<=");
    return cmp(ptr, compiler, "sle", "i32");
}

VarPtr RegisterVariable::gt(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, ">");
    return cmp(ptr, compiler, "sgt", "i32");
}

VarPtr RegisterVariable::gte(const VarPtr& ptr, Compiler *compiler) {
    typeControl(ptr, {TypeSpecifier::Int}, ">=");
    return cmp(ptr, compiler, "sge", "i32");
}

VarPtr RegisterVariable::eq(const VarPtr& ptr, Compiler *compiler) {
    throwIfTypesDiffer(ptr, "==");

    switch (ptr->getType()) {
        case TypeSpecifier::Int:
            return cmp(ptr, compiler, "eq", "i32");
        case TypeSpecifier::Bool:
            return cmp(ptr, compiler, "eq", "i1");
        default:
            typeCheckFailure("==");
    }
}

VarPtr RegisterVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    throwIfTypesDiffer(ptr, "!=");

    switch (ptr->getType()) {
        case TypeSpecifier::Int:
            return cmp(ptr, compiler, "ne", "i32");
        case TypeSpecifier::Bool:
            return cmp(ptr, compiler, "ne", "i1");
        default:
            typeCheckFailure("!=");
    }
}

bool RegisterVariable::isEqual(const Variable& b) const {
    auto brv = dynamic_cast<const RegisterVariable&>(b);
    return type == brv.type && reg == brv.reg;
}
