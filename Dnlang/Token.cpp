#include <iostream>
#include <sstream>
#include <string>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"

std::ostream& operator<<(std::ostream& os, const Token& tk) {
  os << Dnlang::DnLexer::token_names[tk.type] << "," << tk.text;
}
std::string Token::toString() {
  std::stringstream ss;
  if(this->text == "")
    ss << Dnlang::DnLexer::token_names[this->type];
  else
    ss << this->text;
  return ss.str();
}
