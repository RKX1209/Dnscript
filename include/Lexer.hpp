#ifndef __LEXER_HPP__
#define __LEXER_HPP__


class Lexer {
public:
  static const char LEX_EOF;
  std::string input;
  int p;
  char c;
  Lexer();
  Lexer(std::string _input);
  void consume();
  void match(char x);
  virtual std::string get_token_name(int x) {}
  virtual Token nextToken() {}
};

#endif
