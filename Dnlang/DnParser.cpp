#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
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
  std::cout<< "<" << startTokenIndex << "," << #x << ">" << std::endl; \
  try { _##fp } \
  catch(std::string &s) { \
    failed = true; \
    if(isSpeculating()) memorize(#x, startTokenIndex, failed); \
    std::cout<< "</" << startTokenIndex << "," << #x << ">\n\n"; \
    throw s; \
  } \
  if(isSpeculating()) memorize(#x, startTokenIndex, failed); \
  std::cout<< "</" << startTokenIndex << "," << #x << ">\n\n"; \

namespace Dnlang {
  /* type inference
     XXX bit ugly. Is there any better solution? */
void DnParser::_TranslationUnit() {
  if(SPECULATE( ExternalDecl(); TranslationUnit(); )()) {
    ExternalDecl(); TranslationUnit();
  }
  else if(SPECULATE( ExternalDecl(); )()) {
    ExternalDecl();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_FunctionDef() {
  if(SPECULATE( DeclSpecs(); Declarator(); CompoundStat(); )()) {
    DeclSpecs(); Declarator(); CompoundStat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_Decl() {
  if(SPECULATE( DeclSpecs(); InitDecl(); match(DnLexer::SEMICORON); )()) {
    DeclSpecs(); InitDecl(); match(DnLexer::SEMICORON);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_FuncSpec() {
  if(SPECULATE( match(DnLexer::FUNCTION); )()) {
    std::cout<<"[ACTUAL] FUNCTION"<<std::endl;
    match(DnLexer::FUNCTION);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_TypeSpec() {
  if(SPECULATE( match(DnLexer::LET); )()) {
    match(DnLexer::LET);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_Declarator() {
  if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::ID); match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA);
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::ID); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA);
  }
  else if(SPECULATE( match(DnLexer::ID); )()) {
      match(DnLexer::ID);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_IdList() {
  if(SPECULATE( match(DnLexer::ID); match(DnLexer::COMMA); IdList(); )()) {
    match(DnLexer::ID); match(DnLexer::COMMA); IdList();
  }
  else if(SPECULATE( match(DnLexer::ID); )()) {
    match(DnLexer::ID);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_Initializer() {
  if(SPECULATE( AssignExp(); )()) {
    AssignExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_CompoundStat() {
  if(SPECULATE( match(DnLexer::LBRACKB); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_SelectionStat() {
  if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); match(DnLexer::ELSE); Stat(); )()) {
    match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
    match(DnLexer::ELSE); Stat();
  }
  else if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_IterationStat() {
  if(SPECULATE( match(DnLexer::WHILE); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    match(DnLexer::WHILE); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
  }
  else if(SPECULATE( match(DnLexer::FOR); match(DnLexer::LBRACKA); Exp(); match(DnLexer::SEMICORON); Exp(); match(DnLexer::SEMICORON); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    match(DnLexer::FOR); match(DnLexer::LBRACKA);
    Exp(); match(DnLexer::SEMICORON);
    Exp(); match(DnLexer::SEMICORON);
    Exp();
    match(DnLexer::RBRACKA); Stat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }

}
void DnParser::_JumpStat() {
  if(SPECULATE( match(DnLexer::CONTINUE); match(DnLexer::SEMICORON); )()) {
    match(DnLexer::CONTINUE); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::BREAK); match(DnLexer::SEMICORON); )()) {
    match(DnLexer::BREAK); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::RETURN); Exp(); match(DnLexer::SEMICORON); )()) {
    match(DnLexer::RETURN); Exp(); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( match(DnLexer::RETURN); match(DnLexer::SEMICORON); )()) {
    match(DnLexer::RETURN); match(DnLexer::SEMICORON);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_AssignExp() {
  if(SPECULATE( ConditionalExp(); )()) {
    ConditionalExp();
  }
  else if(SPECULATE( UnaryExp(); AssignOperator(); AssignExp(); )()) {
    UnaryExp(); AssignOperator(); AssignExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_AssignOperator() {
  if(SPECULATE( match(DnLexer::EQUAL); )()) {
    match(DnLexer::EQUAL);
  }
  else if(SPECULATE( match(DnLexer::MULASSIGN); )()) {
    match(DnLexer::MULASSIGN);
  }
  else if(SPECULATE( match(DnLexer::DIVASSIGN); )()) {
    match(DnLexer::DIVASSIGN);
  }
  else if(SPECULATE( match(DnLexer::MODASSIGN); )()) {
    match(DnLexer::MODASSIGN);
  }
  else if(SPECULATE( match(DnLexer::PLUSASSIGN); )()) {
    match(DnLexer::PLUSASSIGN);
  }
  else if(SPECULATE( match(DnLexer::MINUSASSIGN); )()) {
    match(DnLexer::MINUSASSIGN);
  }
  else if(SPECULATE( match(DnLexer::ANDASSIGN); )()) {
    match(DnLexer::ANDASSIGN);
  }
  else if(SPECULATE( match(DnLexer::ORASSIGN); )()) {
    match(DnLexer::ORASSIGN);
  }
  else if(SPECULATE( match(DnLexer::XORASSIGN); )()) {
    match(DnLexer::XORASSIGN);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_ConditionalExp() {
  if(SPECULATE( LogicalOrExp(); )()) {
    LogicalOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_LogicalOrExp() {
  if(SPECULATE( LogicalAndExp(); )()) {
    LogicalAndExp();
  }
  else if(SPECULATE( LogicalAndExp(); match(DnLexer::OROR); LogicalOrExp(); )()) {
    LogicalAndExp(); match(DnLexer::OROR); LogicalOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_LogicalAndExp() {
  if(SPECULATE( InclusiveOrExp(); match(DnLexer::ANDAND); LogicalAndExp(); )()) {
    InclusiveOrExp(); match(DnLexer::ANDAND); LogicalAndExp();
  }
  else if(SPECULATE( InclusiveOrExp(); )()) {
    InclusiveOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_InclusiveOrExp() {
  if(SPECULATE( ExclusiveOrExp(); match(DnLexer::OR); InclusiveOrExp(); )()) {
    ExclusiveOrExp(); match(DnLexer::OR); InclusiveOrExp();
  }
  else if(SPECULATE( ExclusiveOrExp(); )()) {
    ExclusiveOrExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_ExclusiveOrExp() {
  if(SPECULATE( AndExp(); match(DnLexer::XOR); ExclusiveOrExp(); )()) {
    AndExp(); match(DnLexer::XOR); ExclusiveOrExp();
  }
  else if(SPECULATE( AndExp(); )()) {
    AndExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }

}
void DnParser::_AndExp() {
  if(SPECULATE( EqualityExp(); match(DnLexer::AND); AndExp(); )()) {
    EqualityExp(); match(DnLexer::AND); AndExp();
  }
  else if(SPECULATE( EqualityExp(); )()) {
    EqualityExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_EqualityExp() {
  if(SPECULATE( RelationalExp(); match(DnLexer::EQUALEQUAL); EqualityExp(); )()) {
    RelationalExp(); match(DnLexer::EQUALEQUAL); EqualityExp();
  }
  else if(SPECULATE( RelationalExp(); match(DnLexer::NOTEQUAL); EqualityExp(); )()) {
    RelationalExp(); match(DnLexer::NOTEQUAL); EqualityExp();
  }
  else if(SPECULATE( RelationalExp(); )()) {
    RelationalExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_RelationalExp() {
  if(SPECULATE( ShiftExp(); match(DnLexer::LESS); RelationalExp(); )()) {
    ShiftExp(); match(DnLexer::LESS); RelationalExp();
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVE); RelationalExp(); )()) {
    ShiftExp(); match(DnLexer::ABOVE); RelationalExp();
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp(); )()) {
    ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp();
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp(); )()) {
    ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp();
  }
  else if(SPECULATE( ShiftExp(); )()) {
    ShiftExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_ShiftExp() {
  if(SPECULATE( AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp(); )()) {
    AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp();
  }
  else if(SPECULATE( AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp(); )()) {
    AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp();
  }
  else if(SPECULATE( AdditiveExp(); )()) {
    AdditiveExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_AdditiveExp() {
  if(SPECULATE( MultExp(); match(DnLexer::PLUS); AdditiveExp(); )()) {
    MultExp(); match(DnLexer::PLUS); AdditiveExp();
  }
  else if(SPECULATE( MultExp(); match(DnLexer::MINUS); AdditiveExp(); )()) {
    MultExp(); match(DnLexer::MINUS); AdditiveExp();
  }
  else if(SPECULATE( MultExp(); )()) {
    MultExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_MultExp() {
  if(SPECULATE( UnaryExp(); match(DnLexer::MUL); MultExp(); )()) {
    UnaryExp(); match(DnLexer::MUL); MultExp();
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::DIV); MultExp(); )()) {
    UnaryExp(); match(DnLexer::DIV); MultExp();
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::MOD); MultExp(); )()) {
    UnaryExp(); match(DnLexer::MOD); MultExp();
  }
  else if(SPECULATE( UnaryExp(); )()) {
    std::cout<<"[ACUTAL] UnaryExp"<<std::endl;
    UnaryExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_UnaryExp() {
  if(SPECULATE( PostfixExp(); )()) {
    PostfixExp();
  }
  else if(SPECULATE( match(DnLexer::PLUSPLUS); UnaryExp(); )()) {
    match(DnLexer::PLUSPLUS); UnaryExp();
  }
  else if(SPECULATE( match(DnLexer::MINUSMINUS); UnaryExp(); )()) {
    match(DnLexer::MINUSMINUS); UnaryExp();
  }
  else if(SPECULATE( UnaryOperator(); UnaryExp(); )()) {
    UnaryOperator(); UnaryExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_UnaryOperator() {
  if(SPECULATE( match(DnLexer::PLUS); )()) {
    match(DnLexer::PLUS);
  }
  else if(SPECULATE( match(DnLexer::MINUS); )()) {
    match(DnLexer::MINUS);
  }
  else if(SPECULATE( match(DnLexer::NOT); )()) {
    match(DnLexer::NOT);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_PostfixExp() {
  if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK); )()) {
    PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA); )()) {
    PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); )()) {
    PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::PLUSPLUS); )()) {
    PrimaryExp(); match(DnLexer::PLUSPLUS);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::MINUSMINUS); )()) {
    PrimaryExp(); match(DnLexer::MINUSMINUS);
  }
  else if(SPECULATE( PrimaryExp(); )()) {
    std::cout<<"[ACTUAL] PrimaryExp"<<std::endl;
    PrimaryExp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }

}
void DnParser::_PrimaryExp() {
  if(SPECULATE( match(DnLexer::ID); )()) {
    match(DnLexer::ID);
  }
  else if(SPECULATE( Const(); )()) {
    Const();
  }
  else if(SPECULATE( match(DnLexer::STRING); )()) {
    std::cout<<"[ACTUAL] STRING"<<std::endl;
    match(DnLexer::STRING);
  }
  else if(SPECULATE( match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::_Const() {
  if(SPECULATE( match(DnLexer::INTCONST); )()) {
    match(DnLexer::INTCONST);
  }
  else if(SPECULATE( match(DnLexer::CHARCONST); )()) {
    match(DnLexer::CHARCONST);
  }
  else if(SPECULATE( match(DnLexer::FLOATCONST); )()) {
    match(DnLexer::FLOATCONST);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
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
