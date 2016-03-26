#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Token.hpp"
#include "AST.hpp"

std::string AST::toString() {
  return !isNil()?token.toString():"nil";
}

std::string AST::toStringTree(int depth) {
  if(children.size() == 0) return this->toString();
  std::string buf;
  if(!isNil()) {
    if(token.text == "") {
      std::string align(depth - 1, '\t');
      buf += "\n";
      buf += align;
    }
    buf += "(";
    buf += this->toString();
    buf += " ";
  }
  //std::cout << buf << std::endl;
  for(int i = 0; i < children.size(); i++) {
    AST t = (AST)children[i];
    if(i > 0) buf += " ";
    buf += t.toStringTree(depth + 1);
  }
  if(!isNil()) buf += ")";
  return buf;
}
