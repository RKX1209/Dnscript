#ifndef __INTERPRETER_HPP__
#define __INTERPRETER_HPP__

#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "DnInLexer.hpp"
#include "Parser.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Symbols.hpp"
#include "Register.hpp"
#include "AST.hpp"
#include "DnParser.hpp"
#include "ASTVisitor.hpp"
#include "DnInParser.hpp"

namespace Dnlang {

class Interprter {
public:
  Object *target;
  std::string path;
  std::string script;
  std::vector<std::string> code;

  Dnlang::DnParser *parser;
  Dnlang::AST *ast;
  Dnlang::Semantics *seman;
  Dnlang::CodeGen *cgen;

  Dnlang::DnInParser *inparser;

  Interprter(Object *obj, std::string _path);
  ~Interprter();
  void load_script();
  void compile();
  void preprocess();
  void execLabel(std::string lab);
  void Initialize();
  void MainLoop();
  void DrawLoop();
};

}

#endif
