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
public:
    bool swap = false;

    virtual TypeSpecifier getType() = 0;

    virtual bool isConst() = 0;
    virtual std::string getCode(Compiler *) = 0;
    virtual VarPtr copy() = 0;
    virtual VarPtr add(const VarPtr&, Compiler*) = 0;
    virtual void incr(Compiler*) = 0;
    virtual void decr(Compiler*) = 0;
    virtual VarPtr sub(const VarPtr&, Compiler*) = 0;
    virtual VarPtr neg(Compiler*) = 0;
    virtual VarPtr mul(const VarPtr&, Compiler*) = 0;
    virtual VarPtr div(const VarPtr&, Compiler*) = 0;
    virtual VarPtr rem(const VarPtr&, Compiler*) = 0;
    virtual VarPtr band(const VarPtr&, Compiler*) = 0;
    virtual VarPtr bor(const VarPtr&, Compiler*) = 0;
    virtual VarPtr not_(Compiler*) = 0;
    virtual VarPtr lt(const VarPtr&, Compiler*) = 0;
    virtual VarPtr lte(const VarPtr&, Compiler*) = 0;
    virtual VarPtr gt(const VarPtr&, Compiler*) = 0;
    virtual VarPtr gte(const VarPtr&, Compiler*) = 0;
    virtual VarPtr eq(const VarPtr&, Compiler*) = 0;
    virtual VarPtr neq(const VarPtr&, Compiler*) = 0;
};

#endif //INSTANT_VARIABLE_HPP
