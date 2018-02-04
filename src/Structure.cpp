//
// Created by ihoold on 30.01.18.
//

#include <sstream>
#include <utility>
#include "Structure.hpp"
#include "Compiler.hpp"
#include "ConstVariable.hpp"

Structure::Structure(Ident name_) : name(std::move(name_)) {}

int Structure::getAttribute(const Ident& id) {
    for (int i = 0; i < size(); i++) {
        if (at(i).first == id)
            return i;
    }

    throw std::logic_error("Structure attribute not found.");
}

VarPtr Structure::getSize(Compiler* compiler) {
    auto size_ptr = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Struct(name)));
    std::stringstream ss_size;
    ss_size << "\t" << size_ptr->getCode(compiler) << " = getelementptr inbounds "
            << this->getTranslation() << ", " << size_ptr->getType()->getTranslation() << " null, i32 1";
    compiler->getCompiledCode().emplace_back(ss_size.str());

    auto size_int = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Int()));
    std::stringstream ss_size_int;
    ss_size_int << "\t" << size_int->getCode(compiler) << " = ptrtoint "
                << size_ptr->getType()->getTranslation() << " " << size_ptr->getCode(compiler) << " to i32";
    compiler->getCompiledCode().emplace_back(ss_size_int.str());

    return size_int;
}


std::string Structure::getTranslation() {
    return "%struct." + name;
}

VarPtr Structure::allocateStruct(Compiler* compiler) {
    auto size = getSize(compiler);

    auto void_ptr = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Str()));
    std::stringstream ss_malloc;
    ss_malloc << "\t" << void_ptr->getCode(compiler) << " = call i8* @malloc(i32 "
              << size->getCode(compiler) << ")";
    compiler->getCompiledCode().emplace_back(ss_malloc.str());

    auto casted_ptr = compiler->getCurrentFunction().getNewRegisterVar(TypePtr(new Struct(name)));
    std::stringstream ss_bitcast;
    ss_bitcast << "\t" << casted_ptr->getCode(compiler) << " = bitcast i8* " << void_ptr->getCode(compiler)
               << " to " << casted_ptr->getType()->getTranslation();
    compiler->getCompiledCode().emplace_back(ss_bitcast.str());

    for (const auto& attr : *this) {
        auto ptrToAttr = casted_ptr->getField(attr.first, compiler);
        auto castedPtrToAttr = std::dynamic_pointer_cast<PointerVariable>(ptrToAttr);
        castedPtrToAttr->store(ConstVariable::getConstDefault(ptrToAttr->getType()), compiler);
    }

    return casted_ptr;
}

const Ident& Structure::getName() const {
    return name;
}
