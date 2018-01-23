//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_REGISTERVARIABLE_HPP
#define INSTANT_REGISTERVARIABLE_HPP

#include "Variable.hpp"

class RegisterVariable : public Variable {
    std::string reg;
    TypeSpecifier type;
protected:
    bool isEqual(const Variable& b) const override;
public:
    RegisterVariable(std::string reg_, TypeSpecifier _type);

    bool isConst() override;
    TypeSpecifier getType() override;
    std::string getCode(Compiler *compiler) override;
    VarPtr copy() override;

    VarPtr twoOp(const VarPtr& ptr, Compiler* compiler, const std::string& operation);
    VarPtr add(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr sub(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neg(Compiler* compiler) override;
    VarPtr mul(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr div(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr rem(const VarPtr& ptr, Compiler* compiler) override;

    void incr(Compiler *compiler) override;
    void decr(Compiler *compiler) override;

    VarPtr band(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr bor(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr not_(Compiler* compiler) override;

    VarPtr cmp(const VarPtr& ptr, Compiler* compiler, const std::string& operation, const std::string& type);
    VarPtr lt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr lte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr eq(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neq(const VarPtr& ptr, Compiler* compiler) override;

private:
    void throwIfTypesDiffer(const VarPtr& ptr, const std::string& operation);
    void typeControl(const VarPtr& ptr, std::vector<TypeSpecifier> expectedTypes, const std::string& operation);
};


#endif //INSTANT_REGISTERVARIABLE_HPP
