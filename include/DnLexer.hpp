#ifndef __DNLEXER_HPP__
#define __DNLEXER_HPP__

namespace Dnlang {
class DnLexer : public Lexer {
public:
  enum {
    EOF_TYPE = 1,
    /* Reserved words */
    BREAK, CONTINUE, ELSE, FOR, FUNCTION, IF, LET, RETURN, SWITCH,
    WHILE, ID,
    /* Constants */
    INTCONST, CHARCONST, FLOATCONST, STRING,

    SEMICORON, COMMA, LBRACKA, RBRACKA, LBRACK, RBRACK, LBRACKB, RBRACKB,
    /* Assignment */
    MULASSIGN, DIVASSIGN, MODASSIGN, PLUSASSIGN, MINUSASSIGN,
    ANDASSIGN, ORASSIGN, XORASSIGN, EQUAL,
    /* Expressions */
    OROR, OR, ANDAND, AND, XOR, NOT, PLUS, MINUS, MUL, DIV, MOD,
    PLUSPLUS, MINUSMINUS,
    /* Relation */
    LESSLESS, ABOVEABOVE, EQUALEQUAL, NOTEQUAL,
    LESS, LESSEQUAL, ABOVE, ABOVEEQUAL,

    /* virtual token for AST */
    FUNC_DEF, DECL, AREF, CALL, PARAM, ASSIGN,
    INITIALIZER, EXP, BLOCK, UNARYEXP, PRIMARYEXP,
  };
  static const std::string token_names[];
  static const std::string reserved[];
  DnLexer(std::string input) : Lexer(input) { }
  virtual std::string get_token_name(int x) { return token_names[x]; }
  virtual Token nextToken();
  int isReserved(std::string str);
  Token IntConst();
  Token CharConst();
  Token FloatConst();
  Token String();
  Token Id();  
};

}
#endif
