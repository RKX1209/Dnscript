#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnLexer.hpp"
#include "Token.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Register.hpp"
#include "AST.hpp"
#include "Symbols.hpp"

namespace Dnlang {

std::string AST::toString() {
  if(symbol) return symbol->toString();
  if(scope) return scope->getScopeName();
  return !isNil()?token.toString():"nil";
}

std::string AST::toStringTree(int depth) {
  if(children.size() == 0) {
    //std::string pstr = "[" + this->parent->toString() + "]";
    return this->toString();
  }
  //if(children.size() == 0) return this->toString();
  std::string buf;
  if(!isNil()) {
    if(token.text == "") {
      std::string align(depth - 1, '\t');
      buf += "\n";
      buf += align;
    }
    buf += "(";
    //buf += "[" + this->parent->toString() + "]";
    buf += this->toString();
    buf += " ";
  }
  //std::cout << "<buf>" << buf << std::endl;
  for(int i = 0; i < children.size(); i++) {
    AST *t = children[i];
    if(i > 0) buf += " ";
    buf += t->toStringTree(depth + 1);
  }
  if(!isNil()) buf += ")";
  //std::cout << "</buf>" << buf << std::endl;
  return buf;
}

std::string AST::getRegId() {
  if(this->getNodeType() == DnLexer::AREF) {
    return this->children[0]->reg->getId() + "[ " + this->reg->getId() + " ]";
  }
  return reg->getId();
}

}
