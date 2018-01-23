//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_CONSTBOOLVARIABLE_HPP
#define INSTANT_CONSTBOOLVARIABLE_HPP

#include "ConstVariable.hpp"

class ConstBoolVariable : public ConstVariable {
    bool value;
protected:
    bool isEqual(const Variable& b) const override;
public:
    explicit ConstBoolVariable(bool b = false);

    bool getValue() const;
    std::string getCode(Compiler *compiler) override;
    TypeSpecifier getType() override;
    VarPtr copy() override;

    VarPtr band(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr bor(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr not_(Compiler* compiler) override;

    VarPtr eq(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neq(const VarPtr& ptr, Compiler* compiler) override;
};

#endif //INSTANT_CONSTBOOLVARIABLE_HPP
