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
#include "AST.hpp"
#include "ASTVisitor.hpp"

namespace Dnlang {

void ASTVisitor::downup(AST *root) {
  for(int i = 0; i < root->children.size(); i++) {
    AST *t = root->children[i];
    enter(t);
    downup(t);
    exit(t);
  }
}

void ASTVisitor::enter(AST *t) {
  std::cout<<"[ENTER]"<<t->token<<std::endl;
  if(t->getNodeType() == DnLexer::BLOCK) {
    enterBlock(t);
  }
  else if(t->getNodeType() == DnLexer::FUNC_DEF) {
    enterMethod(t);
  }
  else if(t->getNodeType() == DnLexer::ID) {
    enterId(t);
  }
  else if(isConst(t->getNodeType())) {
    enterConst(t);
  }
}

void ASTVisitor::exit(AST *t) {
  std::cout<<"[EXIT]"<<t->token<<std::endl;
  if(t->getNodeType() == DnLexer::BLOCK) {
    exitBlock(t);
  }
  else if(t->getNodeType() == DnLexer::FUNC_DEF) {
    exitMethod(t);
  }
  else if(t->getNodeType() == DnLexer::DECL) {
    exitDecl(t);
  }
  else if(t->getNodeType() == DnLexer::RETURN) {
    exitReturn(t);
  }
  else if(t->getNodeType() == DnLexer::CALL) {
    exitCall(t);
  }
  else if(isExp(t->getNodeType())) {
    exitExp(t);
  }
}

void ASTVisitor::enterBlock(AST *block) {
  currentScope = new LocalScope("LocalScope", currentScope);
}

void ASTVisitor::exitBlock(AST *block) {
  /* If BLOCK is nested, the evalType of this BLOCK is propageted to parent. */
  if(block->parent->getNodeType() == DnLexer::BLOCK)
    block->parent->evalType = block->evalType;
  std::cout<<"[exitBlock]"<<currentScope->scopeName<<std::endl;
  currentScope = currentScope->getEnclosingScope();
}

void ASTVisitor::enterMethod(AST *method) {
  std::string MethodName = method->children[0]->getNodeText();
  std::cout<<"[enterMethod]"<<currentScope->scopeName<<std::endl;
  MethodSymbol *ms = new MethodSymbol(MethodName, currentScope);
  currentScope->define(*ms);
  currentScope = ms;
  std::cout<<"[enterMethod]"<<currentScope->scopeName<<std::endl;
}

void ASTVisitor::exitMethod(AST *method) {
  std::string MethodName = method->children[0]->getNodeText();
  AST *block = method->children[1];
  method->symbol = new Symbol(MethodName, block->evalType);
  std::cout<<"[exitMethod]"<<currentScope->scopeName<<std::endl;
  currentScope = currentScope->getEnclosingScope();
  std::cout<<"[exitMethod]"<<currentScope->scopeName<<std::endl;
}

void ASTVisitor::exitDecl(AST *decl) {
  /* Define new symbol */
  AST *id = decl->children[0];
  AST *exp = decl->children[1];
  std::cout<<"[DEFINE]"<<id->getNodeText()<<","<<exp->evalType.toString()<<std::endl;
  id->symbol = new Symbol(id->getNodeText(), exp->evalType);
  currentScope->define(*id->symbol);
}

void ASTVisitor::exitReturn(AST *ret) {
  if(ret->children.empty()) {
    ret->evalType = Type::VOID;
    return;
  }
  AST *exp = ret->children[0];
  ret->evalType = exp->evalType;
  /* The parent of RETURN node must be always BLOCK. */
  ret->parent->evalType = exp->evalType;
}

void ASTVisitor::exitCall(AST *call) {
  AST *id = call->children[0];
  Symbol *func = currentScope->resolve(id->getNodeText());
  call->evalType = func->type;
}

void ASTVisitor::enterId(AST *id) {
  if(id->parent->getNodeType() == DnLexer::DECL ||
     id->parent->getNodeType() == DnLexer::FUNC_DEF ) return;
  /* Not definition but reference */
  Symbol *sym = currentScope->resolve(id->getNodeText());
  if(!sym) throw (boost::format("%s is not declared") % id->getNodeText()).str();
  id->symbol = sym;
  id->evalType = sym->type;
}

void ASTVisitor::exitExp(AST *exp) {
  /* Are all types of sub-expressions are same? */
  unsigned long long flag = 0LL;
  for(int i = 0; i < exp->children.size(); i++) {
    AST *child = exp->children[i];
    unsigned long long tflag = (1 << child->evalType.type);
    flag |= tflag;
    /* If different type exists, flag has already different tflag. */
    if(flag & ~tflag) throw (boost::format("[ERROR] type confusion")).str();
  }
  exp->evalType = exp->children[0]->evalType;
}

void ASTVisitor::enterConst(AST *_const) {
  if(_const->getNodeType() == DnLexer::INTCONST) _const->evalType = Type::INT;
  else if(_const->getNodeType() == DnLexer::CHARCONST) _const->evalType = Type::CHAR;
  else if(_const->getNodeType() == DnLexer::FLOATCONST) _const->evalType = Type::FLOAT;
  else if(_const->getNodeType() == DnLexer::STRING) _const->evalType = Type::STRING;
}

bool ASTVisitor::isExp(int type) {
  return DnLexer::OROR <= type && type <= DnLexer::ABOVEEQUAL;
}
bool ASTVisitor::isConst(int type) {
  return DnLexer::INTCONST <= type && type <= DnLexer::STRING;
}

}
