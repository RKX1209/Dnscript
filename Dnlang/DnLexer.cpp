#include <string>
#include <algorithm>
#include <iostream>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"


/* TODO: These macros are bit ugly. Refactor it to better one. */
#define STR(str) #str
#define ASSIGNCON(__o,__o2,__token) \
consume(); \
switch(c) { \
  case '=': consume(); return Token(__token##ASSIGN, STR(__o##=)); \
  case __o2: consume(); return Token(__token##__token, STR(__o##__o)); \
  default: return Token(__token, #__o); \
}
#define ASSIGN(__o,__token) \
consume(); \
switch(c) { \
  case '=': consume(); return Token(__token##ASSIGN, STR(__o##=)); \
  default: return Token(__token, #__o); \
}

#define EQUALCON(__o,__o2,__token) \
consume(); \
switch(c) { \
  case '=': consume(); return Token(__token##EQUAL, STR(__o##=)); \
  case __o2: consume(); return Token(__token##__token, STR(__o##__o)); \
  default: return Token(__token, #__o); \
}
#define EQUALL(__o,__token) \
consume(); \
switch(c) { \
  case '=': consume(); return Token(__token##EQUAL, STR(__o##=)); \
  default: return Token(__token, #__o); \
}

namespace Dnlang {

const std::string DnLexer::token_names[] = {
  "n/a", "<EOF>",
  "BREAK", "CONTINUE", "ELSE", "FOR", "FUNCTION", "IF", "LET", "RETURN", "SWITCH",
  "WHILE",
  "ID", "INTCONST", "CHARCONST", "FLOATCONST", "STRING", "SEMICORON", "COMMA",
  "LBRACKA", "RBRACKA", "LBRACK", "RBRACK", "LBRACKB", "RBRACKB",
  "MULASSIGN", "DIVASSIGN", "MODASSIGN", "PLUSASSIGN", "MINUSASSIGN",
  "ANDASSIGN", "ORASSIGN", "XORASSIGN","EQUAL",
  "OROR", "OR", "ANDAND", "AND", "XOR", "NOT", "PLUS", "MINUS", "MUL", "DIV", "MOD",
  "PLUSPLUS", "MINUSMINUS",
  "LESSLESS", "ABOVEABOVE", "EQUALEQUAL", "NOTEQUAL",
  "LESS", "LESSEQUAL", "ABOVE", "ABOVEEQUAL",
  /* virtual token for AST */
  "FUNC_DEF", "DECL", "AREF", "CALL", "PARAM", "ASSIGN",
  "INITIALIZER", "EXP", "BLOCK", "UNARYEXP", "PRIMARYEXP",
};

const std::string DnLexer::reserved[] = {
  "break", "continue", "else", "for", "function", "if", "let", "return", "switch", "while",
};

Token DnLexer::nextToken() {
    while(c != LEX_EOF) {
      switch(c) {
        case ' ': case '\t': case '\n': case '\r': skipSpaces(); continue;
        case ';': consume(); return Token(SEMICORON, ";");
        case ',': consume(); return Token(COMMA, ",");
        case '(': consume(); return Token(LBRACKA, "(");
        case ')': consume(); return Token(RBRACKA, ")");
        case '[': consume(); return Token(LBRACK, "[");
        case ']': consume(); return Token(RBRACK, "]");
        case '{': consume(); return Token(LBRACKB, "{");
        case '}': consume(); return Token(RBRACKB, "}");
        case '=':
          EQUALL(=, EQUAL)
        case '+':
          ASSIGNCON(+, '+', PLUS)
        case '-':
          ASSIGNCON(-, '-', MINUS)
        case '/':
          ASSIGN(/, DIV)
        case '*':
          ASSIGN(*, MUL)
        case '%':
          ASSIGN(%, MOD)
        case '&':
          ASSIGNCON(&, '&', AND)
        case '|':
          ASSIGNCON(|, '|', OR)
        case '^':
          ASSIGN(^, XOR)
        case '!':
          EQUALL(!, NOT)
        case '<':
          EQUALCON(<, '<', LESS)
        case '>':
          EQUALCON(>, '>', ABOVE)
        case '\"':
          /* "hoge" (string) */
          if(isString()) return String();
        case '\'':
          /* 'X' (char) */
          if(isChar()) return CharConst();
        default:
          if(isDecimal()) {
            /* {D} */
            if(isFloat()) return FloatConst();
            else return IntConst();
          }else if(isId()) {
            /* {L} It could be id or reserved word */
            return Id();
          }
          break;
    }
  }
  return Token(EOF_TYPE, "<EOF>");
}

void DnLexer::skipSpaces() {
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r') consume();
}

bool DnLexer::isLetter() {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

bool DnLexer::isDecimal() {
  return '0' <= c && c <= '9';
}

bool DnLexer::isChar() {
  return c == '\'' && (p + 2) < input.size() && input[p + 2] == '\'';
}

bool DnLexer::isSym() {
  return c == '_' || c == '-' || c == '@' || c == '\\' || c == '.';
}

bool DnLexer::isFloat() {
  return input.find(".") != std::string::npos;
}

bool DnLexer::isString() {
  return c == '\"' && input.find("\"", p + 1) != std::string::npos;
}

bool DnLexer::isId() {
  return isLetter() || isSym();
}

/* TODO: Is it reserved word? It's judged by using binary search. */
int DnLexer::isReserved(std::string str) {
  int rsize = sizeof(reserved) / sizeof(std::string *);
  for(int i = 0; i < rsize; i++){
    if(reserved[i] == str) return i;
  }
  return -1;
  /*std::string *pos = std::lower_bound(reserved, reserved + rsize, str);
  return (pos != rsize && *pos == str); */
}

Token DnLexer::IntConst() {
  std::string buf;
  do { buf.append(1, c); consume(); } while(isDecimal());
  return Token(INTCONST, buf);
}

Token DnLexer::CharConst() {
  std::string buf;
  consume();
  buf.append(1,c);
  consume();
  return Token(CHARCONST, buf);
}

Token DnLexer::FloatConst() {
  std::string buf;
  do { buf.append(1, c); consume(); } while(isDecimal() || c == '.');
  return Token(FLOATCONST, buf);
}

Token DnLexer::String() {
  std::string buf;
  consume();
  do { buf.append(1, c); consume(); } while(isDecimal() || isLetter() || isSym());
  consume();
  return Token(STRING, buf);
}

Token DnLexer::Id() {
  std::string buf;
  int resv = -1;
  do { buf.append(1, c); consume(); } while(isDecimal() || isLetter() || isSym());
  if((resv = isReserved(buf)) != -1){
    /* Is this id reserved word? */
    return Token(2 + resv, buf);
  }
  return Token(ID, buf);
}

}
