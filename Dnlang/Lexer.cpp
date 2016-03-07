#include <string>
#include <boost/format.hpp>
#include "Lexer.hpp"

const char Lexer::LEX_EOF = (char)-1;
Lexer::Lexer(std::string _input) : input(_input) {
  p = 0;
  c = input[p];
}

void Lexer::consume() {
  p++;
  if(p >= input.size()) c = EOF;
  else c = input[p];
}

void Lexer::match(char x) {
  if(c == x) consume();
  else {
    std::string error = (boost::format("expecting %c; found %c") % x % c).str();
    throw error;
  }
}
