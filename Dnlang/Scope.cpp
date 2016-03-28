#include <map>
#include <string>
#include "Symbol.hpp"
#include "Scope.hpp"

namespace Dnlang {

Symbol *Scope::resolve(std::string name) {
  if(symbols.find(name) != symbols.end()) return &symbols[name];
  if(parent != 0) {
    return parent->resolve(name);
  }
  return 0;
}

}
