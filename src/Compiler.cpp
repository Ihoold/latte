/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Compiler.hpp"
#include "Label.hpp"
#include "CompilationException.hpp"
#include "ConstStringVariable.hpp"
#include "ConstBoolVariable.hpp"
#include "ConstIntVariable.hpp"
#include "RegisterVariable.hpp"
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
    std::vector<std::pair<Ident, VarPtr>> printIntArguments =
            {{"i", VarPtr(new ConstIntVariable())}};
    functions["printInt"] = Function(TypeSpecifier::Void, printIntArguments);
    compiledCode.emplace_back("declare void @printInt(i32)");

    std::vector<std::pair<Ident, VarPtr>> printStringArguments =
            {{"string", VarPtr(new ConstStringVariable())}};
    functions["printString"] = Function(TypeSpecifier::Void, printStringArguments);
    compiledCode.emplace_back("declare void @printString(i8*)");

    functions["errror"] = Function(TypeSpecifier::Void, std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare void @error()");

    functions["readInt"] = Function(TypeSpecifier::Int, std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare i32 @readInt()");

    functions["readString"] = Function(TypeSpecifier::String, std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare i8* @readString()");

    compiledCode.emplace_back("\n");

    prog->listtopdef_->accept(this);
    if(functions.find("main") == functions.end())
        reportError("No main function found.", prog->line_number);

    if(functions.at("main").getReturnType() != TypeSpecifier::Int) {
        reportError("Type of main function is not int.", prog->line_number);
    }
}

void Compiler::visitFnDef(FnDef *fndef) {
    switch (currentPhase) {
        case Phase::SCANNING_DEFINITIONS: {
            fndef->type_->accept(this);
            if (!typeIsDeclarable(declaredType) && declaredType != TypeSpecifier::Void)
                reportError("Cannot declare function of this type.", fndef->line_number);

            if (functions.find(fndef->ident_) != functions.end())
                reportError("Function " + fndef->ident_ + " is already declared.", fndef->line_number);

            std::vector<std::pair<Ident, VarPtr>> args;
            for (auto arg : *fndef->listarg_) {
                auto ar = dynamic_cast<Ar *>(arg);

                ar->type_->accept(this);
                if (!typeIsDeclarable(declaredType))
                    reportError("Cannot declare argument of this type.", ar->line_number);

                if (std::any_of(args.begin(), args.end(), [ar](auto a) { return a.first == ar->ident_; })) {
                    reportError("Duplicated argument name", arg->line_number);
                }

                std::stringstream ss;
                ss << "%ar_" << args.size();
                args.emplace_back(ar->ident_, VarPtr(new RegisterVariable(ss.str(), declaredType)));
            }

            functions[fndef->ident_] = Function(fndef->type_->getTypeSpecifier(), args);
        }
            break;
        case Phase::COMPILING:
            currentFunction = functions[fndef->ident_];
            currentFunction.initVariables();
            currentFunction.setReturnStatements(0);
            std::string arguments_list;
            bool first = true;
            for (auto ar : currentFunction.getArguments()) {
                arguments_list += ((first) ? "" : ", ")+ translateTypeSpecifier(ar.second->getType())
                                  + " " + ar.second->getCode(this);
                first = false;
            }

            compiledCode.push_back("define " + translateTypeSpecifier(fndef->type_->getTypeSpecifier()) + " @" +
                                           fndef->ident_ + "(" + arguments_list + ") {");
            currentFunction.setLastLabel(currentFunction.getNewLabel(std::vector<int>()).getLabelNum());
            fndef->block_->accept(this);
            compiledCode.emplace_back("}\n");

            if (currentFunction.getReturnStatements() == 0 && currentFunction.getReturnType() != TypeSpecifier::Void) {
                reportError("No return statement in function.", fndef->line_number);
            }
            break;
    }
}

void Compiler::visitAr(Ar *ar) {
    ar->type_->accept(this);
}

void Compiler::visitBlk(Blk *blk) {
    blk->liststmt_->accept(this);
}

void Compiler::visitEmpty(Empty *empty) {}

void Compiler::visitBStmt(BStmt *bstmt) {
    currentFunction.getVariables().emplace_back();
    bstmt->block_->accept(this);
    currentFunction.clearBlockVariables();
}

void Compiler::visitDecl(Decl *decl) {
    decl->type_->accept(this);
    if (!typeIsDeclarable(declaredType))
        reportError("Cannot declare variable of this type.", decl->line_number);

    decl->listitem_->accept(this);
}

void Compiler::visitAss(Ass *ass) {
    try {
        VarPtr e1 = currentFunction.getVar(ass->ident_);
        ass->expr_->accept(this);
        VarPtr e2 = lastResult;

        if (e1->getType() != e2->getType())
            reportError("Type of variable and assigned expression doesn't match.", ass->line_number);

        currentFunction.changeVar(ass->ident_, e2);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), ass->line_number);
    }
}

void Compiler::visitIncr(Incr *incr) {
    try {
        VarPtr e1 = currentFunction.getVar(incr->ident_);
        e1->incr(this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), incr->line_number);
    }
}

void Compiler::visitDecr(Decr *decr) {
    try {
        VarPtr e1 = currentFunction.getVar(decr->ident_);
        e1->decr(this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), decr->line_number);
    }
}

void Compiler::visitRet(Ret *ret) {
    ret->expr_->accept(this);
    VarPtr e1 = lastResult;

    if (e1->getType() != currentFunction.getReturnType())
        reportError("Return type mismatch.", ret->line_number);

    std::stringstream ss;
    ss << "\tret " << translateTypeSpecifier(e1->getType()) << " " << e1->getCode(this);
    compiledCode.emplace_back(ss.str());

    currentFunction.setReturnStatements(currentFunction.getReturnStatements()+1);
}

void Compiler::visitVRet(VRet *vret) {
    if (TypeSpecifier::Void != currentFunction.getReturnType())
        reportError("Return type mismatch.", vret->line_number);

    compiledCode.emplace_back("\tret void");
    currentFunction.setReturnStatements(currentFunction.getReturnStatements()+1);
}

void Compiler::visitCond(Cond *cond) {
    cond->expr_->accept(this);
    if (lastResult->getType() !=TypeSpecifier::Bool)
        reportError("If condition has to be boolean.", cond->line_number);

    if(lastResult->isConst()) {
        auto bVar = dynamic_cast<ConstBoolVariable*>(lastResult.get());
        if (bVar->getValue()) {
            cond->stmt_->accept(this);
        }
    } else {
        unsigned long jumpCodePosition = compiledCode.size();
        auto curr_label = currentFunction.getLastLabel();

        auto if_branch_label = currentFunction.getNewLabel({currentFunction.getLastLabel()});
        compiledCode.emplace_back(if_branch_label.getCode());
        currentFunction.setLastLabel(if_branch_label.getLabelNum());
        cond->stmt_->accept(this);

        currentFunction.setReturnStatements(0);
        auto after_if_label = currentFunction.getNewLabel({curr_label, if_branch_label.getLabelNum()});
        compiledCode.emplace_back(if_branch_label.getCode());
        currentFunction.setLastLabel(if_branch_label.getLabelNum());

    }
}

void Compiler::visitCondElse(CondElse *condelse) {
    condelse->expr_->accept(this);
    if (lastResult->getType() != TypeSpecifier::Bool)
        reportError("If condition has to be boolean.", condelse->line_number);


    if(lastResult->isConst()) {
        auto bVar = dynamic_cast<ConstBoolVariable*>(lastResult.get());
        if (bVar->getValue()) {
            condelse->stmt_1->accept(this);
        } else {
            condelse->stmt_2->accept(this);
        }
    } else {
        condelse->stmt_1->accept(this);
        int if_returned = currentFunction.getReturnStatements();

        condelse->stmt_2->accept(this);
        int else_returned = currentFunction.getReturnStatements();

        currentFunction.setReturnStatements(std::min(if_returned, else_returned));
    }
}

void Compiler::visitWhile(While *whileLoop) {
    whileLoop->expr_->accept(this);
    if (lastResult->getType() != TypeSpecifier::Bool)
        reportError("While condition has to be boolean.", whileLoop->line_number);

    if(lastResult->isConst()) {
        auto bVar = dynamic_cast<ConstBoolVariable*>(lastResult.get());
        if(bVar->getValue()) {
            // TODO
        }
    } else {
        whileLoop->stmt_->accept(this);
    }
    currentFunction.setReturnStatements(0); // TODO ?
}

void Compiler::visitSExp(SExp *sexp) {
    sexp->expr_->accept(this);
}

void Compiler::visitNoInit(NoInit *noinit) {
    try {
        currentFunction.putVar(noinit->ident_, ConstVariable::getConstDefault(declaredType));
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), noinit->line_number);
    }

}

void Compiler::visitInit(Init *init) {
    init->expr_->accept(this);
    if (lastResult->getType() != declaredType)
        reportError("Type of variable and assigned expression doesn't match.", init->line_number);

    try {
        currentFunction.putVar(init->ident_, VarPtr(lastResult->copy()));
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), init->line_number);
    }
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
    try {
        lastResult = currentFunction.getVar(evar->ident_);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), evar->line_number);
    }
}


const int INT_LIMIT = 1 << 30;
void Compiler::visitELitInt(ELitInt *elitint) {
    if (elitint->integer_ > INT_LIMIT)
        reportError("Integer overflow.", elitint->line_number);
    lastResult = VarPtr(new ConstIntVariable(elitint->integer_));
}

void Compiler::visitELitTrue(ELitTrue *elittrue) {
    lastResult = VarPtr(new ConstBoolVariable(true));
}

void Compiler::visitELitFalse(ELitFalse *elitfalse) {
    lastResult = VarPtr(new ConstBoolVariable(false));
}

void Compiler::visitEApp(EApp *eapp) {
    if (functions.find(eapp->ident_) == functions.end())
        reportError("Function " + eapp->ident_ + " undeclared.", eapp->line_number);

    if (eapp->listexpr_->size() != functions[eapp->ident_].getArguments().size())
        reportError("Wrong number of function arguments.", eapp->line_number);

    std::stringstream ss;
    TypeSpecifier retType = functions[eapp->ident_].getReturnType();
    VarPtr result;

    ss << "\t";
    if(retType != TypeSpecifier::Void) {
        result = currentFunction.getNewRegisterVar(retType);
        ss << result->getCode(this) << " = ";
    }

    ss << "call " << translateTypeSpecifier(retType) << " @" << eapp->ident_ << "(";

    std::string arguments;
    bool first = true;
    for (auto i = 0; i < functions[eapp->ident_].getArguments().size(); i++) {
        (*eapp->listexpr_)[i]->accept(this);

        if (lastResult->getType() != functions[eapp->ident_].getArguments()[i].second->getType())
            reportError("Type of argument and assigned expression doesn't match.", eapp->line_number);

        ss << ((first) ? "" : ", ") << translateTypeSpecifier(lastResult->getType()) << " " << lastResult->getCode(this);
        first = false;
    }

    ss << ")";
    compiledCode.push_back(ss.str());

    if(retType != TypeSpecifier::Void) {
        lastResult = result;
    }
}

void Compiler::visitEString(EString *estring) {
    lastResult = VarPtr(new ConstStringVariable(estring->string_));
}

void Compiler::visitNeg(Neg *neg) {
    neg->expr_->accept(this);
    VarPtr e1 = lastResult;

    try {
        lastResult = e1->neg(this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), neg->line_number);
    }
}

void Compiler::visitNot(Not * notOp) {
    notOp->expr_->accept(this);
    VarPtr e1 = lastResult;

    try {
        lastResult = e1->not_(this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), notOp->line_number);
    }
}

void Compiler::visitEMul(EMul *emul) {
    emul->expr_1->accept(this);
    VarPtr e1 = lastResult;

    emul->expr_2->accept(this);
    VarPtr e2 = lastResult;

    try {
        switch (emul->mulop_->getOperatorType()) {
            case OperatorType::MULTIPLY:
                lastResult = e1->mul(e2, this);
                break;
            case OperatorType::DIVIDE:
                lastResult = e1->div(e2, this);
                break;
            case OperatorType::MODULO:
                lastResult = e1->rem(e2, this);
                break;
            default:
                assert(false);
        }
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), emul->line_number);
    }
}

void Compiler::visitEAdd(EAdd *eadd) {
    eadd->expr_1->accept(this);
    VarPtr e1 = lastResult;

    eadd->expr_2->accept(this);
    VarPtr e2 = lastResult;

    try {
        switch (eadd->addop_->getOperatorType()) {
            case OperatorType::PLUS:
                lastResult = e1->add(e2, this);
                break;
            case OperatorType::MINUS:
                lastResult = e1->sub(e2, this);
                break;
            default:
                assert(false);
        }
    }  catch (const std::logic_error& ex) {
        reportError(ex.what(), eadd->line_number);
    }
}

void Compiler::visitERel(ERel *erel) {
    erel->expr_1->accept(this);
    VarPtr e1 = lastResult;

    erel->expr_2->accept(this);
    VarPtr e2 = lastResult;

    try {
        switch (erel->relop_->getOperatorType()) {
            case OperatorType::GE:
                lastResult = e1->gte(e2, this);
                break;
            case OperatorType::GT:
                lastResult = e1->gt(e2, this);
                break;
            case OperatorType::LE:
                lastResult = e1->lte(e2, this);
                break;
            case OperatorType::LT:
                lastResult = e1->lt(e2, this);
                break;
            case OperatorType::EQ:
                lastResult = e1->eq(e2, this);
                break;
            case OperatorType::NEQ:
                lastResult = e1->neq(e2, this);
                break;
            default:
                assert(false);
        }
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), erel->line_number);
    }
}

void Compiler::visitEAnd(EAnd *eand) {
    eand->expr_1->accept(this);
    VarPtr e1 = lastResult;

    eand->expr_2->accept(this);
    VarPtr e2 = lastResult;

    try {
        lastResult = e1->band(e2, this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), eand->line_number);
    }
}

void Compiler::visitEOr(EOr *eor) {
    eor->expr_1->accept(this);
    VarPtr e1 = lastResult;

    eor->expr_2->accept(this);
    VarPtr e2 = lastResult;

    try {
        lastResult = e1->bor(e2, this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), eor->line_number);
    }
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
        if (currentFunction.getReturnStatements() > 0)
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

Function& Compiler::getCurrentFunction() {
    return currentFunction;
}

Code& Compiler::getCompiledCode() {
    return compiledCode;
}
