#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

class Token {
public:
  int type;
  std::string text;
  Token() { type = -1; }
  Token(int _type,std::string _text) : type(_type), text(_text){}
  friend std::ostream& operator<<(std::ostream& os, const Token& tk);
};

#endif
