#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <cstdlib>
#include <typeinfo>
#include "Object.hpp"
#include "Api.hpp"
#include "Token.hpp"
#include "Lexer.hpp"
#include "DnInLexer.hpp"
#include "Symbol.hpp"
#include "Scope.hpp"
#include "Parser.hpp"
#include "DnInParser.hpp"

namespace Dnlang {

void DnInParser::Addr3() {
  std::cout<<"Next:"<<LT(1)<<std::endl;
  if (LA(1) == DnInLexer::ADDR) {
    Assign();
  } else if (LA(1) == DnInLexer::GOTO) {
    Jump();
  } else if (LA(1) == DnInLexer::IF) {
    CondJump();
  } else if (LA(1) == DnInLexer::PARAM) {
    Param();
  } else if (LA(1) == DnInLexer::CALL) {
    CallFunc();
  } else if (LA(1) == DnInLexer::RET) {
    Ret();
  } else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}

void DnInParser::Assign() {
  std::cout<<"[ENTER] Assign\n";
  Token left = LT(1);
  consume();
  if ( LA(1) == DnInLexer::EQUAL ) {
    consume();
    int op_res = (int)RVal();
    setVal(left, op_res); //define register value
    pc++;
  } else {
    std::stringstream error;
    error << "Error: " << LT(1) << LT(2);
    throw error.str();
  }
}

double DnInParser::RVal() {
  return Operation();
}

double DnInParser::Operation() {
  std::cout<<"[ENTER] Op\n";
  int op_res = 0;
  Token addr = LT(1);
  double res = getVal(addr);
  consume();
  if (!isFin()) {
    if ( LA(1) == DnInLexer::PLUS ) {
      consume();
      res += getVal(LT(1));
      consume();
    } else if ( LA(1) == DnInLexer::MINUS ) {
      consume();
      res -= getVal(LT(1));
      consume();
    } else if ( LA(1) == DnInLexer::MUL ) {
      consume();
      res *= getVal(LT(1));
      consume();
    } else if ( LA(1) == DnInLexer::DIV ) {
      consume();
      res /= getVal(LT(1));
      consume();
    } else if ( LA(1) == DnInLexer::MOD ) {
      consume();
      int mod_res = (int)res % (int)getVal(LT(1));
      res = mod_res;
      consume();
    }
  }
  return res;
}

void DnInParser::Jump() {
  consume();
  Token label = LT(1);
  int line = getLabel(label.text);
  pc = line; //jump to line
  consume();
}

void DnInParser::CondJump() {
  consume(); // "if"
  if (Cond()) {
    Token label = LT(2);
    int line = getLabel(label.text);
    pc = line;
  }
  consume(); // "goto"
  consume(); //"label"
  pc++;
}

bool DnInParser::Cond() {
  Token left = LT(1);
  double lval = getVal(left);
  consume();
  if (LA(1) == DnInLexer::LESS) {
    consume();
    Token right = LT(1);
    double rval = getVal(right);
    consume();
    return lval < rval;
  } else if (LA(1) == DnInLexer::LESSEQUAL) {
    consume();
    Token right = LT(1);
    double rval = getVal(right);
    consume();
    return lval <= rval;
  } else if (LA(1) == DnInLexer::ABOVE) {
    consume();
    Token right = LT(1);
    double rval = getVal(right);
    consume();
    return lval > rval;
  } else if (LA(1) == DnInLexer::ABOVEEQUAL) {
    consume();
    Token right = LT(1);
    double rval = getVal(right);
    consume();
    return lval >= rval;
  } else if (LA(1) == DnInLexer::EQUALEQUAL) {
    consume();
    Token right = LT(1);
    double rval = getVal(right);
    consume();
    return lval == rval;
  }
  return false;
}

void DnInParser::Param() {
  consume();
  Token addr = LT(1);
  double val = getVal(addr);
  stack.push_back(val);
  consume();
  pc++;
}

void DnInParser::Ret() {
  consume();
  if (LA(1) == DnInLexer::ADDR) {
    double val = getVal(LT(1));
    setRetVal(val);
    consume();
  }
  pc++;
}

void DnInParser::CallFunc() {
  consume();
  Token label = LT(1);
  int argc = std::atoi(LT(2).text.c_str());
  int fn_line = getLabel(label.text);
  std::vector<double>argv;
  consume();
  consume();
  for(int i = 0; i < argc; i++) {
    argv.push_back(stack[stack.size() - 1]);
    stack.pop_back();
  }
  if(fn_line == -1) {
    std::string api_name = label.text;
    if (api_name == "LoadGraphic") { api->_LoadGraphic(target, argv[0]); }
    else if (api_name == "DeleteGraphic"){}
    else if (api_name == "SetTexture") { api->_SetTexture(target, argv[0]); }
    else if (api_name == "SetGraphicRect") { api->_SetGraphicRect(target, argv[0],argv[1],argv[2],argv[3]); }
    //else if (api_name == "SetGraphicPos") { api->_SetGraphicPos(target, argv[0],argv[1],argv[2],argv[3]); }
    else if (api_name == "SetGraphicAngle") { api->_SetGraphicAngle(target, argv[0]); }
    else if (api_name == "DrawGraphic") { api->_DrawGraphic(target, argv[0], argv[1]); }
    else if (api_name == "SetCollisionA"){}
    else if (api_name == "SetInitialBombCount"){}
    else if (api_name == "SetGrazeCircle"){}
    else if (api_name == "SetIntersectionCircle"){}
    else if (api_name == "SetSpeed") { api->_SetSpeed(target, argv[0]); }
    else if (api_name == "SetLife") { api->_SetLife(target, argv[0]); }
    else if (api_name == "SetX") { api->_SetX(target, argv[0]); }
    else if (api_name == "SetY") { api->_SetY(target, argv[0]); }
    else if (api_name == "GetPlayerX") { setRetVal(api->_GetPlayerX(target)); }
    else if (api_name == "GetPlayerY") { setRetVal(api->_GetPlayerX(target)); }
    else if (api_name == "GetSpeedX") { setRetVal(api->_GetSpeedX(target)); }
    else if (api_name == "GetSpeedY") { setRetVal(api->_GetSpeedY(target)); }
    else if (api_name == "GetX") { setRetVal(api->_GetX(target)); }
    else if (api_name == "GetY") { setRetVal(api->_GetY(target)); }
    else if (api_name == "GetW") { setRetVal(api->_GetW(target)); }
    else if (api_name == "GetH") { setRetVal(api->_GetH(target)); }
    else if (api_name == "GetCenterX") { setRetVal(api->_GetCenterX()); }
    else if (api_name == "GetCenterY") { setRetVal(api->_GetCenterY()); }
    else if (api_name == "CreatePlayerShot01") { api->_CreatePlayerShot01(target, argv[0],argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]); }
    else if (api_name == "CreateShot01") { api->_CreateShot01(target,argv[0],argv[1],argv[2],argv[3],argv[4],argv[5]); }
    else if (api_name == "CutIn") { api->_CutIn(target,argv[0],argv[1],argv[2],argv[3],argv[4],argv[5]); }
    else if (api_name == "SetMovePosition02") { api->_SetMovePosition02(target,argv[0],argv[1],argv[2]); }
    else if (api_name == "GetKeyState"){
      int key = (int)api->_GetKeyState(argv[0]);
      setRetVal(key);
    }
    else if (api_name == "GetCurrentScriptDirectory") {
      std::string *namep = new std::string(api->_GetCurrentScriptDirectory());
      setRetVal(reinterpret_cast<unsigned long>(namep->c_str()));
    }
    pc++;
  } else {
    /* TODO: Implment calling normal function */
    pc = fn_line;
  }
}

void DnInParser::execline(std::string oneline, int _pc) {
  /* Execute only one line of code */
  lexer = new DnInLexer(oneline);
  input = lexer;
  // std::cout<<"<lexer>\n";
  // while (lexer->c != -1) std::cout<<"word:"<<lexer->nextToken();
  // std::cout<<"</lexer>\n";
  pc = _pc;
  this->Addr3();
  delete lexer;
  Clear();
}

int DnInParser::defString(std::string str) {
  std::string *strp = new std::string(str);
  int addr = reinterpret_cast<unsigned long>(strp->c_str());
  syms[str] = addr;
  revmap[addr] = str;
  return addr;
};

double DnInParser::getVal(Token token) {
  if (token.type == DnInLexer::INTCONST || token.type == DnInLexer::FLOATCONST) {
    return std::stod(token.text.c_str());
  } else if(token.type == DnInLexer::STRING) {
    if(syms.find(token.text) == syms.end()) {
      /* alloc new string data and return its address */
      return static_cast<double>(defString(token.text));
    }
  }
  return syms[token.text];
}

void DnInParser::setVal(Token token, double val) {
  syms[token.text] = val;
}

void DnInParser::setRetVal(double val) {
  syms["r0"] = val;
}

void DnInParser::TestLex() {

}
}
