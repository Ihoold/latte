//
// Created by ihoold on 20.01.18.
//

#include <iostream>
#include <sstream>
#include "RegisterVariable.hpp"
#include "ConstIntVariable.hpp"
#include "Compiler.hpp"

void RegisterVariable::throwIfTypesDiffer(const VarPtr& ptr, const std::string& operation) {
    if (ptr->getType()->getTypeSpecifier() != type->getTypeSpecifier())
        typeCheckFailure(operation);
}

void
RegisterVariable::typeControl(const VarPtr& ptr, std::vector<TypeSpecifier> expectedTypes, const std::string& operation) {
    if (!typeIn(type->getTypeSpecifier(), std::move(expectedTypes)))
        typeCheckFailure(operation);
    throwIfTypesDiffer(ptr, operation);
}

bool RegisterVariable::isConst() {
    return false;
}

TypePtr RegisterVariable::getType() {
    return type;
}

RegisterVariable::RegisterVariable(std::string reg_, TypePtr type_) : reg(std::move(reg_)), type(type_) {}

std::string RegisterVariable::getCode(Compiler *compiler) {
    return reg;
}

VarPtr RegisterVariable::copy() {
    return VarPtr(new RegisterVariable(reg, type));
}

VarPtr RegisterVariable::twoOp(const VarPtr& ptr, Compiler *compiler, const std::string& operation) {
    throwIfTypesDiffer(ptr, operation);

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Int()));

    if(swap) {
        ss << "\t" << result->getCode(compiler) << " = " << operation << " i32 " << ptr->getCode(compiler) << ", " << this->getCode(compiler);
    } else {
        ss << "\t" << result->getCode(compiler) << " = " << operation << " i32 " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
    }
    swap = false;
    compiler->getCompiledCode().push_back(ss.str());
    return result;
}

VarPtr RegisterVariable::add(const VarPtr& ptr, Compiler *compiler) {
    switch (ptr->getType()->getTypeSpecifier()) {
        case TypeSpecifier::Int:
            return twoOp(ptr, compiler, "add");
        case TypeSpecifier::String: {
            VarPtr result(compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Str())));
            std::stringstream ss;
            if (swap) {
                ss << "\t" << result->getCode(compiler) << " = call i8* @concat(" << type->getTranslation()
                   << " " << ptr->getCode(compiler) << ", " << ptr->getType()->getTranslation() << " " << getCode(compiler) << ")";
            } else {
                ss << "\t" << result->getCode(compiler) << " = call i8* @concat(" << type->getTranslation()
                   << " " << getCode(compiler) << ", " << ptr->getType()->getTranslation() << " " << ptr->getCode(compiler) << ")";
            }
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

VarPtr RegisterVariable::neg(Compiler *compiler) {
    VarPtr e2(new ConstIntVariable(0));
    swap = true;
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

VarPtr RegisterVariable::band(Expr* expr, Compiler *compiler) {
    if (type->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    auto jumpPosition = compiler->getCompiledCode().size();
    auto curr_label = compiler->getCurrentFunction().getLastLabel();

    auto second_exp_label = compiler->getCurrentFunction().getNewLabel({curr_label});
    compiler->getCurrentFunction().setLastLabel(second_exp_label.getLabelNum());
    compiler->getCompiledCode().emplace_back(second_exp_label.getCode());

    expr->accept(compiler);
    auto var2 = compiler->getLastResult();

    if (var2->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("&&");

    auto after_second_exp_label = compiler->getCurrentFunction().getLastLabel();
    auto after_label = compiler->getCurrentFunction().getNewLabel({curr_label, after_second_exp_label});
    compiler->getCurrentFunction().setLastLabel(after_label.getLabelNum());
    std::stringstream jump_ss_e2;
    jump_ss_e2 << "\tbr label %" << after_label.getLabelNum();
    compiler->getCompiledCode().emplace_back(jump_ss_e2.str());
    compiler->getCompiledCode().emplace_back(after_label.getCode());

    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Bool()));
    std::stringstream ss;

    ss << "\t" << result->getCode(compiler) << " = phi i1 [" << 0 << ", %" << curr_label << "], ["
       << var2->getCode(compiler) << ", %" << after_second_exp_label << "]";
    compiler->getCompiledCode().push_back(ss.str());

    std::stringstream jump_ss;
    jump_ss << "\tbr i1 " << getCode(compiler) << ", label %" << second_exp_label.getLabelNum()
            << ", label %" << after_label.getLabelNum();

    compiler->getCompiledCode().insert(compiler->getCompiledCode().begin() + jumpPosition, jump_ss.str());
    return result;
}

VarPtr RegisterVariable::bor(Expr* expr, Compiler *compiler) {

    if (type->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("||");

    auto jumpPosition = compiler->getCompiledCode().size();
    auto curr_label = compiler->getCurrentFunction().getLastLabel();

    auto second_exp_label = compiler->getCurrentFunction().getNewLabel({curr_label});
    compiler->getCurrentFunction().setLastLabel(second_exp_label.getLabelNum());
    compiler->getCompiledCode().emplace_back(second_exp_label.getCode());

    expr->accept(compiler);
    auto var2 = compiler->getLastResult();

    if (var2->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("||");

    auto after_second_exp_label = compiler->getCurrentFunction().getLastLabel();
    auto after_label = compiler->getCurrentFunction().getNewLabel({curr_label, after_second_exp_label});
    compiler->getCurrentFunction().setLastLabel(after_label.getLabelNum());
    std::stringstream jump_ss_e2;
    jump_ss_e2 << "\tbr label %" << after_label.getLabelNum();
    compiler->getCompiledCode().emplace_back(jump_ss_e2.str());
    compiler->getCompiledCode().emplace_back(after_label.getCode());

    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Bool()));
    std::stringstream ss;

    ss << "\t" << result->getCode(compiler) << " = phi i1 [" << 1 << ", %" << curr_label << "], ["
       << var2->getCode(compiler) << ", %" << after_second_exp_label << "]";
    compiler->getCompiledCode().push_back(ss.str());

    std::stringstream jump_ss;
    jump_ss << "\tbr i1 " << getCode(compiler) << ", label %" << after_label.getLabelNum() << ", label %"
            << second_exp_label.getLabelNum();

    compiler->getCompiledCode().insert(compiler->getCompiledCode().begin() + jumpPosition, jump_ss.str());
    return result;
}

VarPtr RegisterVariable::not_(Compiler *compiler) {
    if (type->getTypeSpecifier() != TypeSpecifier::Bool)
        typeCheckFailure("!");

    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Bool()));

    ss << "\t" << result->getCode(compiler) << " = " << "add i1 " << this->getCode(compiler) << ", 1";
    compiler->getCompiledCode().push_back(ss.str());

    return result;
}

VarPtr RegisterVariable::cmp(const VarPtr& ptr, Compiler *compiler, const std::string& operation, const std::string& type) {
    std::stringstream ss;
    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Bool()));

    if(swap) {
        ss << "\t" << result->getCode(compiler) << " = " << "icmp " << operation << " "
           << type << " " << ptr->getCode(compiler) << ", " << this->getCode(compiler);
    } else {
        ss << "\t" << result->getCode(compiler) << " = " << "icmp " << operation << " "
           << type << " " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
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

    switch (ptr->getType()->getTypeSpecifier()) {
        case TypeSpecifier::Int:
            return cmp(ptr, compiler, "eq", "i32");
        case TypeSpecifier::Bool:
            return cmp(ptr, compiler, "eq", "i1");
        case TypeSpecifier::Struct:
            return cmp(ptr, compiler, "eq", ptr->getType()->getTranslation());
        default:
            typeCheckFailure("==");
    }
}

VarPtr RegisterVariable::neq(const VarPtr& ptr, Compiler *compiler) {
    throwIfTypesDiffer(ptr, "!=");

    switch (ptr->getType()->getTypeSpecifier()) {
        case TypeSpecifier::Int:
            return cmp(ptr, compiler, "ne", "i32");
        case TypeSpecifier::Bool:
            return cmp(ptr, compiler, "ne", "i1");
        case TypeSpecifier::Struct:
            return cmp(ptr, compiler, "ne", ptr->getType()->getTranslation());
        default:
            typeCheckFailure("!=");
    }
}

bool RegisterVariable::isEqual(const Variable& b) const {
    auto brv = dynamic_cast<const RegisterVariable&>(b);
    return type == brv.type && reg == brv.reg;
}

VarPtr RegisterVariable::getSize(Compiler *compiler) {
    if (getType()->getTypeSpecifier() != TypeSpecifier::SizedArray) {
        throw std::logic_error("Not an array type.");
    }

    auto size = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Int()));

    std::stringstream ss;
    ss << "\t" << size->getCode(compiler) << " = extractvalue " << type->getTranslation() << " "
       << reg << ", 1";
    compiler->getCompiledCode().emplace_back(ss.str());
    return size;
}

VarPtr RegisterVariable::getArray(Compiler *compiler) {
    if (getType()->getTypeSpecifier() != TypeSpecifier::SizedArray) {
        throw std::logic_error("Not an array type.");
    }

    auto array_type = std::dynamic_pointer_cast<SizedArray>(type);
    auto var = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(array_type->getArray()->clone()));
    std::stringstream ss;
    ss << "\t" << var->getCode(compiler) << " = extractvalue " << array_type->getTranslation() << " "
       << reg << ", 0";
    compiler->getCompiledCode().emplace_back(ss.str());
    return var;
}

PointerVarPtr RegisterVariable::getElementPtr(VarPtr expression, Compiler *compiler) {
    if (getType()->getTypeSpecifier() != TypeSpecifier::Array) {
        throw std::logic_error("Not an array type.");
    }

    if (expression->getType()->getTypeSpecifier() != TypeSpecifier::Int) {
        throw std::logic_error("Array index have to be int.");
    }

    auto array_type = std::dynamic_pointer_cast<Array>(type);
    auto ptr_reg = compiler->getCurrentFunction().getNewRegister();
    auto ptr = std::make_shared<PointerVariable>(TypePtr(array_type->getType_()->clone()), ptr_reg);

    std::stringstream ss;
    ss << "\t" << ptr->getCode(compiler) << " = getelementptr inbounds " << ptr->getType()->getTranslation()
       << ", " << type->getTranslation() << " " << reg << ", i32 " << expression->getCode(compiler);
    compiler->getCompiledCode().emplace_back(ss.str());

    return ptr;
}

VarPtr RegisterVariable::getField(Ident field, Compiler* compiler) {
    if (getType()->getTypeSpecifier() != TypeSpecifier::Struct)
        throw std::logic_error("Not a struct type.");

    auto structType = std::dynamic_pointer_cast<Struct>(getType());
    if (compiler->getStructures().find(structType->ident_) == compiler->getStructures().end())
        throw std::logic_error("Struct type not declared");
    auto structure = compiler->getStructures().at(structType->ident_);

    int offset = structure.getAttribute(field);
    auto pointer_type = structure[offset].second;

    auto ptr = std::make_shared<PointerVariable>(pointer_type, compiler->getCurrentFunction().getNewRegister());

    std::stringstream ss;
    ss << "\t" << ptr->getCode(compiler) << " = getelementptr inbounds " << structure.getTranslation()
       << ", " << getType()->getTranslation() << " " << getCode(compiler) << ", i32 0, i32 " << offset;

    compiler->getCompiledCode().emplace_back(ss.str());
    return ptr;
}
