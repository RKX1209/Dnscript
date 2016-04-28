#ifndef __DNINLEXER_HPP__
#define __DNINLEXER_HPP__

namespace Dnlang {
class DnInLexer : public Lexer {
public:
  enum {
    EOF_TYPE = 1,
    /* reserved words */
    IF, GOTO, CALL, PARAM, RET,
    /* assign words */
    EQUAL,
    /* binary operations */
    MUL, PLUS, MINUS, AND, DIV, MOD, NOT,
    /* relations */
    LESS, LESSEQUAL, ABOVE, ABOVEEQUAL, EQUALEQUAL,
    /* const*/
    INTCONST, FLOATCONST, STRING,
    ADDR,
  };
  static const std::string token_names[];
  static const std::string reserved[];
  DnInLexer(std::string input) : Lexer(input) { }
  virtual std::string get_token_name(int x) { return token_names[x]; }
  virtual Token nextToken();
  int isReserved(std::string str);
  Token IntConst();
  Token FloatConst();
  Token String();
  Token Addr();
};

}
#endif
