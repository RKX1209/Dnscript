#ifndef __DNPARSER_HPP__
#define __DNPARSER_HPP__

namespace Dnlang {
class DnParser : public Parser {
public:
  DnLexer *dnlexer;
  AST *ast_root;
  DnParser(std::string script) : Parser(script) {
    dnlexer = new DnLexer(script);
    ast_root = new AST();
    input = dnlexer;
  }
  ~DnParser() {
    delete ast_root;
    delete dnlexer;
  }
  AST *get_AST() { return ast_root; }
  void TranslationUnit();
  void ExternalDecl();
  void FunctionDef();
  void Decl();
  void DeclList();
  void DeclSpecs();
  void FuncSpec();
  void TypeSpec();
  void InitDeclList();
  void InitDecl();
  void Declarator();
  void IdList();
  void Initializer();
  void Stat();
  void ExpStat();
  void CompoundStat();
  void StatList();
  void SelectionStat();
  void IterationStat();
  void JumpStat();
  void Exp();
  void AssignExp();
  void AssignOperator();
  void ConditionalExp();
  void LogicalOrExp();
  void LogicalAndExp();
  void InclusiveOrExp();
  void ExclusiveOrExp();
  void AndExp();
  void EqualityExp();
  void RelationalExp();
  void ShiftExp();
  void AdditiveExp();
  void MultExp();
  void UnaryExp();
  void UnaryOperator();
  void PostfixExp();
  void PrimaryExp();
  void ArgumentExpList();
  void Const();

  void _TranslationUnit();
  void _ExternalDecl();
  void _FunctionDef();
  void _Decl();
  void _DeclList();
  void _DeclSpecs();
  void _FuncSpec();
  void _TypeSpec();
  void _InitDeclList();
  void _InitDecl();
  void _Declarator();
  void _IdList();
  void _Initializer();
  void _Stat();
  void _ExpStat();
  void _CompoundStat();
  void _StatList();
  void _SelectionStat();
  void _IterationStat();
  void _JumpStat();
  void _Exp();
  void _AssignExp();
  void _AssignOperator();
  void _ConditionalExp();
  void _LogicalOrExp();
  void _LogicalAndExp();
  void _InclusiveOrExp();
  void _ExclusiveOrExp();
  void _AndExp();
  void _EqualityExp();
  void _RelationalExp();
  void _ShiftExp();
  void _AdditiveExp();
  void _MultExp();
  void _UnaryExp();
  void _UnaryOperator();
  void _PostfixExp();
  void _PrimaryExp();
  void _ArgumentExpList();
  void _Const();
};
}
#endif
