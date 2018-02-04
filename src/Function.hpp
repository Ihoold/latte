//
// Created by ihoold on 20.01.18.
//

#ifndef INSTANT_FUNCTION_HPP
#define INSTANT_FUNCTION_HPP

#include "Absyn.hpp"
#include "Variable.hpp"
#include "Label.hpp"
#include "ExtraTypes.hpp"

class PointerVariable;

class Function {
private:
    TypePtr returnType;
    std::vector<std::pair<Ident, VarPtr>> arguments;
    std::vector<std::unordered_map<Ident, PointerVarPtr>> variables;

    int counter = 0;
    int lastLabel = 0;
    int returnStatements = 0;
public:
    Function();
    Function(TypePtr type, std::vector<std::pair<Ident, VarPtr>> args);

    std::string getNewRegister();
    VarPtr getNewRegisterVar(TypePtr);
    Label getNewLabel(std::vector<int> preds);

    void setLastLabel(int lastLabel);
    int getLastLabel() const;

    std::vector<std::pair<Ident, VarPtr>> getArguments() const;
    std::vector<std::unordered_map<Ident, PointerVarPtr>>& getVariables();
    void initVariables(Compiler*, bool = false);
    void clearBlockVariables(Compiler*);
    PointerVarPtr getVar(const Ident id);
    void putVar(const Ident& id, PointerVarPtr& val);

    int getReturnStatements() const;
    void setReturnStatements(int returnStatements);
    const TypePtr getReturnType() const;
};


#endif //INSTANT_FUNCTION_HPP
