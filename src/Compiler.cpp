/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Compiler.hpp"
#include <algorithm>
#include <iostream>
#include <boost/assert.hpp>


void Compiler::visitProgram(Program *t) {} //abstract class
void Compiler::visitTopDef(TopDef *t) {} //abstract class
void Compiler::visitArg(Arg *t) {} //abstract class
void Compiler::visitBlock(Block *t) {} //abstract class
void Compiler::visitStmt(Stmt *t) {} //abstract class
void Compiler::visitItem(Item *t) {} //abstract class
void Compiler::visitType(Type *t) {} //abstract class
void Compiler::visitExpr(Expr *t) {} //abstract class
void Compiler::visitAddOp(AddOp *t) {} //abstract class
void Compiler::visitMulOp(MulOp *t) {} //abstract class
void Compiler::visitRelOp(RelOp *t) {} //abstract class

void Compiler::visitProg(Prog *prog) {
    // error, readInt, readString
    functions["printInt"] = Function(TypeSpecifier::Void,
                                     std::vector<std::pair<Ident, TypeSpecifier>> {{"to_print", TypeSpecifier::Int}});
    functions["printString"] = Function(TypeSpecifier::Void,
                                     std::vector<std::pair<Ident, TypeSpecifier>> {{"to_print", TypeSpecifier::String}});
    functions["errror"] = Function(TypeSpecifier::Void, std::vector<std::pair<Ident, TypeSpecifier>> {});
    functions["readInt"] = Function(TypeSpecifier::Int, std::vector<std::pair<Ident, TypeSpecifier>> {});
    functions["readString"] = Function(TypeSpecifier::String, std::vector<std::pair<Ident, TypeSpecifier>> {});

    prog->listtopdef_->accept(this);
    if(functions.find("main") == functions.end())
        reportError("No main function found.", prog->line_number);

    if(!typesAreEqual(functions.at("main").getReturnType(), TypeSpecifier::Int)) {
        reportError("Type of main function is not int.", prog->line_number);
    }
}

void Compiler::visitFnDef(FnDef *fndef) {
    switch (currentPhase) {
        case Phase::SCANNING_DEFINITIONS: {
            fndef->type_->accept(this);
            if (!typeIsDeclarable(declaredType) && !typesAreEqual(declaredType, TypeSpecifier::Void))
                reportError("Cannot declare function of this type.", fndef->line_number);

            if (functions.find(fndef->ident_) != functions.end())
                reportError("Function " + fndef->ident_ + " is already declared.", fndef->line_number);

            std::vector<std::pair<Ident, TypeSpecifier>> args;
            for (auto arg : *fndef->listarg_) {
                auto ar = dynamic_cast<Ar *>(arg);

                ar->type_->accept(this);
                if (!typeIsDeclarable(declaredType))
                    reportError("Cannot declare argument of this type.", ar->line_number);

                if (std::any_of(args.begin(), args.end(), [ar](auto a) { return a.first == ar->ident_; })) {
                    reportError("Duplicated argument name", arg->line_number);
                }

                args.emplace_back(ar->ident_, declaredType);
            }

            functions[fndef->ident_] = Function(fndef->type_->getTypeSpecifier(), args);
        }
            break;
        case Phase::COMPILING:
            currentFunction = functions[fndef->ident_];
            currentFunction.initVariables();
            currentFunction.returnStatements = 0;

            fndef->block_->accept(this);

            if (currentFunction.returnStatements == 0) {
                reportError("No return statement in function.", fndef->line_number);
            }
            break;
    }
}

void Compiler::visitAr(Ar *ar) {
    ar->type_->accept(this);
    visitIdent(ar->ident_);
}

void Compiler::visitBlk(Blk *blk) {
    blk->liststmt_->accept(this);
}

void Compiler::visitEmpty(Empty *empty) {
    lastResult = ExpResult(TypeSpecifier::Void);
}

void Compiler::visitBStmt(BStmt *bstmt) {
    bstmt->block_->accept(this);
    std::unordered_map<Ident, ExpResult> oldVariables(currentFunction.getVariables());
    lastResult = ExpResult(TypeSpecifier::Void);
    currentFunction.setVariables(oldVariables);
}

void Compiler::visitDecl(Decl *decl) {
    decl->type_->accept(this);
    if (!typeIsDeclarable(declaredType))
        reportError("Cannot declare variable of this type.", decl->line_number);

    decl->listitem_->accept(this);
}

void Compiler::visitAss(Ass *ass) {
    if (currentFunction.getVariables().find(ass->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + ass->ident_ + " undeclared.", ass->line_number);
    ExpResult e1 = currentFunction.getVariables().at(ass->ident_);

    ass->expr_->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Type of variable and assigned expression doesn't match.", ass->line_number);

    lastResult = e1;
}

void Compiler::visitIncr(Incr *incr) {
    if (currentFunction.getVariables().find(incr->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + incr->ident_ + " undeclared.", incr->line_number);
    ExpResult e1 = currentFunction.getVariables().at(incr->ident_);

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
        typesNotSupported("++", incr->line_number);

    lastResult = e1;
}

void Compiler::visitDecr(Decr *decr) {
    if (currentFunction.getVariables().find(decr->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + decr->ident_ + " undeclared.", decr->line_number);
    ExpResult e1 = currentFunction.getVariables().at(decr->ident_);

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
        typesNotSupported("--", decr->line_number);

    lastResult = e1;
}

void Compiler::visitRet(Ret *ret) {
    ret->expr_->accept(this);
    ExpResult e1 = lastResult;

    if (!typesAreEqual(e1.getType(), currentFunction.getReturnType())) {
        reportError("Return type mismatch.", ret->line_number);
    }

    currentFunction.returnStatements++;
}

void Compiler::visitVRet(VRet *vret) {
    if (!typesAreEqual(TypeSpecifier::Void, currentFunction.getReturnType())) {
        reportError("Return type mismatch.", vret->line_number);
    }

    currentFunction.returnStatements++;
}

void Compiler::visitCond(Cond *cond) {
    cond->expr_->accept(this);
    if (!typesAreEqual(lastResult.getType(), TypeSpecifier::Bool))
        reportError("If condition has to be boolean.", cond->line_number);
    cond->stmt_->accept(this);
    currentFunction.returnStatements = 0;
}

void Compiler::visitCondElse(CondElse *condelse) {
    condelse->expr_->accept(this);
    if (!typesAreEqual(lastResult.getType(), TypeSpecifier::Bool))
        reportError("If condition has to be boolean.", condelse->line_number);

    condelse->stmt_1->accept(this);
    currentFunction.returnStatements = 0;
    condelse->stmt_2->accept(this);
    currentFunction.returnStatements = 0;
}

void Compiler::visitWhile(While *whileLoop) {
    whileLoop->expr_->accept(this);
    if (!typesAreEqual(lastResult.getType(), TypeSpecifier::Bool))
        reportError("While condition has to be boolean.", whileLoop->line_number);

    whileLoop->stmt_->accept(this);
    currentFunction.returnStatements = 0;
}

void Compiler::visitSExp(SExp *sexp) {
    sexp->expr_->accept(this);
}

void Compiler::visitNoInit(NoInit *noinit) {
    if (currentFunction.getVariables().find(noinit->ident_) != currentFunction.getVariables().end())
        reportError("Variable already exists.", noinit->line_number);

    currentFunction.getVariables()[noinit->ident_] = ExpResult(declaredType);
}

void Compiler::visitInit(Init *init) {
    if (currentFunction.getVariables().find(init->ident_) != currentFunction.getVariables().end())
        reportError("Variable already exists.", init->line_number);

    init->expr_->accept(this);
    if (!typesAreEqual(lastResult.getType(), declaredType))
        reportError("Type of variable and assigned expression doesn't match.", init->line_number);

    currentFunction.getVariables()[init->ident_] = ExpResult(declaredType);
}

void Compiler::visitInt(Int * intConst) {
    declaredType = TypeSpecifier::Int;
}

void Compiler::visitStr(Str *str) {
    declaredType = TypeSpecifier::String;
}

void Compiler::visitBool(Bool * boolConst) {
    declaredType = TypeSpecifier::Bool;
}

void Compiler::visitVoid(Void * voidConst) {
    declaredType = TypeSpecifier::Void;
}

// Internal type
void Compiler::visitFun(Fun *fun) {
    assert(false);
}

void Compiler::visitEVar(EVar *evar) {
    if (currentFunction.getVariables().find(evar->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + evar->ident_ + " undeclared.", evar->line_number);

    lastResult = currentFunction.getVariables().at(evar->ident_);
}

void Compiler::visitELitInt(ELitInt *elitint) {
    lastResult = ExpResult(TypeSpecifier::Int);
}

void Compiler::visitELitTrue(ELitTrue *elittrue) {
    lastResult = ExpResult(TypeSpecifier::Bool);
}

void Compiler::visitELitFalse(ELitFalse *elitfalse) {
    lastResult = ExpResult(TypeSpecifier::Bool);
}

void Compiler::visitEApp(EApp *eapp) {
    if (functions.find(eapp->ident_) == functions.end())
        reportError("Function " + eapp->ident_ + " undeclared.", eapp->line_number);

    if (eapp->listexpr_->size() != functions[eapp->ident_].getArguments().size())
        reportError("Wrong number of function arguments.", eapp->line_number);

    for (auto i = 0; i < functions[eapp->ident_].getArguments().size(); i++) {
        eapp->listexpr_[i].accept(this);

        if (!typesAreEqual(lastResult.getType(), functions[eapp->ident_].getArguments()[i].second))
            reportError("Type of argument and assigned expression doesn't match.", eapp->line_number);
    }

    lastResult = ExpResult(functions.at(eapp->ident_).getReturnType());
}

void Compiler::visitEString(EString *estring) {
    lastResult = ExpResult(TypeSpecifier::String);
}

void Compiler::visitNeg(Neg *neg) {
    neg->expr_->accept(this);
    ExpResult e1 = lastResult;

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
        typesNotSupported("-", neg->line_number);

    lastResult = ExpResult(e1.getType());
}

void Compiler::visitNot(Not * notOp) {
    notOp->expr_->accept(this);
    ExpResult e1 = lastResult;

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Bool))
        typesNotSupported("!", notOp->line_number);

    lastResult = ExpResult(e1.getType());
}

void Compiler::visitEMul(EMul *emul) {
    emul->expr_1->accept(this);
    ExpResult e1 = lastResult;

    emul->expr_2->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Types doesn't match.", emul->line_number);

    switch (emul->mulop_->getOperatorType()) {
        case OperatorType::MULTIPLY:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
                typesNotSupported("*", emul->line_number);
            break;
        case OperatorType::DIVIDE:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
                typesNotSupported("/", emul->line_number);
            break;
        case OperatorType::MODULO:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
                typesNotSupported("%", emul->line_number);
            break;
        default:
            assert(false);
    }

    lastResult = ExpResult(e1.getType());
}

void Compiler::visitEAdd(EAdd *eadd) {
    eadd->expr_1->accept(this);
    ExpResult e1 = lastResult;

    eadd->expr_2->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Types doesn't match.", eadd->line_number);

    switch (eadd->addop_->getOperatorType()) {
        case OperatorType::PLUS:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int) && !typesAreEqual(e1.getType(), TypeSpecifier::String))
                typesNotSupported("+", eadd->line_number);
            break;
        case OperatorType::MINUS:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int))
                typesNotSupported("-", eadd->line_number);
            break;
        default:
            assert(false);
    }

    lastResult = ExpResult(e1.getType());
}

void Compiler::visitERel(ERel *erel) {
    erel->expr_1->accept(this);
    ExpResult e1 = lastResult;

    erel->expr_2->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Types doesn't match.", erel->line_number);

    switch (erel->relop_->getOperatorType()) {
        case OperatorType::GE:
        case OperatorType::GT:
        case OperatorType::LE:
        case OperatorType::LT:
        case OperatorType::EQ:
        case OperatorType::NEQ:
            if (!typesAreEqual(e1.getType(), TypeSpecifier::Int) && !typesAreEqual(e1.getType(), TypeSpecifier::String))
                typesNotSupported("compare", erel->line_number);
            break;
        default:
            assert(false);
    }

    lastResult = ExpResult(TypeSpecifier::Bool);
}

void Compiler::visitEAnd(EAnd *eand) {
    eand->expr_1->accept(this);
    ExpResult e1 = lastResult;

    eand->expr_2->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Types doesn't match.", eand->line_number);

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Bool))
        typesNotSupported("&&", eand->line_number);

    lastResult = ExpResult(TypeSpecifier::Bool);
}

void Compiler::visitEOr(EOr *eor) {
    eor->expr_1->accept(this);
    ExpResult e1 = lastResult;

    // TODO: add laziness
    eor->expr_2->accept(this);
    ExpResult e2 = lastResult;

    if (!typesAreEqual(e1.getType(), e2.getType()))
        reportError("Types doesn't match.", eor->line_number);

    if (!typesAreEqual(e1.getType(), TypeSpecifier::Bool))
        typesNotSupported("||", eor->line_number);

    lastResult = ExpResult(TypeSpecifier::Bool);
}

// Not used.
void Compiler::visitPlus(Plus *plus) {}
void Compiler::visitMinus(Minus *minus) {}
void Compiler::visitTimes(Times *times) {}
void Compiler::visitDiv(Div *div) {}
void Compiler::visitMod(Mod *mod) {}
void Compiler::visitLTH(LTH *lth) {}
void Compiler::visitLE(LE *le) {}
void Compiler::visitGTH(GTH *gth) {}
void Compiler::visitGE(GE *ge) {}
void Compiler::visitEQU(EQU *equ) {}
void Compiler::visitNE(NE *ne) {}


// Lists.
void Compiler::visitListTopDef(ListTopDef *listtopdef) {
    for (auto elem : *listtopdef) {
        elem->accept(this);
    }

    currentPhase = Phase::COMPILING;

    for (auto elem : *listtopdef) {
        elem->accept(this);
    }

}

void Compiler::visitListArg(ListArg *listarg) {
    for (auto elem : *listarg) {
        elem->accept(this);
    }
}

void Compiler::visitListStmt(ListStmt *liststmt) {
    for (auto elem : *liststmt) {
        elem->accept(this);
        // Unreachable code optimalization.
        if (currentFunction.returnStatements > 0)
            return;
    }
}

void Compiler::visitListItem(ListItem *listitem) {
    for (auto elem : *listitem) {
        elem->accept(this);
    }
}

void Compiler::visitListType(ListType *listtype) {
    for (auto elem : *listtype) {
        elem->accept(this);
    }
}

void Compiler::visitListExpr(ListExpr *listexpr) {
    for (auto elem : *listexpr) {
        elem->accept(this);
    }
}

// Not used as well.
void Compiler::visitInteger(Integer x) {}
void Compiler::visitChar(Char x) {}
void Compiler::visitDouble(Double x) {}
void Compiler::visitString(String x) {}
void Compiler::visitIdent(Ident x) {}

// Helpers.
void Compiler::reportError(std::string&& msg, int line) {
    throw CompilationException(msg, line);
}

bool Compiler::typesAreEqual(const TypeSpecifier t1, const TypeSpecifier t2) {
    return t1 == t2;
}

void Compiler::typesNotSupported(const std::string& operation, int line) {
    reportError("Provided types are not supported by operation " + operation + ".", line);
}

bool Compiler::typeIsDeclarable(const TypeSpecifier t) {
    return typesAreEqual(t, TypeSpecifier::Int) ||
            typesAreEqual(t, TypeSpecifier::String) ||
            typesAreEqual(t, TypeSpecifier::Bool);
}