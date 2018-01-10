/*** BNFC-Generated Visitor Design Pattern Skeleton. ***/
/* This implements the common visitor design pattern.
   Note that this method uses Visitor-traversal of lists, so
   List->accept() does NOT traverse the list. This allows different
   algorithms to use context information differently. */

#include "Compiler.hpp"


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
    /* Code For Prog Goes Here */

    prog->listtopdef_->accept(this);

}

void Compiler::visitFnDef(FnDef *fndef) {
    /* Code For FnDef Goes Here */

    fndef->type_->accept(this);
    visitIdent(fndef->ident_);
    fndef->listarg_->accept(this);
    fndef->block_->accept(this);

}

void Compiler::visitAr(Ar *ar) {
    /* Code For Ar Goes Here */

    ar->type_->accept(this);
    visitIdent(ar->ident_);

}

void Compiler::visitBlk(Blk *blk) {
    /* Code For Blk Goes Here */

    blk->liststmt_->accept(this);

}

void Compiler::visitEmpty(Empty *empty) {
    /* Code For Empty Goes Here */


}

void Compiler::visitBStmt(BStmt *bstmt) {
    /* Code For BStmt Goes Here */

    bstmt->block_->accept(this);

}

void Compiler::visitDecl(Decl *decl) {
    /* Code For Decl Goes Here */

    decl->type_->accept(this);
    decl->listitem_->accept(this);

}

void Compiler::visitAss(Ass *ass) {
    /* Code For Ass Goes Here */

    visitIdent(ass->ident_);
    ass->expr_->accept(this);

}

void Compiler::visitIncr(Incr *incr) {
    /* Code For Incr Goes Here */

    visitIdent(incr->ident_);

}

void Compiler::visitDecr(Decr *decr) {
    /* Code For Decr Goes Here */

    visitIdent(decr->ident_);

}

void Compiler::visitRet(Ret *ret) {
    /* Code For Ret Goes Here */

    ret->expr_->accept(this);

}

void Compiler::visitVRet(VRet *vret) {
    /* Code For VRet Goes Here */


}

void Compiler::visitCond(Cond *cond) {
    /* Code For Cond Goes Here */

    cond->expr_->accept(this);
    cond->stmt_->accept(this);

}

void Compiler::visitCondElse(CondElse *condelse) {
    /* Code For CondElse Goes Here */

    condelse->expr_->accept(this);
    condelse->stmt_1->accept(this);
    condelse->stmt_2->accept(this);

}

void Compiler::visitWhile(While *whileLoop) {
    /* Code For While Goes Here */

    whileLoop->expr_->accept(this);
    whileLoop->stmt_->accept(this);

}

void Compiler::visitSExp(SExp *sexp) {
    /* Code For SExp Goes Here */

    sexp->expr_->accept(this);

}

void Compiler::visitNoInit(NoInit *noinit) {
    /* Code For NoInit Goes Here */

    visitIdent(noinit->ident_);

}

void Compiler::visitInit(Init *init) {
    /* Code For Init Goes Here */

    visitIdent(init->ident_);
    init->expr_->accept(this);

}

void Compiler::visitInt(Int * intConst) {
    /* Code For Int Goes Here */


}

void Compiler::visitStr(Str *str) {
    /* Code For Str Goes Here */


}

void Compiler::visitBool(Bool * boolConst) {
    /* Code For Bool Goes Here */


}

void Compiler::visitVoid(Void * voidConst) {
    /* Code For Void Goes Here */


}

void Compiler::visitFun(Fun *fun) {
    /* Code For Fun Goes Here */

    fun->type_->accept(this);
    fun->listtype_->accept(this);

}

void Compiler::visitEVar(EVar *evar) {
    /* Code For EVar Goes Here */

    visitIdent(evar->ident_);

}

void Compiler::visitELitInt(ELitInt *elitint) {
    /* Code For ELitInt Goes Here */

    visitInteger(elitint->integer_);

}

void Compiler::visitELitTrue(ELitTrue *elittrue) {
    /* Code For ELitTrue Goes Here */


}

void Compiler::visitELitFalse(ELitFalse *elitfalse) {
    /* Code For ELitFalse Goes Here */


}

void Compiler::visitEApp(EApp *eapp) {
    /* Code For EApp Goes Here */

    visitIdent(eapp->ident_);
    eapp->listexpr_->accept(this);

}

void Compiler::visitEString(EString *estring) {
    /* Code For EString Goes Here */

    visitString(estring->string_);

}

void Compiler::visitNeg(Neg *neg) {
    /* Code For Neg Goes Here */

    neg->expr_->accept(this);

}

void Compiler::visitNot(Not * notOp) {
    /* Code For Not Goes Here */

    notOp->expr_->accept(this);

}

void Compiler::visitEMul(EMul *emul) {
    /* Code For EMul Goes Here */

    emul->expr_1->accept(this);
    emul->mulop_->accept(this);
    emul->expr_2->accept(this);

}

void Compiler::visitEAdd(EAdd *eadd) {
    /* Code For EAdd Goes Here */

    eadd->expr_1->accept(this);
    eadd->addop_->accept(this);
    eadd->expr_2->accept(this);

}

void Compiler::visitERel(ERel *erel) {
    /* Code For ERel Goes Here */

    erel->expr_1->accept(this);
    erel->relop_->accept(this);
    erel->expr_2->accept(this);

}

void Compiler::visitEAnd(EAnd *eand) {
    /* Code For EAnd Goes Here */

    eand->expr_1->accept(this);
    eand->expr_2->accept(this);

}

void Compiler::visitEOr(EOr *eor) {
    /* Code For EOr Goes Here */

    eor->expr_1->accept(this);
    eor->expr_2->accept(this);

}

void Compiler::visitPlus(Plus *plus) {
    /* Code For Plus Goes Here */


}

void Compiler::visitMinus(Minus *minus) {
    /* Code For Minus Goes Here */


}

void Compiler::visitTimes(Times *times) {
    /* Code For Times Goes Here */


}

void Compiler::visitDiv(Div *div) {
    /* Code For Div Goes Here */


}

void Compiler::visitMod(Mod *mod) {
    /* Code For Mod Goes Here */


}

void Compiler::visitLTH(LTH *lth) {
    /* Code For LTH Goes Here */


}

void Compiler::visitLE(LE *le) {
    /* Code For LE Goes Here */


}

void Compiler::visitGTH(GTH *gth) {
    /* Code For GTH Goes Here */


}

void Compiler::visitGE(GE *ge) {
    /* Code For GE Goes Here */


}

void Compiler::visitEQU(EQU *equ) {
    /* Code For EQU Goes Here */


}

void Compiler::visitNE(NE *ne) {
    /* Code For NE Goes Here */


}


void Compiler::visitListTopDef(ListTopDef *listtopdef) {
    for (ListTopDef::iterator i = listtopdef->begin(); i != listtopdef->end(); ++i) {
        (*i)->accept(this);
    }
}

void Compiler::visitListArg(ListArg *listarg) {
    for (ListArg::iterator i = listarg->begin(); i != listarg->end(); ++i) {
        (*i)->accept(this);
    }
}

void Compiler::visitListStmt(ListStmt *liststmt) {
    for (ListStmt::iterator i = liststmt->begin(); i != liststmt->end(); ++i) {
        (*i)->accept(this);
    }
}

void Compiler::visitListItem(ListItem *listitem) {
    for (ListItem::iterator i = listitem->begin(); i != listitem->end(); ++i) {
        (*i)->accept(this);
    }
}

void Compiler::visitListType(ListType *listtype) {
    for (ListType::iterator i = listtype->begin(); i != listtype->end(); ++i) {
        (*i)->accept(this);
    }
}

void Compiler::visitListExpr(ListExpr *listexpr) {
    for (ListExpr::iterator i = listexpr->begin(); i != listexpr->end(); ++i) {
        (*i)->accept(this);
    }
}


void Compiler::visitInteger(Integer x) {
    /* Code for Integer Goes Here */
}

void Compiler::visitChar(Char x) {
    /* Code for Char Goes Here */
}

void Compiler::visitDouble(Double x) {
    /* Code for Double Goes Here */
}

void Compiler::visitString(String x) {
    /* Code for String Goes Here */
}

void Compiler::visitIdent(Ident x) {
    /* Code for Ident Goes Here */
}



