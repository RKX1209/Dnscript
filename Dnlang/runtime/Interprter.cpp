#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include "Object.hpp"
#include "Api.hpp"
#include "Interprter.hpp"

namespace Dnlang {

Interprter::Interprter(Object *obj, std::string _path) : path(_path) {
  this->load_script();
  parser = new DnParser(script);
  inparser = new DnInParser(target);
}

Interprter::~Interprter() {
  delete parser;
  delete seman;
  delete cgen;
  delete inparser;
}

void Interprter::load_script() {
  std::ifstream ifs(path);
  if(ifs.fail()) {
    std::cerr << "Failed to open script file" << std::endl;
    abort();
  }
  std::string script((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());
  this->script = script;
  std::cout << this->script << std::endl;
}

void Interprter::compile() {
  try{
    std::cout<<"compiling..."<<std::endl;
    parser->TranslationUnit();
    ast = parser->get_AST();
    std::cout << ast->toStringTree(0) << std::endl;
    seman = new Dnlang::Semantics(ast);
    seman->downup(ast);
    std::cout<<"Semantics: complete\n";
    cgen = new Dnlang::CodeGen(ast);
    cgen->downup(ast);
    //std::cout<<ast->code<<std::endl;
    std::string delim("\n");
    boost::algorithm::split(this->code, ast->code, boost::is_any_of(delim));
    BOOST_FOREACH(std::string s, this->code) {
      std::cout << s << std::endl;
    }
    preprocess();
  }catch(std::string s) {
    std::cout<<s<<std::endl;
    abort();
  }
}

void Interprter::Initialize() {
  this->execLabel("@Initialize:");
}
void Interprter::MainLoop() {
  this->execLabel("@MainLoop:");
}
void Interprter::DrawLoop() {
  this->execLabel("@DrawLoop:");
}

void Interprter::execLabel(std::string lab) {
  int lab_pc = inparser->getLabel(lab);
  int pc = lab_pc + 1;
  std::string oneline = this->code[pc];
  std::cout<<pc<<std::endl;  
  while (oneline.find("ret") == std::string::npos) {
    /* XXX: User defined function can't adjsut this structure.
            I'll implment it in the near future.... */
    if (oneline == "") { pc++; continue; }
    std::cout<<"execute: "<<oneline<<std::endl;
    inparser->execline(oneline, pc); //execute one line
    pc = inparser->getPC(); // go to next instruction
    oneline = this->code[pc];
  }
}

void Interprter::preprocess() {
  int i = 0;
  BOOST_FOREACH(std::string s, this->code) {
    if (s.find(":") != std::string::npos) {
      inparser->defLabel(s, i);
    }
    i++;
  }
}

}
