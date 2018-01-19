#ifndef COMPILER_HEADER
#define COMPILER_HEADER
/* You might want to change the above name. */

#include <stdexcept>
#include "Absyn.hpp"
#include <memory>
#include <unordered_map>
#include <utility>
#include <set>
#include <sstream>

class Variable;
class Compiler;
class Function;
class ConstIntVariable;
class ConstBoolVariable;
class RegisterVariable;

using Code = std::vector<std::string>;
using VarPtr = std::shared_ptr<Variable>;
using VarAndCode = std::pair<VarPtr , Code>;

void typeCheckFailure(const std::string& operation);

class Variable {
public:
    bool swap = false;

    virtual TypeSpecifier getType() = 0;

    virtual bool isConst() {
        return false;
    };
    virtual std::string getCode() = 0;
    virtual VarPtr copy() = 0;
    virtual VarPtr add(VarPtr, Compiler*) = 0;
    virtual void incr(Compiler*) = 0;
    virtual void decr(Compiler*) = 0;
    virtual VarPtr sub(VarPtr, Compiler*) = 0;
    virtual VarPtr mul(VarPtr, Compiler*) = 0;
    virtual VarPtr div(VarPtr, Compiler*) = 0;
    virtual VarPtr rem(VarPtr, Compiler*) = 0;
    virtual VarPtr band(VarPtr, Compiler*) = 0;
    virtual VarPtr bor(VarPtr, Compiler*) = 0;
    virtual VarPtr not_(Compiler*) = 0;
    virtual VarPtr lt(VarPtr, Compiler*) = 0;
    virtual VarPtr lte(VarPtr, Compiler*) = 0;
    virtual VarPtr gt(VarPtr, Compiler*) = 0;
    virtual VarPtr gte(VarPtr, Compiler*) = 0;
    virtual VarPtr eq(VarPtr, Compiler*) = 0;
    virtual VarPtr neq(VarPtr, Compiler*) = 0;
};

class Function {
private:
    TypeSpecifier returnType = TypeSpecifier::None;
    std::vector<std::pair<Ident, VarPtr>> arguments;
    std::unordered_map<Ident, VarPtr> variables;
public:
    int returnStatements = 0;
    Function() = default;
    Function(TypeSpecifier type, std::vector<std::pair<Ident, VarPtr>> args)
            : returnType(type), arguments(std::move(args)) {}

    void initVariables() {
        variables.clear();
        for (auto arg : arguments) {
            variables[arg.first] = arg.second->copy();
        }
    }

    void setVariables(const std::unordered_map<Ident, VarPtr>& variables) {
        Function::variables = variables;
    }

    std::vector<std::pair<Ident, VarPtr>> getArguments() const {
        return arguments;
    }

    std::unordered_map<Ident, VarPtr>& getVariables() {
        return variables;
    }

    const TypeSpecifier getReturnType() const {
        return returnType;
    }

};

class Compiler : public Visitor {
private:
    enum class Phase {
        SCANNING_DEFINITIONS, COMPILING
    };
    Phase currentPhase = Phase::SCANNING_DEFINITIONS;
    std::unordered_map<Ident, Function> functions;
    VarPtr lastResult;
    Function currentFunction;
    TypeSpecifier declaredType;
    Code compiledCode;
    int counter = 0;

    bool typesAreEqual(TypeSpecifier t1, TypeSpecifier t2);

    void reportError(std::string&& msg, int line);

    void typesNotSupported(const std::string& operation, int line);

public:
    std::shared_ptr<Variable> getNewRegisterVar(TypeSpecifier);

    Compiler() : lastResult(nullptr), declaredType(TypeSpecifier::None) {};

    void visitProgram(Program *p) override;

    void visitTopDef(TopDef *p) override;

    void visitArg(Arg *p) override;

    void visitBlock(Block *p) override;

    void visitStmt(Stmt *p) override;

    void visitItem(Item *p) override;

    void visitType(Type *p) override;

    void visitExpr(Expr *p) override;

    void visitAddOp(AddOp *p) override;

    void visitMulOp(MulOp *p) override;

    void visitRelOp(RelOp *p) override;

    void visitProg(Prog *p) override;

    void visitFnDef(FnDef *p) override;

    void visitAr(Ar *p) override;

    void visitBlk(Blk *p) override;

    void visitEmpty(Empty *p) override;

    void visitBStmt(BStmt *p) override;

    void visitDecl(Decl *p) override;

    void visitNoInit(NoInit *p) override;

    void visitInit(Init *p) override;

    void visitAss(Ass *p) override;

    void visitIncr(Incr *p) override;

    void visitDecr(Decr *p) override;

    void visitRet(Ret *p) override;

    void visitVRet(VRet *p) override;

    void visitCond(Cond *p) override;

    void visitCondElse(CondElse *p) override;

    void visitWhile(While *p) override;

    void visitSExp(SExp *p) override;

    void visitInt(Int *p) override;

    void visitStr(Str *p) override;

    void visitBool(Bool *p) override;

    void visitVoid(Void *p) override;

    void visitFun(Fun *p) override;

    void visitEVar(EVar *p) override;

    void visitELitInt(ELitInt *p) override;

    void visitELitTrue(ELitTrue *p) override;

    void visitELitFalse(ELitFalse *p) override;

    void visitEApp(EApp *p) override;

    void visitEString(EString *p) override;

    void visitNeg(Neg *p) override;

    void visitNot(Not *p) override;

    void visitEMul(EMul *p) override;

    void visitEAdd(EAdd *p) override;

    void visitERel(ERel *p) override;

    void visitEAnd(EAnd *p) override;

    void visitEOr(EOr *p) override;

    void visitPlus(Plus *p) override;

    void visitMinus(Minus *p) override;

    void visitTimes(Times *p) override;

    void visitDiv(Div *p) override;

    void visitMod(Mod *p) override;

    void visitLTH(LTH *p) override;

    void visitLE(LE *p) override;

    void visitGTH(GTH *p) override;

    void visitGE(GE *p) override;

    void visitEQU(EQU *p) override;

    void visitNE(NE *p) override;

    void visitListTopDef(ListTopDef *p) override;

    void visitListArg(ListArg *p) override;

    void visitListStmt(ListStmt *p) override;

    void visitListItem(ListItem *p) override;

    void visitListType(ListType *p) override;

    void visitListExpr(ListExpr *p) override;

    void visitInteger(Integer x) override;

    void visitChar(Char x) override;

    void visitDouble(Double x) override;

    void visitString(String x) override;

    void visitIdent(Ident x) override;

    Code& getCompiledCode() {
        return compiledCode;
    }
};


class ConstVariable : public Variable {
public:
    bool isConst() override {
        return true;
    }

    static VarPtr getConstDefault(TypeSpecifier t);

    VarPtr add(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("+");
    }
    VarPtr sub(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("-");
    }
    void incr(Compiler *compiler) override {
        typeCheckFailure("++");
    }
    void decr(Compiler *compiler) override {
        typeCheckFailure("--");
    }
    VarPtr mul(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("*");
    }
    VarPtr div(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("/");
    }
    VarPtr rem(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("%");
    }
    VarPtr band(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("&&");
    }
    VarPtr bor(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("||");
    }
    VarPtr not_(Compiler *compiler) override {
        typeCheckFailure("!");
    }
    VarPtr lt(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("<");
    }
    VarPtr lte(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("<=");
    }
    VarPtr gt(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure(">");
    }
    VarPtr gte(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure(">=");
    }
    VarPtr eq(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("==");
    }
    VarPtr neq(VarPtr ptr, Compiler *compiler) override {
        typeCheckFailure("!=");
    }
    VarPtr copy() override = 0;
};

class ConstStringVariable : public ConstVariable {
    std::string value;
public:
    explicit ConstStringVariable(std::string v = "") : value(std::move(v)) {};

    const std::string& getValue() const {
        return value;
    }

    VarPtr copy() override {
        return VarPtr(new ConstStringVariable(value));
    }

    TypeSpecifier getType() override {
        return TypeSpecifier::String;
    }

    std::string getCode() override {
        throw std::logic_error("Cannot use const string.");
    }

    VarPtr add(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::String)
            typeCheckFailure("+");

        if (ptr->isConst()) {
            auto strVar = dynamic_cast<ConstStringVariable*>(ptr.get());
            return VarPtr(new ConstStringVariable(value + strVar->getValue()));
        } else {
            // TODO
        }
    }
};

class ConstBoolVariable : public ConstVariable {
    bool value;
public:
    explicit ConstBoolVariable(bool b = false) : value(b) {};

    bool getValue() const {
        return value;
    }

    std::string getCode() override {
        return (value) ? "true" : "false";
    }

    TypeSpecifier getType() override {
        return TypeSpecifier::Bool;
    }

    void switchValue() {
        value = !value;
    }

    VarPtr copy() override {
        return VarPtr(new ConstBoolVariable(value));
    }

    VarPtr band(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Bool)
            typeCheckFailure("&&");

        if (!value) {
            return VarPtr(new ConstBoolVariable(false));
        } else {
            return ptr;
        }
    }

    VarPtr bor(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Bool)
            typeCheckFailure("&&");

        if (value) {
            return VarPtr(new ConstBoolVariable(true));
        } else {
            return ptr;
        }
    }

    VarPtr not_(Compiler* compiler) override {
        return VarPtr(new ConstBoolVariable(not value));
    }

    VarPtr eq(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Bool)
            typeCheckFailure("&&");

        if (ptr->isConst()) {
            auto boolVar1 = dynamic_cast<ConstBoolVariable*>(ptr.get());
            return VarPtr(new ConstBoolVariable(boolVar1->value == value));
        } else {
            return ptr->eq(VarPtr(new ConstBoolVariable(value)), compiler);
        }
    }

    VarPtr neq(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Bool)
            typeCheckFailure("&&");

        if (ptr->isConst()) {
            auto boolVar1 = dynamic_cast<ConstBoolVariable*>(ptr.get());
            return VarPtr(new ConstBoolVariable(boolVar1->value != value));
        } else {
            return ptr->neq(VarPtr(new ConstBoolVariable(value)), compiler);
        }
    }
};

class ConstIntVariable : public ConstVariable {
public:
    int value;
    explicit ConstIntVariable(int i = 0) : value(i) {};

    std::string getCode() override {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    TypeSpecifier getType() override {
        return TypeSpecifier::Int;
    }

    VarPtr copy() override {
        return VarPtr(new ConstIntVariable(value));
    }

    VarPtr add(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("+");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value + intVar1->value));
        } else {
            return ptr->add(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr sub(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("-");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value - intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->sub(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    void incr(Compiler *compiler) override {
        value++;
    }

    void decr(Compiler *compiler) override {
        value--;
    }

    VarPtr mul(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("*");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return {VarPtr(new ConstIntVariable(value * intVar1->value)), {}};
        } else {
            return ptr->mul(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr div(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("/");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value / intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->div(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr rem(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("%");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value % intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->rem(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr lt(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("<");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value < intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->lt(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr lte(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("<=");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value <= intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->lte(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr gt(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure(">");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value > intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->gt(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr gte(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure(">=");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value >= intVar1->value));
        } else {
            ptr->swap = true;
            return ptr->gte(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr eq(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("==");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value == intVar1->value));
        } else {
            return ptr->eq(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }

    VarPtr neq(VarPtr ptr, Compiler* compiler) override {
        if (ptr->getType() != TypeSpecifier::Int)
            typeCheckFailure("!=");

        if (ptr->isConst()) {
            auto intVar1 = dynamic_cast<ConstIntVariable*>(ptr.get());
            return VarPtr(new ConstIntVariable(value != intVar1->value));
        } else {
            return ptr->neq(VarPtr(new ConstIntVariable(value)), compiler);
        }
    }
};

class RegisterVariable : public Variable {
    std::string reg;
    TypeSpecifier type;

    void throwIfTypesDiffer(const VarPtr& ptr, std::string operation) {
        if (ptr->getType() != type)
            typeCheckFailure(std::move(operation));
    }

    void typeControl(VarPtr ptr, std::vector<TypeSpecifier> expectedTypes, std::string operation) {
        if (!typeIn(type, expectedTypes))
            typeCheckFailure(operation);
        throwIfTypesDiffer(ptr, operation);
    }
public:

    bool isConst() override {
        return false;
    }

    TypeSpecifier getType() override {
        return type;
    }

    RegisterVariable(std::string reg_, TypeSpecifier _type) : reg(std::move(reg_)), type(_type) {}

    std::string getCode() override {
        return reg;
    }

    VarPtr copy() override {
        return VarPtr(new RegisterVariable(reg, type));
    }

    VarPtr twoOp(const VarPtr& ptr, Compiler* compiler, const std::string& operation) {
        throwIfTypesDiffer(ptr, operation);

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Int);

        if(swap) {
            ss << "\t" << result->getCode() << " = " << operation << " i32 " << this->getCode() << ", " << ptr->getCode();
        } else {
            ss << "\t" << result->getCode() << " = " << operation << " i32 " << ptr->getCode() << ", " << this->getCode();
        }
        swap = false;
        compiler->getCompiledCode().push_back(ss.str());
        return result;
    }

    VarPtr add(VarPtr ptr, Compiler* compiler) override {
        switch (ptr->getType()) {
            case TypeSpecifier::Int:
                return twoOp(ptr, compiler, "iadd");
            case TypeSpecifier::String: {
                VarPtr result(compiler->getNewRegisterVar(TypeSpecifier::String));
                std::stringstream ss;
                ss << "\t" << result->getCode() << " = call i8* @concat(" << getCode() << ", " << ptr->getCode()
                   << ")";
                compiler->getCompiledCode().push_back(ss.str());
                return result;
            }
            default:
                typeCheckFailure("!=");
        }
    }

    VarPtr sub(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "-");
        return twoOp(ptr, compiler, "isub");
    }

    void incr(Compiler *compiler) override {
        if(type != TypeSpecifier::Int)
            typeCheckFailure("++");

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Int);

        ss << "\t" << result->getCode() << " = iadd i32 " << this->getCode() << ", " << "1";
        compiler->getCompiledCode().push_back(ss.str());
    }

    void decr(Compiler *compiler) override {
        if(type != TypeSpecifier::Int)
            typeCheckFailure("--");

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Int);

        ss << "\t" << result->getCode() << " = isub i32 " << this->getCode() << ", " << "1";
        compiler->getCompiledCode().push_back(ss.str());

    }

    VarPtr mul(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "*");
        return twoOp(ptr, compiler, "imul");
    }

    VarPtr div(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "/");
        return twoOp(ptr, compiler, "sdiv");
    }

    VarPtr rem(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "%");
        return twoOp(ptr, compiler, "srem");
    }

    VarPtr band(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Bool}, "&&");

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Bool);

        ss << "\t" << result->getCode() << " = " << "and i1 " << this->getCode() << ", " << ptr->getCode();
        compiler->getCompiledCode().push_back(ss.str());

        return result;
    }

    VarPtr bor(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Bool}, "||");

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Bool);

        ss << "\t" << result->getCode() << " = " << "or i1 " << this->getCode() << ", " << ptr->getCode();
        compiler->getCompiledCode().push_back(ss.str());

        return result;
    }

    VarPtr not_(Compiler* compiler) override {
        if (type != TypeSpecifier::Bool)
            typeCheckFailure("!");

        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Bool);

        ss << "\t" << result->getCode() << " = " << "iadd i1 " << this->getCode() << ", 1";
        compiler->getCompiledCode().push_back(ss.str());

        return result;
    }

    VarPtr cmp(const VarPtr& ptr, Compiler* compiler, const std::string& operation, const std::string& type) {
        std::stringstream ss;
        auto result = compiler->getNewRegisterVar(TypeSpecifier::Bool);

        if(swap) {
            ss << "\t" << result->getCode() << " = " << "icmp " << operation << " "
               << type << this->getCode() << ", " << ptr->getCode();
        } else {
            ss << "\t" << result->getCode() << " = " << "icmp " << operation << " "
               << type << ptr->getCode() << ", " << this->getCode();
        }
        swap = false;
        compiler->getCompiledCode().push_back(ss.str());
        return result;
    }

    VarPtr lt(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "<");
        return cmp(ptr, compiler, "slt", "i32");
    }

    VarPtr lte(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, "<=");
        return cmp(ptr, compiler, "sle", "i32");
    }

    VarPtr gt(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, ">");
        return cmp(ptr, compiler, "sgt", "i32");
    }

    VarPtr gte(VarPtr ptr, Compiler* compiler) override {
        typeControl(ptr, {TypeSpecifier::Int}, ">=");
        return cmp(ptr, compiler, "sge", "i32");
    }

    VarPtr eq(VarPtr ptr, Compiler* compiler) override {
        throwIfTypesDiffer(ptr, "==");

        switch (ptr->getType()) {
            case TypeSpecifier::Int:
                return cmp(ptr, compiler, "eq", "i32");
            case TypeSpecifier::Bool:
                return cmp(ptr, compiler, "eq", "i1");
            default:
                typeCheckFailure("==");
        }
    }

    VarPtr neq(VarPtr ptr, Compiler* compiler) override {
        throwIfTypesDiffer(ptr, "!=");

        switch (ptr->getType()) {
            case TypeSpecifier::Int:
                return cmp(ptr, compiler, "neq", "i32");
            case TypeSpecifier::Bool:
                return cmp(ptr, compiler, "neq", "i1");
            default:
                typeCheckFailure("!=");
        }
    }
};

class CompilationException : public std::logic_error {
private:
    int line_num;
public:
    CompilationException(const std::string& what, int line) : std::logic_error(what), line_num(line) {};

    int getLine_num() const {
        return line_num;
    }
};

#endif
