//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_CONSTSTRINGVARIABLE_HPP
#define INSTANT_CONSTSTRINGVARIABLE_HPP

#include "ConstVariable.hpp"

class ConstStringVariable : public ConstVariable {
    std::string value;
public:
    explicit ConstStringVariable(std::string v = "");;

    const std::string& getValue() const;
    VarPtr copy() override;
    TypeSpecifier getType() override;
    std::string getCode(Compiler *compiler) override;

    VarPtr add(const VarPtr& ptr, Compiler* compiler) override;
};

#endif //INSTANT_CONSTSTRINGVARIABLE_HPP