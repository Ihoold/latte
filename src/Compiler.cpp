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
#include "NullPtrVariable.hpp"
#include "ExtraTypes.hpp"
#include <algorithm>
#include <iostream>
#include <boost/assert.hpp>

// PROGRAMS

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
void Compiler::visitAttribute(Attribute *p) {} //abstract class
void Compiler::visitLVal(LVal *p) {} // abstract class

void Compiler::visitProg(Prog *prog) {
    std::vector<std::pair<Ident, VarPtr>> printIntArguments =
            {{"i", VarPtr(new ConstIntVariable())}};
    functions["printInt"] = Function(TypePtr(new Void()), printIntArguments);
    compiledCode.emplace_back("declare void @printInt(i32)");

    std::vector<std::pair<Ident, VarPtr>> printStringArguments =
            {{"string", VarPtr(new ConstStringVariable())}};
    functions["printString"] = Function(TypePtr(new Void()), printStringArguments);
    compiledCode.emplace_back("declare void @printString(i8*)");

    functions["error"] = Function(TypePtr(new Void()), std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare void @error()");

    functions["readInt"] = Function(TypePtr(new Int()), std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare i32 @readInt()");

    functions["readString"] = Function(TypePtr(new Str()), std::vector<std::pair<Ident, VarPtr>> {});
    compiledCode.emplace_back("declare i8* @readString()");
    compiledCode.emplace_back("declare i8* @concat(i8*, i8*)");
    compiledCode.emplace_back("declare i8* @calloc(i32, i32)");
    compiledCode.emplace_back("declare i8* @malloc(i32)");
    compiledCode.emplace_back("");
    auto struct_pos = compiledCode.size();
    compiledCode.emplace_back("");


    prog->listtopdef_->accept(this);
    if(functions.find("main") == functions.end())
        reportError("No main function found.", prog->line_number);

    if(functions.at("main").getReturnType()->getTypeSpecifier() != TypeSpecifier::Int) {
        reportError("Type of main function is not int.", prog->line_number);
    }

    if(functions.at("main").getArguments().size() != 0) {
        reportError("Main function received an argument.", prog->line_number);
    }

    for (auto& global : knownStrings) {
        std::stringstream ss;
        ss << global.second << " = private unnamed_addr constant [ " << global.first.size() + 1 << " x i8] c\"" <<
                global.first << "\\00\", align 1";
        compiledCode.emplace_back(ss.str());
    }
}

void Compiler::visitFnDef(FnDef *fndef) {
    switch (currentPhase) {
        case Phase::SCANNING_STRUCTURES:
            break;
        case Phase::SCANNING_DEFINITIONS: {
            fndef->type_->accept(this);
            if (!typeIsDeclarable(declaredType) && declaredType->getTypeSpecifier() != TypeSpecifier::Void)
                reportError("Cannot declare function of this type.", fndef->line_number);

            if (functions.find(fndef->ident_) != functions.end())
                reportError("Function " + fndef->ident_ + " is already declared.", fndef->line_number);

            auto returnType = declaredType;

            std::vector<std::pair<Ident, VarPtr>> args;
            for (auto arg : *fndef->listarg_) {
                auto ar = dynamic_cast<Ar*>(arg);

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

            functions[fndef->ident_] = Function(returnType, args);
        }
            break;
        case Phase::COMPILING:
            currentFunction = functions[fndef->ident_];
            currentFunction.setReturnStatements(0);
            std::string arguments_list;
            bool first = true;
            for (auto ar : currentFunction.getArguments()) {
                arguments_list += ((first) ? "" : ", ") + ar.second->getType()->getTranslation()
                                  + " " + ar.second->getCode(this);
                first = false;
            }

            compiledCode.push_back("define " + functions[fndef->ident_].getReturnType()->getTranslation() + " @" +
                                           fndef->ident_ + "(" + arguments_list + ") {");
            currentFunction.setLastLabel(currentFunction.getNewLabel(std::vector<int>()).getLabelNum());
            currentFunction.initVariables(this);
            fndef->block_->accept(this);
            currentFunction.clearBlockVariables(this);

            if (currentFunction.getReturnStatements() == 0) {
                if(currentFunction.getReturnType()->getTypeSpecifier() != TypeSpecifier::Void) {
                    reportError("No return statement in function.", fndef->line_number);
                } else {
                    compiledCode.emplace_back("\tret void");
                }
            }
            compiledCode.emplace_back("}\n");
            break;
    }
}

void Compiler::visitAr(Ar *ar) {
    ar->type_->accept(this);
}

void Compiler::visitBlk(Blk *blk) {
    currentFunction.getVariables().emplace_back();
    blk->liststmt_->accept(this);
    currentFunction.clearBlockVariables(this);
}

void Compiler::visitStructInh(StructInh *p) {
    // TODO
}

void Compiler::visitStructDef(StructDef *p) {
    switch (currentPhase) {
        case Phase::SCANNING_STRUCTURES: {
            if (structures.find(p->ident_) != structures.end())
                reportError("Duplicated structure name.", p->line_number);

            structures.emplace(p->ident_, Structure(p->ident_));
            currentStructure = &structures.at(p->ident_);

            currentStructPhase = StructPhase::SCANNING_FIELDS;
            p->listattribute_->accept(this);

            std::stringstream ss;
            ss << "%struct." << p->ident_ << " = type { ";
            bool first = true;
            for (auto field : *currentStructure) {
                ss << (first ? "" : ", ") << field.second->getTranslation();
                first = false;
            }
            ss << " }";
            compiledCode.emplace_back(ss.str());

            currentStructPhase = StructPhase::SCANNING_METHODS;
            p->listattribute_->accept(this);

            currentStructPhase = StructPhase::COMPILING;
            p->listattribute_->accept(this);

            currentStructure = nullptr;
        }
            break;
        default:
            return;
    }
}

void Compiler::visitAttr(Attr *p) {
    if (currentStructPhase == StructPhase::SCANNING_FIELDS) {
        p->type_->accept(this);
        if (!typeIsDeclarable(declaredType))
            reportError("Attribute with forbidden type.", p->line_number);

        if (std::any_of(currentStructure->begin(), currentStructure->end(),
                        [p](auto pair){ return pair.first == p->ident_;})) {
            reportError("Attribute with this name already declared in structure.", p->line_number);
        }

        currentStructure->emplace_back(p->ident_, declaredType);
    }
}

void Compiler::visitMethod(Method *fndef) {
    auto method_ident = currentStructure->getName() + "_" + fndef->ident_;

    switch (currentStructPhase) {
        case StructPhase::SCANNING_METHODS: {
            fndef->type_->accept(this);
            if (!typeIsDeclarable(declaredType) && declaredType->getTypeSpecifier() != TypeSpecifier::Void)
                reportError("Cannot declare function of this type.", fndef->line_number);

            if (functions.find(method_ident) != functions.end())
                reportError("Function " + method_ident + " is already declared.", fndef->line_number);

            auto returnType = declaredType;

            std::vector<std::pair<Ident, VarPtr>> args;
            args.emplace_back("self",
                              VarPtr(new RegisterVariable("%self", TypePtr(new Struct(currentStructure->getName())))));
            for (auto arg : *fndef->listarg_) {
                auto ar = dynamic_cast<Ar*>(arg);

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

            functions[method_ident] = Function(returnType, args);
            break;
        }
        case StructPhase::COMPILING: {
            currentFunction = functions[method_ident];
            currentFunction.setReturnStatements(0);
            std::string arguments_list;
            bool first = true;
            for (auto ar : currentFunction.getArguments()) {
                arguments_list += ((first) ? "" : ", ") + ar.second->getType()->getTranslation()
                                  + " " + ar.second->getCode(this);
                first = false;
            }

            compiledCode.push_back("define " + functions[method_ident].getReturnType()->getTranslation() + " @" +
                                           method_ident + "(" + arguments_list + ") {");
            currentFunction.setLastLabel(currentFunction.getNewLabel(std::vector<int>()).getLabelNum());
            currentFunction.initVariables(this, true);
            fndef->block_->accept(this);
            currentFunction.clearBlockVariables(this);
            currentFunction.clearBlockVariables(this);

            if (currentFunction.getReturnStatements() == 0) {
                if(currentFunction.getReturnType()->getTypeSpecifier() != TypeSpecifier::Void) {
                    reportError("No return statement in function.", fndef->line_number);
                } else {
                    compiledCode.emplace_back("\tret void");
                }
            }
            compiledCode.emplace_back("}\n");
            break;
        }
        default:
            return;
    }

}

///////////////////////// LVALS

void Compiler::visitLIdent(LIdent *p) {
    try {
        lastResult = currentFunction.getVar(p->ident_);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), p->line_number);
    }
}

void Compiler::visitLArray(LArray *p) {
    try {
        p->lval_->accept(this);
        VarPtr basePtr = lastResult;

        p->expr_->accept(this);
        VarPtr expr = lastResult;

        if (!basePtr->isLvalue()) {
            throw std::logic_error("Not an lvalue!");
        }

        auto heapPtr = std::dynamic_pointer_cast<PointerVariable>(basePtr);
        auto loaded_array = heapPtr->load(this);
        auto arrayPtr = loaded_array->getArray(this);

        lastResult = arrayPtr->getElementPtr(expr, this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), p->line_number);
    }
}

void Compiler::visitLStruct(LStruct *p) {
    try {
        p->lval_->accept(this);
        auto basePtr = lastResult;

        if (!basePtr->isLvalue()) {
            throw std::logic_error("Not an lvalue!");
        }

        auto castedPtr = std::dynamic_pointer_cast<PointerVariable>(lastResult);
        auto loadedObject = castedPtr->load(this);

        if (loadedObject->getType()->getTypeSpecifier() == TypeSpecifier::SizedArray && p->ident_ == "length") {
            lastResult = loadedObject->getSize(this);
            return;
        }

        lastResult = loadedObject->getField(p->ident_, this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), p->line_number);
    }
}

///////////////////////// STATEMENTS

void Compiler::visitEmpty(Empty *empty) {}

void Compiler::visitBStmt(BStmt *bstmt) {
    bstmt->block_->accept(this);
}

void Compiler::visitDecl(Decl *decl) {
    decl->type_->accept(this);
    if (!typeIsDeclarable(declaredType))
        reportError("Cannot declare variable of this type.", decl->line_number);

    decl->listitem_->accept(this);
}

void Compiler::visitAss(Ass *ass) {
    try {
        ass->lval_->accept(this);
        VarPtr e1 = lastResult;
        ass->expr_->accept(this);
        VarPtr e2 = lastResult;

        if (!(*e1->getType() == *e2->getType()))
            reportError("Type of variable and assigned expression doesn't match.", ass->line_number);

        std::stringstream ss;
        ss << "\tstore " << e2->getType()->getTranslation() << " " << e2->getCode(this)
           << ", " << e1->getType()->getTranslation() << "* " << e1->getCode(this);

        compiledCode.push_back(ss.str());
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), ass->line_number);
    }
}

void Compiler::visitIncr(Incr *incr) {
    try {
        incr->lval_->accept(this);
        if (!lastResult->isLvalue()) {
            throw std::logic_error("Not an lvalue!");
        }
        auto ptr = std::dynamic_pointer_cast<PointerVariable>(lastResult);
        auto ptr_loaded = ptr->load(this);

        VarPtr one(new ConstIntVariable(1));
        auto ptr_incr = ptr_loaded->add(one, this);
        ptr->store(ptr_incr, this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), incr->line_number);
    }
}

void Compiler::visitDecr(Decr *decr) {
    try {
        decr->lval_->accept(this);
        if (!lastResult->isLvalue()) {
            throw std::logic_error("Not an lvalue!");
        }
        auto ptr = std::dynamic_pointer_cast<PointerVariable>(lastResult);
        auto ptr_loaded = ptr->load(this);

        VarPtr one(new ConstIntVariable(1));
        auto ptr_decr = ptr_loaded->sub(one, this);
        ptr->store(ptr_decr, this);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), decr->line_number);
    }
}

void Compiler::visitRet(Ret *ret) {
    try {
        ret->expr_->accept(this);
        VarPtr e1 = lastResult;

        if (!(*e1->getType() == *currentFunction.getReturnType()))
            reportError("Return type mismatch.", ret->line_number);

        std::stringstream ss;

        ss << "\tret " << e1->getType()->getTranslation() << " " << e1->getCode(this);
        compiledCode.emplace_back(ss.str());

        currentFunction.setReturnStatements(currentFunction.getReturnStatements()+1);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), ret->line_number);
    }
}

void Compiler::visitVRet(VRet *vret) {
    try {
        if (TypeSpecifier::Void != currentFunction.getReturnType()->getTypeSpecifier())
            reportError("Return type mismatch.", vret->line_number);

        compiledCode.emplace_back("\tret void");
        currentFunction.setReturnStatements(currentFunction.getReturnStatements()+1);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), vret->line_number);
    }
}

void Compiler::visitCond(Cond *cond) {
    try {
        cond->expr_->accept(this);
        VarPtr e1 = lastResult;
        if (e1->getType()->getTypeSpecifier() !=TypeSpecifier::Bool)
            reportError("If condition has to be boolean.", cond->line_number);

        if(e1->isConst()) {
            auto bVar = std::dynamic_pointer_cast<ConstBoolVariable>(lastResult);
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

            std::vector<int> labels = (currentFunction.getReturnStatements() > 0) ? std::vector<int>{curr_label} :
                                      std::vector<int>{curr_label, if_branch_label.getLabelNum()};
            auto after_if_label = currentFunction.getNewLabel(labels);

            if (currentFunction.getReturnStatements() <= 0) {
                std::stringstream ifJumpStream;
                ifJumpStream << "\t" << "br label %" << after_if_label.getLabelNum();
                compiledCode.emplace_back(ifJumpStream.str());
            }

            currentFunction.setReturnStatements(0);
            compiledCode.emplace_back(after_if_label.getCode());
            currentFunction.setLastLabel(after_if_label.getLabelNum());

            std::stringstream ss;
            ss << "\t" << "br i1 " << e1->getCode(this) << ", label %" << if_branch_label.getLabelNum() << ", label %"
               << after_if_label.getLabelNum();
            compiledCode.insert(compiledCode.begin()+jumpCodePosition, ss.str());
        }
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), cond->line_number);
    }
}

void Compiler::visitCondElse(CondElse *condelse) {
    try {
        condelse->expr_->accept(this);
        VarPtr e1 = lastResult;

        if (e1->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
            reportError("If condition has to be boolean.", condelse->line_number);

        if(e1->isConst()) {
            auto bVar = std::dynamic_pointer_cast<ConstBoolVariable>(e1);
            if (bVar->getValue()) {
                condelse->stmt_1->accept(this);
            } else {
                condelse->stmt_2->accept(this);
            }
        } else {
            unsigned long jumpCodePosition = compiledCode.size();
            auto curr_label = currentFunction.getLastLabel();

            auto if_branch_label = currentFunction.getNewLabel({curr_label});
            compiledCode.emplace_back(if_branch_label.getCode());
            currentFunction.setLastLabel(if_branch_label.getLabelNum());
            currentFunction.setReturnStatements(0);
            condelse->stmt_1->accept(this);
            unsigned long ifJumpPosition = compiledCode.size();
            int if_returned = currentFunction.getReturnStatements();

            auto else_branch_label = currentFunction.getNewLabel({curr_label});
            compiledCode.emplace_back(else_branch_label.getCode());
            currentFunction.setLastLabel(else_branch_label.getLabelNum());
            currentFunction.setReturnStatements(0);
            condelse->stmt_2->accept(this);
            unsigned long elseJumpPosition = compiledCode.size();
            int else_returned = currentFunction.getReturnStatements();

            std::vector<int> labels;
            if (if_returned <= 0)
                labels.push_back(if_branch_label.getLabelNum());
            if (else_returned <= 0)
                labels.push_back(else_branch_label.getLabelNum());

            auto after_if_label = currentFunction.getNewLabel(labels);
            currentFunction.setReturnStatements(std::min(if_returned, else_returned));

            if (else_returned <= 0) {
                std::stringstream elseJumpStream;
                elseJumpStream << "\t" << "br label %" << after_if_label.getLabelNum();
                compiledCode.insert(compiledCode.begin() + elseJumpPosition, elseJumpStream.str());
            }

            if (if_returned <= 0) {
                std::stringstream ifJumpStream;
                ifJumpStream << "\t" << "br label %" << after_if_label.getLabelNum();
                compiledCode.insert(compiledCode.begin() + ifJumpPosition, ifJumpStream.str());
            }

            std::stringstream ss;
            ss << "\t" << "br i1 " << e1->getCode(this) << ", label %" << if_branch_label.getLabelNum() << ", label %"
               << else_branch_label.getLabelNum();
            compiledCode.insert(compiledCode.begin() + jumpCodePosition, ss.str());

            if (currentFunction.getReturnStatements() <= 0) {
                compiledCode.emplace_back(after_if_label.getCode());
                currentFunction.setLastLabel(after_if_label.getLabelNum());
            }
        }
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), condelse->line_number);
    }
}

void Compiler::visitFor(For *p) {
    try {
        // prepare array and counter
        p->expr_->accept(this);
        auto array_pair = lastResult;

        if (array_pair->getType()->getTypeSpecifier() != TypeSpecifier::SizedArray)
            reportError("Forloop object has to be an array.", p->line_number);

        auto size = array_pair->getSize(this);
        auto array = array_pair->getArray(this);

        auto counter = std::make_shared<PointerVariable>(TypePtr(new Int()), this);
        counter->store(VarPtr(new ConstIntVariable(0)), this);

        auto curr_label = currentFunction.getLastLabel();
        // check condition
        auto check_condition_label = currentFunction.getNewLabel({curr_label});
        std::stringstream ss;
        ss << "\t" << "br label %" << check_condition_label.getLabelNum();
        compiledCode.emplace_back(ss.str());

        auto checkLabelPosition = compiledCode.size();
        currentFunction.setLastLabel(check_condition_label.getLabelNum());

        auto counter_loaded = counter->load(this);
        auto comp_result = counter_loaded->lt(size, this);

        auto arrayType = std::dynamic_pointer_cast<Array>(array->getType());

        if (!(*arrayType->getType_() == *p->type_))
            reportError("For argument has to match type of an array.", p->line_number);

        auto pointer_elem = array->getElementPtr(counter_loaded, this);

        currentFunction.getVariables().emplace_back();
        auto heapVar = std::make_shared<PointerVariable>(pointer_elem->getType(), pointer_elem->getCode(this));
        currentFunction.putVar(p->ident_, heapVar);

        VarPtr one(new ConstIntVariable(1));
        auto counter_incr = counter_loaded->add(one, this);
        counter->store(counter_incr, this);

        auto forCondJumpPosition = compiledCode.size();
        // for body
        // TODO: Better labels management?
        auto for_body_label = currentFunction.getNewLabel(std::vector<int>{check_condition_label.getLabelNum()});
        compiledCode.emplace_back(for_body_label.getCode());
        currentFunction.setLastLabel(for_body_label.getLabelNum());
        currentFunction.setReturnStatements(0);

        p->stmt_->accept(this);

        currentFunction.getVariables().pop_back();
        auto for_returns = currentFunction.getReturnStatements();
        std::stringstream forJumpStream;
        forJumpStream << "\t" << "br label %" << check_condition_label.getLabelNum();
        compiledCode.emplace_back(forJumpStream.str());

        // after for
        std::vector<int> labels {check_condition_label.getLabelNum()};
        if (for_returns <= 0) {
            labels.push_back(for_body_label.getLabelNum());
        }
        auto after_for_label = currentFunction.getNewLabel(labels);
        currentFunction.setLastLabel(after_for_label.getLabelNum());
        compiledCode.emplace_back(after_for_label.getCode());

        std::stringstream forCondStream;
        forCondStream << "\t" << "br i1 " << comp_result->getCode(this) << ", label %" << for_body_label.getLabelNum() << ", label %"
                      << after_for_label.getLabelNum();
        compiledCode.insert(compiledCode.begin() + forCondJumpPosition, forCondStream.str());

        if (for_returns <= 0) {
            check_condition_label.addLabel(for_body_label.getLabelNum());
            compiledCode.insert(compiledCode.begin() + checkLabelPosition, check_condition_label.getCode());
        }

        currentFunction.setReturnStatements(0);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), p->line_number);
    }
}

void Compiler::visitWhile(While *whileLoop) {
    try {
        auto curr_label = currentFunction.getLastLabel();
        // check condition
        auto check_condition_label = currentFunction.getNewLabel({curr_label});
        std::stringstream ss;
        ss << "\t" << "br label %" << check_condition_label.getLabelNum();
        compiledCode.emplace_back(ss.str());

        auto checkLabelPosition = compiledCode.size();
        currentFunction.setLastLabel(check_condition_label.getLabelNum());

        whileLoop->expr_->accept(this);
        VarPtr e1 = lastResult;

        if (e1->getType()->getTypeSpecifier() != TypeSpecifier::Bool)
            reportError("While condition has to be boolean.", whileLoop->line_number);

        // while(false)
        if(e1->isConst()) {
            auto bVar = std::dynamic_pointer_cast<ConstBoolVariable>(e1);
            if(!bVar->getValue()) {
                return;
            }
        }
        auto whileCondJumpPosition = compiledCode.size();

        // while body
        std::vector<int> w_labels {check_condition_label.getLabelNum()};
        auto while_body_label = currentFunction.getNewLabel(w_labels);
        compiledCode.emplace_back(while_body_label.getCode());
        currentFunction.setLastLabel(while_body_label.getLabelNum());
        currentFunction.setReturnStatements(0);

        whileLoop->stmt_->accept(this);

        auto while_returns = currentFunction.getReturnStatements();
        std::stringstream whileJumpStream;
        whileJumpStream << "\t" << "br label %" << check_condition_label.getLabelNum();
        compiledCode.emplace_back(whileJumpStream.str());

        // after while
        std::vector<int> labels {check_condition_label.getLabelNum()};
        if (while_returns <= 0) {
            labels.push_back(while_body_label.getLabelNum());
        }
        auto after_while_label = currentFunction.getNewLabel(labels);
        currentFunction.setLastLabel(after_while_label.getLabelNum());
        compiledCode.emplace_back(after_while_label.getCode());

        std::stringstream whileCondStream;
        whileCondStream << "\t" << "br i1 " << e1->getCode(this) << ", label %" << while_body_label.getLabelNum() << ", label %"
                        << after_while_label.getLabelNum();
        compiledCode.insert(compiledCode.begin() + whileCondJumpPosition, whileCondStream.str());

        if (while_returns <= 0) {
            check_condition_label.addLabel(while_body_label.getLabelNum());
            compiledCode.insert(compiledCode.begin() + checkLabelPosition, check_condition_label.getCode());
        }

        // while(true)
        if(e1->isConst()) {
            return;
        }

        currentFunction.setReturnStatements(0);
    } catch(const std::logic_error& ex) {
        reportError(ex.what(), whileLoop->line_number);
    }
}

void Compiler::visitSExp(SExp *sexp) {
    sexp->expr_->accept(this);
}

void Compiler::visitNoInit(NoInit *noinit) {
    try {
        auto heapVar = std::make_shared<PointerVariable>(declaredType, this);

        if (typeIn(declaredType->getTypeSpecifier(),
                   std::vector<TypeSpecifier>{TypeSpecifier::Int,
                                              TypeSpecifier::Bool,
                                              TypeSpecifier::String})) {
            auto defaultConst = ConstVariable::getConstDefault(declaredType);
            heapVar->store(defaultConst, this);
        }

        currentFunction.putVar(noinit->ident_, heapVar);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), noinit->line_number);
    }

}

void Compiler::visitInit(Init *init) {
    try {
        init->expr_->accept(this);
        if (!(*lastResult->getType() == *declaredType))
            reportError("Type of variable and assigned expression doesn't match.", init->line_number);
        VarPtr e1 = lastResult;

        auto heapVar = std::make_shared<PointerVariable>(declaredType, this);
        heapVar->store(e1, this);

        currentFunction.putVar(init->ident_, heapVar);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), init->line_number);
    }
}

/////////////////////////// TYPES

void Compiler::visitInt(Int * intConst) {
    declaredType = TypePtr(intConst->clone());
}

void Compiler::visitStr(Str *str) {
    declaredType = TypePtr(str->clone());
}

void Compiler::visitBool(Bool * boolConst) {
    declaredType = TypePtr(boolConst->clone());
}

void Compiler::visitVoid(Void * voidConst) {
    declaredType = TypePtr(voidConst->clone());
}

void Compiler::visitArray(Array *p) {
    p->type_->accept(this);
    declaredType = TypePtr(new SizedArray(std::shared_ptr<Array>(p->clone())));
}

void Compiler::visitStruct(Struct *p) {
    declaredType = std::shared_ptr<Struct>(p->clone());
}

///////////////////////////// EXPR

void Compiler::visitENull(ENull *p) {
    lastResult = VarPtr(new NullPtrVariable(TypePtr(p->type_->clone())));
}

void Compiler::visitEArray(EArray *p) {
    auto array_type = std::make_shared<Array>(p->type_->clone());
    auto sized_array_type = std::make_shared<SizedArray>(array_type);

    p->expr_->accept(this);
    auto expr = lastResult;

    if (expr->getType()->getTypeSpecifier() != TypeSpecifier::Int)
        reportError("Array size must be int.", p->line_number);

    auto allocated_array = sized_array_type->allocateArray(expr, this);
    lastResult = sized_array_type->createArrayStruct(allocated_array, expr, this);
}

void Compiler::visitEStruct(EStruct *p) {
    if (structures.find(p->ident_) == structures.end())
        reportError("Struct type not declared", p->line_number);

    auto structure = structures.at(p->ident_);
    lastResult = structure.allocateStruct(this);
}

void Compiler::visitEVar(EVar *evar) {
    try {
        evar->lval_->accept(this);
        if (lastResult->isLvalue()) {
            auto ptr = std::dynamic_pointer_cast<PointerVariable>(lastResult);
            lastResult =  ptr->load(this);
        }
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
    try {
        if (functions.find(eapp->ident_) == functions.end())
            reportError("Function " + eapp->ident_ + " undeclared.", eapp->line_number);

        if (eapp->listexpr_->size() != functions[eapp->ident_].getArguments().size())
            reportError("Wrong number of function arguments.", eapp->line_number);

        std::stringstream ss;
        TypePtr retType = functions[eapp->ident_].getReturnType();
        VarPtr result;

        std::stringstream call_stream;
        std::string arguments;
        bool first = true;
        for (auto i = 0; i < functions[eapp->ident_].getArguments().size(); i++) {
            (*eapp->listexpr_)[i]->accept(this);

            if (!(*lastResult->getType() == *functions[eapp->ident_].getArguments()[i].second->getType()))
                reportError("Type of argument and assigned expression doesn't match.", eapp->line_number);

            call_stream << ((first) ? "" : ", ") << lastResult->getType()->getTranslation() << " "
                        << lastResult->getCode(this);
            first = false;
        }
        call_stream << ")";

        ss << "\t";
        if (retType->getTypeSpecifier() != TypeSpecifier::Void) {
            result = currentFunction.getNewRegisterVar(retType);
            ss << result->getCode(this) << " = ";
        }

        ss << "call " << retType->getTranslation() << " @" << eapp->ident_ << "(";
        ss << call_stream.str();

        compiledCode.push_back(ss.str());

        if (retType->getTypeSpecifier() != TypeSpecifier::Void) {
            lastResult = result;
        }
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), eapp->line_number);
    }
}

void Compiler::visitEMethod(EMethod *p) {
    try {
        p->lval_->accept(this);
        if (lastResult->isLvalue()) {
            auto ptr = std::dynamic_pointer_cast<PointerVariable>(lastResult);
            lastResult = ptr->load(this);
        }

        auto object = lastResult;
        if (object->getType()->getTypeSpecifier() != TypeSpecifier::Struct) {
            reportError("Not a struct type.", p->line_number);
        }

        auto struct_type = std::dynamic_pointer_cast<Struct>(lastResult->getType());
        if (structures.find(struct_type->getIdent_()) == structures.end())
            reportError("Not declared class.", p->line_number);
        auto structure = structures.at(struct_type->getIdent_());
        auto method_ident = structure.getName() + "_" +p->ident_;

        if (functions.find(method_ident) == functions.end())
            reportError("Method undeclared.", p->line_number);
        auto function = functions.at(method_ident);

        if (p->listexpr_->size() + 1 != function.getArguments().size())
            reportError("Wrong number of function arguments.", p->line_number);

        TypePtr retType = function.getReturnType();
        VarPtr result;

        std::stringstream call_stream;
        std::string arguments;

        if (!(*object->getType() == *function.getArguments()[0].second->getType()))
            reportError("Wrong object type.", p->line_number);

        call_stream << object->getType()->getTranslation() << " " << object->getCode(this);

        for (auto i = 1; i < function.getArguments().size(); i++) {
            (*p->listexpr_)[i-1]->accept(this);

            if (!(*lastResult->getType() == *function.getArguments()[i].second->getType()))
                reportError("Type of argument and assigned expression doesn't match.", p->line_number);

            call_stream << ", " << lastResult->getType()->getTranslation() << " " << lastResult->getCode(this);
        }
        call_stream << ")";

        std::stringstream ss;
        ss << "\t";
        if(retType->getTypeSpecifier() != TypeSpecifier::Void) {
            result = currentFunction.getNewRegisterVar(retType);
            ss << result->getCode(this) << " = ";
        }

        ss << "call " << retType->getTranslation() << " @" << method_ident << "(";
        ss << call_stream.str();

        compiledCode.push_back(ss.str());

        if(retType->getTypeSpecifier() != TypeSpecifier::Void) {
            lastResult = result;
        }
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), p->line_number);
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

    try {
        lastResult = e1->band(eand->expr_2, this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), eand->line_number);
    }
}

void Compiler::visitEOr(EOr *eor) {
    eor->expr_1->accept(this);
    VarPtr e1 = lastResult;

    try {
        lastResult = e1->bor(eor->expr_2, this);
    } catch (const std::logic_error& ex) {
        reportError(ex.what(), eor->line_number);
    }
}

/////////////////////////////// OPERATORS

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
    compiledCode.emplace_back("");

    currentPhase = Phase::SCANNING_DEFINITIONS;
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

void Compiler::visitListAttribute(ListAttribute *listattr) {
    for (auto elem : *listattr) {
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

std::string Compiler::getGlobalStringName(const std::string& toFind) {
    if (knownStrings.find(toFind) == knownStrings.end()) {
        std::stringstream ss;
        ss << "@.str." << knownStrings.size();
        knownStrings[toFind] = ss.str();
    }

    return knownStrings[toFind];
}

const VarPtr& Compiler::getLastResult() const {
    return lastResult;
}

Compiler::Compiler() : lastResult(nullptr), declaredType(nullptr), currentStructure(nullptr) {}

const std::unordered_map<Ident, Structure>& Compiler::getStructures() const {
    return structures;
}
