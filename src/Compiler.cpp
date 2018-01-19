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
    // TODO: implementations
    std::vector<std::pair<Ident, VarPtr>> printIntArguments =
            {{"to_print", getNewRegisterVar(TypeSpecifier::Int)}};
    functions["printInt"] = Function(TypeSpecifier::Void, printIntArguments);

    std::vector<std::pair<Ident, VarPtr>> printStringArguments =
            {{"to_print", VarPtr(getNewRegisterVar(TypeSpecifier::String))}};
    functions["printString"] = Function(TypeSpecifier::Void, printStringArguments);

    functions["errror"] = Function(TypeSpecifier::Void, std::vector<std::pair<Ident, VarPtr>> {});
    functions["readInt"] = Function(TypeSpecifier::Int, std::vector<std::pair<Ident, VarPtr>> {});
    functions["readString"] = Function(TypeSpecifier::String, std::vector<std::pair<Ident, VarPtr>> {});

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

                args.emplace_back(ar->ident_, getNewRegisterVar(declaredType));
            }

            functions[fndef->ident_] = Function(fndef->type_->getTypeSpecifier(), args);
        }
            break;
        case Phase::COMPILING:
            currentFunction = functions[fndef->ident_];
            currentFunction.initVariables();
            currentFunction.returnStatements = 0;
            std::string arguments_list;
            bool first = true;
            for (auto ar : currentFunction.getArguments()) {
                arguments_list += ((first) ? "" : ", ")+ translateTypeSpecifier(ar.second->getType()) + " " + ar.second->getCode();
                first = false;
            }

            compiledCode.push_back("define " + translateTypeSpecifier(fndef->type_->getTypeSpecifier()) + " @" +
                                           fndef->ident_ + "(" + arguments_list + ") {");
            fndef->block_->accept(this);
            compiledCode.emplace_back("}\n");

            if (currentFunction.returnStatements == 0 && currentFunction.getReturnType() != TypeSpecifier::Void) {
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
    // TODO: block variables can be defined
    bstmt->block_->accept(this);
    std::unordered_map<Ident, VarPtr> oldVariables(currentFunction.getVariables());
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
    VarPtr e1 = currentFunction.getVariables().at(ass->ident_);

    ass->expr_->accept(this);
    VarPtr e2 = lastResult;

    if (e1->getType() != e2->getType())
        reportError("Type of variable and assigned expression doesn't match.", ass->line_number);

    currentFunction.getVariables()[ass->ident_] = e2->copy();
    lastResult = currentFunction.getVariables()[ass->ident_];
}

void Compiler::visitIncr(Incr *incr) {
    if (currentFunction.getVariables().find(incr->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + incr->ident_ + " undeclared.", incr->line_number);
    VarPtr e1 = currentFunction.getVariables().at(incr->ident_);

    try {
        e1->incr(this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), incr->line_number);
    }
}

void Compiler::visitDecr(Decr *decr) {
    if (currentFunction.getVariables().find(decr->ident_) == currentFunction.getVariables().end())
        reportError("Variable " + decr->ident_ + " undeclared.", decr->line_number);
    VarPtr e1 = currentFunction.getVariables().at(decr->ident_);

    try {
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

    currentFunction.returnStatements++;
}

void Compiler::visitVRet(VRet *vret) {
    if (TypeSpecifier::Void != currentFunction.getReturnType())
        reportError("Return type mismatch.", vret->line_number);

    currentFunction.returnStatements++;
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
        // TODO
        cond->stmt_->accept(this);
        currentFunction.returnStatements = 0;
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
        int if_returned = currentFunction.returnStatements > 0;

        condelse->stmt_2->accept(this);
        int else_returned = currentFunction.returnStatements > 0;

        currentFunction.returnStatements = std::min(if_returned, else_returned);
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
    currentFunction.returnStatements = 0;
}

void Compiler::visitSExp(SExp *sexp) {
    sexp->expr_->accept(this);
}

void Compiler::visitNoInit(NoInit *noinit) {
    if (currentFunction.getVariables().find(noinit->ident_) != currentFunction.getVariables().end())
        reportError("Variable already exists.", noinit->line_number);

    currentFunction.getVariables()[noinit->ident_] = ConstVariable::getConstDefault(declaredType);
}

void Compiler::visitInit(Init *init) {
    if (currentFunction.getVariables().find(init->ident_) != currentFunction.getVariables().end())
        reportError("Variable already exists.", init->line_number);

    init->expr_->accept(this);
    if (lastResult->getType() != declaredType)
        reportError("Type of variable and assigned expression doesn't match.", init->line_number);

    currentFunction.getVariables()[init->ident_] = VarPtr(lastResult->copy());
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
        result = getNewRegisterVar(retType);
        ss << result->getCode() << " = ";
    }

    ss << "call " << translateTypeSpecifier(retType) << " @" << eapp->ident_ << "(";

    std::string arguments;
    bool first = true;
    for (auto i = 0; i < functions[eapp->ident_].getArguments().size(); i++) {
        (*eapp->listexpr_)[i]->accept(this);

        if (lastResult->getType() != functions[eapp->ident_].getArguments()[i].second->getType())
            reportError("Type of argument and assigned expression doesn't match.", eapp->line_number);

        ss << ((first) ? "" : ", ") << translateTypeSpecifier(lastResult->getType()) << " " << lastResult->getCode();
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

    if (e1->getType() != TypeSpecifier::Int)
        typesNotSupported("-", neg->line_number);

    VarPtr e2 = VarPtr(new ConstIntVariable(0));
    lastResult = e2->sub(e1, this);
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

void Compiler::typesNotSupported(const std::string& operation, int line) {
    reportError("Provided types are not supported by operation " + operation + ".", line);
}


std::shared_ptr<Variable> Compiler::getNewRegisterVar(TypeSpecifier type) {
    std::stringstream ss;
    ss << "%" << counter++;
    return std::shared_ptr<Variable>(new RegisterVariable(ss.str(), type));
}

VarPtr ConstVariable::getConstDefault(TypeSpecifier t) {
    switch(t) {
        case TypeSpecifier::Int:
            return VarPtr(new ConstIntVariable());
        case TypeSpecifier::Bool:
            return VarPtr(new ConstBoolVariable());
        case TypeSpecifier::String:
            return VarPtr(new ConstStringVariable());
        default:
            throw std::logic_error("Not supported const generation.");
    }
}

void typeCheckFailure(const std::string& operation) {
    throw std::logic_error("Type check failed in operation " + operation + ".");
}