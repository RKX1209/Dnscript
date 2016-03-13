#include <iostream>
#include <string>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"

std::ostream& operator<<(std::ostream& os, const Token& tk) {
  os << Dnlang::DnLexer::token_names[tk.type] << "," << tk.text;
}
