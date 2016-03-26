#ifndef __AST_HPP__
#define __AST_HPP__

class AST {
public:
  Token token;
  std::vector<AST> children;
  AST *parent;
  AST() { this->token.type = -1; }
  AST(Token token) { this->token = token; }
  AST(int type) { Token _token(type); this->token = _token; }
  int getNodeType() { return token.type; }
  AST *addChild(AST t) {
    t.parent = this;
    children.push_back(t);
    return &children[children.size() - 1];
  }
  bool isNil() { return token.type == -1; }
  std::string toString();
  std::string toStringTree(int depth);
};

#endif
