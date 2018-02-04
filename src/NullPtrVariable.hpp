//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_CONSTPTRVARIABLE_HPP
#define INSTANT_CONSTPTRVARIABLE_HPP

#include "ConstVariable.hpp"

class NullPtrVariable : public ConstVariable {
    TypePtr type;
protected:
    bool isEqual(const Variable& b) const override;;
public:
    explicit NullPtrVariable(TypePtr t);;

    std::string getCode(Compiler *compiler) override;
    TypePtr getType() override;;
    VarPtr copy() override;

    VarPtr eq(const VarPtr& ptr, Compiler* compiler) override;
    VarPtr neq(const VarPtr& ptr, Compiler* compiler) override;
};

#endif //INSTANT_CONSTPTRVARIABLE_HPP
