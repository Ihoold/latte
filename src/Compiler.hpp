#ifndef COMPILER_HEADER
#define COMPILER_HEADER
/* You might want to change the above name. */

#include <stdexcept>
#include <memory>
#include <unordered_map>
#include <utility>
#include <set>
#include <sstream>
#include <unordered_set>

class Compiler;

#include "Absyn.hpp"
#include "Label.hpp"
#include "Variable.hpp"
#include "Function.hpp"
#include "Structure.hpp"

using Code = std::vector<std::string>;

class Compiler : public Visitor {
private:
    enum class Phase {
        SCANNING_STRUCTURES, SCANNING_DEFINITIONS, COMPILING
    };
    Phase currentPhase = Phase::SCANNING_STRUCTURES;

    std::unordered_map<Ident, Function> functions;
    std::unordered_map<Ident, Structure> structures;
    Function currentFunction;
    Structure* currentStructure;

    VarPtr lastResult;
    TypePtr declaredType;

    std::unordered_map<std::string, std::string> knownStrings;
    Code compiledCode;
    void reportError(std::string&& msg, int line);
public:
    Compiler();

    Code& getCompiledCode();
    Function& getCurrentFunction();

    const std::unordered_map<Ident, Structure>& getStructures() const;

    std::string getGlobalStringName(const std::string&);

    const VarPtr& getLastResult() const;

    void visitAttribute(Attribute *p) override;
    void visitLVal(LVal *p) override;
    void visitStructDef(StructDef *p) override;
    void visitAttr(Attr *p) override;
    void visitLIdent(LIdent *p) override;
    void visitLArray(LArray *p) override;
    void visitLStruct(LStruct *p) override;
    void visitFor(For *p) override;
    void visitArray(Array *p) override;
    void visitStruct(Struct *p) override;
    void visitENull(ENull *p) override;
    void visitEArray(EArray *p) override;
    void visitEStruct(EStruct *p) override;
    void visitListAttribute(ListAttribute *p) override;
    void visitProgram(Program *p) override;
    void visitTopDef(TopDef *p) override;
    void visitArg(Arg *p) override;
    void visitBlock(Block *p) override;
    void visitStmt(Stmt *t) override;
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
    void visitStructInh(StructInh *p) override;
    void visitMethod(Method *p) override;
    void visitEMethod(EMethod *p) override;
};

#endif
