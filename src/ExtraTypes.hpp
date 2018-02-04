//
// Created by ihoold on 31.01.18.
//

#ifndef LATTE_EXTRATYPES_HPP
#define LATTE_EXTRATYPES_HPP

#include <memory>

class PointerVariable;
using PointerVarPtr = std::shared_ptr<PointerVariable>;

#include "Variable.hpp"

class SizedArray : public Type {
    std::shared_ptr<Array> array;
public:
    explicit SizedArray(std::shared_ptr<Array> array);

    void accept(Visitor *v) override;

    Type *clone() const override;

    const TypeSpecifier getTypeSpecifier() const override;

    std::string getTranslation() const override;

    const std::shared_ptr<Array>& getArray() const;

    VarPtr getElementSize(Compiler*);

    VarPtr allocateArray(VarPtr, Compiler*);

    VarPtr createArrayStruct(VarPtr, VarPtr, Compiler*);
};

class PointerVariable : public Variable {
    TypePtr type;
    std::string reg;
protected:
    bool isEqual(const Variable& obj) const override;
public:
    PointerVariable(TypePtr, Compiler*);
    PointerVariable(TypePtr, std::string);
    void store(VarPtr, Compiler*);
    VarPtr load(Compiler*);

    TypePtr getType() override;

    bool isLvalue() override;
    bool isConst() override;

    std::string getCode(Compiler *compiler) override;

    VarPtr copy() override;

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

};

#endif //LATTE_EXTRATYPES_HPP
