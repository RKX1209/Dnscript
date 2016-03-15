#ifndef __DNPARSER_HPP__
#define __DNPARSER_HPP__

namespace Dnlang {
class DnParser : public Parser {
public:
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
};
}
#endif
