#include <string>
#include <boost/format.hpp>
#include "Symbol.hpp"
namespace Dnlang {

const std::string Type::type_names[] = {
  "<n/a>","int","char","float","string","void",
};
std::string Symbol::toString() {
  std::string stype = type.toString();
  return (boost::format("%s<%s>") % name % stype).str();
}

}
