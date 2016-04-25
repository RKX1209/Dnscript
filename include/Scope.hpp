#ifndef __SCOPE_HPP__
#define __SCOPE_HPP__

namespace Dnlang {

class MethodSymbol;
class Scope {
public:
  std::string scopeName;
  Scope *parent;
  std::map<std::string, Symbol> symbols;

  Scope() { scopeName = ""; parent = 0; }
  Scope(std::string name, Scope *_parent) : scopeName(name), parent(_parent){}
  std::string getScopeName() { return scopeName; }
  virtual Scope *getEnclosingScope() { return parent; }
  void define(Symbol sym) { symbols[sym.name] = sym; }
  Symbol *resolve(std::string name);
};

class GlobalScope : public Scope {
public:
  static const int api_num = 128;
  static MethodSymbol *apis[api_num];
  GlobalScope();
  Scope *getEnclosingScope() { return 0; }
};

class LocalScope : public Scope {
public:
  LocalScope(std::string name, Scope *parent) : Scope(name, parent) {}
  Scope *getEnclosingScope() { return parent; }
};

}
#endif
