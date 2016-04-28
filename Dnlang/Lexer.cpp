#include <string>
#include <boost/format.hpp>
#include "Token.hpp"
#include "Lexer.hpp"

const char Lexer::LEX_EOF = (char)-1;
Lexer::Lexer() {
  p = 0;
}
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
void Lexer::skipSpaces() {
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r') consume();
}

bool Lexer::isLetter() {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool Lexer::isDecimal() {
  return '0' <= c && c <= '9';
}

bool Lexer::isChar() {
  return c == '\'' && (p + 2) < input.size() && input[p + 2] == '\'';
}

bool Lexer::isSym() {
  return c == '_' || c == '@' || c == '\\' || c == '.' || c == '/';
}

bool Lexer::isFloat() {
  return input.find(".") != std::string::npos;
}

bool Lexer::isString() {
  return c == '\"' && input.find("\"", p + 1) != std::string::npos;
}

bool Lexer::isId() {
  return isLetter() || isSym();
}
