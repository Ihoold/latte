//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_CONSTINTVARIABLE_HPP
#define INSTANT_CONSTINTVARIABLE_HPP

#include "ConstVariable.hpp"

class ConstIntVariable : public ConstVariable {
    int value;
protected:
    bool isEqual(const Variable& b) const override;
public:
    explicit ConstIntVariable(int i = 0);

    std::string getCode(Compiler *compiler) override;
    TypeSpecifier getType() override;
    VarPtr copy() override;

    VarPtr add(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr sub(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neg(Compiler *compiler) override;
    VarPtr mul(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr div(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr rem(const VarPtr& ptr, Compiler* compiler) override;

    void incr(Compiler *compiler) override;
    void decr(Compiler *compiler) override;

    VarPtr lt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr lte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gt(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr gte(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr eq(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neq(const VarPtr& ptr, Compiler* compiler) override;
};

#endif //INSTANT_CONSTINTVARIABLE_HPP
