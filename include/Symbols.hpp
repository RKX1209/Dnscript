#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

namespace Dnlang {

class VariableSymbol : public Symbol {
public:
  VariableSymbol(std::string name, Type type) : Symbol(name, type) {}
};

class MethodSymbol : public Symbol, public Scope {
public:
  MethodSymbol(std::string name, Scope *_parent) : Symbol(name, Type::INVALID) , Scope(name, _parent){
  }
  MethodSymbol(std::string name, Type type, Scope *_parent) : Symbol(name, type) , Scope(name, _parent){
  }
};

}

#endif
