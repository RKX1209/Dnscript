#ifndef __PARSER_HPP__
#define __PARSER_HPP__

class Parser {
public:
  Lexer *input;
  /* record points of tokens to role back */
  std::vector<int> markers;
  std::vector<Token> lookahead;
  std::map<std::string, std::map<int, int> > memos;
  static const int FAILED;
  int p;
  bool finished;
  Parser(std::string script) : p(0), finished(false) {}
  ~Parser() {
    Clear();
  }
  void Clear() {
    p = 0;
    finished = false;
    lookahead.clear();
    markers.clear();
    memos.clear();
  }
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
  bool alreadyParsedRule(std::string rule);
  void memorize(std::string rule, int startTokenIndex, bool failed);
  int index();
  bool isFin() { return finished; }
};

#endif
