//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_FUNCTION_HPP
#define INSTANT_FUNCTION_HPP

#include "Absyn.hpp"
#include "Variable.hpp"
#include "Label.hpp"

class Function {
private:
    TypeSpecifier returnType = TypeSpecifier::None;
    std::vector<std::pair<Ident, VarPtr>> arguments;
    std::vector<std::unordered_map<Ident, VarPtr>> variables;

    int counter = 0;
    int lastLabel = 0;
    int returnStatements = 0;
public:
    Function() = default;
    Function(TypeSpecifier type, std::vector<std::pair<Ident, VarPtr>> args);

    std::shared_ptr<Variable> getNewRegisterVar(TypeSpecifier);
    Label getNewLabel(std::vector<int> preds);

    void setLastLabel(int lastLabel);
    int getLastLabel() const;

    std::vector<std::pair<Ident, VarPtr>> getArguments() const;
    std::vector<std::unordered_map<Ident, VarPtr>>& getVariables();
    void initVariables();
    void clearBlockVariables();
    VarPtr getVar(const Ident& id);
    void putVar(const Ident& id, const VarPtr& val);
    void changeVar(const Ident& id, VarPtr val);

    int getReturnStatements() const;
    void setReturnStatements(int returnStatements);
    const TypeSpecifier getReturnType() const;
};


#endif //INSTANT_FUNCTION_HPP
