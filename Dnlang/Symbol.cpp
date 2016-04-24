#include <string>
#include <boost/format.hpp>
#include "Symbol.hpp"
namespace Dnlang {

const std::string Type::type_names[] = {
  "<n/a>","int","char","float","string","void",
};
const int Type::type_sizes[] = {
  0, 4, 1, 4, 4, 4,
};
std::string Symbol::toString() {
  std::string stype = type.toString();
  return (boost::format("%s<%s>") % name % stype).str();
}

}
