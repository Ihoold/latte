//
//    typeControl(ptr, {TypeSpecifier::Bool}, "||");
//
//    std::stringstream ss;
//    auto result = compiler->getCurrentFunction().getNewRegisterVar(TypeSpecifier::Bool);
//
//    ss << "\t" << result->getCode(compiler) << " = " << "or i1 " << this->getCode(compiler) << ", " << ptr->getCode(compiler);
//    compiler->getCompiledCode().push_back(ss.str());
//
//    return result;
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_REGISTERVARIABLE_HPP
#define INSTANT_REGISTERVARIABLE_HPP

#include "Variable.hpp"
#include "ExtraTypes.hpp"
#include <unordered_map>

class RegisterVariable : public Variable {
    std::string reg;
    TypePtr type;
protected:
    bool isEqual(const Variable& b) const override;
public:
    RegisterVariable(std::string reg_,  TypePtr type_);

    bool isConst() override;
    TypePtr getType() override;
    std::string getCode(Compiler *compiler) override;
    VarPtr copy() override;

    VarPtr twoOp(const VarPtr& ptr, Compiler* compiler, const std::string& operation);
    VarPtr add(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr sub(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neg(Compiler* compiler) override;
    VarPtr mul(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr div(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr rem(const VarPtr& ptr, Compiler* compiler) override;

    VarPtr band(Expr* expr, Compiler* compiler) override;
    VarPtr bor(Expr* expr, Compiler* compiler) override;
    VarPtr not_(Compiler* compiler) override;

    VarPtr cmp(const VarPtr& ptr, Compiler* compiler, const std::string& operation, const std::string& type);
    VarPtr lt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr lte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr eq(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neq(const VarPtr& ptr, Compiler* compiler) override;

    VarPtr getSize(Compiler*) override;
    VarPtr getArray(Compiler*) override;
    VarPtr getField(Ident, Compiler*) override;
    PointerVarPtr getElementPtr(VarPtr expression, Compiler *compiler) override;

private:
    void throwIfTypesDiffer(const VarPtr& ptr, const std::string& operation);
    void typeControl(const VarPtr& ptr, std::vector<TypeSpecifier> expectedTypes, const std::string& operation);

};


#endif //INSTANT_REGISTERVARIABLE_HPP
