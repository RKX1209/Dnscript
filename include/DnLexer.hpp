#ifndef __DNLEXER_HPP__
#define __DNLEXER_HPP__

namespace Dnlang {
class DnLexer : public Lexer {
public:
  enum {
    EOF_TYPE = 1,
    BREAK, CONTINUE, FOR, FUNCTION, IF, LET, RETURN, SWITCH,
    WHILE,
    ID, INTCONST, CHARCONST, FLOATCONST, STRING, SEMICORON, COMMA,
    LBRACKA, RBRACKA, LBRACK, RBRACK, LBRACKB, RBRACKB,
    ASSIGN, MULASSIGN, DIVASSIGN, MODASSIGN, PLUSASSIGN, MINUSASSIGN,
    ANDASSIGN, ORASSIGN, XORASSIGN,
    OROR, OR, ANDAND, AND, XOR, NOT, PLUS, MINUS, MUL, DIV, MOD,
    LESSLESS, ABOVEABOVE, PLUSPLUS, MINUSMINUS, EQUAL, EQUALEQUAL, NOTEQUAL,
    LESS, LESSEQUAL, ABOVE, ABOVEEQUAL,
  };
  static const std::string token_names[];
  static const std::string reserved[];
  DnLexer(std::string input) : Lexer(input) { }
  std::string get_token_name(int x) { return token_names[x]; }
  Token nextToken();
  bool isDecimal();
  bool isLetter();
  bool isChar();
  bool isFloat();
  bool isString();
  bool isId();
  int isReserved(std::string str);
  void skipSpaces();
  Token IntConst();
  Token CharConst();
  Token FloatConst();
  Token String();
  Token Id();
};

}
#endif
