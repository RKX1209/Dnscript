#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <boost/format.hpp>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Symbols.hpp"
#include "Register.hpp"
#include "AST.hpp"
#include "ASTVisitor.hpp"

namespace Dnlang {

void ASTVisitor::downup(AST *root) {
  enter(root);
  for(int i = 0; i < root->children.size(); i++) {
    AST *t = root->children[i];
    downup(t);
  }
  exit(root);
}

void ASTVisitor::enter(AST *t) {
  std::cout<<"[ENTER]"<<t->token<<std::endl;
  if(t->getNodeType() == -1) {
    /* Root */
    enterRoot(t);
  }
  else if(t->getNodeType() == DnLexer::BLOCK) {
    enterBlock(t);
  }
  else if(t->getNodeType() == DnLexer::FUNC_DEF) {
    enterMethod(t);
  }
  else if(t->getNodeType() == DnLexer::ID) {
    enterId(t);
  }
  else if(t->getNodeType() == DnLexer::DECL) {
    enterDecl(t);
  }
  else if(t->getNodeType() == DnLexer::CALL) {
    enterCall(t);
  }
  else if(t->getNodeType() == DnLexer::RETURN) {
    enterReturn(t);
  }
  else if(t->getNodeType() == DnLexer::IF) {
    enterIf(t);
  }
  else if(t->getNodeType() == DnLexer::WHILE) {
    enterWhile(t);
  }
  else if(t->getNodeType() == DnLexer::ASSIGN) {
    enterAssign(t);
  }
  else if(t->getNodeType() == DnLexer::AREF) {
    enterAref(t);
  }
  else if(t->getNodeType() == DnLexer::OROR) {
    enterOror(t);
  }
  else if(t->getNodeType() == DnLexer::ANDAND) {
    enterAndand(t);
  }
  else if(t->getNodeType() == DnLexer::NOT) {
    enterNot(t);
  }
  else if(isRel(t->getNodeType())) {
    enterRel(t);
  }
  else if(isConst(t->getNodeType())) {
    enterConst(t);
  }
  else if(isExp(t->getNodeType())) {
    enterExp(t);
  }
}

void ASTVisitor::exit(AST *t) {
  std::cout<<"[EXIT]"<<t->token<<std::endl;
  if(t->getNodeType() == -1) {
    /* Root */
    exitRoot(t);
  }
  else if(t->getNodeType() == DnLexer::BLOCK) {
    exitBlock(t);
  }
  else if(t->getNodeType() == DnLexer::FUNC_DEF) {
    exitMethod(t);
  }
  else if(t->getNodeType() == DnLexer::ID) {
    exitId(t);
  }
  else if(t->getNodeType() == DnLexer::DECL) {
    exitDecl(t);
  }
  else if(t->getNodeType() == DnLexer::CALL) {
    exitCall(t);
  }
  else if(t->getNodeType() == DnLexer::RETURN) {
    exitReturn(t);
  }
  else if(t->getNodeType() == DnLexer::IF) {
    exitIf(t);
  }
  else if(t->getNodeType() == DnLexer::WHILE) {
    exitWhile(t);
  }
  else if(t->getNodeType() == DnLexer::ASSIGN) {
    exitAssign(t);
  }
  else if(t->getNodeType() == DnLexer::AREF) {
    exitAref(t);
  }
  else if(t->getNodeType() == DnLexer::OROR) {
    exitOror(t);
  }
  else if(t->getNodeType() == DnLexer::ANDAND) {
    exitAndand(t);
  }
  else if(t->getNodeType() == DnLexer::NOT) {
    exitNot(t);
  }
  else if(isRel(t->getNodeType())) {
    exitRel(t);
  }
  else if(isConst(t->getNodeType())) {
    exitConst(t);
  }
  else if(isExp(t->getNodeType())) {
    exitExp(t);
  }
}
void ASTVisitor::enterRoot(AST *root) {}
void ASTVisitor::exitRoot(AST *root) {}
void ASTVisitor::enterBlock(AST *block) {}
void ASTVisitor::exitBlock(AST *block) {}
void ASTVisitor::enterId(AST *id) {}
void ASTVisitor::exitId(AST *id) {}
void ASTVisitor::enterMethod(AST *method) {}
void ASTVisitor::exitMethod(AST *method) {}
void ASTVisitor::enterAssign(AST *assign) {}
void ASTVisitor::exitAssign(AST *assign) {}
void ASTVisitor::enterWhile(AST *loop) {}
void ASTVisitor::exitWhile(AST *loop) {}
void ASTVisitor::enterIf(AST *cond) {}
void ASTVisitor::exitIf(AST *cond) {}
void ASTVisitor::enterOror(AST *oror) {}
void ASTVisitor::exitOror(AST *oror) {}
void ASTVisitor::enterAndand(AST *andand) {}
void ASTVisitor::exitAndand(AST *andand) {}
void ASTVisitor::enterNot(AST *_not) {}
void ASTVisitor::exitNot(AST *_not) {}
void ASTVisitor::enterRel(AST *rel) {}
void ASTVisitor::exitRel(AST *rel) {}
void ASTVisitor::enterDecl(AST *decl) {}
void ASTVisitor::exitDecl(AST *decl) {}
void ASTVisitor::enterReturn(AST *ret) {}
void ASTVisitor::exitReturn(AST *ret) {}
void ASTVisitor::enterAref(AST *aref) {}
void ASTVisitor::exitAref(AST *aref) {}
void ASTVisitor::enterCall(AST *call) {}
void ASTVisitor::exitCall(AST *call) {}
void ASTVisitor::enterExp(AST *exp) {}
void ASTVisitor::exitExp(AST *exp) {}
void ASTVisitor::enterConst(AST *_const) {}
void ASTVisitor::exitConst(AST *_const) {}
bool ASTVisitor::isExp(int type) {
  return DnLexer::OROR <= type && type <= DnLexer::ABOVEEQUAL;
}
bool ASTVisitor::isConst(int type) {
  return DnLexer::INTCONST <= type && type <= DnLexer::STRING;
}
bool ASTVisitor::isAssign(int type) {
  return DnLexer::MULASSIGN <= type && type <= DnLexer::EQUAL;
}
bool ASTVisitor::isRel(int type) {
  return DnLexer::LESSLESS <= type && type <= DnLexer::ABOVEEQUAL;
}
void Semantics::enterBlock(AST *block) {
  currentScope = new LocalScope("LocalScope", currentScope);
}

void Semantics::exitBlock(AST *block) {
  /* If BLOCK is nested, the evalType of this BLOCK is propageted to parent. */
  if(block->parent->getNodeType() == DnLexer::BLOCK)
    block->parent->evalType = block->evalType;
  //std::cout<<"[exitBlock]"<<currentScope->scopeName<<std::endl;
  currentScope = currentScope->getEnclosingScope();
}

void Semantics::enterMethod(AST *method) {
  std::string MethodName = method->children[0]->getNodeText();
  AST *param = method->children[1];
  //std::cout<<"[enterMethod]"<<currentScope->scopeName<<std::endl;
  MethodSymbol *ms = new MethodSymbol(MethodName, currentScope);
  currentScope->define(*ms);
  currentScope = ms;
  for(int i = 0; i < param->children.size(); i++) {
    std::string arg = param->children[i]->getNodeText();
    currentScope->define(Symbol(arg, Type()));
  }
}

void Semantics::exitMethod(AST *method) {
  std::string MethodName = method->children[0]->getNodeText();
  AST *block = method->children[1];
  method->symbol = new Symbol(MethodName, block->evalType);
  currentScope = currentScope->getEnclosingScope();
  //std::cout<<"[exitMethod]"<<currentScope->scopeName<<std::endl;
}

void Semantics::exitDecl(AST *decl) {
  /* Define new symbol */
  AST *id = decl->children[0];
  AST *exp = decl->children[1];
  //std::cout<<"[DEFINE]"<<id->getNodeText()<<","<<exp->evalType.toString()<<std::endl;
  id->symbol = new Symbol(id->getNodeText(), exp->evalType);
  currentScope->define(*id->symbol);
}

void Semantics::exitReturn(AST *ret) {
  if(ret->children.empty()) {
    ret->evalType = Type::VOID;
    return;
  }
  AST *exp = ret->children[0];
  ret->evalType = exp->evalType;
  /* The parent of RETURN node must be always BLOCK. */
  ret->parent->evalType = exp->evalType;
}

void Semantics::exitAref(AST *aref) {
  aref->evalType = aref->children[0]->evalType;
}

void Semantics::exitCall(AST *call) {
  AST *id = call->children[0];
  Symbol *func = currentScope->resolve(id->getNodeText());
  call->evalType = func->type;
}

void Semantics::enterId(AST *id) {
  if(id->parent->getNodeType() == DnLexer::DECL ||
     id->parent->getNodeType() == DnLexer::FUNC_DEF ) return;
  /* Not definition but reference */
  Symbol *sym = currentScope->resolve(id->getNodeText());
  if(!sym) throw (boost::format("%s is not declared") % id->getNodeText()).str();
  id->symbol = sym;
  id->evalType = sym->type;
}

void Semantics::exitExp(AST *exp) {
  /* Are all types of sub-expressions are same? */
  unsigned long long flag = 0LL;
  for(int i = 0; i < exp->children.size(); i++) {
    AST *child = exp->children[i];
    unsigned long long tflag = (1 << child->evalType.type);
    flag |= tflag;
    /* If different type exists, flag has already different tflag. */
    //if(flag & ~tflag) throw (boost::format("[ERROR] type confusion")).str();
  }
  exp->evalType = exp->children[0]->evalType;
}

void Semantics::enterConst(AST *_const) {
  if(_const->getNodeType() == DnLexer::INTCONST) _const->evalType = Type::INT;
  else if(_const->getNodeType() == DnLexer::CHARCONST) _const->evalType = Type::CHAR;
  else if(_const->getNodeType() == DnLexer::FLOATCONST) _const->evalType = Type::FLOAT;
  else if(_const->getNodeType() == DnLexer::STRING) _const->evalType = Type::STRING;
}

void Semantics::exitAssign(AST *assign) {
  assign->children[0]->evalType = assign->children[2]->evalType;
  assign->evalType = assign->children[0]->evalType;
}

CodeGen::CodeGen(AST *root) : ASTVisitor(root), reg_index(1), label_index(0) {
  r0 = new Register("r0");
}

void CodeGen::exitRoot(AST *root) {
  joinCodes(root);
}

void CodeGen::exitBlock(AST *block) {
  joinCodes(block);
  //std::cout<<block->code;
}

void CodeGen::exitId(AST *id) {
  id->reg = new Register(id->getNodeText());
  id->code = "";
}

void CodeGen::exitMethod(AST *method) {
  method->code = method->children[0]->getNodeText() + ":\n";
  joinCodes(method);
}

void CodeGen::exitDecl(AST *decl) {
  AST *left = decl->children[0];
  AST *right = decl->children[1];
  decl->code = left->code + right->code;
  // if (left->getNodeType() == DnLexer::AREF) {
  //   /* 1. array[index] = right */
  //   std::string array_id = left->children[0]->getNodeText();
  //   decl->code += array_id + " [ " + left->getRegId() + " ] " + " = " +
  //                  right->getRegId() + "\n";
  // }
  // else if (right->getNodeType() == DnLexer::AREF) {
  //   /* 2. left = array[index] */
  //   std::string array_id = right->children[1]->getNodeText();
  //   decl->code += left->reg->getId() + " = " + array_id + " [ " + right->reg->getId() + " ] " + "\n";
  // }
  {
    /* 3. left = right */
    decl->code += left->getRegId() + " = " + right->getRegId() + "\n";
  }
}
void CodeGen::exitReturn(AST *ret) {
  if(ret->children.empty()) ret->code = "ret\n";
  else {
    AST *val = ret->children[0];
    ret->code += val->code;
    ret->code += "ret " + val->getRegId() + "\n";
  }
}
void CodeGen::exitAref(AST *aref) {
  /* id [E]   <--->   E * sizeof(id) */
  AST *id = aref->children[0];
  AST *exp = aref->children[1];
  aref->reg = genReg();
  std::stringstream ss;
  ss << exp->code;
  ss << aref->reg->getId() + " = " + exp->reg->getId() + " * "  << "4";//aref->evalType.getSize();
  aref->code = ss.str() + "\n";
  //std::cout<< aref->code << std::endl;
}

void CodeGen::exitCall(AST *call) {
  /* TODO: Now, ids are only allowed for arguments.
           Support nested expression in argument. */
  std::string f_name = call->children[0]->getNodeText();
  for(int i = 1; i < call->children.size(); i++) {
    AST *arg = call->children[i];
    call->code += arg->code;
  }
  for(int i = 1; i < call->children.size(); i++) {
    AST *arg = call->children[i];
    call->code += "param " + arg->getRegId() + "\n";
  }
  call->reg = genReg();
  std::stringstream ss;
  ss << "call " + f_name + " " << call->children.size() - 1 << "\n";
  ss << call->getRegId() << " = " << getRetReg()->getId() << "\n";
  call->code += ss.str();
}

void CodeGen::exitExp(AST *exp) {
  /* XXX: Proceed both expression unary and binary. */
  exp->reg = genReg();
  for(int i = 0; i < exp->children.size(); i++) {
    AST *child = exp->children[i];
    exp->code += child->code;
  }
  if(exp->children.size() <= 1) {//unary expression
    if (exp->getNodeType() == DnLexer::PLUSPLUS) {
      exp->code += exp->children[0]->getRegId() + " = " + exp->children[0]->getRegId() + " + 1\n";
    } else if (exp->getNodeType() == DnLexer::MINUSMINUS) {
      exp->code += exp->children[0]->getRegId() + " = " + exp->children[0]->getRegId() + " - 1\n";
    }
    exp->code += exp->getRegId() + " = " + exp->children[0]->getRegId() + "\n";
  } else {                         // binary expression
    exp->code += exp->getRegId() + " = " + exp->children[0]->getRegId() +
                 " " + exp->getNodeText() + " " + exp->children[1]->getRegId() + "\n";
  }
  //std::cout << "exitExp\n" << exp->code <<std::endl;
}

void CodeGen::exitConst(AST *_const) {
  _const->reg = genReg();
  _const->code = _const->getRegId() + " = " + _const->getNodeText() + "\n";
  //std::cout << "exitConst\n" << _const->code <<std::endl;
}

void CodeGen::exitAssign(AST *assign) {
  AST *left = assign->children[0];
  AST *right = assign->children[2];
  std::string op = assign->children[1]->getNodeText();
  assign->code = left->code + right->code;
  // if (left->getNodeType() == DnLexer::AREF) {
  //   /* 1. array[index] = right */
  //   std::string array_id = left->children[0]->getNodeText();
  //   assign->code += array_id + " [ " + left->reg->getId() + " ] " + " " + op + " " +
  //                  right->reg->getId() + "\n";
  // }
  // else if (right->getNodeType() == DnLexer::AREF) {
  //   /* 2. left = array[index] */
  //   std::string array_id = right->children[0]->getNodeText();
  //   assign->code += left->reg->getId() + " " + op + " " + array_id + " [ " + right->reg->getId() + " ] " + "\n";
  // }
  {
    /* 3. left = right */
    if (op.size() == 2) {
      /* "*=" | "/=" | "%=" | "+=" | "-=" | "&=" | "|=" | "^=" */
      std::string subop = op.substr(0,1);
      assign->code += left->getRegId() + " = " + left->getRegId() + " " + subop + " " + right->getRegId() + "\n";
    } else {
      assign->code += left->getRegId() + " " + op + " " + right->getRegId() + "\n";
    }
  }
}

void CodeGen::enterWhile(AST *loop) {
  //AST *c_s = loop->children[0];
  loop->_begin = genLabel();
  genTfLabel(loop);
}

void CodeGen::exitWhile(AST *loop) {
  AST *c_s = loop->children[0];
  AST *t_s = loop->children[1];
  AST *next = loop->parent->children[loop->child_idx + 1];
  loop->code = loop->_begin->getId() + ":\n" + c_s->code +
               c_s->_true->getId() + ":\n" + t_s->code +
               "goto " + loop->_begin->getId() + "\n" +
               c_s->_false->getId() + ":\n";
  //std::cout << "exitWhile\n" << loop->code <<std::endl;
}

void CodeGen::enterIf(AST *cond) {
  //AST *c_s = cond->children[0];
  genTfLabel(cond);
}

void CodeGen::exitIf(AST *cond) {
  AST *c_s = cond->children[0];
  AST *t_s = cond->children[1];
  AST *next = cond->parent->children[cond->child_idx + 1];
  Label *n_label = genLabel();
  if (cond->children.size() == 3) {
    /* if () {...} else() {...} */
    AST *f_s = cond->children[2];
    t_s->next = f_s->next = n_label;
    cond->code = c_s->code +
                 c_s->_true->getId() + ":\n" + t_s->code +
                 "goto " + n_label->getId() + "\n" +
                 c_s->_false->getId() + ":\n" +
                 n_label->getId() + ":\n";
  } else if (cond->children.size() == 2) {
    /* if () {...} */
    t_s->next = n_label;
    cond->code = c_s->code +
                 c_s->_true->getId() + ":\n" + t_s->code +
                 "goto " + n_label->getId() + "\n" +
                 c_s->_false->getId() + ":\n" +
                 n_label->getId() + ":\n";
  }
}

void CodeGen::enterOror(AST *oror) {
  //genTfLabel(oror);
  oror->_true = oror->parent->_true;
  oror->_false = oror->parent->_false;
}

void CodeGen::exitOror(AST *oror) {
  AST *left = oror->children[0];
  AST *right = oror->children[1];
  left->_true = genLabel();
  right->_true = oror->_true;
  right->_false = oror->_false;
  oror->code = left->code  +
               left->_false->getId() + ":\n" +
               right->code;
}

void CodeGen::enterAndand(AST *andand) {
  //genTfLabel(andand);
  andand->_true = andand->parent->_true;
  andand->_false = andand->parent->_false;
}

void CodeGen::exitAndand(AST *andand) {
  AST *left = andand->children[0];
  AST *right = andand->children[1];
  left->_true = genLabel();
  left->_false = andand->_false;
  right->_true = andand->_true;
  right->_false = andand->_false;
  andand->code = left->code +
                 left->_true->getId() + ":\n" +
                 right->code;
}

void CodeGen::enterNot(AST *_not) {
  //genTfLabel(_not);
  _not->_true = _not->parent->_true;
  _not->_false = _not->parent->_false;

}

void CodeGen::exitNot(AST *_not) {
  AST *stat = _not->children[0];
  stat->_true = _not->_false;
  stat->_false = _not->_true;
  _not->code = stat->code;
}

void CodeGen::enterRel(AST *rel) {
  /* XXX: When enter a relation node, new label should be created only if
          its parent isn't while nor if.
          Because while and if statements have already created new labels when it's entered. */
  // if (rel->parent->getNodeType() != DnLexer::WHILE && rel->parent->getNodeType() != DnLexer::IF) {
  //   genTfLabel(rel);
  // }
  rel->_true = rel->parent->_true;
  rel->_false = rel->parent->_false;
}

void CodeGen::exitRel(AST *rel) {
  AST *left = rel->children[0];
  AST *right = rel->children[1];
  rel->code = left->code +
              right->code +
              "if " + left->getRegId() + " " + rel->getNodeText() + " " + right->getRegId() + " " +
              "goto " + rel->_true->getId() + "\n" +
              "goto " + rel->_false->getId() + "\n";
}

void CodeGen::genTfLabel(AST *tf) {
  tf->_true = genLabel();
  tf->_false = genLabel();
}

void CodeGen::joinCodes(AST *parent) {
  for(int i = 0; i < parent->children.size(); i++) {
    AST *child = parent->children[i];
    parent->code += child->code;
  }
}

Register *CodeGen::genReg() {
  std::stringstream reg_id;
  reg_id << "r" << reg_index;
  reg_index++;
  return new Register(reg_id.str());
}

Label *CodeGen::genLabel() {
  std::stringstream label_id;
  label_id << "label" << label_index;
  label_index++;
  return new Label(label_id.str());
}

}
