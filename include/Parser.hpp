#ifndef __PARSER_HPP__
#define __PARSER_HPP__

class Parser {
public:
  Lexer input;
  /* record points of tokens to role back */
  std::vector<int> markers;
  std::vector<Token> lookahead;
  std::map<std::string, std::map<int, int> > memos;
  static const int FAILED;;
  int p;
  Parser() : p(0) {}
  Token LT(int i);
  int LA(int i);
  void match(int x);
  void sync(int i);
  void fill(int n);
  void consume();
  int mark();
  void release();
  void seek(int index);
  bool isSpeculating();
  bool alreadyParsedRule(std::map<int,int> memo);
  void memorize(std::map<int,int> memo, int startTokenIndex, bool failed);
  int index();
};

#endif