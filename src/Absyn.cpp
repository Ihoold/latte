//C++ Abstract Syntax Implementation generated by the BNF Converter.
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include "Absyn.hpp"

/********************   Prog    ********************/
Prog::Prog(ListTopDef *p1)
{
  listtopdef_ = p1;

}

Prog::Prog(const Prog & other)
{
  listtopdef_ = other.listtopdef_->clone();

}

Prog &Prog::operator=(const Prog & other)
{
  Prog tmp(other);
  swap(tmp);
  return *this;
}

void Prog::swap(Prog & other)
{
  std::swap(listtopdef_, other.listtopdef_);

}

Prog::~Prog()
{
  delete(listtopdef_);

}

void Prog::accept(Visitor *v)
{
  v->visitProg(this);
}

Prog *Prog::clone() const
{
  return new Prog(*this);
}



/********************   FnDef    ********************/
FnDef::FnDef(Type *p1, Ident p2, ListArg *p3, Block *p4)
{
  type_ = p1;
  ident_ = p2;
  listarg_ = p3;
  block_ = p4;

}

FnDef::FnDef(const FnDef & other)
{
  type_ = other.type_->clone();
  ident_ = other.ident_;
  listarg_ = other.listarg_->clone();
  block_ = other.block_->clone();

}

FnDef &FnDef::operator=(const FnDef & other)
{
  FnDef tmp(other);
  swap(tmp);
  return *this;
}

void FnDef::swap(FnDef & other)
{
  std::swap(type_, other.type_);
  std::swap(ident_, other.ident_);
  std::swap(listarg_, other.listarg_);
  std::swap(block_, other.block_);

}

FnDef::~FnDef()
{
  delete(type_);
  delete(listarg_);
  delete(block_);

}

void FnDef::accept(Visitor *v)
{
  v->visitFnDef(this);
}

FnDef *FnDef::clone() const
{
  return new FnDef(*this);
}



/********************   Ar    ********************/
Ar::Ar(Type *p1, Ident p2)
{
  type_ = p1;
  ident_ = p2;

}

Ar::Ar(const Ar & other)
{
  type_ = other.type_->clone();
  ident_ = other.ident_;

}

Ar &Ar::operator=(const Ar & other)
{
  Ar tmp(other);
  swap(tmp);
  return *this;
}

void Ar::swap(Ar & other)
{
  std::swap(type_, other.type_);
  std::swap(ident_, other.ident_);

}

Ar::~Ar()
{
  delete(type_);

}

void Ar::accept(Visitor *v)
{
  v->visitAr(this);
}

Ar *Ar::clone() const
{
  return new Ar(*this);
}



/********************   Blk    ********************/
Blk::Blk(ListStmt *p1)
{
  liststmt_ = p1;

}

Blk::Blk(const Blk & other)
{
  liststmt_ = other.liststmt_->clone();

}

Blk &Blk::operator=(const Blk & other)
{
  Blk tmp(other);
  swap(tmp);
  return *this;
}

void Blk::swap(Blk & other)
{
  std::swap(liststmt_, other.liststmt_);

}

Blk::~Blk()
{
  delete(liststmt_);

}

void Blk::accept(Visitor *v)
{
  v->visitBlk(this);
}

Blk *Blk::clone() const
{
  return new Blk(*this);
}



/********************   Empty    ********************/
Empty::Empty()
{

}

Empty::Empty(const Empty & other)
{

}

Empty &Empty::operator=(const Empty & other)
{
  Empty tmp(other);
  swap(tmp);
  return *this;
}

void Empty::swap(Empty & other)
{

}

Empty::~Empty()
{

}

void Empty::accept(Visitor *v)
{
  v->visitEmpty(this);
}

Empty *Empty::clone() const
{
  return new Empty(*this);
}



/********************   BStmt    ********************/
BStmt::BStmt(Block *p1)
{
  block_ = p1;

}

BStmt::BStmt(const BStmt & other)
{
  block_ = other.block_->clone();

}

BStmt &BStmt::operator=(const BStmt & other)
{
  BStmt tmp(other);
  swap(tmp);
  return *this;
}

void BStmt::swap(BStmt & other)
{
  std::swap(block_, other.block_);

}

BStmt::~BStmt()
{
  delete(block_);

}

void BStmt::accept(Visitor *v)
{
  v->visitBStmt(this);
}

BStmt *BStmt::clone() const
{
  return new BStmt(*this);
}



/********************   Decl    ********************/
Decl::Decl(Type *p1, ListItem *p2)
{
  type_ = p1;
  listitem_ = p2;

}

Decl::Decl(const Decl & other)
{
  type_ = other.type_->clone();
  listitem_ = other.listitem_->clone();

}

Decl &Decl::operator=(const Decl & other)
{
  Decl tmp(other);
  swap(tmp);
  return *this;
}

void Decl::swap(Decl & other)
{
  std::swap(type_, other.type_);
  std::swap(listitem_, other.listitem_);

}

Decl::~Decl()
{
  delete(type_);
  delete(listitem_);

}

void Decl::accept(Visitor *v)
{
  v->visitDecl(this);
}

Decl *Decl::clone() const
{
  return new Decl(*this);
}



/********************   Ass    ********************/
Ass::Ass(Ident p1, Expr *p2)
{
  ident_ = p1;
  expr_ = p2;

}

Ass::Ass(const Ass & other)
{
  ident_ = other.ident_;
  expr_ = other.expr_->clone();

}

Ass &Ass::operator=(const Ass & other)
{
  Ass tmp(other);
  swap(tmp);
  return *this;
}

void Ass::swap(Ass & other)
{
  std::swap(ident_, other.ident_);
  std::swap(expr_, other.expr_);

}

Ass::~Ass()
{
  delete(expr_);

}

void Ass::accept(Visitor *v)
{
  v->visitAss(this);
}

Ass *Ass::clone() const
{
  return new Ass(*this);
}



/********************   Incr    ********************/
Incr::Incr(Ident p1)
{
  ident_ = p1;

}

Incr::Incr(const Incr & other)
{
  ident_ = other.ident_;

}

Incr &Incr::operator=(const Incr & other)
{
  Incr tmp(other);
  swap(tmp);
  return *this;
}

void Incr::swap(Incr & other)
{
  std::swap(ident_, other.ident_);

}

Incr::~Incr()
{

}

void Incr::accept(Visitor *v)
{
  v->visitIncr(this);
}

Incr *Incr::clone() const
{
  return new Incr(*this);
}



/********************   Decr    ********************/
Decr::Decr(Ident p1)
{
  ident_ = p1;

}

Decr::Decr(const Decr & other)
{
  ident_ = other.ident_;

}

Decr &Decr::operator=(const Decr & other)
{
  Decr tmp(other);
  swap(tmp);
  return *this;
}

void Decr::swap(Decr & other)
{
  std::swap(ident_, other.ident_);

}

Decr::~Decr()
{

}

void Decr::accept(Visitor *v)
{
  v->visitDecr(this);
}

Decr *Decr::clone() const
{
  return new Decr(*this);
}



/********************   Ret    ********************/
Ret::Ret(Expr *p1)
{
  expr_ = p1;

}

Ret::Ret(const Ret & other)
{
  expr_ = other.expr_->clone();

}

Ret &Ret::operator=(const Ret & other)
{
  Ret tmp(other);
  swap(tmp);
  return *this;
}

void Ret::swap(Ret & other)
{
  std::swap(expr_, other.expr_);

}

Ret::~Ret()
{
  delete(expr_);

}

void Ret::accept(Visitor *v)
{
  v->visitRet(this);
}

Ret *Ret::clone() const
{
  return new Ret(*this);
}



/********************   VRet    ********************/
VRet::VRet()
{

}

VRet::VRet(const VRet & other)
{

}

VRet &VRet::operator=(const VRet & other)
{
  VRet tmp(other);
  swap(tmp);
  return *this;
}

void VRet::swap(VRet & other)
{

}

VRet::~VRet()
{

}

void VRet::accept(Visitor *v)
{
  v->visitVRet(this);
}

VRet *VRet::clone() const
{
  return new VRet(*this);
}



/********************   Cond    ********************/
Cond::Cond(Expr *p1, Stmt *p2)
{
  expr_ = p1;
  stmt_ = p2;

}

Cond::Cond(const Cond & other)
{
  expr_ = other.expr_->clone();
  stmt_ = other.stmt_->clone();

}

Cond &Cond::operator=(const Cond & other)
{
  Cond tmp(other);
  swap(tmp);
  return *this;
}

void Cond::swap(Cond & other)
{
  std::swap(expr_, other.expr_);
  std::swap(stmt_, other.stmt_);

}

Cond::~Cond()
{
  delete(expr_);
  delete(stmt_);

}

void Cond::accept(Visitor *v)
{
  v->visitCond(this);
}

Cond *Cond::clone() const
{
  return new Cond(*this);
}



/********************   CondElse    ********************/
CondElse::CondElse(Expr *p1, Stmt *p2, Stmt *p3)
{
  expr_ = p1;
  stmt_1 = p2;
  stmt_2 = p3;

}

CondElse::CondElse(const CondElse & other)
{
  expr_ = other.expr_->clone();
  stmt_1 = other.stmt_1->clone();
  stmt_2 = other.stmt_2->clone();

}

CondElse &CondElse::operator=(const CondElse & other)
{
  CondElse tmp(other);
  swap(tmp);
  return *this;
}

void CondElse::swap(CondElse & other)
{
  std::swap(expr_, other.expr_);
  std::swap(stmt_1, other.stmt_1);
  std::swap(stmt_2, other.stmt_2);

}

CondElse::~CondElse()
{
  delete(expr_);
  delete(stmt_1);
  delete(stmt_2);

}

void CondElse::accept(Visitor *v)
{
  v->visitCondElse(this);
}

CondElse *CondElse::clone() const
{
  return new CondElse(*this);
}



/********************   While    ********************/
While::While(Expr *p1, Stmt *p2)
{
  expr_ = p1;
  stmt_ = p2;

}

While::While(const While & other)
{
  expr_ = other.expr_->clone();
  stmt_ = other.stmt_->clone();

}

While &While::operator=(const While & other)
{
  While tmp(other);
  swap(tmp);
  return *this;
}

void While::swap(While & other)
{
  std::swap(expr_, other.expr_);
  std::swap(stmt_, other.stmt_);

}

While::~While()
{
  delete(expr_);
  delete(stmt_);

}

void While::accept(Visitor *v)
{
  v->visitWhile(this);
}

While *While::clone() const
{
  return new While(*this);
}



/********************   SExp    ********************/
SExp::SExp(Expr *p1)
{
  expr_ = p1;

}

SExp::SExp(const SExp & other)
{
  expr_ = other.expr_->clone();

}

SExp &SExp::operator=(const SExp & other)
{
  SExp tmp(other);
  swap(tmp);
  return *this;
}

void SExp::swap(SExp & other)
{
  std::swap(expr_, other.expr_);

}

SExp::~SExp()
{
  delete(expr_);

}

void SExp::accept(Visitor *v)
{
  v->visitSExp(this);
}

SExp *SExp::clone() const
{
  return new SExp(*this);
}



/********************   NoInit    ********************/
NoInit::NoInit(Ident p1)
{
  ident_ = p1;

}

NoInit::NoInit(const NoInit & other)
{
  ident_ = other.ident_;

}

NoInit &NoInit::operator=(const NoInit & other)
{
  NoInit tmp(other);
  swap(tmp);
  return *this;
}

void NoInit::swap(NoInit & other)
{
  std::swap(ident_, other.ident_);

}

NoInit::~NoInit()
{

}

void NoInit::accept(Visitor *v)
{
  v->visitNoInit(this);
}

NoInit *NoInit::clone() const
{
  return new NoInit(*this);
}



/********************   Init    ********************/
Init::Init(Ident p1, Expr *p2)
{
  ident_ = p1;
  expr_ = p2;

}

Init::Init(const Init & other)
{
  ident_ = other.ident_;
  expr_ = other.expr_->clone();

}

Init &Init::operator=(const Init & other)
{
  Init tmp(other);
  swap(tmp);
  return *this;
}

void Init::swap(Init & other)
{
  std::swap(ident_, other.ident_);
  std::swap(expr_, other.expr_);

}

Init::~Init()
{
  delete(expr_);

}

void Init::accept(Visitor *v)
{
  v->visitInit(this);
}

Init *Init::clone() const
{
  return new Init(*this);
}



/********************   Int    ********************/
Int::Int()
{

}

Int::Int(const Int & other)
{

}

Int &Int::operator=(const Int & other)
{
  Int tmp(other);
  swap(tmp);
  return *this;
}

void Int::swap(Int & other)
{

}

Int::~Int()
{

}

void Int::accept(Visitor *v)
{
  v->visitInt(this);
}

Int *Int::clone() const
{
  return new Int(*this);
}



/********************   Str    ********************/
Str::Str()
{

}

Str::Str(const Str & other)
{

}

Str &Str::operator=(const Str & other)
{
  Str tmp(other);
  swap(tmp);
  return *this;
}

void Str::swap(Str & other)
{

}

Str::~Str()
{

}

void Str::accept(Visitor *v)
{
  v->visitStr(this);
}

Str *Str::clone() const
{
  return new Str(*this);
}



/********************   Bool    ********************/
Bool::Bool()
{

}

Bool::Bool(const Bool & other)
{

}

Bool &Bool::operator=(const Bool & other)
{
  Bool tmp(other);
  swap(tmp);
  return *this;
}

void Bool::swap(Bool & other)
{

}

Bool::~Bool()
{

}

void Bool::accept(Visitor *v)
{
  v->visitBool(this);
}

Bool *Bool::clone() const
{
  return new Bool(*this);
}



/********************   Void    ********************/
Void::Void()
{

}

Void::Void(const Void & other)
{

}

Void &Void::operator=(const Void & other)
{
  Void tmp(other);
  swap(tmp);
  return *this;
}

void Void::swap(Void & other)
{

}

Void::~Void()
{

}

void Void::accept(Visitor *v)
{
  v->visitVoid(this);
}

Void *Void::clone() const
{
  return new Void(*this);
}



/********************   Fun    ********************/
Fun::Fun(Type *p1, ListType *p2)
{
  type_ = p1;
  listtype_ = p2;

}

Fun::Fun(const Fun & other)
{
  type_ = other.type_->clone();
  listtype_ = other.listtype_->clone();

}

Fun &Fun::operator=(const Fun & other)
{
  Fun tmp(other);
  swap(tmp);
  return *this;
}

void Fun::swap(Fun & other)
{
  std::swap(type_, other.type_);
  std::swap(listtype_, other.listtype_);

}

Fun::~Fun()
{
  delete(type_);
  delete(listtype_);

}

void Fun::accept(Visitor *v)
{
  v->visitFun(this);
}

Fun *Fun::clone() const
{
  return new Fun(*this);
}



/********************   EVar    ********************/
EVar::EVar(Ident p1)
{
  ident_ = p1;

}

EVar::EVar(const EVar & other)
{
  ident_ = other.ident_;

}

EVar &EVar::operator=(const EVar & other)
{
  EVar tmp(other);
  swap(tmp);
  return *this;
}

void EVar::swap(EVar & other)
{
  std::swap(ident_, other.ident_);

}

EVar::~EVar()
{

}

void EVar::accept(Visitor *v)
{
  v->visitEVar(this);
}

EVar *EVar::clone() const
{
  return new EVar(*this);
}



/********************   ELitInt    ********************/
ELitInt::ELitInt(Integer p1)
{
  integer_ = p1;

}

ELitInt::ELitInt(const ELitInt & other)
{
  integer_ = other.integer_;

}

ELitInt &ELitInt::operator=(const ELitInt & other)
{
  ELitInt tmp(other);
  swap(tmp);
  return *this;
}

void ELitInt::swap(ELitInt & other)
{
  std::swap(integer_, other.integer_);

}

ELitInt::~ELitInt()
{

}

void ELitInt::accept(Visitor *v)
{
  v->visitELitInt(this);
}

ELitInt *ELitInt::clone() const
{
  return new ELitInt(*this);
}



/********************   ELitTrue    ********************/
ELitTrue::ELitTrue()
{

}

ELitTrue::ELitTrue(const ELitTrue & other)
{

}

ELitTrue &ELitTrue::operator=(const ELitTrue & other)
{
  ELitTrue tmp(other);
  swap(tmp);
  return *this;
}

void ELitTrue::swap(ELitTrue & other)
{

}

ELitTrue::~ELitTrue()
{

}

void ELitTrue::accept(Visitor *v)
{
  v->visitELitTrue(this);
}

ELitTrue *ELitTrue::clone() const
{
  return new ELitTrue(*this);
}



/********************   ELitFalse    ********************/
ELitFalse::ELitFalse()
{

}

ELitFalse::ELitFalse(const ELitFalse & other)
{

}

ELitFalse &ELitFalse::operator=(const ELitFalse & other)
{
  ELitFalse tmp(other);
  swap(tmp);
  return *this;
}

void ELitFalse::swap(ELitFalse & other)
{

}

ELitFalse::~ELitFalse()
{

}

void ELitFalse::accept(Visitor *v)
{
  v->visitELitFalse(this);
}

ELitFalse *ELitFalse::clone() const
{
  return new ELitFalse(*this);
}



/********************   EApp    ********************/
EApp::EApp(Ident p1, ListExpr *p2)
{
  ident_ = p1;
  listexpr_ = p2;

}

EApp::EApp(const EApp & other)
{
  ident_ = other.ident_;
  listexpr_ = other.listexpr_->clone();

}

EApp &EApp::operator=(const EApp & other)
{
  EApp tmp(other);
  swap(tmp);
  return *this;
}

void EApp::swap(EApp & other)
{
  std::swap(ident_, other.ident_);
  std::swap(listexpr_, other.listexpr_);

}

EApp::~EApp()
{
  delete(listexpr_);

}

void EApp::accept(Visitor *v)
{
  v->visitEApp(this);
}

EApp *EApp::clone() const
{
  return new EApp(*this);
}



/********************   EString    ********************/
EString::EString(String p1)
{
  string_ = p1;

}

EString::EString(const EString & other)
{
  string_ = other.string_;

}

EString &EString::operator=(const EString & other)
{
  EString tmp(other);
  swap(tmp);
  return *this;
}

void EString::swap(EString & other)
{
  std::swap(string_, other.string_);

}

EString::~EString()
{

}

void EString::accept(Visitor *v)
{
  v->visitEString(this);
}

EString *EString::clone() const
{
  return new EString(*this);
}



/********************   Neg    ********************/
Neg::Neg(Expr *p1)
{
  expr_ = p1;

}

Neg::Neg(const Neg & other)
{
  expr_ = other.expr_->clone();

}

Neg &Neg::operator=(const Neg & other)
{
  Neg tmp(other);
  swap(tmp);
  return *this;
}

void Neg::swap(Neg & other)
{
  std::swap(expr_, other.expr_);

}

Neg::~Neg()
{
  delete(expr_);

}

void Neg::accept(Visitor *v)
{
  v->visitNeg(this);
}

Neg *Neg::clone() const
{
  return new Neg(*this);
}



/********************   Not    ********************/
Not::Not(Expr *p1)
{
  expr_ = p1;

}

Not::Not(const Not & other)
{
  expr_ = other.expr_->clone();

}

Not &Not::operator=(const Not & other)
{
  Not tmp(other);
  swap(tmp);
  return *this;
}

void Not::swap(Not & other)
{
  std::swap(expr_, other.expr_);

}

Not::~Not()
{
  delete(expr_);

}

void Not::accept(Visitor *v)
{
  v->visitNot(this);
}

Not *Not::clone() const
{
  return new Not(*this);
}



/********************   EMul    ********************/
EMul::EMul(Expr *p1, MulOp *p2, Expr *p3)
{
  expr_1 = p1;
  mulop_ = p2;
  expr_2 = p3;

}

EMul::EMul(const EMul & other)
{
  expr_1 = other.expr_1->clone();
  mulop_ = other.mulop_->clone();
  expr_2 = other.expr_2->clone();

}

EMul &EMul::operator=(const EMul & other)
{
  EMul tmp(other);
  swap(tmp);
  return *this;
}

void EMul::swap(EMul & other)
{
  std::swap(expr_1, other.expr_1);
  std::swap(mulop_, other.mulop_);
  std::swap(expr_2, other.expr_2);

}

EMul::~EMul()
{
  delete(expr_1);
  delete(mulop_);
  delete(expr_2);

}

void EMul::accept(Visitor *v)
{
  v->visitEMul(this);
}

EMul *EMul::clone() const
{
  return new EMul(*this);
}



/********************   EAdd    ********************/
EAdd::EAdd(Expr *p1, AddOp *p2, Expr *p3)
{
  expr_1 = p1;
  addop_ = p2;
  expr_2 = p3;

}

EAdd::EAdd(const EAdd & other)
{
  expr_1 = other.expr_1->clone();
  addop_ = other.addop_->clone();
  expr_2 = other.expr_2->clone();

}

EAdd &EAdd::operator=(const EAdd & other)
{
  EAdd tmp(other);
  swap(tmp);
  return *this;
}

void EAdd::swap(EAdd & other)
{
  std::swap(expr_1, other.expr_1);
  std::swap(addop_, other.addop_);
  std::swap(expr_2, other.expr_2);

}

EAdd::~EAdd()
{
  delete(expr_1);
  delete(addop_);
  delete(expr_2);

}

void EAdd::accept(Visitor *v)
{
  v->visitEAdd(this);
}

EAdd *EAdd::clone() const
{
  return new EAdd(*this);
}



/********************   ERel    ********************/
ERel::ERel(Expr *p1, RelOp *p2, Expr *p3)
{
  expr_1 = p1;
  relop_ = p2;
  expr_2 = p3;

}

ERel::ERel(const ERel & other)
{
  expr_1 = other.expr_1->clone();
  relop_ = other.relop_->clone();
  expr_2 = other.expr_2->clone();

}

ERel &ERel::operator=(const ERel & other)
{
  ERel tmp(other);
  swap(tmp);
  return *this;
}

void ERel::swap(ERel & other)
{
  std::swap(expr_1, other.expr_1);
  std::swap(relop_, other.relop_);
  std::swap(expr_2, other.expr_2);

}

ERel::~ERel()
{
  delete(expr_1);
  delete(relop_);
  delete(expr_2);

}

void ERel::accept(Visitor *v)
{
  v->visitERel(this);
}

ERel *ERel::clone() const
{
  return new ERel(*this);
}



/********************   EAnd    ********************/
EAnd::EAnd(Expr *p1, Expr *p2)
{
  expr_1 = p1;
  expr_2 = p2;

}

EAnd::EAnd(const EAnd & other)
{
  expr_1 = other.expr_1->clone();
  expr_2 = other.expr_2->clone();

}

EAnd &EAnd::operator=(const EAnd & other)
{
  EAnd tmp(other);
  swap(tmp);
  return *this;
}

void EAnd::swap(EAnd & other)
{
  std::swap(expr_1, other.expr_1);
  std::swap(expr_2, other.expr_2);

}

EAnd::~EAnd()
{
  delete(expr_1);
  delete(expr_2);

}

void EAnd::accept(Visitor *v)
{
  v->visitEAnd(this);
}

EAnd *EAnd::clone() const
{
  return new EAnd(*this);
}



/********************   EOr    ********************/
EOr::EOr(Expr *p1, Expr *p2)
{
  expr_1 = p1;
  expr_2 = p2;

}

EOr::EOr(const EOr & other)
{
  expr_1 = other.expr_1->clone();
  expr_2 = other.expr_2->clone();

}

EOr &EOr::operator=(const EOr & other)
{
  EOr tmp(other);
  swap(tmp);
  return *this;
}

void EOr::swap(EOr & other)
{
  std::swap(expr_1, other.expr_1);
  std::swap(expr_2, other.expr_2);

}

EOr::~EOr()
{
  delete(expr_1);
  delete(expr_2);

}

void EOr::accept(Visitor *v)
{
  v->visitEOr(this);
}

EOr *EOr::clone() const
{
  return new EOr(*this);
}



/********************   Plus    ********************/
Plus::Plus()
{

}

Plus::Plus(const Plus & other)
{

}

Plus &Plus::operator=(const Plus & other)
{
  Plus tmp(other);
  swap(tmp);
  return *this;
}

void Plus::swap(Plus & other)
{

}

Plus::~Plus()
{

}

void Plus::accept(Visitor *v)
{
  v->visitPlus(this);
}

Plus *Plus::clone() const
{
  return new Plus(*this);
}



/********************   Minus    ********************/
Minus::Minus()
{

}

Minus::Minus(const Minus & other)
{

}

Minus &Minus::operator=(const Minus & other)
{
  Minus tmp(other);
  swap(tmp);
  return *this;
}

void Minus::swap(Minus & other)
{

}

Minus::~Minus()
{

}

void Minus::accept(Visitor *v)
{
  v->visitMinus(this);
}

Minus *Minus::clone() const
{
  return new Minus(*this);
}



/********************   Times    ********************/
Times::Times()
{

}

Times::Times(const Times & other)
{

}

Times &Times::operator=(const Times & other)
{
  Times tmp(other);
  swap(tmp);
  return *this;
}

void Times::swap(Times & other)
{

}

Times::~Times()
{

}

void Times::accept(Visitor *v)
{
  v->visitTimes(this);
}

Times *Times::clone() const
{
  return new Times(*this);
}



/********************   Div    ********************/
Div::Div()
{

}

Div::Div(const Div & other)
{

}

Div &Div::operator=(const Div & other)
{
  Div tmp(other);
  swap(tmp);
  return *this;
}

void Div::swap(Div & other)
{

}

Div::~Div()
{

}

void Div::accept(Visitor *v)
{
  v->visitDiv(this);
}

Div *Div::clone() const
{
  return new Div(*this);
}



/********************   Mod    ********************/
Mod::Mod()
{

}

Mod::Mod(const Mod & other)
{

}

Mod &Mod::operator=(const Mod & other)
{
  Mod tmp(other);
  swap(tmp);
  return *this;
}

void Mod::swap(Mod & other)
{

}

Mod::~Mod()
{

}

void Mod::accept(Visitor *v)
{
  v->visitMod(this);
}

Mod *Mod::clone() const
{
  return new Mod(*this);
}



/********************   LTH    ********************/
LTH::LTH()
{

}

LTH::LTH(const LTH & other)
{

}

LTH &LTH::operator=(const LTH & other)
{
  LTH tmp(other);
  swap(tmp);
  return *this;
}

void LTH::swap(LTH & other)
{

}

LTH::~LTH()
{

}

void LTH::accept(Visitor *v)
{
  v->visitLTH(this);
}

LTH *LTH::clone() const
{
  return new LTH(*this);
}



/********************   LE    ********************/
LE::LE()
{

}

LE::LE(const LE & other)
{

}

LE &LE::operator=(const LE & other)
{
  LE tmp(other);
  swap(tmp);
  return *this;
}

void LE::swap(LE & other)
{

}

LE::~LE()
{

}

void LE::accept(Visitor *v)
{
  v->visitLE(this);
}

LE *LE::clone() const
{
  return new LE(*this);
}



/********************   GTH    ********************/
GTH::GTH()
{

}

GTH::GTH(const GTH & other)
{

}

GTH &GTH::operator=(const GTH & other)
{
  GTH tmp(other);
  swap(tmp);
  return *this;
}

void GTH::swap(GTH & other)
{

}

GTH::~GTH()
{

}

void GTH::accept(Visitor *v)
{
  v->visitGTH(this);
}

GTH *GTH::clone() const
{
  return new GTH(*this);
}



/********************   GE    ********************/
GE::GE()
{

}

GE::GE(const GE & other)
{

}

GE &GE::operator=(const GE & other)
{
  GE tmp(other);
  swap(tmp);
  return *this;
}

void GE::swap(GE & other)
{

}

GE::~GE()
{

}

void GE::accept(Visitor *v)
{
  v->visitGE(this);
}

GE *GE::clone() const
{
  return new GE(*this);
}



/********************   EQU    ********************/
EQU::EQU()
{

}

EQU::EQU(const EQU & other)
{

}

EQU &EQU::operator=(const EQU & other)
{
  EQU tmp(other);
  swap(tmp);
  return *this;
}

void EQU::swap(EQU & other)
{

}

EQU::~EQU()
{

}

void EQU::accept(Visitor *v)
{
  v->visitEQU(this);
}

EQU *EQU::clone() const
{
  return new EQU(*this);
}



/********************   NE    ********************/
NE::NE()
{

}

NE::NE(const NE & other)
{

}

NE &NE::operator=(const NE & other)
{
  NE tmp(other);
  swap(tmp);
  return *this;
}

void NE::swap(NE & other)
{

}

NE::~NE()
{

}

void NE::accept(Visitor *v)
{
  v->visitNE(this);
}

NE *NE::clone() const
{
  return new NE(*this);
}




/********************   ListTopDef    ********************/

void ListTopDef::accept(Visitor *v)
{
  v->visitListTopDef(this);
}


ListTopDef *ListTopDef::clone() const
{
  return new ListTopDef(*this);
}


/********************   ListArg    ********************/

void ListArg::accept(Visitor *v)
{
  v->visitListArg(this);
}


ListArg *ListArg::clone() const
{
  return new ListArg(*this);
}


/********************   ListStmt    ********************/

void ListStmt::accept(Visitor *v)
{
  v->visitListStmt(this);
}


ListStmt *ListStmt::clone() const
{
  return new ListStmt(*this);
}


/********************   ListItem    ********************/

void ListItem::accept(Visitor *v)
{
  v->visitListItem(this);
}


ListItem *ListItem::clone() const
{
  return new ListItem(*this);
}


/********************   ListType    ********************/

void ListType::accept(Visitor *v)
{
  v->visitListType(this);
}


ListType *ListType::clone() const
{
  return new ListType(*this);
}


/********************   ListExpr    ********************/

void ListExpr::accept(Visitor *v)
{
  v->visitListExpr(this);
}


ListExpr *ListExpr::clone() const
{
  return new ListExpr(*this);
}



