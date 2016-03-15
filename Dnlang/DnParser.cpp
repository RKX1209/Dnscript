#include <vector>
#include <string>
#include <sstream>
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
  catch (char *str) { success = false; } \
  release(); \
  return success; \
}

namespace Dnlang {
  /* type inference
     TODO bit ugly. Is there any better solution? */
void DnParser::TranslationUnit() {
  if(SPECULATE( ExternalDecl(); match(DnLexer::EOF_TYPE); )()) {
    ExternalDecl(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ExternalDecl(); TranslationUnit(); match(DnLexer::EOF_TYPE); )()) {
    ExternalDecl(); TranslationUnit(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ExternalDecl() {
  if(SPECULATE( FunctionDef(); match(DnLexer::EOF_TYPE); )()) {
    FunctionDef(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( Decl(); match(DnLexer::EOF_TYPE); )()) {
    Decl(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::FunctionDef() {
  if(SPECULATE( DeclSpecs(); Declarator(); CompoundStat(); match(DnLexer::EOF_TYPE); )()) {
    DeclSpecs(); Declarator(); CompoundStat(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::Decl() {
  if(SPECULATE( DeclSpecs(); InitDeclList(); match(DnLexer::SEMICORON); )()) {
    DeclSpecs(); InitDeclList(); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( DeclSpecs(); match(DnLexer::EOF_TYPE); )()) {
    DeclSpecs(); InitDeclList(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::DeclList() {
  if(SPECULATE( Decl(); match(DnLexer::EOF_TYPE); )()) {
    Decl(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( Decl(); DeclList(); match(DnLexer::EOF_TYPE); )()) {
    Decl(); DeclList(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::DeclSpecs() {
  if(SPECULATE( FuncSpec(); match(DnLexer::EOF_TYPE); )()) {
    FuncSpec(); match(DnLexer::SEMICORON);
  }
  else if(SPECULATE( TypeSpec(); match(DnLexer::EOF_TYPE); )()) {
    TypeSpec(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( TypeSpec(); DeclSpecs(); match(DnLexer::EOF_TYPE); )()) {
    TypeSpec(); DeclSpecs(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::FuncSpec() {
  if(SPECULATE( match(DnLexer::FUNCTION); )()) {
    match(DnLexer::FUNCTION);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::TypeSpec() {
  if(SPECULATE( match(DnLexer::LET); )()) {
    match(DnLexer::LET);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::InitDeclList() {
  if(SPECULATE( InitDecl(); match(DnLexer::EOF_TYPE); )()) {
    InitDecl(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( InitDecl(); match(DnLexer::COMMA); InitDeclList(); )()) {
    InitDecl(); match(DnLexer::COMMA); InitDeclList();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::InitDecl() {
  if(SPECULATE( Declarator(); match(DnLexer::EOF_TYPE); )()) {
    Declarator(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( Declarator(); match(DnLexer::EQUAL); Initializer(); )()) {
    Declarator(); match(DnLexer::EQUAL); Initializer();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::Declarator() {
  if(SPECULATE( match(DnLexer::ID); )()) {
    match(DnLexer::ID);
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::ID); match(DnLexer::LBRACKA); IdList(); match(DnLexer::RBRACKA);
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); )()) {
    match(DnLexer::ID); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::IdList() {
  if(SPECULATE( match(DnLexer::ID); )()) {
    match(DnLexer::ID);
  }
  else if(SPECULATE( match(DnLexer::ID); match(DnLexer::COMMA); IdList(); )()) {
    match(DnLexer::ID); match(DnLexer::COMMA); IdList();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::Initializer() {
  if(SPECULATE( AssignExp(); match(DnLexer::EOF_TYPE); )()) {
    AssignExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::Stat() {
  if(SPECULATE( ExpStat(); match(DnLexer::EOF_TYPE); )()) {
    ExpStat(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( CompoundStat(); match(DnLexer::EOF_TYPE); )()) {
    CompoundStat(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( SelectionStat(); match(DnLexer::EOF_TYPE); )()) {
    SelectionStat(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( IterationStat(); match(DnLexer::EOF_TYPE); )()) {
    IterationStat(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( JumpStat(); match(DnLexer::EOF_TYPE); )()) {
    JumpStat(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ExpStat() {
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
void DnParser::CompoundStat() {
  if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); DeclList(); StatList(); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); StatList(); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); DeclList(); match(DnLexer::RBRACKB);
  }
  else if(SPECULATE( match(DnLexer::LBRACKB); match(DnLexer::RBRACKB); )()) {
    match(DnLexer::LBRACKB); match(DnLexer::RBRACKB);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::StatList() {
  if(SPECULATE( Stat(); match(DnLexer::EOF_TYPE); )()) {
    Stat(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( Stat(); StatList(); match(DnLexer::EOF_TYPE); )()) {
    Stat(); StatList(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::SelectionStat() {
  if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); )()) {
    match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
  }
  else if(SPECULATE( match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat(); match(DnLexer::ELSE); Stat(); )()) {
    match(DnLexer::IF); match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); Stat();
    match(DnLexer::ELSE); Stat();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::IterationStat() {
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
void DnParser::JumpStat() {
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
void DnParser::Exp() {
  if(SPECULATE( AssignExp(); match(DnLexer::EOF_TYPE); )()) {
    AssignExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( AssignExp(); match(DnLexer::COMMA); Exp(); )()) {
    AssignExp(); match(DnLexer::COMMA); Exp();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::AssignExp() {
  if(SPECULATE( ConditionalExp(); match(DnLexer::EOF_TYPE); )()) {
    ConditionalExp(); match(DnLexer::EOF_TYPE);
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
void DnParser::AssignOperator() {
  if(SPECULATE( match(DnLexer::EQUAL); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::EQUAL); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::MULASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::MULASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::DIVASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::DIVASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::MODASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::MODASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::PLUSASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::PLUSASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::MINUSASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::MINUSASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::ANDASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::ANDASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::ORASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::ORASSIGN); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::XORASSIGN); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::XORASSIGN); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ConditionalExp() {
  if(SPECULATE( LogicalOrExp(); match(DnLexer::EOF_TYPE); )()) {
    LogicalOrExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::LogicalOrExp() {
  if(SPECULATE( LogicalAndExp(); match(DnLexer::EOF_TYPE); )()) {
    LogicalAndExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( LogicalOrExp(); match(DnLexer::OROR); LogicalOrExp(); match(DnLexer::EOF_TYPE); )()) {
    LogicalOrExp(); match(DnLexer::OROR); LogicalOrExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::LogicalAndExp() {
  if(SPECULATE( InclusiveOrExp(); match(DnLexer::EOF_TYPE); )()) {
    InclusiveOrExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( InclusiveOrExp(); match(DnLexer::ANDAND); InclusiveOrExp(); match(DnLexer::EOF_TYPE); )()) {
    InclusiveOrExp(); match(DnLexer::ANDAND); InclusiveOrExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::InclusiveOrExp() {
  if(SPECULATE( ExclusiveOrExp(); match(DnLexer::EOF_TYPE); )()) {
    ExclusiveOrExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ExclusiveOrExp(); match(DnLexer::OR); ExclusiveOrExp(); match(DnLexer::EOF_TYPE); )()) {
    ExclusiveOrExp(); match(DnLexer::OR); ExclusiveOrExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ExclusiveOrExp() {
  if(SPECULATE( AndExp(); match(DnLexer::EOF_TYPE); )()) {
    AndExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( AndExp(); match(DnLexer::XOR); ExclusiveOrExp(); match(DnLexer::EOF_TYPE); )()) {
    AndExp(); match(DnLexer::XOR); ExclusiveOrExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }

}
void DnParser::AndExp() {
  if(SPECULATE( EqualityExp(); match(DnLexer::EOF_TYPE); )()) {
    EqualityExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( EqualityExp(); match(DnLexer::AND); AndExp(); match(DnLexer::EOF_TYPE); )()) {
    EqualityExp(); match(DnLexer::AND); AndExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::EqualityExp() {
  if(SPECULATE( RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( RelationalExp(); match(DnLexer::EQUALEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    RelationalExp(); match(DnLexer::EQUALEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( RelationalExp(); match(DnLexer::NOTEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    RelationalExp(); match(DnLexer::NOTEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::RelationalExp() {
  if(SPECULATE( ShiftExp(); match(DnLexer::EOF_TYPE); )()) {
    ShiftExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::LESS); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    ShiftExp(); match(DnLexer::LESS); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVE); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    ShiftExp(); match(DnLexer::ABOVE); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    ShiftExp(); match(DnLexer::LESSEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE); )()) {
    ShiftExp(); match(DnLexer::ABOVEEQUAL); RelationalExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ShiftExp() {
  if(SPECULATE( AdditiveExp(); match(DnLexer::EOF_TYPE); )()) {
    AdditiveExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp(); match(DnLexer::EOF_TYPE); )()) {
    AdditiveExp(); match(DnLexer::LESSLESS); ShiftExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp(); match(DnLexer::EOF_TYPE); )()) {
    AdditiveExp(); match(DnLexer::ABOVEABOVE); ShiftExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::AdditiveExp() {
  if(SPECULATE( MultExp(); match(DnLexer::EOF_TYPE); )()) {
    MultExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( MultExp(); match(DnLexer::PLUS); ShiftExp(); match(DnLexer::EOF_TYPE); )()) {
    MultExp(); match(DnLexer::PLUS); AdditiveExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( MultExp(); match(DnLexer::MINUS); ShiftExp(); match(DnLexer::EOF_TYPE); )()) {
    MultExp(); match(DnLexer::MINUS); AdditiveExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::MultExp() {
  if(SPECULATE( UnaryExp(); match(DnLexer::EOF_TYPE); )()) {
    UnaryExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::MUL); MultExp(); match(DnLexer::EOF_TYPE); )()) {
    UnaryExp(); match(DnLexer::MUL); MultExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::DIV); MultExp(); match(DnLexer::EOF_TYPE); )()) {
    UnaryExp(); match(DnLexer::DIV); MultExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( UnaryExp(); match(DnLexer::MOD); MultExp(); match(DnLexer::EOF_TYPE); )()) {
    UnaryExp(); match(DnLexer::MOD); MultExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::UnaryExp() {
  if(SPECULATE( PostfixExp(); match(DnLexer::EOF_TYPE); )()) {
    PostfixExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::PLUSPLUS); UnaryExp(); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::PLUSPLUS); UnaryExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::MINUSMINUS); UnaryExp(); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::MINUSMINUS); UnaryExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( UnaryOperator(); UnaryExp(); match(DnLexer::EOF_TYPE); )()) {
    UnaryOperator(); UnaryExp(); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::UnaryOperator() {
  if(SPECULATE( match(DnLexer::PLUS); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::PLUS); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::MINUS); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::MINUS); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::NOT); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::NOT); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::PostfixExp() {
  if(SPECULATE( PrimaryExp(); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::LBRACK); Exp(); match(DnLexer::RBRACK); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::LBRACKA); ArgumentExpList(); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::LBRACKA); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::PLUSPLUS); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::PLUSPLUS); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( PrimaryExp(); match(DnLexer::MINUSMINUS); match(DnLexer::EOF_TYPE); )()) {
    PrimaryExp(); match(DnLexer::MINUSMINUS); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }

}
void DnParser::PrimaryExp() {
  if(SPECULATE( match(DnLexer::ID); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::ID); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( Const(); match(DnLexer::EOF_TYPE); )()) {
    Const(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::STRING); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::STRING); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::LBRACKA); Exp(); match(DnLexer::RBRACKA); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::ArgumentExpList() {
  if(SPECULATE( AssignExp(); match(DnLexer::EOF_TYPE); )()) {
    AssignExp(); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( AssignExp(); match(DnLexer::COMMA); ArgumentExpList(); )()) {
    AssignExp(); match(DnLexer::COMMA); ArgumentExpList();
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
void DnParser::Const() {
  if(SPECULATE( match(DnLexer::INTCONST); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::INTCONST); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::CHARCONST); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::CHARCONST); match(DnLexer::EOF_TYPE);
  }
  else if(SPECULATE( match(DnLexer::FLOATCONST); match(DnLexer::EOF_TYPE); )()) {
    match(DnLexer::FLOATCONST); match(DnLexer::EOF_TYPE);
  }
  else {
    std::stringstream error;
    error << "Error: " << LT(1);
    throw error.str();
  }
}
}
