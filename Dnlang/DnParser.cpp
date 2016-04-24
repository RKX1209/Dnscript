#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Register.hpp"
#include "AST.hpp"
#include "Parser.hpp"
#include "DnParser.hpp"


#define SPECULATE(x) \
[this]() { \
  bool success = true; \
  mark(); \
  try { x } \
  catch (std::string &str) { success = false; } \
  release(); \
  return success; \
}
#define DEFINE_MEMO(x, fp) \
  bool failed = false; \
  int startTokenIndex = index(); \
  if(isSpeculating() && alreadyParsedRule(#x)) return; \
  try { _##fp } \
  catch(std::string &s) { \
    failed = true; \
    if(isSpeculating()) memorize(#x, startTokenIndex, failed); \
    throw s; \
  } \
  if(isSpeculating()) memorize(#x, startTokenIndex, failed); \

#define ADD_TOKEN(type, str) \
  if(!isSpeculating()) { \
    AST *child= new AST(Token(type, str)); \
    ast_root->addChild(ast_root, child); \
  } \

#define ADD_ROOT_CHROOT(root) \
  if(!isSpeculating()) { \
    AST *child = new AST(root); \
    ast_root = ast_root->addChild(ast_root, child); \
  } \

#define ADD_TOKEN_CHROOT(type, str) \
  if(!isSpeculating()) { \
    AST *child = new AST(Token(type, str)); \
    ast_root = ast_root->addChild(ast_root, child); \
  } \

#define BREAK_UP \
  if(!isSpeculating()) { \
    ast_root = ast_root->parent; \
  } \

namespace Dnlang {
  /* type inference
     XXX bit ugly. Is there any better solution? */
void DnParser::_TranslationUnit() {
  if(SPECULATE( ExternalDecl(); TranslationUnit(); match(DnLexer::EOF_TYPE); )()) {
    ExternalDecl(); TranslationUnit(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ExternalDecl(); match(DnLexer::EOF_TYPE); )()) {
    ExternalDecl(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ExternalDecl() {
  if(SPECULATE( FunctionDef(); )()) {
    FunctionDef();
  }
  else if(SPECULATE( Decl(); )()) {
    Decl();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_FunctionDef() {
  if(SPECULATE( DeclSpecs(); Declarator(); CompoundStat(); )()) {
    ADD_ROOT_CHROOT(DnLexer::FUNC_DEF)
    DeclSpecs(); Declarator(); CompoundStat();
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Decl() {
  if(SPECULATE( DeclSpecs(); InitDecl(); match(DnLexer::SEMICORON); )()) {
    ADD_ROOT_CHROOT(DnLexer::DECL)
    DeclSpecs();
    InitDecl();
    match(DnLexer::SEMICORON);
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_DeclList() {
  if(SPECULATE( Decl(); DeclList(); )()) {
    Decl(); DeclList();
  }
  else if(SPECULATE( Decl(); )()) {
    Decl();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_DeclSpecs() {
  if(SPECULATE( FuncSpec(); )()) {
    FuncSpec();
  }
  else if(SPECULATE( TypeSpec(); )()) {
    TypeSpec();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_FuncSpec() {
  if(SPECULATE( match(DnLexer::FUNCTION); )()) {
    match(DnLexer::FUNCTION);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_TypeSpec() {
  if(SPECULATE( match(DnLexer::LET); )()) {
    match(DnLexer::LET);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_InitDeclList() {
  if(SPECULATE( InitDecl(); match(DnLexer::COMMA); InitDeclList(); )()) {
    InitDecl(); match(DnLexer::COMMA); InitDeclList();
  }
  else if(SPECULATE( InitDecl();  )()) {
    InitDecl();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_InitDecl() {
  if(SPECULATE( Declarator(); match(DnLexer::EQUAL); Initializer(); )()) {
    Declarator(); match(DnLexer::EQUAL); Initializer();
  }
  else if(SPECULATE( Declarator();  )()) {
    Declarator();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Declarator() {
  if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text)
    match(DnLexer::ID);
    ADD_ROOT_CHROOT(DnLexer::PARAM)
    match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text)
    match(DnLexer::ID);
    ADD_ROOT_CHROOT(DnLexer::PARAM)
    match(DnLexer::LBRACKA); match(DnLexer::RBRACKA);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACK); match(DnLexer::INTCONST); match(DnLexer::RBRACK); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text)
    match(DnLexer::ID);
    /* TODO: Implement declaration of array */
  }
  else if(SPECULATE( match(DnLexer::ID); )()) {
      ADD_TOKEN(DnLexer::ID, LT(1).text)
      match(DnLexer::ID);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_IdList() {
  if(SPECULATE( match(DnLexer::ID); match(DnLexer::COMMA); IdList(); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text)
    match(DnLexer::ID);
    match(DnLexer::COMMA); IdList();
  }
  else if(SPECULATE( match(DnLexer::ID); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text)
    match(DnLexer::ID);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Initializer() {
  if(SPECULATE( AssignExp(); )()) {
    AssignExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Stat() {
  if(SPECULATE( ExpStat(); )()) {
    ExpStat();
  }
  else if(SPECULATE( CompoundStat(); )()) {
    CompoundStat();
  }
  else if(SPECULATE( SelectionStat(); )()) {
    SelectionStat();
  }
  else if(SPECULATE( IterationStat(); )()) {
    IterationStat();
  }
  else if(SPECULATE( JumpStat(); )()) {
    JumpStat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ExpStat() {
  if(SPECULATE( Exp(); match(DnLexer::SEMICORON); )()) {
    Exp(); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::SEMICORON); )()) {
    match(DnLexer::SEMICORON);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_CompoundStat() {
  if(SPECULATE( match(DnLexer::LBRACKB); match(DnLexer::RBRACKB); )()) {
    ADD_ROOT_CHROOT(DnLexer::BLOCK)
    match(DnLexer::LBRACKB); match(DnLexer::RBRACKB);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB); )()) {
    ADD_ROOT_CHROOT(DnLexer::BLOCK)
    match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB); )()) {
    ADD_ROOT_CHROOT(DnLexer::BLOCK)
    match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB); )()) {
    ADD_ROOT_CHROOT(DnLexer::BLOCK)
    match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB);
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_StatList() {
  if(SPECULATE( Stat(); StatList(); )()) {
    Stat(); StatList();
  }
  else if(SPECULATE( Stat(); )()) {
    Stat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_SelectionStat() {
  if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); match(DnLexer::ELSE); Stat(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::IF, "IF")
    match(DnLexer::IF);
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
    match(DnLexer::ELSE); Stat();
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::IF, "IF")
    match(DnLexer::IF);
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_IterationStat() {
  if(SPECULATE( match(DnLexer::WHILE); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::WHILE, "WHILE")
    match(DnLexer::WHILE);
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::FOR); match(DnLexer::LBRACKA); Exp(); match(DnLexer::SEMICORON); Exp(); match(DnLexer::SEMICORON); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::FOR, "FOR")
    match(DnLexer::FOR);
    match(DnLexer::LBRACKA);
    Exp(); match(DnLexer::SEMICORON);
    Exp(); match(DnLexer::SEMICORON);
    Exp();
    match(DnLexer::RBRACKA); Stat();
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }

}
void DnParser::_JumpStat() {
  if(SPECULATE( match(DnLexer::CONTINUE); match(DnLexer::SEMICORON); )()) {
    ADD_TOKEN(DnLexer::CONTINUE, "CONTINUE")
    match(DnLexer::CONTINUE);
    match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::BREAK); match(DnLexer::SEMICORON); )()) {
    ADD_TOKEN(DnLexer::BREAK, "BREAK")
    match(DnLexer::BREAK);
    match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::RETURN); Exp(); match(DnLexer::SEMICORON); )()) {
    ADD_TOKEN_CHROOT(DnLexer::RETURN, "RETURN")
    match(DnLexer::RETURN);
    Exp(); match(DnLexer::SEMICORON);
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::RETURN); match(DnLexer::SEMICORON); )()) {
    ADD_TOKEN(DnLexer::RETURN, "RETURN")
    match(DnLexer::RETURN);
    match(DnLexer::SEMICORON);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Exp() {
  if(SPECULATE( AssignExp(); match(DnLexer::COMMA); Exp(); )()) {
    AssignExp(); match(DnLexer::COMMA); Exp();
  }
  else if(SPECULATE( AssignExp(); )()) {
    AssignExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_AssignExp() {
  if(SPECULATE( UnaryExp(); AssignOperator(); AssignExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::ASSIGN, "ASSIGN");
    UnaryExp(); AssignOperator(); AssignExp();
    BREAK_UP
  }
  else if(SPECULATE( ConditionalExp(); )()) {
    ConditionalExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_AssignOperator() {
  if(SPECULATE( match(DnLexer::EQUAL); )()) {
    ADD_TOKEN(DnLexer::EQUAL, "=")
    match(DnLexer::EQUAL);
  }
  else if(SPECULATE( match(DnLexer::MULASSIGN); )()) {
    ADD_TOKEN(DnLexer::MULASSIGN, "*=")
    match(DnLexer::MULASSIGN);
  }
  else if(SPECULATE( match(DnLexer::DIVASSIGN); )()) {
    ADD_TOKEN(DnLexer::DIVASSIGN, "/=")
    match(DnLexer::DIVASSIGN);
  }
  else if(SPECULATE( match(DnLexer::MODASSIGN); )()) {
    ADD_TOKEN(DnLexer::MODASSIGN, "%=")
    match(DnLexer::MODASSIGN);
  }
  else if(SPECULATE( match(DnLexer::PLUSASSIGN); )()) {
    ADD_TOKEN(DnLexer::PLUSASSIGN, "+=")
    match(DnLexer::PLUSASSIGN);
  }
  else if(SPECULATE( match(DnLexer::MINUSASSIGN); )()) {
    ADD_TOKEN(DnLexer::MINUSASSIGN, "-=")
    match(DnLexer::MINUSASSIGN);
  }
  else if(SPECULATE( match(DnLexer::ANDASSIGN); )()) {
    ADD_TOKEN(DnLexer::ANDASSIGN, "&=")
    match(DnLexer::ANDASSIGN);
  }
  else if(SPECULATE( match(DnLexer::ORASSIGN); )()) {
    match(DnLexer::ORASSIGN);
    ADD_TOKEN(DnLexer::ORASSIGN, "|=")
  }
  else if(SPECULATE( match(DnLexer::XORASSIGN); )()) {
    match(DnLexer::XORASSIGN);
    ADD_TOKEN(DnLexer::XORASSIGN, "^=")
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ConditionalExp() {
  if(SPECULATE( LogicalOrExp(); )()) {
    LogicalOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_LogicalOrExp() {
  if(SPECULATE( LogicalAndExp(); )()) {
    LogicalAndExp();
  }
  else if(SPECULATE( LogicalAndExp(); match(DnLexer::OROR); LogicalOrExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::OROR, "||")
    LogicalAndExp(); match(DnLexer::OROR); LogicalOrExp();
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_LogicalAndExp() {
  if(SPECULATE( InclusiveOrExp(); match(DnLexer::ANDAND); LogicalAndExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::ANDAND, "&&")
    InclusiveOrExp(); match(DnLexer::ANDAND); LogicalAndExp();
    BREAK_UP
  }
  else if(SPECULATE( InclusiveOrExp(); )()) {
    InclusiveOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_InclusiveOrExp() {
  if(SPECULATE( ExclusiveOrExp(); match(DnLexer::OR); InclusiveOrExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::OR, "|")
    ExclusiveOrExp(); match(DnLexer::OR); InclusiveOrExp();
    BREAK_UP
  }
  else if(SPECULATE( ExclusiveOrExp(); )()) {
    ExclusiveOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ExclusiveOrExp() {
  if(SPECULATE( AndExp(); match(DnLexer::XOR); ExclusiveOrExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::XOR, "^")
    AndExp(); match(DnLexer::XOR); ExclusiveOrExp();
    BREAK_UP
  }
  else if(SPECULATE( AndExp(); )()) {
    AndExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }

}
void DnParser::_AndExp() {
  if(SPECULATE( EqualityExp(); match(DnLexer::AND); AndExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::AND, "&")
    EqualityExp(); match(DnLexer::AND); AndExp();
    BREAK_UP
  }
  else if(SPECULATE( EqualityExp(); )()) {
    EqualityExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_EqualityExp() {
  if(SPECULATE( RelationalExp(); match(DnLexer::EQUALEQUAL); EqualityExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::EQUALEQUAL, "==")
    RelationalExp(); match(DnLexer::EQUALEQUAL); EqualityExp();
    BREAK_UP
  }
  else if(SPECULATE( RelationalExp(); match(DnLexer::NOTEQUAL); EqualityExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::NOTEQUAL, "!=")
    RelationalExp(); match(DnLexer::NOTEQUAL); EqualityExp();
    BREAK_UP
  }
  else if(SPECULATE( RelationalExp(); )()) {
    RelationalExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_RelationalExp() {
  if(SPECULATE( ShiftExp(); match(DnLexer::LESS); RelationalExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::LESS, "<")
    ShiftExp(); match(DnLexer::LESS); RelationalExp();
    BREAK_UP
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVE); RelationalExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::ABOVE, ">")
    ShiftExp(); match(DnLexer::ABOVE); RelationalExp();
    BREAK_UP
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::LESSEQUAL, "<=")
    ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp();
    BREAK_UP
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::ABOVEEQUAL, ">=")
    ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp();
    BREAK_UP
  }
  else if(SPECULATE( ShiftExp(); )()) {
    ShiftExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ShiftExp() {
  if(SPECULATE( AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::LESSLESS, "<<")
    AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp();
    BREAK_UP
  }
  else if(SPECULATE( AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::ABOVEABOVE, ">>")
    AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp();
    BREAK_UP
  }
  else if(SPECULATE( AdditiveExp(); )()) {
    AdditiveExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_AdditiveExp() {
  if(SPECULATE( MultExp(); match(DnLexer::PLUS); AdditiveExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::PLUS, "+")
    MultExp(); match(DnLexer::PLUS); AdditiveExp();
    BREAK_UP
  }
  else if(SPECULATE( MultExp(); match(DnLexer::MINUS); AdditiveExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::MINUS, "-")
    MultExp(); match(DnLexer::MINUS); AdditiveExp();
    BREAK_UP
  }
  else if(SPECULATE( MultExp(); )()) {
    MultExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_MultExp() {
  if(SPECULATE( UnaryExp(); match(DnLexer::MUL); MultExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::MUL, "*")
    UnaryExp(); match(DnLexer::MUL); MultExp();
    BREAK_UP
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::DIV); MultExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::DIV, "/")
    UnaryExp(); match(DnLexer::DIV); MultExp();
    BREAK_UP
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::MOD); MultExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::MOD, "%")
    UnaryExp(); match(DnLexer::MOD); MultExp();
    BREAK_UP
  }
  else if(SPECULATE( UnaryExp(); )()) {
    UnaryExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_UnaryExp() {
  if(SPECULATE( PostfixExp(); )()) {
    PostfixExp();
  }
  else if(SPECULATE( match(DnLexer::PLUSPLUS); UnaryExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::PLUSPLUS, "++")
    match(DnLexer::PLUSPLUS); UnaryExp();
    BREAK_UP
  }
  else if(SPECULATE( match(DnLexer::MINUSMINUS); UnaryExp(); )()) {
    ADD_TOKEN_CHROOT(DnLexer::MINUSMINUS, "--")
    match(DnLexer::MINUSMINUS); UnaryExp();
    BREAK_UP
  }
  else if(SPECULATE( UnaryOperator(); UnaryExp(); )()) {
    UnaryOperator(); UnaryExp();
    BREAK_UP
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_UnaryOperator() {
  if(SPECULATE( match(DnLexer::PLUS); )()) {
    ADD_TOKEN_CHROOT(DnLexer::PLUS, "+")
    match(DnLexer::PLUS);
  }
  else if(SPECULATE( match(DnLexer::MINUS); )()) {
    ADD_TOKEN_CHROOT(DnLexer::MINUS, "-")
    match(DnLexer::MINUS);
  }
  else if(SPECULATE( match(DnLexer::NOT); )()) {
    ADD_TOKEN_CHROOT(DnLexer::NOT, "!")
    match(DnLexer::NOT);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_PostfixExp() {
  if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK); )()) {
    ADD_ROOT_CHROOT(DnLexer::AREF)
    PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK);
    BREAK_UP
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA); )()) {
    ADD_ROOT_CHROOT(DnLexer::CALL)
    PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA);
    BREAK_UP
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); )()) {
    ADD_ROOT_CHROOT(DnLexer::CALL)
    PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA);
    BREAK_UP
  }
  else if(SPECULATE( PrimaryExp(); )()) {
    PrimaryExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }

}
void DnParser::_PrimaryExp() {
  if(SPECULATE( match(DnLexer::ID); )()) {
    ADD_TOKEN(DnLexer::ID, LT(1).text);
    match(DnLexer::ID);
  }
  else if(SPECULATE( Const(); )()) {
    Const();
  }
  else if(SPECULATE( match(DnLexer::STRING); )()) {
    ADD_TOKEN(DnLexer::STRING, LT(1).text);
    match(DnLexer::STRING);
  }
  else if(SPECULATE( match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_ArgumentExpList() {
  if(SPECULATE( AssignExp(); match(DnLexer::COMMA); ArgumentExpList(); )()) {
    AssignExp(); match(DnLexer::COMMA); ArgumentExpList();
  }
  else if(SPECULATE( AssignExp(); )()) {
    AssignExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::_Const() {
  if(SPECULATE( match(DnLexer::INTCONST); )()) {
    ADD_TOKEN(DnLexer::INTCONST, LT(1).text);
    match(DnLexer::INTCONST);
  }
  else if(SPECULATE( match(DnLexer::CHARCONST); )()) {
    ADD_TOKEN(DnLexer::CHARCONST, LT(1).text);
    match(DnLexer::CHARCONST);
  }
  else if(SPECULATE( match(DnLexer::FLOATCONST); )()) {
    ADD_TOKEN(DnLexer::FLOATCONST, LT(1).text);
    match(DnLexer::FLOATCONST);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}
void DnParser::TranslationUnit() { DEFINE_MEMO(TranslationUnit,TranslationUnit();) }
void DnParser::ExternalDecl() { DEFINE_MEMO(ExternalDecl,ExternalDecl();) }
void DnParser::FunctionDef() { DEFINE_MEMO(FunctionDef,FunctionDef();) }
void DnParser::Decl() { DEFINE_MEMO(Decl,Decl();) }
void DnParser::DeclList() { DEFINE_MEMO(DeclList,DeclList();) }
void DnParser::DeclSpecs() { DEFINE_MEMO(DeclSpecs,DeclSpecs();) }
void DnParser::FuncSpec() { DEFINE_MEMO(FuncSpec,FuncSpec();) }
void DnParser::TypeSpec() { DEFINE_MEMO(TypeSpec,TypeSpec();) }
void DnParser::InitDeclList() { DEFINE_MEMO(InitDeclList,InitDeclList();) }
void DnParser::InitDecl() { DEFINE_MEMO(InitDecl,InitDecl();) }
void DnParser::Declarator() { DEFINE_MEMO(Declarator,Declarator();) }
void DnParser::IdList() { DEFINE_MEMO(IdList,IdList();) }
void DnParser::Initializer() { DEFINE_MEMO(Initializer,Initializer();) }
void DnParser::Stat() { DEFINE_MEMO(Stat,Stat();) }
void DnParser::ExpStat() { DEFINE_MEMO(ExpStat,ExpStat();) }
void DnParser::CompoundStat() { DEFINE_MEMO(CompoundStat,CompoundStat();) }
void DnParser::StatList() { DEFINE_MEMO(StatList,StatList();) }
void DnParser::SelectionStat() { DEFINE_MEMO(SelectionStat,SelectionStat();) }
void DnParser::IterationStat() { DEFINE_MEMO(IterationStat,IterationStat();) }
void DnParser::JumpStat() { DEFINE_MEMO(JumpStat,JumpStat();) }
void DnParser::Exp() { DEFINE_MEMO(Exp,Exp();) }
void DnParser::AssignExp() { DEFINE_MEMO(AssignExp,AssignExp();) }
void DnParser::AssignOperator() { DEFINE_MEMO(AssignOperator,AssignOperator();) }
void DnParser::ConditionalExp() { DEFINE_MEMO(ConditionalExp,ConditionalExp();) }
void DnParser::LogicalOrExp() { DEFINE_MEMO(LogicalOrExp,LogicalOrExp();) }
void DnParser::LogicalAndExp() { DEFINE_MEMO(LogicalAndExp,LogicalAndExp();) }
void DnParser::InclusiveOrExp() { DEFINE_MEMO(InclusiveOrExp,InclusiveOrExp();) }
void DnParser::ExclusiveOrExp() { DEFINE_MEMO(ExclusiveOrExp,ExclusiveOrExp();) }
void DnParser::AndExp() { DEFINE_MEMO(AndExp,AndExp();) }
void DnParser::EqualityExp() { DEFINE_MEMO(EqualityExp,EqualityExp();) }
void DnParser::RelationalExp() { DEFINE_MEMO(RelationalExp,RelationalExp();) }
void DnParser::ShiftExp() { DEFINE_MEMO(ShiftExp,ShiftExp();) }
void DnParser::AdditiveExp() { DEFINE_MEMO(AdditiveExp,AdditiveExp();) }
void DnParser::MultExp() { DEFINE_MEMO(MultExp,MultExp();) }
void DnParser::UnaryExp() { DEFINE_MEMO(UnaryExp,UnaryExp();) }
void DnParser::UnaryOperator() { DEFINE_MEMO(UnaryOperator,UnaryOperator();) }
void DnParser::PostfixExp() { DEFINE_MEMO(PostfixExp,PostfixExp();) }
void DnParser::PrimaryExp() { DEFINE_MEMO(PrimaryExp,PrimaryExp();) }
void DnParser::ArgumentExpList() { DEFINE_MEMO(ArgumentExpList,ArgumentExpList();) }
void DnParser::Const() { DEFINE_MEMO(Const,Const();) }
}
