#include <string>
#include <algorithm>
#include <iostream>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnInLexer.hpp"

namespace Dnlang {

const std::string DnInLexer::token_names[] = {
  "n/a", "<EOF>", "EQUAL",
  "IF", "GOTO", "CALL", "PARAM", "EQUAL", "RET",
  "MUL", "PLUS", "MINUS", "AND", "DIV", "MOD", "NOT",
  "LESS", "LESSEQUAL", "ABOVE", "ABOVEEQUAL", "EQUALEQUAL",
  "INTCONST", "FLOATCONST", "STRING",
  "ADDR",
};

const std::string DnInLexer::reserved[] = {
  "if", "goto", "call", "param", "ret",
};

Token DnInLexer::nextToken() {
  while(c != LEX_EOF) {
    switch(c) {
      case ' ': case '\t': case '\n': case '\r': skipSpaces(); continue;
      case '=':
        consume();
        if (c == '=') { // ==
          consume();
          return Token(EQUALEQUAL, "==");
        } else {
          return Token(EQUAL, "=");
        }
      case '+':
          consume();
          return Token(PLUS, "+");
      case '-':
          consume();
          return Token(MINUS, "-");
      case '/':
          consume();
          return Token(DIV, "/");
      case '*':
          consume();
          return Token(MUL, "*");
      case '%':
          consume();
          return Token(MOD, "%");
      case '&':
          consume();
          return Token(AND, "&");
      case '!':
          consume();
          return Token(NOT, "!");
      case '<':
        consume();
        if (c == '=') { // <=
          consume();
          return Token(LESSEQUAL, "<=");
        } else {
          return Token(LESS, "<");
        }
      case '>':
        consume();
        if (c == '=') { // >=
          consume();
          return Token(ABOVEEQUAL, ">=");
        } else {
          return Token(ABOVE, ">");
        }
      case '\"':
        /* "hoge" (string) */
        if(isString()) return String();
      default:
        if(isDecimal()) {
          /* {D} */
          if(isFloat()) return FloatConst();
          else return IntConst();
        }else {
          /* {L} It could be id or reserved word */
          return Addr();
        }
        break;
      }
  }
  return Token(EOF_TYPE, "<EOF>");
}
/* TODO: Is it reserved word? It's judged by using binary search. */
int DnInLexer::isReserved(std::string str) {
  int rsize = sizeof(reserved) / sizeof(std::string *);
  for(int i = 0; i < rsize; i++){
    if(reserved[i] == str) return i;
  }
  return -1;
  /*std::string *pos = std::lower_bound(reserved, reserved + rsize, str);
  return (pos != rsize && *pos == str); */
}

Token DnInLexer::IntConst() {
  std::string buf;
  do { buf.append(1, c); consume(); } while(isDecimal());
  return Token(INTCONST, buf);
}

Token DnInLexer::FloatConst() {
  std::string buf;
  do { buf.append(1, c); consume(); } while(isDecimal() || c == '.');
  return Token(FLOATCONST, buf);
}

Token DnInLexer::String() {
  std::string buf;
  consume();  
  do { buf.append(1, c); consume(); } while(isDecimal() || isLetter() || isSym());
  consume();
  return Token(STRING, buf);
}

Token DnInLexer::Addr() {
  std::string buf;
  int resv = -1;
  do { buf.append(1, c); consume(); } while(isDecimal() || isLetter() || isSym() || c == '[' || c == ']');
  if((resv = isReserved(buf)) != -1){
    /* Is this id reserved word? */
    return Token(2 + resv, buf);
  }
  return Token(ADDR, buf);
}

}
