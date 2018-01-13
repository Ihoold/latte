#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include <stdexcept>
#include "Absyn.hpp"
#include <memory>
#include <unordered_map>
#include <utility>

class ExpResult {
private:
    TypeSpecifier type;
public:
    ExpResult() : type(TypeSpecifier::None) {};
    ExpResult(TypeSpecifier t) : type(t) {};

    const TypeSpecifier getType() const {
        return type;
    }

    void setType(TypeSpecifier _type) {
        type = _type;
    }
};

class Function {
private:
    TypeSpecifier returnType = TypeSpecifier::None;
    std::vector<std::pair<Ident, TypeSpecifier>> arguments;
    std::unordered_map<Ident, ExpResult> variables;
public:
    int returnStatements = 0;
    Function() = default;
    Function(TypeSpecifier type, std::vector<std::pair<Ident, TypeSpecifier>> args)
            : returnType(type), arguments(std::move(args)) {}

    void initVariables() {
        variables.clear();
        for (auto arg : arguments) {
            variables[arg.first] = ExpResult(arg.second);
        }
    }

    void setVariables(const std::unordered_map<Ident, ExpResult>& variables) {
        Function::variables = variables;
    }

    std::vector<std::pair<Ident, TypeSpecifier>> getArguments() const {
        return arguments;
    }

    std::unordered_map<Ident, ExpResult>& getVariables() {
        return variables;
    }

    const TypeSpecifier getReturnType() const {
        return returnType;
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


class Compiler : public Visitor {
private:
    enum class Phase {
        SCANNING_DEFINITIONS, COMPILING
    };
    Phase currentPhase = Phase::SCANNING_DEFINITIONS;
    std::unordered_map<Ident, Function> functions;
    ExpResult lastResult;
    Function currentFunction;
    TypeSpecifier declaredType;

    bool typesAreEqual(const TypeSpecifier t1, const TypeSpecifier t2);

    void reportError(std::string&& msg, int line);

    void typesNotSupported(const std::string& operation, int line);

public:
    Compiler() : lastResult(TypeSpecifier::None) {};

    void visitProgram(Program *p);

    void visitTopDef(TopDef *p);

    void visitArg(Arg *p);

    void visitBlock(Block *p);

    void visitStmt(Stmt *p);

    void visitItem(Item *p);

    void visitType(Type *p);

    void visitExpr(Expr *p);

    void visitAddOp(AddOp *p);

    void visitMulOp(MulOp *p);

    void visitRelOp(RelOp *p);

    void visitProg(Prog *p);

    void visitFnDef(FnDef *p);

    void visitAr(Ar *p);

    void visitBlk(Blk *p);

    void visitEmpty(Empty *p);

    void visitBStmt(BStmt *p);

    void visitDecl(Decl *p);

    void visitNoInit(NoInit *p);

    void visitInit(Init *p);

    void visitAss(Ass *p);

    void visitIncr(Incr *p);

    void visitDecr(Decr *p);

    void visitRet(Ret *p);

    void visitVRet(VRet *p);

    void visitCond(Cond *p);

    void visitCondElse(CondElse *p);

    void visitWhile(While *p);

    void visitSExp(SExp *p);

    void visitInt(Int *p);

    void visitStr(Str *p);

    void visitBool(Bool *p);

    void visitVoid(Void *p);

    void visitFun(Fun *p);

    void visitEVar(EVar *p);

    void visitELitInt(ELitInt *p);

    void visitELitTrue(ELitTrue *p);

    void visitELitFalse(ELitFalse *p);

    void visitEApp(EApp *p);

    void visitEString(EString *p);

    void visitNeg(Neg *p);

    void visitNot(Not *p);

    void visitEMul(EMul *p);

    void visitEAdd(EAdd *p);

    void visitERel(ERel *p);

    void visitEAnd(EAnd *p);

    void visitEOr(EOr *p);

    void visitPlus(Plus *p);

    void visitMinus(Minus *p);

    void visitTimes(Times *p);

    void visitDiv(Div *p);

    void visitMod(Mod *p);

    void visitLTH(LTH *p);

    void visitLE(LE *p);

    void visitGTH(GTH *p);

    void visitGE(GE *p);

    void visitEQU(EQU *p);

    void visitNE(NE *p);

    void visitListTopDef(ListTopDef *p);

    void visitListArg(ListArg *p);

    void visitListStmt(ListStmt *p);

    void visitListItem(ListItem *p);

    void visitListType(ListType *p);

    void visitListExpr(ListExpr *p);

    void visitInteger(Integer x);

    void visitChar(Char x);

    void visitDouble(Double x);

    void visitString(String x);

    void visitIdent(Ident x);

    bool typeIsDeclarable(const TypeSpecifier t);
};


#endif
