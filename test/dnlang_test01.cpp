#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "Parser.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Symbols.hpp"
#include "Register.hpp"
#include "AST.hpp"
#include "DnParser.hpp"
#include "ASTVisitor.hpp"

int main() {
  //std::ifstream ifs("Dnlang/sample/test01.dn");
  std::ifstream ifs("Dnlang/sample/enemy.dn");
  if(ifs.fail()) {
    std::cerr << "Failed to open script file" << std::endl;
    return -1;
  }
  std::string script((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  std::cout << script << std::endl;
  // Dnlang::DnLexer lex(script);
  // Token token;
  // while(token.type != Dnlang::DnLexer::EOF_TYPE) {
  //   token = lex.nextToken();
  //   std::cout << token << std::endl;
  // }
  Dnlang::DnParser parser(script);
  Dnlang::AST *ast;
  Dnlang::Semantics *seman;
  Dnlang::CodeGen *cgen;
  try{
    parser.TranslationUnit();
    ast = parser.get_AST();
    std::cout << ast->toStringTree(0) << std::endl;
    seman = new Dnlang::Semantics(ast);
    seman->downup(ast);
    std::cout<<"Semantics: complete\n";
    cgen = new Dnlang::CodeGen(ast);
    cgen->downup(ast);
    std::cout<<ast->code<<std::endl;
    delete seman;
    delete cgen;
  }catch(std::string s) {
    std::cout<<s<<std::endl;
    return 0;
  }
}
