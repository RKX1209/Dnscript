#include <fstream>
#include <iostream>
#include <string>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
int main() {
  std::ifstream ifs("Dnlang/sample/test01.dn");
  if(ifs.fail()) {
    std::cerr << "Failed to open script file" << std::endl;
    return -1;
  }
  std::string script((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  std::cout << script << std::endl;
  Dnlang::DnLexer lex(script);
  Token token;
  while(token.type != Dnlang::DnLexer::EOF_TYPE) {
    token = lex.nextToken();
    std::cout << token << std::endl;
  }
}
