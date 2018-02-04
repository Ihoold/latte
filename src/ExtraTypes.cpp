//
// Created by ihoold on 31.01.18.
//

#include "ExtraTypes.hpp"
#include "Compiler.hpp"

void SizedArray::accept(Visitor *v) {
    assert(false);
}

Type *SizedArray::clone() const {
    return new SizedArray(array);
}

const TypeSpecifier SizedArray::getTypeSpecifier() const {
    return TypeSpecifier::SizedArray;
}

std::string SizedArray::getTranslation() const {
    return "{ " + array->getTranslation() + ", i32 }";
}

SizedArray::SizedArray(std::shared_ptr<Array> array) : array(std::move(array)) {}

const std::shared_ptr<Array>& SizedArray::getArray() const {
    return array;
}

VarPtr SizedArray::getElementSize(Compiler *compiler) {
    auto size_ptr = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(array->clone()));
    std::stringstream ss_size;
    ss_size << "\t" << size_ptr->getCode(compiler) << " = getelementptr inbounds "
            << array->getType_()->getTranslation() << ", " << size_ptr->getType()->getTranslation() << " null, i32 1";
    compiler->getCompiledCode().emplace_back(ss_size.str());

    auto size_int = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Int()));
    std::stringstream ss_size_int;
    ss_size_int << "\t" << size_int->getCode(compiler) << " = ptrtoint "
                << size_ptr->getType()->getTranslation() << " " << size_ptr->getCode(compiler) << " to i32";
    compiler->getCompiledCode().emplace_back(ss_size_int.str());

    return size_int;
}

VarPtr SizedArray::allocateArray(VarPtr expr, Compiler* compiler) {
    auto elemSize = getElementSize(compiler);

    auto void_ptr = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Str()));
    std::stringstream ss_malloc;
    ss_malloc << "\t" << void_ptr->getCode(compiler) << " = call i8* @calloc(i32 "
              << elemSize->getCode(compiler) << ", i32 " << expr->getCode(compiler) << ")";
    compiler->getCompiledCode().emplace_back(ss_malloc.str());

    auto casted_ptr = compiler->getCurrentFunction().getNewRegisterVar(array);
    std::stringstream ss_bitcast;
    ss_bitcast << "\t" << casted_ptr->getCode(compiler) << " = bitcast i8* " << void_ptr->getCode(compiler)
               << " to " << casted_ptr->getType()->getTranslation();
    compiler->getCompiledCode().emplace_back(ss_bitcast.str());

    return casted_ptr;
}

VarPtr SizedArray::createArrayStruct(VarPtr array, VarPtr size, Compiler *compiler) {
    auto var_1 = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(this->clone()));

    std::stringstream ss;
    ss << "\t" << var_1->getCode(compiler) << " = insertvalue " << this->getTranslation() << " "
       << "undef, i32 " << size->getCode(compiler) << ", 1";
    compiler->getCompiledCode().emplace_back(ss.str());

    auto var_2 = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(this->clone()));
    std::stringstream ss_insert_array;
    ss_insert_array << "\t" << var_2->getCode(compiler) << " = insertvalue " << this->getTranslation() << " "
       << var_1->getCode(compiler) << ", " << array->getType()->getTranslation() << " " << array->getCode(compiler) << ", 0";
    compiler->getCompiledCode().emplace_back(ss_insert_array.str());

    return var_2;
}

PointerVariable::PointerVariable(TypePtr type_, Compiler* compiler)
        : type(type_->clone()) {
    reg = compiler->getCurrentFunction().getNewRegister();
    std::stringstream ss;
    ss << "\t" << reg << " = alloca " << type_->getTranslation();
    compiler->getCompiledCode().emplace_back(ss.str());
}

void PointerVariable::store(VarPtr variable, Compiler* compiler) {
    assert(*variable->getType() == *type);
    std::stringstream ss;
    ss << "\tstore " << variable->getType()->getTranslation() << " " << variable->getCode(compiler)
       << ", " << type->getTranslation() << "* " << reg;
    compiler->getCompiledCode().emplace_back(ss.str());
}

VarPtr PointerVariable::load(Compiler* compiler) {
    auto var = compiler->getCurrentFunction().getNewRegisterVar(type);
    std::stringstream ss;
    ss << "\t" << var->getCode(compiler) << " = load " << type->getTranslation() << ", "
       << type->getTranslation() << "* " << reg;
    compiler->getCompiledCode().emplace_back(ss.str());
    return var;
}

TypePtr PointerVariable::getType() {
    return type;
}

bool PointerVariable::isConst() {
    return false;
}

std::string PointerVariable::getCode(Compiler *compiler) {
    return reg;
}

VarPtr PointerVariable::copy() {
    return VarPtr(new PointerVariable(type, reg));
}

bool PointerVariable::isEqual(const Variable& obj) const {
    auto hv = dynamic_cast<const PointerVariable&>(obj);
    return type == hv.type && reg == hv.reg;
}

PointerVariable::PointerVariable(TypePtr type_, std::string reg_) : type(std::move(type_)), reg(reg_) {}

bool PointerVariable::isLvalue() {
    return true;
}
