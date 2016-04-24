#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

namespace Dnlang {

class Type {
public:
  enum {
    INVALID, INT, CHAR, FLOAT, STRING, VOID,
  };
  static const std::string type_names[];
  static const int type_sizes[];
  int type;
  Type(){ type = INVALID; }
  Type(int _type) : type(_type) {}
  std::string toString() { return type_names[type]; }
  int getSize() { return type_sizes[type]; }
};

class Symbol {
public:
  std::string name;
  Type type;
  Symbol() {}
  Symbol(std::string _name, Type _type) : name(_name), type(_type) {}
  std::string toString();
};

}

#endif
