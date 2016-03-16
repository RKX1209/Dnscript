#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "Parser.hpp"
#include "DnParser.hpp"
int main() {
  std::ifstream ifs("Dnlang/sample/test01.dn");
  if(ifs.fail()) {
    std::cerr << "Failed to open script file" << std::endl;
    return -1;
  }
  std::string script((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  std::cout << script << std::endl;
  Dnlang::DnParser parser(script);
  try{
    parser.TranslationUnit();
  }catch(std::string s) {
    std::cout<<s<<std::endl;
  }
  // while(token.type != Dnlang::DnLexer::EOF_TYPE) {
  //   token = lex.nextToken();
  //   std::cout << token << std::endl;
  // }
}
