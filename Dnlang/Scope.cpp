#include <map>
#include <string>
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Symbols.hpp"

#define DEF_API(name,type) new MethodSymbol(name,type,0)
namespace Dnlang {

Symbol *Scope::resolve(std::string name) {
  if(symbols.find(name) != symbols.end()) return &symbols[name];
  if(parent != 0) {
    return parent->resolve(name);
  }
  return 0;
}
GlobalScope::GlobalScope() : Scope("global", 0) {
  for(int i = 0; apis[i] != 0; i++) {
    /* Pre define apis. */
    this->define(*apis[i]);
  }
}

MethodSymbol *GlobalScope::apis[GlobalScope::api_num] = {
  DEF_API("LoadGraphic",Type::VOID), DEF_API("DeleteGraphic",Type::VOID),
  DEF_API("SetTexture", Type::VOID), DEF_API("SetGraphicRect", Type::VOID),
  DEF_API("SetGraphicPos", Type::VOID),  
  DEF_API("SetGraphicAngle",Type::VOID), DEF_API("DrawGraphic", Type::VOID),
  DEF_API("SetCollisionA",Type::VOID), DEF_API("SetInitialBombCount", Type::VOID),
  DEF_API("SetGrazeCircle", Type::VOID), DEF_API("SetIntersectionCircle", Type::VOID),
  DEF_API("SetSpeed", Type::VOID), DEF_API("SetLife", Type::VOID),
  DEF_API("SetX", Type::VOID), DEF_API("SetY", Type::VOID),
  DEF_API("GetPlayerX", Type::FLOAT), DEF_API("GetPlayerY", Type::FLOAT),
  DEF_API("GetSpeedX", Type::FLOAT), DEF_API("GetSpeedY", Type::FLOAT),
  DEF_API("GetX", Type::FLOAT), DEF_API("GetY", Type::FLOAT),
  DEF_API("GetW", Type::FLOAT), DEF_API("GetH", Type::FLOAT),
  DEF_API("GetCenterX", Type::FLOAT), DEF_API("GetCenterY", Type::FLOAT),
  DEF_API("CreatePlayerShot01", Type::VOID), DEF_API("CreateShot01", Type::VOID),
  DEF_API("CutIn", Type::VOID), DEF_API("SetMovePosition02", Type::VOID),
  DEF_API("GetKeyState", Type::INT), DEF_API("GetCurrentScriptDirectory", Type::STRING),0
};

}
