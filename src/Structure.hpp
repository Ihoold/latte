//
// Created by ihoold on 30.01.18.
//

#ifndef LATTE_STRUCTURE_HPP
#define LATTE_STRUCTURE_HPP


#include <vector>
#include "Absyn.hpp"

class Structure : public std::vector<std::pair<Ident, TypePtr>> {
    Ident name;
public:
    explicit Structure(Ident name_);

    int getAttribute(const Ident& id);

    VarPtr getSize(Compiler*);
    VarPtr allocateStruct(Compiler*);

    std::string getTranslation();
};


#endif //LATTE_STRUCTURE_HPP
