#include <string>
#include <algorithm>
#include "Lexer.hpp"
#include "Token.hpp"
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
  "ID", "INTCONST", "CHARCONST", "FLOATCONST", "STRING", "SEMICORON", "COMMA",
  "LBRACKA", "RBRACKA", "LBRACK", "RBRACK", "LBRACKB", "RBRACKB",
  "ASSIGN", "MULASSIGN", "DIVASSIGN", "MODASSIGN", "PLUSASSIGN", "MINUSASSIGN",
  "ANDASSIGN", "ORASSIGN", "XORASSIGN",
  "OROR", "OR", "ANDAND", "AND", "XOR", "NOT", "PLUS", "MINUS", "MUL", "DIV", "MOD",
  "LESSLESS", "ABOVEABOVE", "PLUSPLUS", "MINUSMINUS", "EQUALEQUAL", "NOTEQUAL",
  "LESS", "LESSEQUAL", "ABOVE", "ABOVEEQUAL",
  "IF", "ELSE", "SWITCH", "WHILE", "FOR", "CONTINUE", "BREAK", "RETURN",
  "LET", "FUNCTION",
};

const std::string DnLexer::reserved[] = {
  "break", "continue", "for", "function", "if", "let", "return", "switch", "while",
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
        default:
          break;
    }
  }
}

void DnLexer::skipSpaces() {
    while(c == ' ' || c == '\t' || c == '\n' || c == '\r') consume();
}

bool DnLexer::isLetter() {
  return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

bool DnLexer::isDecimal() {
  return '0' <= c && c <= '9';
}
/* TODO: Is it reserved word? It's judged by using binary search. */
bool DnLexer::isReserved(std::string str) {
  int rsize = sizeof(reserved) / sizeof(std::string *);
  for(int i = 0; i < rsize; i++){
    if(reserved[i] == str) return true;
  }
  return false;
  /*std::string *pos = std::lower_bound(reserved, reserved + rsize, str);
  return (pos != rsize && *pos == str); */
}

}
