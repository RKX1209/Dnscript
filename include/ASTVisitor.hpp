#ifndef __AST_VISITOR_HPP__
#define __AST_VISITOR_HPP__

#include "Register.hpp"

namespace Dnlang {

class ASTVisitor {
public:
  Scope *currentScope;
  ASTVisitor(AST *root) { currentScope = root->scope; }
  void downup(AST *root);
  void enter(AST *t);
  void exit(AST *t);
  bool isExp(int type);
  bool isConst(int type);

  // = += /= ...
  bool isAssign(int type);

  // Relation == != <= >= < > ...
  bool isRel(int type);

  // ROOT
  virtual void enterRoot(AST *root);
  virtual void exitRoot(AST *root);

  // DECL
  virtual void enterDecl(AST *decl);
  virtual void exitDecl(AST *decl);

  // BLOCK
  virtual void enterBlock(AST *block);
  virtual void exitBlock(AST *block);

  // FUNC_DEF
  virtual void enterMethod(AST *method);
  virtual void exitMethod(AST *method);

  // RETURN
  virtual void enterReturn(AST *ret);
  virtual void exitReturn(AST *ret);

  // AREF
  virtual void enterAref(AST *aref);
  virtual void exitAref(AST *aref);

  // CALL
  virtual void enterCall(AST *call);
  virtual void exitCall(AST *call);

  // ASSIGN
  virtual void enterAssign(AST *assign);
  virtual void exitAssign(AST *assign);

  // WHILE
  virtual void enterWhile(AST *loop);
  virtual void exitWhile(AST *loop);

  // IF
  virtual void enterIf(AST *cond);
  virtual void exitIf(AST *cond);

  // OROR(||)
  virtual void enterOror(AST *oror);
  virtual void exitOror(AST *oror);

  // ANDAND(&&)
  virtual void enterAndand(AST *andand);
  virtual void exitAndand(AST *andand);

  // NOT(!)
  virtual void enterNot(AST *_not);
  virtual void exitNot(AST *_not);

  //Relations
  virtual void enterRel(AST *rel);
  virtual void exitRel(AST *rel);

  virtual void enterId(AST *id);
  virtual void exitId(AST *id);

  virtual void enterExp(AST *exp);
  virtual void exitExp(AST *exp);

  virtual void enterConst(AST *_const);
  virtual void exitConst(AST *_const);

};

class Semantics : public ASTVisitor {
public:
  Semantics(AST *root) : ASTVisitor(root) {}
  void enterBlock(AST *block);
  void exitBlock(AST *block);
  void enterId(AST *id);
  void enterMethod(AST *method);
  void exitMethod(AST *method);
  void exitDecl(AST *decl);
  void exitReturn(AST *ret);
  void exitAref(AST *aref);
  void exitCall(AST *call);
  void exitExp(AST *exp);
  void enterConst(AST *_const);
  void exitAssign(AST *assign);
};

class CodeGen : public ASTVisitor {
public:
  int reg_index;
  int label_index;
  CodeGen(AST *root) : ASTVisitor(root), reg_index(0), label_index(0) {}
  Register* genReg();
  Label *genLabel();
  void exitRoot(AST *root);
  void exitBlock(AST *block);
  void exitId(AST *id);
  void exitMethod(AST *method);
  void exitDecl(AST *decl);
  void exitReturn(AST *ret);
  void exitAref(AST *aref);
  void exitCall(AST *call);
  void exitExp(AST *exp);
  void exitConst(AST *_const);
  void exitAssign(AST *assign);
  void enterWhile(AST *loop);
  void exitWhile(AST *loop);
  void enterIf(AST *cond);
  void exitIf(AST *cond);
  void enterOror(AST *oror);
  void exitOror(AST *oror);
  void enterAndand(AST *andand);
  void exitAndand(AST *andand);
  void enterNot(AST *_not);
  void exitNot(AST *_not);
  void enterRel(AST *rel);
  void exitRel(AST *rel);
  void joinCodes(AST *parent);
  void genTfLabel(AST *tf);
};

}
#endif
