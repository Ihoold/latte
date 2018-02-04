//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_CONSTVARIABLE_HPP
#define INSTANT_CONSTVARIABLE_HPP

#include "Variable.hpp"
#include "ExtraTypes.hpp"

class ConstVariable : public Variable {
protected:
    virtual bool isEqual(const Variable& b) const = 0;
public:
    bool isConst() override {
        return true;
    }

    static VarPtr getConstDefault(TypePtr t);

    VarPtr add(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("+");
    }
    VarPtr sub(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("-");
    }
    VarPtr neg(Compiler *compiler) override {
        typeCheckFailure("-");
    }
    VarPtr mul(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("*");
    }
    VarPtr div(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("/");
    }
    VarPtr rem(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("%");
    }
    VarPtr band(Expr* expr, Compiler *compiler) override {
        typeCheckFailure("&&");
    }
    VarPtr bor(Expr* expr, Compiler *compiler) override {
        typeCheckFailure("||");
    }
    VarPtr not_(Compiler *compiler) override {
        typeCheckFailure("!");
    }
    VarPtr lt(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("<");
    }
    VarPtr lte(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("<=");
    }
    VarPtr gt(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure(">");
    }
    VarPtr gte(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure(">=");
    }
    VarPtr eq(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("==");
    }
    VarPtr neq(const VarPtr& ptr, Compiler *compiler) override {
        typeCheckFailure("!=");
    }
    VarPtr getSize(Compiler*) override {
        typeCheckFailure(".length");
    }
    VarPtr getArray(Compiler*) override {
        typeCheckFailure("[]");
    }
    VarPtr getField(Ident, Compiler*) override {
        typeCheckFailure(".");
    }
    PointerVarPtr getElementPtr(VarPtr expression, Compiler *compiler) override {
        typeCheckFailure("[]");
    }

    VarPtr copy() override = 0;
};

#endif //INSTANT_CONSTVARIABLE_HPP
