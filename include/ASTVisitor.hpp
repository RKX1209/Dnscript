#ifndef __AST_VISITOR_HPP__
#define __AST_VISITOR_HPP__

namespace Dnlang {

class ASTVisitor {
public:
  Scope *currentScope;
  ASTVisitor(AST *root) { currentScope = root->scope; }
  void downup(AST *root);
  void enter(AST *t);
  void exit(AST *t);
  void enterBlock(AST *block);
  void exitBlock(AST *block);
  void enterId(AST *id);
  void enterMethod(AST *method);
  void exitMethod(AST *method);
  void exitDecl(AST *decl);
  void exitReturn(AST *ret);
  void exitCall(AST *call);
  void exitExp(AST *exp);
  void enterConst(AST *_const);
  bool isExp(int type);
  bool isConst(int type);
};

}
#endif
