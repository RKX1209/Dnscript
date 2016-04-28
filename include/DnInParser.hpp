#ifndef __DNINPARSER_HPP__
#define __DNINPARSER_HPP__

namespace Dnlang {

class DnInParser : Parser {
public:
  std::map<std::string, double> syms;
  std::map<int, std::string> revmap; // addr |-> string value
  std::map<std::string, int> labels;
  std::vector<double> stack;
  DnInLexer *lexer;
  Api *api;
  Object *target;
  int pc;
  DnInParser(Object *_target) : Parser(""), pc(0), target(_target){
    api = Api::instance();
  }
  ~DnInParser() {
  }
  void execline(std::string oneline, int _pc);
  void defLabel(std::string lab, int line) { labels[lab] = line; }
  int defString(std::string str);
  int getLabel(std::string lab) {
    if (labels.find(lab) == labels.end()) return -1;
    return labels[lab];
  }
  int getPC() { return pc; }
  void setRetVal(double val);
  double getVal(Token token);
  void setVal(Token token, double val);
  void Addr3();
  void Assign();
  double RVal();
  double Operation();
  void Jump();
  void CondJump();
  bool Cond();
  void CallFunc();
  void Param();
  void Ret();

  void TestLex();
};

}
#endif
