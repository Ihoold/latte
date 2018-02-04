//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_VARIABLE_HPP
#define INSTANT_VARIABLE_HPP

#include "Absyn.hpp"
#include <memory>

class Compiler;
class Variable;
using VarPtr = std::shared_ptr<Variable>;

void typeCheckFailure(const std::string& operation);

class Variable {
protected:
    friend bool operator==(const Variable&, const Variable&);
    virtual bool isEqual(const Variable& obj) const = 0;
public:
    bool swap = false;

    virtual TypePtr getType() = 0;

    virtual bool isConst() = 0;
    virtual bool isLvalue() {
        return false;
    };
    virtual std::string getCode(Compiler *) = 0;
    virtual VarPtr copy() = 0;
    virtual VarPtr add(const VarPtr&, Compiler*) = 0;
    virtual VarPtr sub(const VarPtr&, Compiler*) = 0;
    virtual VarPtr neg(Compiler*) = 0;
    virtual VarPtr mul(const VarPtr&, Compiler*) = 0;
    virtual VarPtr div(const VarPtr&, Compiler*) = 0;
    virtual VarPtr rem(const VarPtr&, Compiler*) = 0;
    virtual VarPtr band(Expr*, Compiler*) = 0;
    virtual VarPtr bor(Expr*, Compiler*) = 0;
    virtual VarPtr not_(Compiler*) = 0;
    virtual VarPtr lt(const VarPtr&, Compiler*) = 0;
    virtual VarPtr lte(const VarPtr&, Compiler*) = 0;
    virtual VarPtr gt(const VarPtr&, Compiler*) = 0;
    virtual VarPtr gte(const VarPtr&, Compiler*) = 0;
    virtual VarPtr eq(const VarPtr&, Compiler*) = 0;
    virtual VarPtr neq(const VarPtr&, Compiler*) = 0;

    virtual VarPtr getSize(Compiler*) = 0;
    virtual VarPtr getArray(Compiler*) = 0;
    virtual VarPtr getField(Ident, Compiler*) = 0;
    virtual PointerVarPtr getElementPtr(VarPtr, Compiler*) = 0;

    };

#endif //INSTANT_VARIABLE_HPP
