#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <list>
#include "Object.hpp"
#include "Api.hpp"
#include "Interprter.hpp"

int main() {
  Object *dummy;
  Dnlang::Interprter interp(dummy, "Dnlang/sample/enemy.dn");
  interp.compile();
}
