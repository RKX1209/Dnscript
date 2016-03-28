#ifndef __AST_HPP__
#define __AST_HPP__

namespace Dnlang {

class AST {
public:
  Token token;
  std::vector<AST*> children;
  AST *parent;
  Scope *scope;
  Symbol *symbol;
  Type evalType;
  AST() : scope(0), symbol(0), parent(0){ this->token.type = -1; }
  AST(Token _token) : scope(0), symbol(0), parent(0){ this->token = _token; }
  AST(int type) : scope(0), symbol(0), parent(0){ this->token = Token(type); }
  AST(const AST &ast) {
    token = ast.token; parent = ast.parent;
    evalType = ast.evalType;
    scope = ast.scope; symbol = ast.symbol;
  }
  int getNodeType() { return token.type; }
  std::string getNodeText() { return token.text; }
  AST *addChild(AST *_parent, AST *t) {
    t->parent = _parent;
    children.push_back(t);
    return children[children.size() - 1];
  }
  bool isNil() { return token.type == -1; }
  std::string toString();
  std::string toStringTree(int depth);
};

}
#endif
