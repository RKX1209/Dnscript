#include <iostream>
#include <map>
#include "Event.hpp"

Event* Event::mInstance = 0;

Event* Event::instance(){
    return mInstance;
}

void Event::create(){
  try{
    if(mInstance) throw "[*ERROR*] Event::create() cannnot create instance twice";
    mInstance = new Event();
  }catch(char *error){
    std::cerr << error << "\n";
    abort();
  }
}

void Event::destroy(){
  delete mInstance;
}
