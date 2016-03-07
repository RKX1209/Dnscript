#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__

class Token {
public:
  int type;
  std::string text;
  Token(int _type,std::string _text) : type(_type), text(_text){}
};

#endif
